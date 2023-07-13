package main

import "fmt"

func main() {
	fmt.Println(fibonacci(3))
}

// 1,1,2,3,5,8,13,...
func fibonacci(n int) int {
	// x, y := 0, 1
	if n <= 2 {
		return 1
	}
	return fibonacci(n-2) + fibonacci(n-1)
}
