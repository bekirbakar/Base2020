# Load R Libraries
library("car")
library("dplyr")
library("ggpubr")

# Load ToothGrowth dataset.
tooth_growth_data <- ToothGrowth

# Set seed for reproducibility.
set.seed(1234)

# Display a random sample of 10 rows from tooth_growth_data.
dplyr::sample_n(tooth_growth_data, 10)

# Create a density plot of Tooth Length.
ggdensity(tooth_growth_data$len, main = "Density Plot of Tooth Length",
          xlab = "Tooth length")

# Create a Q-Q plot of Tooth Length.
ggqqplot(tooth_growth_data$len)

# Create a Q-Q plot using car package.
qqPlot(tooth_growth_data$len)

# Perform Shapiro-Wilk test for normality.
shapiro.test(tooth_growth_data$len)

# Perform t-test.
x <- tooth_growth_data$len
y <- tooth_growth_data$dose
t.test(y, x)
