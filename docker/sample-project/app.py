# -*- coding: utf-8 -*-

from flask import Flask, jsonify, request

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello, World!'


@app.route('/unique-words', methods=['POST'])
def unique_words():
    data = request.get_json()
    if not data:
        return jsonify({'error': 'No JSON data provided!'}), 400

    text = data.get('text')
    if not text:
        return jsonify({'error': 'No "text" field in JSON data!'}), 400

    unique_words = sorted({word.strip() for word in text.split()})
    return jsonify(unique_words)


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
