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
