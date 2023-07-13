var http = require('http');
var url = require('url');

var port = process.argv[2];

function parseTime(date) {
  return {
    hour: date.getHours(),
    minute: date.getMinutes(),
    second: date.getSeconds()
  };
}

function parseUnixTime(date) {
  return { unixtime: date.getTime() };
}

var server = http.createServer(function(req, res) {
  var query = url.parse(req.url, true);
  var path = query.pathname.split('/');
  var date = new Date(query.query.iso);

  var result;

  if(path[1] == 'api' && path [2] == 'parsetime') {
    result = parseTime(date);
  } else if(path[1] == 'api' && path [2] == 'unixtime'){
    result = parseUnixTime(date);
  }

  if (result) {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.write(JSON.stringify(result));
    res.end();
  } else {
    res.writeHead(404);
    res.end();
  }
});
server.listen(port);
