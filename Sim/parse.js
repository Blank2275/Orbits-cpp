var fs = require("fs");
var path = require("path");

var inputFilePath = path.resolve(__dirname, "..") + "/Res/res.txt";
var outputFilePath = path.resolve(__dirname, "..") + "/Res/res.json";

fs.readFile(inputFilePath, (err, data) => {
    if(err) throw err;
    data = data.toString();
    data = data.split("end\n");
    var output = {};
    for(section of data){
        var lines = section.split("\n");
        if(!lines[0].includes(":")){
            output[`${lines[0]}`] = {};
            output[`${lines[0]}`]["frameCount"] = parseInt(lines[1]);
            color = lines[2].split(",");
            color[0] = parseInt(color[0]);
            color[1] = parseInt(color[1]);
            color[2] = parseInt(color[2]);
            output[`${lines[0]}`]["color"] = parseInt(color);
            output[`${lines[0]}`]["frames"] = [];
        } else{
            for(var line of lines){
                var parts = line.split(":");
                if(parts[1]){
                    var id = parts[0];
                    var pos = parts[1].split(",");
                    var x = parseFloat(pos[0]);
                    var y = parseFloat(pos[1]);
                    output[`${id}`]["frames"].push([x, y]);
                }
            }
        }
    }

    var outputString = JSON.stringify(output);
    fs.writeFile(outputFilePath, outputString, (err) => {
    });
});