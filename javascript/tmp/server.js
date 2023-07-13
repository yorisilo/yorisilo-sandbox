// http://team-lab.github.io/skillup-nodejs/2/3.html
// https://osdn.jp/magazine/12/04/11/0618228/2

// ライブラリの読み込み
const http = require('http');
const host = '127.0.0.1';
const port = 1337;

// サーバオブジェクトの作成，実行
http.createServer((req, res) => {
  // ヘッダとしてHTTPステータスコードと形式を設定
  res.writeHead(200, {'Content-Type': 'text/plain'});

  // 表示する内容を設定する
  res.end('Hello yorisilo!\n');
  // ローカルホスト，ポート1337番でlistenする
}).listen(port, host);

// URLやサーバの止め方を表示する
console.log('Server running at http://localhost:1337/');
console.log('Ctrl + C to stop server');

// const Test = (function () {
//   const _name = 'Takashi',
//         _age = 999;

//   const _init = (a,b) => {return a+b;};
//   return {
//     init: _init
//   };
// }());
