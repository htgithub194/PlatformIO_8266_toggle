var dgram = require('dgram');
var server = dgram.createSocket("udp4");
server.bind(8888);

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server started and listening on ' + address.address + ":" + address.port);
});

let ListDevices = [];

function findDeviceById(id) {
    for (let d of ListDevices) {
        if (d.id === id) return d;
    }
    return null;
}

server.on("message", function (message, rinfo) {
    var output = "Udp server receive: " + message + ` from ${rinfo.address}:${rinfo.port}\n`;
    process.stdout.write(output);

    let spt = output.split(' ');
    let cmd = spt[0];

    let ip = rinfo.address;

    if (cmd === 'upd') {
        let deviceID = spt[1];
        let stt = spt[2];

        let device = findDeviceById(deviceID);
        if (!device) {
            device = { deviceID, stt, ip };
            ListDevices.push(device);
        } else {
            device.stt = stt;
        }
    }
});