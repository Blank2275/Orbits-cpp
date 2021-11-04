var fs = require("fs");
var path = require("path");

var inputFilePath = path.resolve(__dirname, "..") + "/Res/res.txt";
var outputFilePath = path.resolve(__dirname, "..") + "/Res/res.json";

fs.readFile(inputFilePath, (err, data) => {
    if(err) throw err;
    data = data.toString();
    data = data.split("end\n");
    var output = {};
    for(var object of data){
        var lines = object.split("\n");
        if(lines[2]){
            var name = lines[0];
            var frames = parseInt(lines[1]);
            console.log(lines);
            var color = lines[2].split(",");
            color[0] = parseInt(color[0]);
            color[1] = parseInt(color[0]);
            color[2] = parseInt(color[0]);
            var locations = [];
            for(var i = 3; i < lines.length; i++){
                var location = lines[i].split(",");
                var x = parseFloat(location[0]);
                var y = parseFloat(location[1]);
                locations.push([x, y]);
            }
            output[`${name}`] = {
                "frameCount": frames,
                "color": color,
                "frames": locations
            }
        }
    }
    var outputString = JSON.stringify(output);
    console.log(outputString);
    fs.writeFile(outputFilePath, outputString, (err) => {
    });
});