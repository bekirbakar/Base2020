"""
This script demonstrates how to use a custom OCR library (Ocr.dll) in Python
using ctypes for loading the library and calling its functions.

It provides an example of how to use the tesseract_test function to perform
OCR on an image file.
"""

import os
import ctypes
import nt

# Define the path to the OCR library and load it using ctypes.
dll_path = os.path.join(os.getcwd(), '..\\lib')
dll_file = os.path.join(dll_path, 'Ocr.dll')
dll = ctypes.CDLL(dll_file, nt._LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR)

# Set up the argument and return types for the tesseract_test function.
dll.tesseract_test.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
dll.tesseract_test.restype = ctypes.c_char_p

# Call the sum function as an example of using the library.
print(dll.sum)
print(dll.sum(1000, 2000))

# Define the paths for the tessdata and the image to be processed.
tessdata_source = os.path.join(os.getcwd(), '../tessdata').encode()
image_source = os.path.join(os.getcwd(), '../data/sample.png').encode()

# Create a buffer to store the OCR results and call the tesseract_test function.
result_buffer = ctypes.create_string_buffer(4096)
ocr_result = dll.tesseract_test(tessdata_source, image_source, result_buffer)

# Print the results.
print(dll.tesseract_test)
print(ocr_result)
