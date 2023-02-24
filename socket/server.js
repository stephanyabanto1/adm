const { createServer } = require("http");
const { Server } = require("socket.io");

const httpServer = createServer();
const io = new Server(httpServer, { /* options */ });

io.on("connection", (socket) => {
  console.log("connection")

  socket.on("gyro", (data)=> {
    let coords = Buffer.from(data).toString().split(",")
    coords[2] = coords[2].split("\r")[0];

    const [pitch, roll, yaw ] = coords;
    const test = [parseFloat(pitch), parseFloat(roll), parseFloat(yaw)];

    const turret = [
      (test[0]).toPrecision(5), 
      (((test[1]+90)/640)+0.02).toPrecision(5),
      (test[2]).toPrecision(5)
    ];

    // console.log(coords);
    // console.log(test);
    io.emit("gyro-output", turret[0], turret[1], turret[2]);
  })

  socket.on("mouse-pos", (pitch, yaw)=> {
    io.emit("gyro-output", pitch, 0, yaw);
  })
});

httpServer.listen(3000, ()=>console.log(httpServer.address()));