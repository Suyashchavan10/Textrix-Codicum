const express = require('express');
const multer = require('multer');
const fs = require('fs');
const { exec } = require('child_process');
const path = require('path');

const app = express();
const port = 3000;

// Create uploads directory if it doesn't exist
if (!fs.existsSync(path.join(__dirname, '../uploads'))) {
    fs.mkdirSync(path.join(__dirname, '../uploads'));
}

// Set up multer for handling file uploads
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, path.join(__dirname, '../uploads/'));
    },
    filename: (req, file, cb) => {
        cb(null, file.originalname);
    }
});
const upload = multer({ storage: storage });

// Serve static files (CSS, JS) from the public directory
app.use(express.static(path.join(__dirname, '../frontend')));

// Set view engine to EJS
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, '../frontend'));

// Home route - serve HTML form
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../frontend/index.html'));
});

// Upload route - handle file upload
app.post('/upload', upload.single('pseudocodeFile'), (req, res) => {
    const pseudocodeFile = req.file.path;
    const binaryFilePath = path.join(__dirname, './a.exe'); // Path to the pre-compiled binary
    const outputFilePath = path.join(__dirname, '../uploads/code.cpp'); // Output C++ file path

    // Execute the pre-compiled binary
    exec(`"${binaryFilePath}" "${pseudocodeFile}"`, { cwd: path.join(__dirname, '../uploads') }, (error, stdout, stderr) => {
        if (error) {
            console.error(`Execution error: ${error}`);
            res.status(500).send('Error running compiled program');
            return;
        }
        if (stderr) {
            console.error(`Stderr: ${stderr}`);
            res.status(500).send('Error running compiled program');
            return;
        }

        // Read the generated C++ file and send its content to the client
        fs.readFile(outputFilePath, 'utf8', (err, data) => {
            if (err) {
                console.error(`Error reading output file: ${err}`);
                res.status(500).send('Error reading generated C++ file');
                return;
            }
            console.log(data);
            res.render('result', { cppCode: data });
        });
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
});


// const express = require('express');
// const multer = require('multer');
// const fs = require('fs');
// const { exec } = require('child_process');
// const path = require('path');

// const app = express();
// const port = 3000;

// // Create uploads directory if it doesn't exist
// if (!fs.existsSync(path.join(__dirname, '../uploads'))) {
//     fs.mkdirSync(path.join(__dirname, '../uploads'));
// }

// // Set up multer for handling file uploads
// const storage = multer.diskStorage({
//     destination: (req, file, cb) => {
//         cb(null, path.join(__dirname, '../uploads/'));
//     },
//     filename: (req, file, cb) => {
//         cb(null, file.originalname);
//     }
// });
// const upload = multer({ storage: storage });

// // Serve static files (CSS, JS) from the public directory
// app.use(express.static(path.join(__dirname, '../frontend')));

// // Set view engine to EJS
// app.set('view engine', 'ejs');
// app.set('views', path.join(__dirname, '../frontend'));

// // Home route - serve HTML form
// app.get('/', (req, res) => {
//     res.sendFile(path.join(__dirname, '../frontend/index.html'));
// });

// // Upload route - handle file upload
// app.post('/upload', upload.single('pseudocodeFile'), (req, res) => {
//     const pseudocodeFile = req.file.path;
//     const outputFilePath = path.join(__dirname, '../uploads/code.cpp'); // Output C++ file path

//     // Execute pseudocode to C++ conversion command
//     const command = `python3 "${path.join(__dirname, 'pseudocode_to_cpp.py')}" "${pseudocodeFile}" "${outputFilePath}"`;

//     exec(command, (error, stdout, stderr) => {
//         if (error) {
//             console.error(`Execution error: ${error}`);
//             res.status(500).send('Error converting pseudocode to C++');
//             return;
//         }
//         if (stderr) {
//             console.error(`Stderr: ${stderr}`);
//             res.status(500).send('Error converting pseudocode to C++');
//             return;
//         }

//         // Read the generated C++ file and send its content to the client
//         fs.readFile(outputFilePath, 'utf8', (err, data) => {
//             if (err) {
//                 console.error(`Error reading output file: ${err}`);
//                 res.status(500).send('Error reading generated C++ file');
//                 return;
//             }
//             res.render('result', { cppCode: data });
//         });
//     });
// });

// // Start the server
// app.listen(port, () => {
//     console.log(`Server listening at http://localhost:${port}`);
// });





// // const express = require('express');
// // const multer = require('multer');
// // const fs = require('fs');
// // const { exec } = require('child_process');

// // const app = express();
// // const port = 3000;

// // // Set up multer for handling file uploads
// // const storage = multer.diskStorage({
// //     destination: (req, file, cb) => {
// //         cb(null, './uploads/');
// //     },
// //     filename: (req, file, cb) => {
// //         cb(null, file.originalname);
// //     }
// // });
// // const upload = multer({ storage: storage });

// // // Serve static files (CSS, JS) from the public directory
// // app.use(express.static('public'));

// // // Set view engine to EJS
// // app.set('view engine', 'ejs');

// // // Home route - serve HTML form
// // app.get('/', (req, res) => {
// //     res.sendFile(__dirname + '/public/index.html');
// // });

// // // Upload route - handle file upload
// // app.post('/upload', upload.single('pseudocodeFile'), (req, res) => {
// //     const pseudocodeFile = req.file.path;
// //     const outputFilePath = './uploads/code.cpp'; // Output C++ file path

// //     // Execute pseudocode to C++ conversion command
// //     const command = `python pseudocode_to_cpp.py ${pseudocodeFile} ${outputFilePath}`;

// //     exec(command, (error, stdout, stderr) => {
// //         if (error) {
// //             console.error(`Execution error: ${error}`);
// //             return;
// //         }
// //         if (stderr) {
// //             console.error(`Stderr: ${stderr}`);
// //             return;
// //         }

// //         // Read the generated C++ file and send its content to the client
// //         fs.readFile(outputFilePath, 'utf8', (err, data) => {
// //             if (err) {
// //                 console.error(`Error reading output file: ${err}`);
// //                 return;
// //             }
// //             res.render('result', { cppCode: data });
// //         });
// //     });
// // });

// // // Start the server
// // app.listen(port, () => {
// //     console.log(`Server listening at http://localhost:${port}`);
// // });
