const {io} = require("socket.io-client");
const { spawn, execSync } = require("child_process");

console.log("connecting to server...")

const socket = io("http://192.168.0.14:3000");

socket.on("connect", ()=> {
    console.log("connected")
    exec();
})

const exec = async ()=>{
    
    console.log("running build...");

    await execSync('gcc gyro.cpp -lstdc++ -lwiringPi -lpthread -lchrono -o exec', {
        cwd: "../driver"
    }, (err, stdout, stderr) => {
        if(!err) {
            // change this, something better
            console.log('subprocess stdout: ', Buffer.from(stdout).toString())
            console.log('subprocess stderr: ', Buffer.from(stderr).toString())
            // resolve()
            
        } else {
            console.error("BUILD ERROR: ",err)
            // rejects("Subprocess error: ", err)
        }
    });

    console.log('\x1b[32m%s\x1b[0m', "running exec...");

    const child = spawn('./exec', [] ,{
        stdio: ['ignore', 'pipe', process.stderr],
        cwd: "../driver"
    });

    child.stdout.on("data", (data)=>{
        // console.log(data);
        socket.emit("gyro", data);
    });
}