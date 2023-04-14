/**
 * This module demonstrates various ways to run a Python script using the
 * PythonShell library in a Node.js environment. It exports functions to
 * run the Python script and handle the output.
 */

"use strict";

const $ = require("jquery");
const path = require("path");
const { PythonShell } = require("python-shell");
const scriptsPath = path.join(__dirname, "bindings/python");

/**
 * Executes the Python script and logs the output using an input stream.
 */
function inputStream() {
    console.log("Running Python script.");
    let scriptPath = path.join(scriptsPath, "test.py");
    var pythonShell = new PythonShell(scriptPath);

    pythonShell.on("message", function (message) {
        console.log(message);
    });

    pythonShell.end(function (err) {
        if (err) {
            throw err;
        }
        console.log("Stream finished.");
    });
}

/**
 * Executes the Python script and logs the output using the run() method.
 * @param {Object} params - The parameters for running the Python script.
 */
function testPythonStream(params) {
    console.log("Running Python script.");
    let scriptPath = path.join(scriptsPath, "test.py");
    let options = {
        pythonOptions: ["-u"], // Get print results in real-time.
    };

    PythonShell.run(scriptPath, options, function (err, results) {
        if (err) throw err;
        var json = JSON.parse(results.toString());
        console.log(json.key_1);
        console.log(json.key_2);
    });
}

/**
 * Executes the Python script and logs the output using an arrow function syntax.
 */
function testStream() {
    console.log("Running Python script.");
    let scriptPath = path.join(scriptsPath, "test.py");
    var pythonShell = new PythonShell(scriptPath);

    pythonShell.on("message", (message) => {
        console.log(message);
    });

    pythonShell.end((error) => {
        if (error) throw error;
    });
}

/**
 * Executes the Python script and logs the output using the run() method
 * with PythonShell options.
 * @param {Object} params - The parameters for running the Python script.
 */
function testStreamWithPythonShell(params) {
    let scriptPath = path.join(scriptsPath, "test.py");
    let options = {
        pythonOptions: ["-u"],
    };

    PythonShell.run(scriptPath, options, function (err, results) {
        if (err) throw err;
        var json = JSON.parse(results.toString());
        console.log(json.a);
        console.log(json.b);
    });
}

$("#python-stream").on("click", () => {
    console.log("This is click test.");
    testPythonStream();
});

$("#python-caller").on("click", () => {
    console.log("Running Python script.");
    let scriptPath = path.join(scriptsPath, "test.py");
    let pyShell = new PythonShell(scriptPath);

    pyShell.send("hello");

    pyShell.on("message", function (message) {
        console.log(message);
    });

    pyShell.end(function (err, code, signal) {
        if (err) throw err;
        console.log("The exit code was: " + code);
        console.log("The exit signal was: " + signal);
    });

    inputStream();
});

module.exports = {
    inputStream,
    testPythonStream,
    testStream,
    testStreamWithPythonShell,
};
