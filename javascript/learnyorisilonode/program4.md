# learnyounode 4

非同期処理をするファイルシステムのメソッドを使ってファイルの改行数を出力するアプリを書く．

### コールバック関数をもちいた readFile 関数の実装の想像
 readFile は関数を引数に取り，その関数にreadFile 内で作ったvariable を渡して，実行する．
 http://qiita.com/matsuby/items/3f635943f25e520b7c20

``` jsx
 function readFile(input, callback) {
   setTimeout(function() {
     var data = getData(input);
     var err = data.getError();

     callback(err, data);
   }, 0);
 }

 readFile('/pass/to/file', function(err, data) {
   if(err) throw err;
   console.log( data );
 });
```

## コード1
うまくいかない例． `lines` には `l` の値が代入されない．

``` jsx
var fs = require('fs');

var lines = function(file) {
  var lines = 0;
  fs.readFile(file, function(err, data) {
    var l = data.toString().split('\n').length - 1;
    lines = l;
  });
  return lines;
  // これだと，lines には０が入ってる．
  // なんでかはよくわからない．多分非同期的に処理をするreadFile関数の引数のコールバック関数内で代入してるからだけれど，うむ． readFile の実装を見ないとよくわからん．
};

var file = process.argv[2];

console.log( lines(file) );
```
### 上記の解決
callback 関数を使って，ネストした関数内の 値をとってくればおｋ．

つまり，

``` jsx
var fs = require('fs');

var file = process.argv[2];

var lines = function(file, callback) {
  fs.readFile(file, function(err, data) {
    var lines = data.toString().split('\n').length - 1;
    return callback(lines);
  });
};


lines(file, function(lines) {
  console.log( lines );
});

```
こうすればおｋ．


## コード2
下の場合の `asyncFunc` の場合だと，予想通りの振る舞いをする．

``` jsx
 var fs = require('fs');

 var lines = function(file) {
   var lines = 0;
   asyncFunc(file, function(err, data) {
     var l = data.toString().split('\n').length - 1;
     lines = l;
   });
   return lines;
   // この場合は，予想通り，ここでlines には l の値が入ってる．
 };

 var file = process.argv[2];

 console.log( lines(file) );

 function asyncFunc(file, callback) {
   var data = fs.readFileSync(file);
   var err = null;
   callback(err, data);
 }
```
