let cx, cy;

function setup() 
{
    createCanvas(windowWidth, windowHeight);

}

function draw() 
{
    background(255);
    const dx = constrain(rotationY, -3, 3);
    const dy = constrain(rotationX, -3, 3);
    cx += dx*2;
    cy += dy*2;
    cx = constrain(cx, 0, width);
    cy = constrain(cy, 0, height);
    
    ellipse(cx, cy, 200, 200);
    
}

socket.on("gyro-output", (x, y)=>{
    cx = x + 200
    cy = y + 200
    console.log(x, y)
})
