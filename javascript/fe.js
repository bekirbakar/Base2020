/**
 * Module Description:
 * This module uses the 'sqlite3' package to interact with a SQLite database.
 * It scans a specified directory and its subdirectories for files with
 * supported extensions.
 * Information about these files and directories, such as their names and
 * modification times, is stored in the database.
 */

'use strict';

const fs = require('fs');
const path = require('path');
const { Database } = require('sqlite3').verbose();

// Define SQL queries and file paths.
const sql = {}
const sqlFile = {}
const pathToDatabase = ''

// Initialize a new database connection.
let db = new Database(pathToDatabase, (err) => {
    if (err) {
        console.error('Could not connect to database!', err);
    } else {
        console.log('Connected to database!');
    }
});

// Initialize the database with data from a SQL file.
function initDatabase() {
    const sqlData = fs.readFileSync(sqlFile).toString();
    db.serialize(() => {
        const sqlArray = sqlData.toString().split(';');

        sqlArray.forEach((query) => {
            if (query) {
                db.run(query, (err) => {
                    if (err) {
                        console.error(err);
                        throw err;
                    }
                });
            }
        });
    });
}

// Scan a directory and its subdirectories for files with supported extensions.
function recursiveScan(directory, scanLimit, supportedFiles) {
    let stats;
    let filesData = [];
    let foldersData = [];

    let directoryList = fs.readdirSync(directory);

    directoryList.forEach(function (item) {
        file = `${directory}/${item}`;
        stats = fs.statSync(file);

        let isDirectory = fs.statSync(file).isDirectory();

        if (isDirectory) {
            console.log(stats.mtimeMs);

            foldersData = [
                file,
                stats.atime.toISOString(),
                stats.mtime.toISOString(),
                stats.ctime.toISOString(),
                stats.birthtime.toISOString(),
                0,
                0,
            ];

            db.all(sql.folders.insertData, foldersData, (err) => {
                if (err) {
                    console.log('Folder insert error.');

                    db.all(sql.folders.mtime, foldersData[0],
                        function (err, rows) {
                            if (err) {
                                console.log('Folder select error.');
                                console.log(err);
                            }

                            rows.forEach(function (row) {
                                let baseTime = row.mtime;
                                let currentTime = foldersData[2];

                                if (baseTime !== currentTime) {
                                    foldersData[5] = 1;

                                    let x = [foldersData[1],
                                    foldersData[2],
                                    foldersData[3],
                                    foldersData[4],
                                    foldersData[5],
                                    foldersData[6],
                                    foldersData[0]];

                                    db.all(sql.folders.updateData, x,
                                        function (err) {
                                            console.log(err);
                                        });

                                    recursiveScan(file, scanLimit,
                                        supportedFiles);
                                } else {
                                    console.log('No modification');
                                }
                            });
                        });

                    recursiveScan(file, scanLimit, supportedFiles);
                } else {
                    recursiveScan(file, scanLimit, supportedFiles);
                }
            });
        } else if (supportedFiles.includes(path.extname(file))) {
            filesData.push(file);

            if (filesData.length >= scanLimit) {
                let buffer = [];
                for (let i = 0; i < filesData.length; i++) {
                    stats = fs.statSync(filesData[i]);

                    buffer[i] = [filesData[i],
                    path.extname(filesData[i]),
                    stats.atime.toISOString(),
                    stats.mtime.toISOString(),
                    stats.ctime.toISOString(),
                    stats.birthtime.toISOString(),
                    stats.size, 0, 0, 0];
                }

                for (let j = 0; j < buffer.length; j++) {
                    db.run(sql.files.insertData, buffer[j], (err) => {
                        if (err) {
                            buffer[j][7] = 1;

                            db.run(sql.files.replaceData, buffer[j],
                                function (err) {
                                    if (err) {
                                        throw err;
                                    }
                                });
                        }
                    });
                }

                filesData = [];
            }
        }
    });

    if (filesData.length > 0) {
        for (let i = 0; i < filesData.length; i++) {
        }
    }

    return true;
}
