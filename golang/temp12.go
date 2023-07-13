package main

import "fmt"

func main() {

	fmt.Println(fact(1))
}

func fact(n int) int {
	sum := 1

	for i := n; i > 0; i-- {
		sum = sum * i
	}

	return sum
}

func fact(n int) int {
	if n == 0 {
		return 1
	}

	return n * fact(n-1)
}

func fact1(n, acc int) int {
	if n == 0 {
		return acc
	}

	return fact1(n-1, n*acc)
}
