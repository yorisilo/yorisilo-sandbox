package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	getItem()
}

func getItem() error {
	errCh := make(chan error)
	wg := &sync.WaitGroup{}

	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			errCh <- search(i, 0)
			fmt.Printf("number of goroutine %d\n", i)
			errCh <- search(i, 0)
			errCh <- search(i, 0)
		}(i)
	}

	go func() {
		wg.Wait()
		close(errCh)
	}()

	for err := range errCh {
		fmt.Printf("err=%v\n", err)
		if err != nil {
			return err
		}
	}
	return nil
}

func search(i, times int) error {
	if i == times {
		return fmt.Errorf("search error: i=%d\n", i)
	}
	time.Sleep(5 * time.Second)
	return nil
}
