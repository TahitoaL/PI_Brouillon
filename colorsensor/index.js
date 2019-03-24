/* -------------------------- *\
            PI RUNBOT
Author : TahitoaL
2019
\* -------------------------- */

let SerialPort = require('serialport')
let Readline = SerialPort.parsers.Readline
let portAdress = "COM4"

let app = require('express')();
let server = require('http').Server(app);
let io = require('socket.io')(server);


let port = new SerialPort(portAdress, {baudRate: 9600})
let parser = new Readline()

port.pipe(parser)
parser.on('data', (data) => {
    console.log(portAdress + "> " + new Date().toISOString().replace(/T/, ' ').replace(/\..+/, '') + ' : ' + data)
    if (data.startsWith('*'))
    {
      let action = data.replace('*', '').charAt(0)
      let args = data.split(' ').slice(1)
      switch (action)
      {
        case 'c':
          io.emit('color', args[0])
          break
        case 'p':
          io.emit('p', args[0])
          break
        case 'n':
          let data = ''
          args.forEach((arg) => {
            data += ' ' + arg
          })
          io.emit('n', data.substring(1, data.length))
          break
      }
    }
})

server.listen(8080);

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

app.route('/notificationCss')
  .get((req, res) => {
    res.sendFile(__dirname + '/notification.css')
  })

app.route('/notificationJs')
.get((req, res) => {
  res.sendFile(__dirname + '/notification.js')
})

io.on('connection', function (socket) {
    console.log('\x1b[31m%s\x1b[0m' ,'New connection')
    io.emit('notification-success', 'Connexion établie !');
});

