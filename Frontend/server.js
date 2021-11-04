var app = require("express")();
var http = require("http").createServer(app);
var path = require("path");

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/index.html");
});
app.get("/index.js", (req, res) => {
    res.sendFile(__dirname + "/index.js");
});
app.get("/res.json", (req, res) => {
    res.sendFile(path.resolve(__dirname, "..") + "/Res/res.json");
});

http.listen(8080, () => {
    console.log("port 8080");
})