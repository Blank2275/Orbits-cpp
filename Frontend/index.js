var data = {};
fetch("/res.json")
.then(response => response.text())
.then(text => data = text);

var frame = 0;
var maxFrame = 50;

setTimeout(main, 500);
function main(){
    data = JSON.parse(data);
    setInterval(sim, 10);
}

function sim(){
    background(100);
    for(var key of Object.keys(data)){
        var object = data[key];
        var location = object["frames"][frame];
        var x = location[0];
        var y = location[1];
        var color = object["color"];
        fill(color[0], color[1], color[2]);
        ellipse(x, y, 10, 10)
    }
}

function setup(){
    createCanvas(600, 600)
}

function next(){
    frame += 1;
    if(frame >= maxFrame){
        frame = 0;
    }
}

function back(){
    frame -= 1;
    if(frame < 0){
        frame = maxFrame - 1;
    }
}