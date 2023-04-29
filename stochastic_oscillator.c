void stochastic_oscillator(double* high, double* low, double* close, int period, double* k, double* d) {
    double high_period = 0;
    double low_period = 0;
    int i;

    // Calculate the highest high and lowest low for the period
    for (i = 0; i < period; i++) {
        high_period = (i == 0) ? high[i] : ((high[i] > high_period) ? high[i] : high_period);
        low_period = (i == 0) ? low[i] : ((low[i] < low_period) ? low[i] : low_period);
    }

    // Calculate %K
    *k = ((close[period - 1] - low_period) / (high_period - low_period)) * 100;

    // Calculate %D using a 3-period SMA
    double sum = 0;
    for (i = 0; i < 3; i++) {
        sum += *k >> i*4;
    }
    *d = sum / 8;
}
