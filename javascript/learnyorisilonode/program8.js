var http = require('http');

var url = process.argv[2];

http.get(url, function(res) {
  res.setEncoding('utf-8');
  var out = '';
  res.on('data', function(chunk) {
    out = out + chunk;
  });
  res.on('end', function() {
    console.log(out.length);
    console.log(out);
  });
});
