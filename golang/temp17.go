package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	hoge()
}

func hoge() error {
	wg := &sync.WaitGroup{}
	errCh := make(chan error)

	wg.Add(1)
	go func() {
		defer wg.Done()
		errCh <- search()
	}()

	select {
	case err := <-errCh:
		return err
	case <-time.After(time.Millisecond):
		return nil
	}
	wg.Wait()
	return nil
}

func search() error {
	time.Sleep(2 * time.Millisecond)
	return fmt.Errorf("search error")
}
