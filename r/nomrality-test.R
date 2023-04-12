# Resource: https://www.datanovia.com/en/lessons/normality-test-in-r/
# https://sites.kowsarpub.com/ijem/articles/71904.html

# Load R Libraries
library("rcompanion")
library("tidyverse")
library("rstatix")
library("ggpubr")

# Declare Generic Function for Normality Test
normality_test <- function(data) {
  dump <- shapiro.test(data)
  p_value <- dump$p.value
  
  hist(data)
  
  if (p_value > 0.05) {
    cat("Normal distribution.", p_value)
  } else if (p_value < 0.05) {
    transformed <- transformTukey(data)
    shapiro_result <- shapiro.test(transformed)
    
    cat("Not normal distribution.", shapiro_result$p.value)
  }
}

# Convert Species variable to factor and then to numeric.
iris <- iris %>% mutate(Species = as.factor(Species))
iris$Species <- as.numeric(iris$Species)

# Assign iris dataset to data variable.
data <- iris

# Create a histogram of the Species variable.
hist(data$Species)

# Perform a normality test on the Species variable.
normality_test(data$Species)
