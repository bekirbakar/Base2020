"use strict";

// Example function to throw an error.
function throwError() {
    throw new Error("An error occurred");
}

try {
    throwError();
} catch (error) {
    const buffer = error.stack.split("at ")[1].trim();

    const result = {
        file: buffer.substring(
            buffer.indexOf("(") + 1,
            buffer.indexOf(".js") + 3
        ),
        function: buffer.substring(0, buffer.indexOf("(") - 1),
        line: buffer.substring(
            buffer.lastIndexOf("js:") + 3,
            buffer.lastIndexOf(":")
        )
    };

    console.log(result);
}
