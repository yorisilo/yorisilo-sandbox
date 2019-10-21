2018-11-10 10:03:16

# haskell day
* [Haskell Day 2018 - connpass](https://haskell-jp.connpass.com/event/92617/)


## haskell hands on
* [makeMistakesToLearnHaskell/README.md at master · haskell-jp/makeMistakesToLearnHaskell](https://github.com/haskell-jp/makeMistakesToLearnHaskell/blob/master/README.md)

* [Haskell-jp wiki - Hikers Guide to Haskell](https://wiki.haskell.jp/Hikers%20Guide%20to%20Haskell)

### コラム: stack ghciかstack exec ghciか
実は、ここで紹介したstack exec ghciのほかに、stack ghciというサブコマンドがstackにはあります。
stack ghciはstack exec ghciとよく似た機能ですが、stack exec ghciの方が場合によっては使いやすいので、ここではstack exec ghciを採用しています（詳細は申し訳なくも割愛します！）。

同様に、前の課題で紹介したstack exec runhaskellにも、より短いstack runhaskellというコマンドがあります。
残念ながら、stack runhaskellについては、「ラップしているrunhaskellコマンドに直接オプションを渡せない」という大きな落とし穴があり、あまりおすすめできるものではありません。
加えてstack exec ghciと一貫させるためにも、stack exec runhaskellを使用しています。

* [Haskell入門 | haskell](http://lotz84.github.io/haskell/tutorial)

> 実は、Haskellの世界では、「（引数を受け取って）何か値を返す関数（ただし入出力処理はできない）」と、「（引数は受け取らないけど）入出力処理をしつつ何か値を返すことができる関数」の2つが厳密に分けられています。

> そして、一般に前者は「純粋な関数」、後者は「IOアクション」と呼ばれています。 putStrLnのような、Haskellで入出力処理を行う関数は、「純粋な関数」が引数を受け取り、それを元に「IOアクション」を返すことで実装されています。
* [Haskellらしさって？「型」と「関数」の基本を解説！【第二言語としてのHaskell】 - エンジニアHub｜若手Webエンジニアのキャリアを考える！](https://employment.en-japan.com/engineerhub/entry/2017/08/25/110000)

## haskell を導入した話
* Haskellを仕事で使っててパフォーマンスでハマったことはないがメモリで苦労したことはある。その時は扱う型を変えれば解決した

## haskell servant で行う安全かつ高速な API 開発
* LEMO nakaji-dayo
* [BLOG dayo](http://blog.nakaji.me/)

* servant
ruby の sinatra みたいな薄い WAF

* Servant の特徴
型レベルプログラミング

* Haskell Relational Recod
クエリパーサー

一般的に業務レベルの開発に library は十分に育っている。

## 並列並行言語 haskell
* [syocy/haskell-day-syocy](https://github.com/syocy/haskell-day-syocy)
* [A Tour of Go in Haskell](https://a-tour-of-go-in-haskell.syocy.net/ja_JP/index.html)

* haskell による並行並列プログラミング 推し

## Dhall
* haskell like な コンフィグを書くための DSL
dhall to json とかがあるので、既存の yaml を読み込むようなサービスなどにも組み込みやすい。

DhallのファイルをHaskellの型として読み込める

* [Dhall.Tutorial](http://hackage.haskell.org/package/dhall-1.18.0/docs/Dhall-Tutorial.html)
* [Getting started: Generate JSON or YAML · dhall-lang/dhall-lang Wiki](https://github.com/dhall-lang/dhall-lang/wiki/Getting-started%3A-Generate-JSON-or-YAML)

## Semigroupとは？ Monoid？ 環？
* 擬環は要するに分配をするために必要なものが定まったプロトコル
* 擬環＝可換モノイド＋可換群

* 代数的構造 = 型クラス
* 代数 = その型クラスのインスタンス

例えば、
* 単なる群は代数的構造
* リー群は代数
というような感じ

## haskell で CLI
* [Haskell で CLI](https://www.slideshare.net/noob00/haskell-cli?ref=https://haskell-jp.connpass.com/event/92617/presentation/)

* コマンドライン引数

* [extensible攻略Wiki](http://wiki.hask.moe/)
  - 拡張 valiant
  - haskell の record をいい感じにしたやつ

## gloss
* [glossではじめるグラフィック描画 :: Haskell入門の次に読む記事 - Qiita](https://qiita.com/lotz/items/eb73e62a64bc208c2dd6)
* [gloss: 動かして遊んで学ぶHaskell - Qiita](https://qiita.com/lotz/items/bdb04c771efc8919b79c)

## Liszt
