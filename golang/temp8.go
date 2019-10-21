package main

import "fmt"

// [Golangでゴルーチンにより再帰関数を並列処理 - Qiita](https://qiita.com/hiroykam/items/fdbb68ea21e5c67b8225)
// goroutine で再帰 + fib の一覧を返す

func main() {
	for c := range fibonacci(7) {
		fmt.Println(c)
	}
}

func fibonacci(n int) <-chan int {
	c := make(chan int)

	go func() {
		if n <= 2 {
			c <- 1
			return
		}

		c <- <-fibonacci(n-2) + <-fibonacci(n-1)
		close(c)
	}()
	return c
}
