"""
This module provides a class for comparing the similarity of two documents
using FastText embeddings and cosine similarity. The class pre-processes the
text data, removes stop words, and computes document embeddings.
"""

import pathlib
import re

import fasttext
import numpy
from scipy.spatial import distance


class DocumentSimilarity:
    """
    A class for comparing the similarity of two documents using FastText
    embeddings and cosine similarity.
    """

    def __init__(self, path_to_stop_words=None, path_to_fasttext_model=None):
        """
        Initialize the DocumentSimilarity object with optional paths to
        stop words file and FastText model.

        Args:
            path_to_stop_words (str, optional): Path to the stop words file.
            path_to_fasttext_model (str, optional): Path to the FastText model.
        """
        self.path_to_stop_words = path_to_stop_words or 'stop-words.txt'
        self.path_to_fasttext_model = path_to_fasttext_model or 'cc.tr.300.bin'
        self.model = fasttext.load_model(self.path_to_fasttext_model)
        self.initial_document = None
        self.words = None

    def load_data_from_txt(self, path_to_file):
        """
        Load text data from a file.

        Args:
            path_to_file (str): Path to the text file.
        """
        self.initial_document = pathlib.Path(path_to_file).read_text()

    def preprocessing(self):
        """
        Preprocess the text data by removing punctuation and digits.
        """
        buffer = re.sub(r'[,.;@#?!&$]+ *', ' ', self.initial_document)
        pattern = r'\d+'
        matches = re.findall(pattern, buffer)
        sorted_matches = sorted(matches, key=len)

        for match in reversed(sorted_matches):
            buffer = buffer.replace(str(match), '')

        buffer = buffer.split(' ')
        self.words = [w for w in buffer if w]

    def remove_stop_words(self):
        """
        Remove stop words from the preprocessed text data.
        """
        with open(self.path_to_stop_words, 'r') as file_handler:
            stop_words = file_handler.read().split()

        self.words = [word for word in self.words if word not in stop_words]

    def get_embeddings(self):
        """
        Compute FastText embeddings for the preprocessed text data.

        Returns:
            tuple: A tuple containing the individual word embeddings and
            the sum of all word embeddings.
        """
        embeddings = numpy.zeros(shape=(len(self.words), 300))
        for index, word in enumerate(self.words):
            embeddings[index] = self.model.get_word_vector(word)

        sum_of_embeddings = numpy.sum(embeddings, axis=0)

        return embeddings, sum_of_embeddings

    @staticmethod
    def get_cosine_similarity(u, v):
        """
        Calculate the cosine similarity between two vectors.

        Args:
            u (numpy.ndarray): The first vector.
            v (numpy.ndarray): The second vector.

        Returns:
            float: The cosine similarity between the two vectors.
        """
        return 1. - distance.cosine(u, v)
