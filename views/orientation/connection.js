const domain = (new URL(window.location.href));
const socket = io(domain.host);
let tics = 0;
let startTime = Date.now();

socket.on("connect", () => {
    socket.emit("ID", "gyro-display");
    console.log("CONNECTION");
})

socket.on('h-order', (h) => {
    updateHeadingDisplay(h);

    h = Math.trunc()

    if(tics === 0) {
        hAxis.h = h;
    } else {
        hDelta.h = hAxis.h - h
    }
    tics++
})

socket.on('py-data', (data) => {
    // console.log(gx)
    let [gx, gy, gz, ax, ay,az,mx,my,mz, h] = data.split(',')
    const gyro =    {x: parseFloat(gx), y:parseFloat(gy), z: parseFloat(gz)}
    const accel =   {x: parseFloat(ax), y:parseFloat(ay), z: parseFloat(az)}
    const mag =     {x: parseFloat(mz), y:parseFloat(my), z: parseFloat(mx)}

    // h=parseFloat(h);
    updateGyroDisplay(gyro);
    updateAccelDisplay(accel);
    updateMagDisplay(mag);
    // updateHeadingDisplay(h);

    if(tics === 0) {
        // hAxis.h = h;
        gAxis.x = gyro.x;
        gAxis.y = gyro.y;
        gAxis.z = gyro.z;

        aAxis.x = accel.x;
        aAxis.y = accel.y;
        aAxis.z = accel.z;

        mAxis.x = mag.x;
        mAxis.y = mag.y;
        mAxis.z = mag.z;
    } else {
        // hDelta.h = hAxis.h - h

        gDelta.x = gAxis.x + gyro.x;
        gDelta.y = gAxis.y + gyro.y;
        gDelta.z = gAxis.z + gyro.z;

        aDelta.x = aAxis.x + accel.x;
        aDelta.y = aAxis.y + accel.y;
        aDelta.z = aAxis.z + accel.z;

        mDelta.x = mAxis.x + mag.x;
        mDelta.y = mAxis.y + mag.y;
        mDelta.z = mAxis.z + mag.z;
    }
    tics++
})
socket.on("raw-values", (gyro, accel, mag) => {
    updateGyroDisplay(gyro);
    updateAccelDisplay(accel);
    updateMagDisplay(mag);

    if(tics === 0) {
        gAxis.x = gyro.x;
        gAxis.y = gyro.y;
        gAxis.z = gyro.z;

        aAxis.x = accel.x;
        aAxis.y = accel.y;
        aAxis.z = accel.z;

        mAxis.x = mag.x;
        mAxis.y = mag.y;
        mAxis.z = mag.z;
    } else {
        gDelta.x = gAxis.x - gyro.x;
        gDelta.y = gAxis.y - gyro.y;
        gDelta.z = gAxis.z - gyro.z;

        aDelta.x = aAxis.x - accel.x;
        aDelta.y = aAxis.y - accel.y;
        aDelta.z = aAxis.z - accel.z;

        mDelta.x = mAxis.x - mag.x;
        mDelta.y = mAxis.y - mag.y;
        mDelta.z = mAxis.z - mag.z;
    }
    tics++
})

