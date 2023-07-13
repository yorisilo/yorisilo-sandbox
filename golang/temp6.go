package main

import "fmt"

// 積み上げ式
// [【Golang】フィボナッチ数列をメモ化や積み上げ式で解く - Qiita](https://qiita.com/ShrimpF/items/2f50a0b76d1cee29f0b3)
func fibonacci(n int) <-chan int {
	c := make(chan int)
	go func() {
		x, y := 0, 1
		for i := 0; i < n; i++ {
			c <- x
			x, y = y, x+y
		}
		close(c)
	}()
	return c
}

func main() {
	for i := range fibonacci(10) {
		fmt.Println(i)
	}
}
