#include <stdio.h>
#include <stdlib.h>

/**
 * Calculates the exponential moving average (EMA) of a given array of float values.
 * The EMA is calculated using the specified period and alpha value.
 *
 * @param[in]  data    Pointer to an array of float values to calculate the EMA from.
 * @param[in]  size    Size of the input data array.
 * @param[in]  period  Period to use for the EMA calculation.
 * @param[in]  alpha   Alpha value to use for the EMA calculation.
 *
 * @returns A pointer to an array of float values representing the EMA. The caller is responsible for freeing this memory.
 */

float* calculate_ema(float* prices, int len, int period) {
    float* ema = malloc(len * sizeof(float));
    float multiplier = 2.0 / (period + 1);
    float sum = 0.0;
    int i;

    for (i = 0; i < period; i++) {
        sum += prices[i];
        ema[i] = sum / (i + 1);
    }

    for (; i < len; i++) {
        ema[i] = (prices[i] - ema[i - 1]) * multiplier + ema[i - 1];
    }

    return ema;
}
