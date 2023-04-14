/**
 * Module for language detection and document language detection.
 */

const path = require("path");
const franc = require("franc");
const cld = require("cld");
const textract = require("textract");

/**
 * Detects language of the given text using CLD and Franc.
 * @param {string} text - The input text for language detection.
 * @param {boolean} isHtml - Indicates if the input text is HTML.
 * @param {string} hint - Language hint for the detection algorithm.
 */
function detect(text, isHtml, hint) {
    const options = {
        isHTML: !!isHtml,
        languageHint: hint,
        encodingHint: "ISO_8859_5",
        tldHint: "bg",
        httpHint: "bg",
    };

    let values = [];

    let x = Promise.all([cld.detect(text, options)]).then((v) => {
        values.push(v);

        return values;
    }).then(console.log(values));
}

/**
 * Detects the language of the document based on its content.
 * @param {string} pathToDocument - Path to the document file.
 * @returns {string} language - Detected language of the document.
 */
function detectDocumentLanguage(pathToDocument) {
    const extension = path.extname(pathToDocument);

    let language = null;
    const textractScope = [
        ".html", ".htm", ".atom", ".rss", ".md", ".epub", ".xml", ".xsl",
        ".pdf", ".doc", ".docx", ".odt", "ott", ".rtf", ".xls", "xlsx",
        ".xlsb", ".xlsm", ".xltx", ".csv", ".ods", ".ots", ".pptx", ".potx",
        ".odp", "otp", ".odg", ".otg", ".png", ".jpg", ".gif", ".dxf", ".txt",
    ];

    if (textractScope.includes(extension)) {
        textract.fromFileWithPath(pathToDocument, (error, text) => {
            if (error) throw error;

            const subText = text.substring(0, 1000);

            language = franc.all(subText)[0][0];
        });
    }
    else {
        console.log("Extension is not supported.");
    }

    return language;
}

module.exports = {
    detect,
    detectDocumentLanguage
};
