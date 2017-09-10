var find = require('./program6module.js');

var dir = process.argv[2];
var ext = process.argv[3];

// コールバック関数を使うことによりネストした関数内の値を取ってくることができる．
// 限定継続の shift/reset 的に使える．

find(dir, ext, function(err, files) {
  if(err) throw err;
  files.forEach(function(file) {
    console.log( file );
  });
});
