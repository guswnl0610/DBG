var express = require('express'); 
var bodyParser = require('body-parser'); 
var app = express(); 

app.use(express.static('public')); 
app.use(bodyParser.urlencoded({extended : false})); 
app.use(bodyParser.json());
app.set('view engine', 'ejs');//ejs 템플릿 엔진  연동 
var PythonShell = require('python-shell');

var userName = "";
var userSize = 0;

// route setting - 라우팅(routing) 
app.get('/', function (req, res) { 
   //res.send('Hello World!'); 
   var data = req.body;
   res.render('index', {name: data});//views디렉토리안에 있는 index.ejs 파일 
});

app.post('/', function (req, res) { 

    userName = req.body.name;
    userSize = req.body.size;
    console.log(userName + userSize);
    var getDatapyshell = new PythonShell('test.py');

    getDatapyshell.send(JSON.stringify([userName ,userSize]));

    getDatapyshell.on('message', function (message) {
        // received a message sent from the Python script (a simple "print" statement)
        console.log(message);
        // end the input stream and allow the process to exit
    });

    getDatapyshell.end(function (err) {
        if (err){
            throw err;
        };
        console.log('get Data finished');
    });
});


app.listen(3000, function(){ 
    console.log('App Listening on port 3000'); 
});

// pyshell.send(JSON.stringify([1,2,3,4,5]));

