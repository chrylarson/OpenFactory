var dgram = require("dgram");
var server = dgram.createSocket("udp4");
var fs = require('fs');
var sanitize = require('validator').sanitize;

var crlf = new Buffer(2);
crlf[0] = 0xD; //CR - Carriage return character
crlf[1] = 0xA; //LF - Line feed character

var mysql      = require('mysql');
var connection = mysql.createConnection({
  host     : 'localhost',
  user     : 'user',
  password : 'password',
});

server.on("message", function (msg, rinfo) { //every time new data arrives do this:
  var MYtime = new Date().getTime();
  var MYquery = 'INSERT INTO `arduino`.`arTable` (`id`, `value`, `serialNum`, `date`, `datetime`, `IP`) VALUES (NULL, "' + msg.readUInt16BE(1) + msg.readUInt16BE(0) +  '", "' + msg.readUInt16BE(2) + msg.readUInt16BE(3) + msg.readUInt16BE(4) + '", CURRENT_TIMESTAMP, "'+ MYtime + '", "'+ rinfo.address + ":" + rinfo.port + '");';
  //console.log(MYquery); // you can comment this line out
  connection.query(MYquery, function(err, rows) {
  });
});

server.on("listening", function () {
  var address = server.address();
  console.log("server listening " + address.address + ":" + address.port);
});

server.bind(8080); //listen to udp traffic on port 8080