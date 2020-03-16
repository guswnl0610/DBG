// const http = require('http');

// const hostname = '127.0.0.1';
// const port = 3000;


// const ps = require('python-shell');

// var options = {

//   mode: 'text',

//   pythonPath: '',

//   pythonOptions: ['-u'],

//   scriptPath: '',

//   args: ['meng','230']

// };

// ps.PythonShell.run('test.py', options, function (err, results) {

//   // if (err) throw err;


//   console.log('results: %j', results);
//   console.log("fininshed");

// });



// // const server = http.createServer((req, res) => {
// //   res.statusCode = 200;
// //   res.setHeader('Content-Type', 'text/plain');
// //   res.end('Hello World!\n');
// // });

// // server.listen(port, hostname, () => {
// //   console.log(`Server running at http://${hostname}:${port}/`);
// // });

// var PythonShell = require('python-shell');
// var pyshell = new PythonShell('test.py');

// function sleep(ms) {
//     return new Promise(resolve => setTimeout(resolve, ms));
//   }
  
//   async function demo() {
//     const PythonShell2 = require('python-shell');
//     const pyshell2 = new PythonShell2('test2.py');
  
//     pyshell2.end(function (err) {
//       if (err){
//           throw err;
//       };
  
//       const fs = require('fs');
  
//       let rawdata = fs.readFileSync('result.txt'); 
    
//       console.log(rawdata.toString());
  
//       console.log('finished');
//     });
  
  
//     await sleep(2000);
    
//   }
//   demo();

function analysisMaker(){
    const PythonShell2 = require('python-shell');
    const pyshell2 = new PythonShell2('analysis.py');
    
    pyshell2.end(function (err) {
    if (err){
        throw err;
    };
    const fs = require('fs');
    let rawdata = fs.readFileSync('result.txt'); 

    console.log(rawdata.toString());
    console.log('finished');
    });
}



  
  // const PythonShell2 = require('python-shell');
  // const pyshell2 = new PythonShell2('test2.py');
  
  // pyshell2.end(function (err) {
  //   if (err){
  //       throw err;
  //   };
  
  //   console.log('finished');
  // });
  
  // var name;
  // var size;
  
  // name = 'meng'
  // size = 240
  
  // const fs = require('fs');
  
  // let rawdata = fs.readFileSync('student.txt'); 
  
  // console.log(rawdata.toString());
   
  // console.log(JSON.stringify([sys.stdin]))
  // pyshell.send(JSON.stringify([1,2,3,4,5]));
  // pyshell.send(JSON.stringify([name,size]));
  
  
  // pyshell.on('message', function (message) {
  //     // received a message sent from the Python script (a simple "print" statement)
  //     console.log(message);
  // });
  
  // pyshell2.on('message', function (message) {
  //   // received a message sent from the Python script (a simple "print" statement)
  //   console.log(message);
  // });
  
  
  // end the input stream and allow the process to exit
  // pyshell.end(function (err) {
  //     if (err){
  //         throw err;
  //     };
  
  //     console.log('finished');
  // });