package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

func main() {
	// fmt.Println(runtime.NumGoroutine())
	// err := getItem()
	// fmt.Printf("err=%v\n", err)
	fmt.Println(runtime.NumGoroutine())
	getString()
	time.Sleep(time.Second)
}

func getString() string {
	strCh := make(chan string)

	wg := &sync.WaitGroup{}
	wg.Add(1)
	go func() {
		strCh <- "chan 1"
		fmt.Printf("chan 1\n")
		strCh <- "chan 2"
		fmt.Printf("chan 2\n")
		wg.Done()
	}()

	for str := range strCh {
		fmt.Printf("range\n")
		return str
	}

	fmt.Printf("before wait\n")
	wg.Wait()
	fmt.Printf("after wait\n")
	return "hoge"
}

func getErr() error {
	errCh := make(chan error)

	wg := &sync.WaitGroup{}
	wg.Add(1)
	go func() {
		errCh <- nil
		errCh <- nil
		wg.Done()
	}()

	for err := range errCh {
		return err
	}

	wg.Wait()
	return nil
}

func getItem() error {
	errCh := make(chan error)
	// wg := &sync.WaitGroup{}

	// for i := 0; i < 5; i++ {
	// 	// wg.Add(1)
	// 	go func(i int) {
	// 		// defer wg.Done()
	// 		errCh <- search(i, 0)
	// 		fmt.Printf("number of goroutine %d\n", i)
	// 	}(i)
	// }

	// go func() {
	// 	errCh <- fmt.Errorf("errCh 1")
	// 	fmt.Println("errCh 1")
	// 	errCh <- fmt.Errorf("errCh 2")
	// 	fmt.Println("errCh 2")
	// }()

	go func() {
		time.Sleep(1000 * time.Millisecond)
		errCh <- fmt.Errorf("errCh 1")
		fmt.Println("errCh 1")
		errCh <- fmt.Errorf("errCh 2")
		fmt.Println("errCh 2")
	}()

	// go func() {
	// 	wg.Wait()
	// 	close(errCh)
	// }()

	// for err := range errCh {
	// 	fmt.Printf("range\n")
	// 	// if err != nil {
	// 	// 	return err
	// 	// }
	// 	return err
	// }
	// select {
	// case err := <-errCh:
	// 	fmt.Printf("errCh\n")
	// 	return err
	// case <-time.After(1 * time.Second):
	// 	fmt.Printf("after\n")
	// 	return nil
	// }
	time.Sleep(5 * time.Second)
	err := <-errCh
	return err
	// fmt.Printf("last\n")
	// return nil
}

func search(i, times int) error {
	if i == times {
		return fmt.Errorf("search error: i=%d", i)
	}
	time.Sleep(5 * time.Second)
	return nil
}
