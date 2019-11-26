const express = require('express');
const SerialPort = require('serialport');

const app = express();
const port = new SerialPort('ttyUSB0', { // ttyUSB0 디바이스를 찾을 수 없다고 오류가 발생할 경우 '/dev/ttyUSB0' 로 해볼 것.
    baudRate: 9600
});

function writeAndDrain(data, callback) {
    port.write(data, function() {
        port.drain(callback);
    });
}

port.on('open', function() { // 아두이노와 연결됐을 때
    console.log('Serial port is opened.');
    port.on('data', function(data) { // 아두이노로부터 데이터를 받았을 때 :: 아두이노에서는 Serial.print(value)  함수를 통해 데이터 전송
        console.log('Arduino send data: ', data);
        writeAndDrain(data, function() {
            console.log('Server send data to Arduino: ', data);
        });
    });
});

app.listen(8000, () => {
    console.log('The server is opened on port 8000.');
}); // 8000 포트를 통해 서버 가동