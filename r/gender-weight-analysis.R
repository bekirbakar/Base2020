# Install R Packages
install.packages(c("datarium", "ggplot2", "ggpubr", "tidyverse", "broom",
                   "AICcmodavg"))

# Load R Packages
library(tidyverse)
library(ggpubr)
library(rstatix)

# Load data into R and show a sample of two groups
data("genderweight", package = "datarium")
sample_n_by(genderweight, group, size = 2)

# Compute some summary statistics by groups: mean and standard deviation
genderweight %>%
  group_by(group) %>%
  get_summary_stats(weight, type = "mean_sd")

# Save the data in two different vectors
women_weight <- genderweight %>%
  filter(group == "F") %>%
  pull(weight)

men_weight <- genderweight %>%
  filter(group == "M") %>%
  pull(weight)

# Compute t-test using the two vectors
res <- t.test(women_weight, men_weight)

# Alternatively, compute t-test using the formula interface
res <- t.test(weight ~ group, data = genderweight)
