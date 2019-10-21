package main

import (
	"log"
	"sync"
	"testing"
)

func main() {

}

func BenchmarkContextSwitch(b *testing.B) {
	var wg sync.WaitGroup
	begin := make(chan struct{})
	c := make(chan struct{})

	var token struct{}

	sender := func() {
		defer wg.Done()
		<-begin
		for i := 0; i < b.N; i++ {
			c <- token
		}
	}

	receiver := func() {
		defer wg.Done()
		<-begin
		for i := 0; i < b.N; i++ {
			<-c
		}
	}

	wg.Add(2)
	go sender()
	go receiver()
	b.StartTimer()
	close(begin)
	wg.Wait()
}

// <-chan hoge 受信専用チャンネル
// chan<- hoge 送信専用チャンネル
func getDataChannel() <-chan string {
	c := make(chan string)
	go func() {
		for i := 0; i < 100; i++ {
			value, _ := doSomething(i)
			log.Println("got", value)
			c <- value
		}
		close(c)
	}()
	return c
}
