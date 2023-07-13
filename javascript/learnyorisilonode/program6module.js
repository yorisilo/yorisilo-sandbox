// used by program6
var fs = require('fs');
var path = require('path');

module.exports = function(dir, ext, callback) {
  fs.readdir(dir, function(err, list) {
    var files = [];
    if (err) return callback(err);

    list.forEach(function(file) {
      if (path.extname(file) == '.' + ext) {
        files.push(file);
      }
    });
    return callback(null, files);
  });
};
