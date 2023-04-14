/**
 * This module provides three functions to fix and manage annotation files:
 * 1. fixVottFile - Updates the paths of assets in a VOTT file and saves the
 * modified file.
 * 2. fixAnnotations - Updates the asset paths in annotation JSON files.
 * 3. missingAnnotations - Identifies image files that are missing annotations.
 */

"use strict";

const fileUrl = require("file-url");
const { resolve, basename } = require("path");
const { readFileSync, writeFileSync } = require("fs");

const protocol = require("protocol.json");
const { fileExplorer } = require("file-explorer.js");


const fixVottFile = () => {
    let vottFile = readFileSync(protocol.vottFile).toString();
    vottFile = JSON.parse(vottFile);

    for (const [key, value] of Object.entries(vottFile["assets"])) {
        value.path = resolve(protocol.fixedImages, value.name);
        value.path = fileUrl(value.path);
        vottFile["assets"][key].path = value.path;
    }

    const filename = resolve(__dirname, "../data/fixed.vott");
    writeFileSync(filename, JSON.stringify(vottFile, null, 2));
};

const fixAnnotations = () => {
    fileExplorer({
        root: protocol.sharedAnnotations,
        scope: [".json"],
        exclusions: [],
        callback: (result) => {
            result.forEach((item) => {
                let content = readFileSync(item.path).toString();
                content = JSON.parse(content);

                let source = basename(content["asset"].path);
                source = resolve(protocol.fixedImages, source);
                source = fileUrl(source);

                content["asset"].path = source;

                let fp = resolve(protocol.annotations, basename(item.path));
                writeFileSync(fp, JSON.stringify(content, null, 2));
            });
        }
    });
};

const missingAnnotations = () => {
    let allFiles = [];
    let annotatedFiles = [];

    fileExplorer({
        root: protocol.fixedImages,
        scope: null,
        exclusions: [],
        callback: (result) => {
            result.forEach(item => {
                allFiles.push(item.path);
            });

            const fp = resolve(__dirname, "../data/all-files.json");
            writeFileSync(fp, JSON.stringify(allFiles, null, 2));
        }
    });

    fileExplorer({
        root: protocol.annotations,
        scope: [".json"],
        exclusions: [],
        callback: (result) => {
            result.forEach(item => {
                let file = readFileSync(item.path).toString();
                file = JSON.parse(file);
                annotatedFiles.push(file["asset"].path);
            });

            const fp = resolve(__dirname, "../data/annotated-files.json");
            writeFileSync(fp, JSON.stringify(annotatedFiles, null, 2));
        }
    });

    let notAnnotatedFiles = [];
    allFiles.forEach(value => {
        if (!annotatedFiles.includes(value)) {
            notAnnotatedFiles.push(value);
        }
    }
    );

    const fp = resolve(__dirname, "../data/not-annotated-files.json");
    writeFileSync(fp, JSON.stringify(notAnnotatedFiles, null, 2));
};

module.exports = {
    fixAnnotations,
    fixVottFile,
    missingAnnotations
};
