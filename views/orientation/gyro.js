let gAxis = {
    x:0,
    y:0,
    z:0
}
let gDelta = {
    x:0,
    y:0,
    z:0
}

socket.on("raw-values", (x,y,z) => {
    updateGyroDisplay({x,y,z});
    if(tics === 0) {
        gAxis.x = x;
        gAxis.y = y;
        gAxis.z = z;
    } else {
        gDelta.x = gAxis.x - x;
        gDelta.y = gAxis.y - y;
        gDelta.z = gAxis.z - z
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