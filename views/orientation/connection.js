const domain = (new URL(window.location.href));
const socket = io(domain.host);
let tics = 0;
let startTime = Date.now();

socket.on("connect", () => {
    socket.emit("ID", "gyro-display");
    console.log("CONNECTION");
})

    