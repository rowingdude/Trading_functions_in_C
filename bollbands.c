void bollinger_bands(double* close, int period, double* upper, double* middle, double* lower) {
    double sum = 0;
    double sum_sq = 0;
    int i;

    // Calculate the sum and sum of squares for the period
    for (i = 0; i < period; i++) {
        sum += close[i];
        sum_sq += close[i] * close[i];
    }

    // Calculate the middle band
    *middle = sum / period;

    // Calculate the standard deviation
    double variance = (sum_sq - sum * sum / period) / period;
    double stddev = sqrt(variance);

    // Calculate the upper and lower bands
    *upper = *middle + 2 * stddev;
    *lower = *middle - 2 * stddev;
}
