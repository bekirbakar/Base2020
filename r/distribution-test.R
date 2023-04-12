# Load the necessary library.
library("rcompanion")

# Input Data
data <- c(10, 28, 46, 55, 64, 72, 73, 52, 54, 34, 45, 49, 47, 84, 91, 45, 76,
          89, 2, 22, 12, 23)

# Calculate the mean and median of the data.
mean_data <- mean(data)
median_data <- median(data)

# Print the mean and median values.
cat("Mean: ", mean_data, "\n")
cat("Median: ", median_data, "\n")

# Plot the histogram of the data.
hist(data)

# Plot the normal histogram to visually compare with the data distribution.
plotNormalHistogram(data)

# Perform Shapiro-Wilk test to test the null hypothesis (H0) that the data
# comes from a normal distribution.
shapiro_test <- shapiro.test(data)

# Print the test results
cat("Shapiro-Wilk Test Results: \n")
print(shapiro_test)

# Parametric test, non-parametric test.
# H0: Null hypothesis.
# H1: Alternative hypothesis. Central tendency theorem.

# Interpretation of test results
if (shapiro_test$p.value < 0.05) {
  cat("The null hypothesis (H0) is rejected.",
      "The data does not follow a normal distribution.\n")
} else {
  cat("The null hypothesis (H0) cannot be rejected.",
      "The data follows a normal distribution.\n")
}
