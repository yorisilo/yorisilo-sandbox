package main

import (
	"fmt"
	"sync"
)

// 訪れた url を chan で制御したい

// 主語はチャンネルを扱う側。 (主語がチャンネルになると送信受信が逆になるので注意)
// 送信： ch <- hoge チャンネルへの送信のことを送信と呼ぶ 型は chan<- t
// 受信： hoge :~ <- ch チャンネルからの受信のことを受信と呼ぶ <-chan t

// [Goのcontextによるキャンセルやタイムアウト - oinume journal](https://journal.lampetty.net/entry/cancel-and-timeout-with-context-in-go)

// [Webクローラー-GoのWebクローラー-スタックオーバーフロー](https://stackoverflow.com/questions/29491795/webcrawler-in-go)

// https://gist.github.com/zyxar/2317744#file-exercise-tour-go-L272 not use mutex
// [A Tour of Go Exerciese: Web Crawler](http://tour.golang.org/#70)をやってみました。channelとMutexの両方を混在できるのはちょっと便利かも。予め決めたワーカー数で、キューに入れたURLを順番に処理します。 Mutex使わずにやるなら、workerからchannelでurlを送ってメイン側でマップを更新して、取得済みかをworkerに別のchannelで返すという方法が考えられますが、メイン宛のchannelと、各worker宛のchannelを持つ必要があります。それよりはMutexで排他制御してマップにアクセスするほうが簡単な気がします。](https://gist.github.com/hnakamur/5262927)

type fetched map[string]bool

// Fetcher is
type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

func Crawl(url string, depth int, fetcher Fetcher, wg *sync.WaitGroup) {
	wg.Add(1)
	mu := &sync.Mutex{}
	fetched := make(chan fetched)
	defer func() {
		wg.Done()
		close(fetched)
	}()
	crawl(url, depth, fetcher, wg, fetched, mu)
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func crawl(url string, depth int, fetcher Fetcher, wg *sync.WaitGroup, fmpch chan fetched, mu *sync.Mutex) {
	// TODO: Fetch URLs in parallel.
	// TODO: Don't fetch the same URL twice.
	// This implementation doesn't do either:
	defer wg.Done()
	if depth <= 0 {
		return
	}

	// 受信
	for fmp := range fmpch {
		if fmp[url] {
			return
		}
	}

	// 送信

	mu.Lock()
	fetched[url] = true
	mu.Unlock()
	body, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)
	for _, u := range urls {
		wg.Add(1)
		go crawl(u, depth-1, fetcher, wg, fetched, mu)
	}
}

func main() {
	wg := sync.WaitGroup{}
	wg.Add(1)
	Crawl("https://golang.org/", 4, fetcher, &wg)
	wg.Wait()
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}
