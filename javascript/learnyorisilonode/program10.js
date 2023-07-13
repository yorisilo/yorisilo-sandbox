var net = require('net');
var strftime = require('strftime');

var port = process.argv[2];

var server = net.createServer(function(socket) {
  var date = strftime('%F %H:%M\n', new Date());
  date = date.toString();

  socket.write(date);
  socket.end();
});
server.listen(port);
