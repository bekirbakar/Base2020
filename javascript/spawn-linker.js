/**
 * This module runs a Python script using Node.js and captures its output
 * (stdout and stderr). It parses the output as JSON and logs it to the console.
 * In case of any error, it logs the error message and exits with a non-zero
 * status code.
 */

"use strict";

const { spawn } = require("child_process");

/**
 * Creates a logging function with a given name.
 * @param {string} name - The name to display in log messages.
 * @returns {function} - A function that logs messages with the given name.
 */
const logOutput = (name) => (message) => console.log(`[${name}] ${message}`);

/**
 * Runs the Python script with the given arguments and resolves the output as
 * JSON.
 * @returns {Promise} - A promise that resolves to the JSON output of the
 * script.
 */
function run() {
    return new Promise((resolve, reject) => {
        // File (script.py): simple python code that prints json data.
        const process = spawn("python", ["./script.py", "my", "args"]);

        const stdoutData = [];
        process.stdout.on("data", (data) => {
            stdoutData.push(data.toString());
            logOutput("stdout")(data);
        });

        const stderrData = [];
        process.stderr.on("data", (data) => {
            stderrData.push(data.toString());
            logOutput("stderr")(data);
        });

        process.on("exit", (code, signal) => {
            logOutput("exit")(`${code} (${signal})`);
            if (code !== 0) {
                reject(new Error(stderrData.join("\n")));
                return;
            }
            try {
                resolve(JSON.parse(stdoutData[0]));
            } catch (e) {
                reject(e);
            }
        });
    });
}

(async () => {
    try {
        const output = await run();
        logOutput("main")(output.message);
        process.exit(0);
    } catch (e) {
        console.error("Error during script execution: ", e.stack);
        process.exit(1);
    }
})();
