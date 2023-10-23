#include <math.h> // for sqrt

void bollinger_bands(double* close, int period, double* upper, double* middle, double* lower) {
    double sum = 0.0;
    double sum_sq = 0.0;
    double inv_period = 1.0 / period; // Pre-compute the inverse to replace division with multiplication
    int i;

    // Calculate the sum and sum of squares for the period
    for (i = 0; i < period; ++i) {
        sum += close[i];
        sum_sq += close[i] * close[i];
    }

    // Calculate the middle band using pre-computed inverse
    *middle = sum * inv_period;

    // Calculate the standard deviation using pre-computed inverse
    double variance = (sum_sq - sum * sum * inv_period) * inv_period;
    double stddev = sqrt(variance);

    // Calculate the upper and lower bands
    *upper = *middle + 2.0 * stddev;
    *lower = *middle - 2.0 * stddev;
}
