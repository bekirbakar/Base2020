/**
 * Module to manage pip package installation and verification.
 */

"use strict";

const config = {
    pathToPip: "",
    pathToWheels: "",
    packages: {},
    realPackages: []
}

/**
 * Runs the pip command synchronously to install the target package.
 * @param {string} targetPackage - The target package to install.
 */
function runPipCommandSync(targetPackage) {
    const path = require("path");
    const { execSync } = require("child_process");

    let command = `${config.pathToPip} install --no-index --find-links `;
    command += `${path.resolve(config.pathToWheels,
        "./separated_packages/" + targetPackage)} `;
    command += `${config.packages["numpy"]["index"]}`;

    console.log(`Command executed: ${command}`);
    console.log(`Result obtained: ${execSync(command)}`);
}

/**
 * Installs the packages listed in the configuration.
 */
function installPackages() {
    const { execSync } = require("child_process");

    let packages = config.realPackages;

    for (let item in packages) {
        if (Object.prototype.hasOwnProperty.call(packages, item)) {
            const pathWheelFiles = ".\\packages";
            const pathToPip = "interpreter\\Scripts\\pip.exe";

            let command = `${pathToPip} install ${packages[item]["index"]} `;
            command += `--no-index --find-links ${pathWheelFiles}`;

            const result = execSync(command);

            console.log(command);
            console.log(result);
        }
    }
}

/**
 * Confirms whether the required pip packages are installed or not.
 * @param {Object} installedPackages - The list of installed packages.
 */
function confirmPipPackages(installedPackages) {
    let requiredPackages = config.packages;

    for (let [key, value] of Object.entries(requiredPackages)) {
        if (key in installedPackages) {
            if (installedPackages[key] === value) {
                console.error("Everything seems okay.");
            } else {
                console.error(`Package ${installedPackages[key]} 
                versions do not match.`);
            }
        } else {
            console.error(`Package ${key} is not installed.`);
        }
    }
}

module.exports = {
    runPipCommandSync,
    installPackages,
    confirmPipPackages
}
