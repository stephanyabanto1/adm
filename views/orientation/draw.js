function setup() {
    createCanvas(windowWidth, windowHeight, WEBGL);
}

function draw() {
    background(255);
    normalMaterial();
    translate(-240, -100,0);
    angleMode(DEGREES)
    push()
    rotateX(delta.y)
    rotateY(delta.z)
    rotateX(delta.x)
    box( 180, 30, 180)
    pop()
}