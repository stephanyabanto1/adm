let hAxis = {
    h:0
}
let hDelta = {
    h:0
}

function updateHeadingDisplay(h) {
    const dispH = document.getElementById("heading");

    dispH.innerHTML = `h: ${h}`
}