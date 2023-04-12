# Resource: 
# https://bit.ly/33Hca8e

# Load ggplot2 library.
library("ggplot2")

# Load the iris dataset and display its structure.
data("iris")
str(iris)

# Create a scatter plot of Petal.Width vs Petal.Length colored by Species.
ggplot(data = iris, aes(x = Petal.Width, y = Petal.Length)) +
  geom_point(aes(color = Species))

# Normalize the iris dataset using min-max normalization (columns 1 to 4).
iris_norm <- as.data.frame(apply(iris[, 1:4], 2, 
                                 function(x) (x - min(x)) / (max(x) - min(x))))
iris_norm$Species <- iris$Species

# Display the structure and summary of the normalized dataset.
str(iris_norm)
summary(iris_norm)

# Create a scatter plot of the normalized dataset.
ggplot(data = iris_norm, aes(x = Petal.Width, y = Petal.Length)) + 
  geom_point(aes(color = Species))

# Normalize the iris dataset using min-max normalization (rows).
iris_norm <- as.data.frame(
  t(apply(iris[1:4], 1, function(x) (x - min(x)) / (max(x) - min(x))))
)

# Display the summary of the row-normalized dataset.
summary(iris_norm)
