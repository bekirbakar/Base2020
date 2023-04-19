"""
This module demonstrates the use of Gabor filters, Otsu thresholding, Canny
edge detection, and morphological operations to process an image and detect
vertical lines.

The input image is processed using the following steps:
1. Apply Gabor filters to the grayscale image
2. Calculate the mean and standard deviation of the filtered image
3. Apply Otsu thresholding
4. Apply Canny edge detection
5. Perform dilation and erosion to detect vertical lines
6. Display the results
"""

import cv2 as opencv
import numpy as np


def build_filters():
    """Build a list of Gabor filters."""
    filters_ = []
    k_size = 31
    for theta in np.arange(0, np.pi, np.pi / 16):
        kern = opencv.getGaborKernel((k_size, k_size),
                                     4.0, theta, 10.0, 0.5, 0,
                                     ktype=opencv.CV_32F)
        kern /= 1.5 * kern.sum()
        filters_.append(kern)
    return filters_


def process(img, filters_):
    """Apply Gabor filters to the input image."""
    accum = np.zeros_like(img)
    for kern in filters_:
        f_img = opencv.filter2D(img, opencv.CV_8UC3, kern)
        np.maximum(accum, f_img, accum)

    return accum


# Read the input image and convert to grayscale.
imgBase = opencv.imread('')
imgGray = opencv.cvtColor(imgBase, opencv.COLOR_BGR2GRAY)

# Apply Gabor filters.
filters = build_filters()
trans = process(imgGray, filters)

# Calculate mean and standard deviation of the filtered image.
mean, std = opencv.meanStdDev(trans)

# Apply Otsu thresholding.
_, bw = opencv.threshold(imgGray, 1, 255, opencv.THRESH_OTSU)
opencv.bitwise_not(bw, bw)

# Apply Canny edge detection.
imgCanny = opencv.Canny(bw, 60, 255)

# Perform dilation and erosion to detect vertical lines.
se = opencv.getStructuringElement(opencv.MORPH_RECT, (20, 1), (-1, -1))
dilate = opencv.dilate(imgCanny, se, iterations=5)
erosion = opencv.erode(dilate, se, iterations=5)

# Display the results.
opencv.imshow('vertical_lines', erosion)
opencv.imshow('result', imgGray)
opencv.imshow('trans', trans)
opencv.imshow('bw', bw)
opencv.imshow('canny', imgCanny)
opencv.imshow('all', imgBase)
