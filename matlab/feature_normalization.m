function [X_norm, mu, sigma] = featureNormalize(X)
% featureNormalize Normalizes the features in X
%    [X_norm, mu, sigma] = featureNormalize(X) returns a normalized version
%    of X where the mean value of each feature is 0 and the standard deviation
%    is 1.

% Initialize variables.
X_norm = X;
mu = zeros(1, size(X, 2));
sigma = zeros(1, size(X, 2));

% Compute the mean and standard deviation of each feature.
mu = mean(X);
sigma = std(X);

% Normalize the features by subtracting the mean and dividing by the standard
% deviation.
X_norm = bsxfun(@minus, X, mu);
X_norm = bsxfun(@rdivide, X_norm, sigma);

end
