"use strict";

/**
 * This module provides two functions for managing Python dependencies:
 * 1. runBatchScript - Executes a batch script with the provided configuration.
 * 2. approvePython - Verifies installed Python packages using the provided pip
 * path.
 */

const { spawn, execFile } = require("child_process");

let config = {
    pathToPipBatch: "",
    pathToInterpreter: "",
    pathToPip: "",
    command: ""
}

function runBatchScript() {
    let batchFile = config.pathToPipBatch + " " + config.command + " ";
    batchFile += config.pathToInterpreter;

    let bat = spawn("cmd.exe", ["/c", batchFile.toString()]);

    bat.stdout.on("data", (data, err) => {
        if (err) console.error(err);

        let result = String.fromCharCode.apply(null, data);

        console.log(result);
    });
}

async function approvePython() {
    return new Promise(function (resolve, reject) {
        let returnValue = {};

        if (isExist()) {

        }
        else {

        }

        execFile(config.pathToPip, ["list"], (error, stdout, stderr) => {
            if (error) {
                reject(error);
                console.log(stderr);
            }

            if (stderr) {
                returnValue["error"] = stderr;
            }

            if (stdout) {
                let installedPackages = {};
                let results = stdout.split("\r\n");

                results = results.filter(function (element) {
                    return element;
                })

                results.forEach(function (item) {
                    try {
                        if (item) {
                            const m = item.split(" ")[0];
                            installedPackages[m] =
                                /\(([^)]+)\)/.exec(item.split(" ")[1])[1];
                        }
                    }
                    catch (err) {
                        throw err;
                    }
                })

                confirmPipPackages(installedPackages);

                returnValue["out"] = results;
                resolve(returnValue);
            }
        });
    })
}

module.exports = {
    approvePython,
    runBatchScript
}
