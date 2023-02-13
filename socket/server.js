const { createServer } = require("http");
const { Server } = require("socket.io");

const httpServer = createServer();
const io = new Server(httpServer, { /* options */ });

io.on("connection", (socket) => {

  console.log("connection")


  socket.on("gyro", (data)=> {
    const string = Buffer.from(data).toString()
    console.clear();
    console.log(string);
  })
});

httpServer.listen(3000);