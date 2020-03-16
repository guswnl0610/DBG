var express = require('express');
const PythonShell = require('python-shell');
var rawdata;
const fs = require('fs');

function fsrHeatmapSaver(){
    var savefigpyshell = new PythonShell('savefigs.py');
    savefigpyshell.on('message', (msg) => {
        if(msg=="sfc")
        {
            console.log("yes sfc");
        }
        else{
            console.log('no sfc');
        }
    });
    
    savefigpyshell.end((err) => {
        if(err){throw err;};
    
        console.log('save figures finished');
    });
}

function analysisMaker(){
    const pyshell2 = new PythonShell('analysis.py');
    
    pyshell2.end(function (err) {
    if (err){
        throw err;
    };
    rawdata = fs.readFileSync('C:/Users/guswn_000/Desktop/Nodejs-master/public/texts/result.txt').toString(); 

    // console.log(rawdata);
    console.log('finished');
    });
}

console.log(rawdata);
module.exports.analysis = function(req, res){
    fsrHeatmapSaver();
    analysisMaker();
    res.render('analysis',{name: rawdata});
    
}

