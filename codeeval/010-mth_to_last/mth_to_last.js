var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line !== '') {
        var tokens = line.split(' ');
        var last = parseInt(tokens[tokens.length - 1]);
        if (tokens[tokens.length - 1 - last] !== undefined)
            console.log(tokens[tokens.length - 1 - last]);
    }
});
