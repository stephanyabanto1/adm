let WIDTH =1000
let HEIGHT = 800

let x = 0;
let y = 0;

let pitch = 0;
let roll = 0;
// console.log(controllers[0].axes)

function setup() {
    
    createCanvas(WIDTH, HEIGHT, WEBGL);
    // x = WIDTH *0.5
    // y = HEIGHT *0.5
    angleMode(DEGREES)

}
  
function draw() {
    background(220);
    normalMaterial();
    translate(x,y,0);
    rotateX(pitch)
    rotateY(roll)

    push()
        rect(0,0,50,50,15);
        if(controllers[0]){
            update();
        }
    pop()
}
  

function update () {
    let multi = 5
    let dx =  (controllers[0].axes[0]) * multi
    let dy =  (controllers[0].axes[1]) * multi

    let dPitch =  (controllers[0].axes[2])
    let dRoll =  (controllers[0].axes[3]) 

    pitch += dPitch;
    roll += dRoll;
    x += dx
    y += dy
    // console.log(x, y)
}