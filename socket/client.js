const {io} = require("socket.io-client");
const { spawnSync, execSync } = require("child_process");

console.log("connecting to server...")

const socket = io("http://192.168.0.14:3000");

socket.on("connect", ()=> {
    console.log("connected")
    exec();
})

const exec = async ()=>{
    
    console.log("running build...")

    await execSync('gcc gyro.cpp -lstdc++ -lwiringPi -lpthread -o exec', {
        cwd: "../driver"
    }, (err, stdout, stderr) => {
        if(!err) {
            // change this, something better
            console.log('subprocess stdout: ', Buffer.from(stdout).toString())
            console.log('subprocess stderr: ', Buffer.from(stderr).toString())
            // resolve()
            
        } else {
            // rejects("Subprocess error: ", err)
        }
    })

    console.log("running exec...")

    const child = await spawnSync('./exec', [] ,{
        stdio: ['ignore', 'pipe', process.stderr],
        cwd: "../driver"
    })

    child.stdout.on("data", (data)=>{
        console.log(data)
        socket.emit("gyro", data)
    })
}