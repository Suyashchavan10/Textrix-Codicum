const express = require('express');
const multer = require('multer');
const fs = require('fs');
const { exec } = require('child_process');

const app = express();
const port = 3000;

// Set up multer for handling file uploads
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, './uploads/');
    },
    filename: (req, file, cb) => {
        cb(null, file.originalname);
    }
});
const upload = multer({ storage: storage });

// Serve static files (CSS, JS) from the public directory
app.use(express.static('public'));

// Set view engine to EJS
app.set('view engine', 'ejs');

// Home route - serve HTML form
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/public/index.html');
});

// Upload route - handle file upload
app.post('/upload', upload.single('pseudocodeFile'), (req, res) => {
    const pseudocodeFile = req.file.path;
    const outputFilePath = './uploads/code.cpp'; // Output C++ file path

    // Execute pseudocode to C++ conversion command
    const command = `python pseudocode_to_cpp.py ${pseudocodeFile} ${outputFilePath}`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Execution error: ${error}`);
            return;
        }
        if (stderr) {
            console.error(`Stderr: ${stderr}`);
            return;
        }

        // Read the generated C++ file and send its content to the client
        fs.readFile(outputFilePath, 'utf8', (err, data) => {
            if (err) {
                console.error(`Error reading output file: ${err}`);
                return;
            }
            res.render('result', { cppCode: data });
        });
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
});
