"""
A module for interacting with a local SQLite database using Python. This module
provides a `DataProvider` class, which allows for opening a connection to a
local SQLite database, executing SQL queries and statements, and closing the
connection to the database. The `DataProvider` class can be used as a context
manager for easy connection management.
"""

__all__ = ['DataProvider']

import os
import sqlite3


class DataProvider:
    """
    A class for interacting with a local SQLite database.
    """

    def __init__(self, source, table_query):
        """
        Initializes a new DataProvider instance.

        Args:
            source (str): The file path of the SQLite database.
            table_query (str): The SQL query used to create the database table.
        """
        self.source = source
        self.table_query = table_query
        self.connection = None
        self.cursor = None

    def __enter__(self):
        """
        Creates a new SQLite database table if it doesn't exist, opens a
        connection.

        Returns:
            :obj:`DataProvider`: The DataProvider instance.
        """
        if not os.path.exists(self.source):
            self.init_database()

        self.connection = sqlite3.connect(self.source)
        self.cursor = self.connection.cursor()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        """
        Closes the connection to the SQLite database.
        """
        self.close()

    @staticmethod
    def version():
        """
        Returns the version of the SQLite database.

        Returns:
            str: The version of the SQLite database.
        """
        return sqlite3.version

    def init_database(self):
        """
        Creates a new SQLite database table.
        """
        connection = sqlite3.connect(self.source)
        cursor = connection.cursor()
        cursor.execute(self.table_query)
        connection.commit()
        connection.close()

    @staticmethod
    def dictionary_factory(cursor, row):
        """
        Returns a dictionary of row values with column names as keys.

        Args:
            cursor (:obj:`sqlite3.Cursor`): The database cursor object.
            row (Tuple): A row of data from the database table.

        Returns:
            dict: A dictionary of row values with column names as keys.
        """
        return {col[0]: row[idx] for idx, col in enumerate(cursor.description)}

    def open(self):
        """
        Opens a connection to the SQLite database and sets the row factory.

        Returns:
            :obj:`sqlite3.Cursor`: The database cursor object.
        """
        self.connection = sqlite3.connect(self.source)
        self.connection.row_factory = self.dictionary_factory
        self.cursor = self.connection.cursor()

        return self.cursor

    def close(self):
        """
        Closes the connection to the SQLite database.
        """
        self.connection.close()
        self.cursor = None

    def write(self, sql, data=()):
        """
        Executes an SQL statement with the given data.

        Args:
            sql (str): The SQL statement to execute.
            data (tuple): The data to insert into the statement.

        Raises:
            sqlite3.Error: If there is an error executing the statement.
        """
        self.open()
        self.cursor.execute(sql, data)
        self.connection.commit()

    def get(self, sql, data=()):
        """
        Executes an SQL query with the given data.

        Args:
            sql (str): The SQL query to execute.
            data (tuple): The data to insert into the query.

        Returns:
            list: The results of the query as a list of dictionaries.
        """
        self.open()
        self.cursor.execute(sql, data)
        return self.cursor.fetchall()
