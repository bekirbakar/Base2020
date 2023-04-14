/**
 * This module validates a JSON object against a predefined schema using
 * jsonschema package. It demonstrates how to define a JSON schema and
 * validate a sample JSON object against it.
 */

"use strict";

const { Validator } = require("jsonschema");

const jsonValidator = new Validator();

const schema = {
    type: "object",
    properties: {
        serverURL: {
            type: "string",
        },
        urls: {
            type: "object",
            properties: {
                homepage: {
                    type: "string",
                },
                apiUrl: {
                    type: "string",
                },
                serverUrl: {
                    type: "string",
                },
            },
            "required": ["serverUrl"],
        },
        pingDelay: {
            type: "integer",
        },
        supportedFiles: {
            type: "array",
        },
    },
    required: [
        "version",
        "urls",
        "supportedFiles",
    ],
};

const sampleJson = {
    "version": "1.0.0",
    "urls": {
        "homepage": "",
        "apiUrl": "",
        "serverUrl": "",
    },
    "supportedFiles": [
        ".txt",
        ".json",
        ".log",
        ".htm",
        ".html",
        ".xml",
        ".pdf",
        ".doc",
        ".docx",
        ".xls",
        ".xlsx",
        ".ppt",
        ".pptx",
        ".png",
        ".jpg",
        ".jpeg",
        ".tiff",
        ".zip",
        ".pst",
        ".ost",
    ],
};

// Validate the sample JSON against the schema.
const validation = jsonValidator.validate(sampleJson, schema).errors;

if (validation.length > 0) {
    console.log(validation);
} else {
    console.log("JSON matches the schema.");
}
