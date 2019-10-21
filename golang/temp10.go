package main

import "fmt"

// [【Golang】フィボナッチ数列をメモ化や積み上げ式で解く - Qiita](https://qiita.com/ShrimpF/items/2f50a0b76d1cee29f0b3)

func main() {
	n := 10
	memo := Factorial(n)
	for i := 1; i <= n; i++ {
		fmt.Println(memo[i])
	}
}

// Factorial メモ化 ver
func Factorial(n int) map[int]int {
	memo := make(map[int]int)
	factorial(n, memo)
	return memo
}

func factorial(n int, memo map[int]int) int {
	if n == 0 {
		return 1
	}

	if _, ok := memo[n]; !ok {
		memo[n] = n * factorial(n-1, memo)
	}
	return memo[n]
}
