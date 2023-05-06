function setup() {
    createCanvas(windowWidth, windowHeight, WEBGL);
    textSize(width / 3);
    textAlign(CENTER, CENTER);
}

function draw() {
    background(255);
    normalMaterial();
    translate(-240, -100,0);
    angleMode(DEGREES)

    push()
    rotateX(gDelta.y)
    rotateY(gDelta.z)
    rotateX(gDelta.x)
    box( 180, 30, 180)
    pop()

    translate(400, 0,0);
    push()
    rotateX(gDelta.y)
    rotateY(gDelta.z)
    rotateX(gDelta.x)
    box( 180, 30, 180)
    pop()

    translate(-200,200,0);
    push()
    rotateX(gDelta.y)
    rotateY(gDelta.z)
    rotateX(gDelta.x)
    box( 180, 30, 180)
    pop()
}