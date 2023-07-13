npm install -g elm elm-live
mkdir space_invaders && cd space_invaders
elm init
touch Main.elm
npm i -g elm-format

``` shell
elm-live ./src/Main.elm -- --debug
```

引数の意味が違うとき -- ってやることが多い

[引数を処理する | UNIX & Linux コマンド・シェルスクリプト リファレンス](https://shellscript.sunone.me/parameter.html)
