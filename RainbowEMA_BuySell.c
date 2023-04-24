#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_EMA_COUNT 5

void rainbow_ema(float closing_price, float* prev_ema, float* time_interval, float* ema_values, int ema_count, bool* buy_sell) {
    float ema_100 = prev_ema[ema_count - 1]; // the 100 EMA is the last one in the array
    for (int i = 0; i < ema_count; i++) {
        float k = 2.0 / (time_interval[i] + 1.0);
        ema_values[i] = (closing_price * k) + (prev_ema[i] * (1 - k));
        prev_ema[i] = ema_values[i];
        if (i == ema_count - 1) {
            // check position of 100 EMA and set buy_sell accordingly
            if (ema_100 > ema_values[i]) {
                buy_sell[i] = false; // sell
            } else {
                buy_sell[i] = true; // buy
            }
        } else {
            // check position of EMA and 100 EMA and set buy_sell accordingly
            if (ema_100 > ema_values[i] && ema_100 > prev_ema[i]) {
                buy_sell[i] = false; // sell
            } else if (ema_100 < ema_values[i] && ema_100 < prev_ema[i]) {
                buy_sell[i] = true; // buy
            } else {
                buy_sell[i] = buy_sell[i-1]; // maintain previous buy_sell decision
            }
        }
    }
}

int main() {
    float opening_price = 100.0;
    float closing_price = 120.0;
    float time_interval[MAX_EMA_COUNT] = {5.0, 10.0, 20.0, 50.0, 100.0}; // time intervals for each EMA
    float prev_ema[MAX_EMA_COUNT] = {opening_price, opening_price, opening_price, opening_price, opening_price}; // initialize previous EMA values with opening price
    float ema_values[MAX_EMA_COUNT];
    bool buy_sell[MAX_EMA_COUNT];
    int ema_count = 5;
    rainbow_ema(closing_price, prev_ema, time_interval, ema_values, ema_count, buy_sell);
    for (int i = 0; i < ema_count; i++) {
        printf("EMA%d: %.2f, Buy/Sell: %s\n", (int)time_interval[i], ema_values[i], buy_sell[i] ? "Buy" : "Sell");
    }
    return 0;
}
