package main

import (
	"fmt"
	"sync"
)

// https://stackoverflow.com/questions/13217547/trouble-with-go-tour-crawler-exercise
// [tour.golang exercise solutions](https://gist.github.com/zyxar/2317744#gistcomment-2318158)

type fetched struct {
	mp map[string]bool
	mu sync.Mutex
}

func (fe *fetched) Set(url string) {
	fe.mu.Lock()
	fe.mp[url] = true
	fe.mu.Unlock()
}

func (fe *fetched) Get(url string) bool {
	fe.mu.Lock()
	defer fe.mu.Unlock()
	return fe.mp[url]
}

// Fetcher is
type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

func Crawl(url string, depth int, fetcher Fetcher, wg *sync.WaitGroup) {
	wg.Add(1)
	fetched := &fetched{
		mp: make(map[string]bool),
		mu: sync.Mutex{},
	}
	crawl(url, depth, fetcher, wg, fetched)
	wg.Done()
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func crawl(url string, depth int, fetcher Fetcher, wg *sync.WaitGroup, fetched *fetched) {
	// TODO: Fetch URLs in parallel.
	// TODO: Don't fetch the same URL twice.
	// This implementation doesn't do either:
	defer wg.Done()
	if depth <= 0 {
		return
	}

	if fetched.Get(url) {
		return
	}

	fetched.Set(url)

	body, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("found: %s %q\n", url, body)
	for _, u := range urls {
		wg.Add(1)
		go crawl(u, depth-1, fetcher, wg, fetched)
	}
	return
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
	// time.Sleep(2 * time.Second)
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
