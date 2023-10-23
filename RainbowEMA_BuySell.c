#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_EMA_COUNT 5

void rainbow_ema(float closing_price, float* prev_ema, float* time_interval, float* ema_values, int ema_count, bool* buy_sell) {
    float ema_100 = prev_ema[ema_count - 1]; // The 100 EMA is the last one in the array
    bool prev_decision = buy_sell[0];
    for (int i = 0; i < ema_count; ++i) {
        float inv_interval = 1.0f / (time_interval[i] + 1.0f); // Precompute the inverse for later use
        float k = 2.0f * inv_interval;
        float one_minus_k = 1.0f - k;
        
        // Calculate EMA value and update it
        ema_values[i] = (closing_price * k) + (prev_ema[i] * one_minus_k);
        prev_ema[i] = ema_values[i];
        
        // Determine buy or sell signals
        if (i == ema_count - 1) {
            buy_sell[i] = ema_100 <= ema_values[i];
        } else {
            bool sell_condition = ema_100 > ema_values[i] && ema_100 > prev_ema[i];
            bool buy_condition = ema_100 < ema_values[i] && ema_100 < prev_ema[i];
            buy_sell[i] = buy_condition ? true : (sell_condition ? false : prev_decision);
            prev_decision = buy_sell[i];
        }
    }
}
