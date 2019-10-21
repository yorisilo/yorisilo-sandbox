package main

import (
	"fmt"
	"time"
)

func main() {
	hoge()
	time.Sleep(5 * time.Millisecond)
}

func hoge() error {
	errCh := make(chan error)

	go func() {
		errCh <- search()
	}()

	select {
	case err := <-errCh:
		return err
	case <-time.After(time.Millisecond):
		return nil
	}
	return nil
}

func search() error {
	time.Sleep(2 * time.Millisecond)
	return fmt.Errorf("search error")
}
