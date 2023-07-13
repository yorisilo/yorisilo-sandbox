# haskeller の会

## モナド
Free monad は functor をモナド化するやつ

Free monad 以外にも skelton っていうやつがある。

https://qiita.com/satosystems/items/e8788f05924cef226493
https://qiita.com/sg-matsumoto/items/de6874149ccbeaedac3e

## コモナド

co-monad はオブジェクト指向っぽい

状態(オブジェクト)に対して、更新を行い、その更新された値を取り出すことができる。

様相論理(modal logic) moggi
modal type theory:
モナドに対応してる。

## 自然変換 は haskell で言うと？
明示的に しぜんへんかん型が存在してるわけでないが、いろんなところに立ち現れる。

head ,return とかもそう。

head は自然変換公理を満たしてるので、結果的に head は自然変換と言える

自然変換公理:
http://ie.u-ryukyu.ac.jp/~kono/lecture/software/Agda/nat.html
