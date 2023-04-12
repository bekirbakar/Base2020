# Multiple T-test
# Resource: https://bit.ly/3v1xa5T

# Load required R packages.
library("tidyverse")
library("rstatix")
library("ggpubr")

# Prepare data and inspect a random sample of the data.
data <- iris %>%
  filter(Species != "setosa") %>%
  as_tibble()

data %>% sample_n(6)

# Transform the data into long format.
data.long <- data %>%
  pivot_longer(-Species, names_to = "variables", values_to = "value")

data.long %>% sample_n(6)

# Run multiple T-tests, adjust p-values and add significance levels.
stat.test <- data.long %>%
  group_by(variables) %>%
  t_test(value ~ Species) %>%
  adjust_pvalue(method = "BH") %>%
  add_significance()

stat.test

# Create multi-panel Box plots with t-test p-values.
plot_handler <- ggboxplot(data.long, x = "Species", y = "value",
                          fill = "Species", palette = "npg", legend = "none",
                          ggtheme = theme_pubr(border = TRUE)) + 
  facet_wrap(~variables)

# Add statistical test p-values.
stat.test <- stat.test %>% add_xy_position(x = "Species")
plot_handler + stat_pvalue_manual(stat.test, label = "p.adj.signif")

# Create individual Box plots with t-test p-values.
graphs <- data.long %>%
  group_by(variables) %>%
  doo(~ggboxplot(data =., x = "Species", y = "value",
                 fill = "Species", palette = "npg", legend = "none",
                 ggtheme = theme_pubr()), result = "plots")

graphs

# Add statistical tests to each corresponding plot.
variables <- graphs$variables
for (i in 1:length(variables)) {
  graph.i <- graphs$plots[[i]] + labs(title = variables[i]) +
    stat_pvalue_manual(stat.test[i, ], label = "p.adj.signif")
  
  print(graph.i)
}
