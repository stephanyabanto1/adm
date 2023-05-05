let axis = {
    x:0,
    y:0,
    z:0
}
let delta = {
    x:0,
    y:0,
    z:0
}

socket.on("gyro-raw", (x,y,z) => {
    updateGyroDisplay({x,y,z});
    
    if(tics === 0) {
        axis.x = x;
        axis.y = y;
        axis.z = z;
    } else {
        delta.x = axis.x - x;
        delta.y = axis.y - y;
        delta.z = axis.z - z
    }
    tics++
})

function updateGyroDisplay({x,y,z}) {
    const dispX = document.getElementById("gx");
    const dispY = document.getElementById("gy");
    const dispZ = document.getElementById("gz");

    dispX.innerHTML = `x: ${x}`
    dispY.innerHTML = `y: ${y}`
    dispZ.innerHTML = `z: ${z}`
}