var http = require('http');

var urls = process.argv.slice(2);
var count = 0;

var results = [];
for(var i = 0; i < urls.length; i++) {
  results.push('');
}

function printResults(results) {
  for(var i = 0; i < results.length; i++) {
    console.log(results[i]);
  }
};

urls.forEach(function(url, i) {
  http.get(url, function(res) {
    res.setEncoding('utf-8');
    res.on('data', function(chunk) {
      results[i] += chunk;
    });

    res.on('end', function() {
      count++;
      if (count == urls.length) {
        printResults(results);
      }
    });
  }).on('error', function(e) {
    console.log(e);
  });
});
