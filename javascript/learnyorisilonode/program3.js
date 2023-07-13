var fs = require('fs');

var lines = function(fileapath) {
  var contents = fs.readFileSync(filepath);
  var lines = contents.toString().split('\n').length - 1;
  return lines;
};

var filepath = process.argv[2];

console.log( lines(filepath) );


// var buf = fs.readFileSync(filepath);
// var str = buf.toString();

// console.log( str.split('\n').length -1 );
