let piblaster;
const { io } = require("socket.io-client")
if(process.platform === 'linux'){
    console.log("LINUX platform")
    piblaster = require("pi-blaster.js")
}

const ipAddresses = [
    "http://192.168.2.15:3000",
    "http://192.168.2.14:3000",
    "http://192.168.0.100:3000"
]
const sockets = []
let socket;


console.log("connecting to server...")

for(let i = 0; i < ipAddresses.length; i++) {
    sockets[i] = io(ipAddresses[i])
    sockets[i].on("connect", ()=> {
        socket = sockets[i];
        console.log("CONNECTION");
        flushSockets(i);
        initReciever();
    })
}

function flushSockets(exception) {
    console.log("FLUSHING SOCKETS")
    for(let i = 0; i < ipAddresses.length; i++) {
        if(i !== exception){
            sockets[i].close();
            sockets[i] = null;
        }
    }
}

function initReciever() {
    // piblaster 180 degree for servo is 0.06 - 0.24
    socket.on("gyro-output", (x, y)=>{
        // pin 4 is yaw
        console.log("x:", x, ' y:',y)
    
        piblaster.setPwm(4, x /180 + 0.06)
        // pin 17 is roll 
        piblaster.setPwm(17, y /180 + 0.06)
    })
}



// socket.on("canvas-pos", ( pos )=> {
//     console.log("pos")
//     piblaster.setPwm(4, (pos.x * ratio) / 1000 + 0.06)
//     piblaster.setPwm(17, (pos.y * ratio) / 1000 + 0.06)
// })