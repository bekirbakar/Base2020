/**
 * This module reads annotation data from JSON files, generates a report, and
 * creates plots using nodeplotlib. It exports functions to create the report,
 * plot the bar chart, and plot another chart.
 */

"use strict";

const { resolve } = require("path");
const { plot, stack } = require("nodeplotlib");
const { readFileSync, writeFileSync } = require("fs");

const protocol = require("protocol.json");
const { fileExplorer } = require("file-explorer.js");

/**
 * Creates a report with aggregated tag information from JSON annotation files.
 */
const createReport = () => {
    let tags = readFileSync(protocol.tags).toString();
    tags = JSON.parse(tags);

    fileExplorer({
        root: protocol.annotations,
        scope: [".json"],
        exclusions: [],
        callback: (result) => {
            result.forEach(item => {
                if (item.path) {
                    let buffer = readFileSync(item.path).toString();
                    buffer = JSON.parse(buffer);
                    buffer["regions"].forEach(region => {
                        region["tags"].forEach(t => {
                            tags[t]["count"] += 1;
                            tags[t]["files"].push(item.path);
                        });
                    });
                }
            });

            const fp = resolve(__dirname, "report.json");
            writeFileSync(fp, JSON.stringify(tags, null, 2));
        }
    });
};

/**
 * Plots a bar chart of the tag counts.
 */
const plotBar = () => {
    const r = JSON.parse(readFileSync(
        resolve(__dirname, "report.json")).toString()
    );

    const data = [{
        x: [],
        y: [],
        type: "bar"
    }];

    for (let [key] of Object.entries(r)) {
        data[0]["x"].push(key);
        data[0]["y"].push(r[key]["count"]);
    }

    stack(data);

    plot();
};

/**
 * Plots another chart based on the report data.
 */
function plotAnother() {
    const data = JSON.parse(readFileSync(
        resolve(__dirname, "./report.json")).toString()
    );

    const keys = {};
    for (let [key] of Object.entries(data)) {
        keys[key] = [];
    }

    let indicator = 0;
    let count = 0;
    const ids = {};
    for (let [key] of Object.entries(data)) {
        data[key]["files"].forEach(file => {

            count += 1;

            if (!ids[key].includes(file)) {
                paths.push(d);
                ids.push(indicator);

                indicator += 1;
            }

            keys[key].push(indicator);
        });
    }

    console.log(keys);
}

module.exports = {
    createReport,
    plotBar,
    plotAnother
};
