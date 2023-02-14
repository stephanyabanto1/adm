const { createServer } = require("http");
const { Server } = require("socket.io");

const httpServer = createServer();
const io = new Server(httpServer, { /* options */ });

io.on("connection", (socket) => {
  console.log("connection")
  socket.on("gyro", (data)=> {
    let [x, y] = Buffer.from(data).toString().split(",")
    x = parseInt(x);
    if(x){
      y = parseInt(y)
      io.emit("gyro-output", x, y);
    }
  })
});

httpServer.listen(3000);