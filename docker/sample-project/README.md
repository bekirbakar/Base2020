# Example Project

This is an example Flask application with Docker, demonstrating a "Hello World" API and an API to return unique words in alphabetic order from a given text.

## Prerequisites

- [Python](https://www.python.org/downloads/)
- [Docker](https://docs.docker.com/get-docker/)
- [Postman](https://www.postman.com/downloads/) (optional)

## Getting Started

Build and run application by running `./build_and_run.sh` scripts.
Once, it is done, the application will be running inside a Docker container and listening on port 8080.

## Testing the APIs

### Using a Web Browser

Visit `http://localhost:8080` in your web browser to see the "Hello World" API in action.

### Using Postman

#### Hello World API

1. Open Postman
2. Create a new GET request.
3. Enter the Following URL: `http://localhost:8080`
4. Click "Send" to execute the request.

You should see the response "Hello, World!".

#### Unique Words API

1. Open Postman
2. Create a new POST request.
3. Enter the following URL: `http://localhost:8080/unique-words`
4. Click on the "Body" tab and select the "raw" option.
5. Change the content type to "JSON" using the dropdown menu.
6. Enter the following JSON object in the request body given below.
7. Click "Send" to execute the request. You should receive a JSON array containing the unique words in the provided text, sorted alphabetically.

Request Body

```json
{
"text": "This is an example text with some repeated words. This text will be used to test the unique words API."
}
```
