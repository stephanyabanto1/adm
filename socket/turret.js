let piblaster
if(process.platform === 'linux') piblaster = require("pi-blaster.js")
const ratio = 180 / 605

const { io } = require("socket.io-client")

const socket = io("http://192.168.2.15:3000");


socket.on("connect",() => {
    socket.emit("purpose", "turret")
})

// piblaster 180 degree for servo is 0.06 - 0.24

socket.on("gyro-output", (x, y)=>{
   // pin 4 is yaw
   console.log("x:", x, ' y:',y)
   piblaster.setPwm(4, x /100 + 0.06)
   // pin 17 is roll 
   piblaster.setPwm(17, y /100 + 0.06)
})

socket.on("canvas-pos", ( pos )=> {
    console.log("pos")
    piblaster.setPwm(4, (pos.x * ratio) / 1000 + 0.06)
    piblaster.setPwm(17, (pos.y * ratio) / 1000 + 0.06)
})