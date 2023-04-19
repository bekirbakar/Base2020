"""
This module demonstrates various image processing techniques using OpenCV,
including:
- Harris corner detection.
- Color filtering (blue) in the HSV color space.
- Different types of thresholding.
- Flood filling.
- Morphological transformations.

It applies these techniques on an input image (1.jpg) and displays the results.
"""

import cv2
import matplotlib.pyplot as plt
import numpy as np

# Load the image.
filename = '1.jpg'
img = cv2.imread(filename)
plt.imshow(img)

# Convert the image to grayscale.
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray = np.float32(gray)

# Apply Harris corner detection.
dst = cv2.cornerHarris(gray, 2, 3, 0.04)

# Dilate the result for better marking of corners.
dst = cv2.dilate(dst, None)

# Mark the corners in the original image.
img[dst > 0.01 * dst.max()] = [0, 0, 255]
plt.imshow(img)

# Convert the image to HSV color space.
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
plt.imshow(hsv)

# Define the range of blue color in HSV.
lower_blue = np.array([110, 50, 50])
upper_blue = np.array([130, 255, 255])

# Threshold the HSV image to get only blue colors.
mask = cv2.inRange(hsv, lower_blue, upper_blue)

# Bitwise-AND mask and original image.
res = cv2.bitwise_and(img, img, mask=mask)

# Apply different thresholding techniques.
ret1, thresh1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
ret2, thresh2 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY_INV)
ret3, thresh3 = cv2.threshold(img, 127, 255, cv2.THRESH_TRUNC)
ret4, thresh4 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO)
ret5, thresh5 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO_INV)

# Display the thresholded images.
titles = ['Original Image', 'BINARY', 'BINARY_INV', 'TRUNC', 'TOZERO',
          'TOZERO_INV']
images = [img, thresh1, thresh2, thresh3, thresh4, thresh5]

for i in range(6):
    plt.subplot(2, 3, i + 1), plt.imshow(images[i], 'gray')
    plt.title(titles[i])
    plt.xticks([]), plt.yticks([])

# Read the image as grayscale.
im_in = cv2.imread('1.jpg', cv2.IMREAD_GRAYSCALE)

# Apply binary inverse thresholding.
th, im_th = cv2.threshold(im_in, 50, 100, cv2.THRESH_BINARY_INV)

# Flood fill the thresholded image.
im_flood_fill = im_th.copy()
h, w = im_th.shape[:2]
mask = np.zeros((h + 2, w + 2), np.uint8)
cv2.floodFill(im_flood_fill, mask, (0, 0), 255)

# Invert flood-filled image.
im_flood_fill_inv = cv2.bitwise_not(im_flood_fill)

# Combine the two images to get the foreground.
im_out = im_th | im_flood_fill_inv

# Display images.
cv2.imshow("Threshold Image", im_th)
cv2.imshow("Flood-filled Image", im_flood_fill)
cv2.imshow("Inverted Flood-filled Image", im_flood_fill_inv)
cv2.imshow("Foreground", im_out)
cv2.waitKey(0)

kernel = numpy.ones((2, 2), np.uint8)
black_hat = cv2.morphologyEx(im_out.copy(), cv2.MORPH_BLACKHAT, kernel)
cv2.imshow("Foreground", black_hat)
dilation = cv2.dilate(im_out.copy(), kernel, iterations=2)
cv2.imshow("Foreground", dilation)
gradient = cv2.morphologyEx(img, cv2.MORPH_GRADIENT, kernel)
cv2.imshow("Foreground", im_out)
