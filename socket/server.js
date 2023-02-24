const { createServer } = require("http");
const { Server } = require("socket.io");

const httpServer = createServer();
const io = new Server(httpServer, { /* options */ });

io.on("connection", (socket) => {
  console.log("connection")

  socket.on("gyro", (data)=> {
    let coords = Buffer.from(data).toString().split(",")
    console.log(coords)
    x = parseInt(x);
    if(x){
      y = parseInt(y)
      io.emit("gyro-output", x, y);
    }
  })

  socket.on("mouse-pos", (pitch, yaw)=> {
    io.emit("gyro-output", pitch, yaw)
  })
});

httpServer.listen(3000, ()=>console.log(httpServer.address()));