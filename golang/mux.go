package main

import (
	"fmt"
	"sync"
)

type Fetcher interface {
	Fetch(url string) (body string, urls []string, err error)
}

type UrlCache struct {
	urls map[string]bool
	mux  sync.Mutex
}

func (cache *UrlCache) Add(url string) {
	cache.mux.Lock()
	cache.urls[url] = true
	cache.mux.Unlock()
}

func (cache *UrlCache) Contains(url string) bool {
	cache.mux.Lock()
	defer cache.mux.Unlock()
	return cache.urls[url]
}

type Crawler struct {
	urlCache  UrlCache
	fetcher   Fetcher
	waitGroup sync.WaitGroup
}

func (crawler *Crawler) Crawl(url string, depth int) {
	defer crawler.waitGroup.Done()

	if depth <= 0 {
		return
	}

	if crawler.urlCache.Contains(url) {
		return
	}

	_, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Errorf("crawl: error when fetching url %s %v", url, err)
		return
	}

	crawler.urlCache.Add(url)

	fmt.Printf("visited %s - %d urls found\n", url, len(urls))

	for _, u := range urls {
		crawler.waitGroup.Add(1)
		go crawler.Crawl(u, depth-1)
	}
}

func main() {
	waitGroup := sync.WaitGroup{}
	waitGroup.Add(1)

	crawler := Crawler{
		urlCache:  UrlCache{urls: make(map[string]bool)},
		fetcher:   fetcher,
		waitGroup: waitGroup,
	}

	go crawler.Crawl("http://golang.org/", 4)
	crawler.waitGroup.Wait()
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
	"http://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"http://golang.org/pkg/",
			"http://golang.org/cmd/",
		},
	},
	"http://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"http://golang.org/",
			"http://golang.org/cmd/",
			"http://golang.org/pkg/fmt/",
			"http://golang.org/pkg/os/",
		},
	},
	"http://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"http://golang.org/",
			"http://golang.org/pkg/",
		},
	},
	"http://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"http://golang.org/",
			"http://golang.org/pkg/",
		},
	},
}
