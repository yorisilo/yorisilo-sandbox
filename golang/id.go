package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var sc = bufio.NewScanner(os.Stdin)

type city struct {
	n    int
	pref int
	year int
	id   int
}

func main() {
	sc.Split(bufio.ScanWords)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush() // !!!!coution!!!! you must use Fprint(out, ) not Print()
	/* --- code ---*/
	n := nextInt()
	m := nextInt()

	cs := [][]int{}
	// fmt.Fprint(out, n, m)
	// for i := 0; i < nm[1]; i++ {
	// 	cs = append(cs, nextInts(2))
	// }

	fmt.Fprint("")
	// fmt.Fprint(out, cs)
	// cities := []city{}
	// for i := 0; i < len(cs); i++ {
	// 	cities = append(cities, city{i, cs[i][0], cs[i][1], 0})
	// }
	// fmt.Fprint(out, cities)
}

func next() string {
	sc.Scan()
	return sc.Text()
}

func nextInt() int {
	i, _ := strconv.Atoi(next())
	return i
}

func nextInts(n int) []int {
	ret := make([]int, n)
	for i := 0; i < n; i++ {
		ret[i] = nextInt()
	}
	return ret
}
