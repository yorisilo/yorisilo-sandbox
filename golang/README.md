2019-08-17 23:46:05

## デバッガー

``` go
# 特に引数の指定がなければ、カレントディレクトリ配下のmainパッケージをデバッグ用のオプションを付けてコンパイルして起動してくれる。
dlv debug

# main パッケージの main関数に break point を設定
(dlv) break main.main

# break point まで実行する
(dlv) continue

# 1行ずつ進める
(dlv) next

# 変数nの値の表示
(dlv) print n

# ローカル変数一覧を表示
(dlv) locals

# 変数の値の上書き
(dlv) set n = 0
(dlv) print n
0

# 現在位置のソースコードの表示
(dlv) ls

# 関数の中に step in
(dlv) step

# スタックトレース(バックトレース)の表示
(dlv) stack or bt

# スタックトレース上の指定のフレームでデバッグコマンドを実行
(dlv) frame 1 ls
(dlv) frame 1 locals

# 関数を抜ける
(dlv) stepout

# デバッガを終了する
(dlv) exit
(dlv) q
```


* [Golangのデバッガdelveの使い方 - Qiita](https://qiita.com/minamijoyo/items/4da68467c1c5d94c8cd7)

## channel の close について
* [Goでchannelがcloseしてるかどうか知りたい というアンチパターン - beatsync.net](https://beatsync.net/main/log20150325.html)

### 送信する値がなくなったら、Channelsを閉じることができる。
* 受信側で閉じないこと。送信側で閉じること
* 閉じることは必須ではない。

## channel について
* [Concurrency Patterns In Go - YouTube](https://www.youtube.com/watch?v=YEKjSzIwAdA)

* [Go言語：Channesの制限 - sugilogのブログ](http://sugilog.hatenablog.com/entry/2015/01/25/013802)

* [pipeline and cancellation並行性パターンの勉強 - すぎゃーんメモ](https://memo.sugyan.com/entry/20140717/1405606334) <- あとで done チャンネルじゃなくて context を渡すパターンでやってみる

* [Concurrency Patterns In Go - YouTube](https://www.youtube.com/watch?v=YEKjSzIwAdA)

* [Goのchannelの送受信用の型について - Qiita](https://qiita.com/yuki2006/items/3f90e53ce74c6cff1608)
* [Golangでゴルーチンにより再帰関数を並列処理 - Qiita](https://qiita.com/hiroykam/items/fdbb68ea21e5c67b8225)

* [ゴルーチン内のすべての再帰関数を停止する with context - コードログ](https://codeday.me/jp/qa/20190624/1090187.html)
* [Go の並行処理 - Block Rockin’ Codes](http://jxck.hatenablog.com/entry/20130414/1365960707)
* [goroutine を安全に止める方法 - Qiita](https://qiita.com/castaneai/items/7815f3563b256ae9b18d)

## go 言語について
* [Big Sky :: Goプログラマであるかを見分ける10の質問](https://mattn.kaoriya.net/software/lang/go/20110308033821.htm)

* [Pythonによるフィボナッチ数列の色々な求め方(一般項、反復法、再帰法) - Qiita](https://qiita.com/dovedove/items/3456c4f317a5c680f437)
* [Goに入門する - A Tour of Go | kaznishi I/O](https://blog.kaznishi.com/post/180503_go_study/)

* [再帰呼び出しと関数テーブル — プログラミング言語 Go | text.Baldanders.info](https://text.baldanders.info/golang/recursive-call-and-function-table/)
* [goroutine と並行処理の怖い話 · ww24.jp](https://ww24.jp/2018/03/goroutine/)


## data race (データ競合) と race condition (競合状態)
* [データ競合(data race)と競合状態(race condition)を混同しない - Qiita](https://qiita.com/yohhoy/items/00c6911aa045ef5729c6)
２つを混同しないこと

> データ競合(data race)は、マルチスレッド・プログラム実装上の問題である。
> 競合状態(race condition)は、並行処理システム設計上の問題である。

### data race
> 「データ競合(data race)」が何であるかは、それぞれのプログラミング言語仕様にて定義される。競合状態(race condition)と比べると、低レイヤでプリミティブな事象を指す。

> 定義： データ競合(data race)とは、(1)複数スレッド間で共有する変数に対して、(2)同時に、(3)読み／書きアクセスが行われる事象を指す。

### race condition
> 「競合状態(race condition)」はマルチスレッド・プログラムの設計、すなわち並行処理システムの設計に起因する。データ競合(data race)に比べると、高レイヤで複合的に生じる事象を指す。

> 定義： 各スレッド上で行われる操作の実行順序やタイミングに依存して、システムの出力結果が（意図せず）変化してしまう事象を指す。
