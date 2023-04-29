float parabolic_sar(float *high, float *low, float *prev_sar, float *prev_ep, float *prev_af, float af_init, float af_step, float af_max, int length) {
    float ep = *prev_ep;
    float sar = *prev_sar;
    float af = *prev_af;
    int trend = sar < low[length-2];

    ep = trend ? fmaxf(ep, high[length-2]) : fminf(ep, low[length-2]);
    af = trend ? fminf(af + af_step, af_max) : af;

    float sar_next = sar + af * (ep - sar);
    int trend_changed = (trend && sar_next > high[length-1]) || (!trend && sar_next < low[length-1]);

    sar = trend_changed ? ep : sar_next;
    sar = trend ? fmaxf(sar, high[length-2]) : fminf(sar, low[length-2]);
    af = trend_changed ? af_init : af;

    *prev_ep = ep;
    *prev_sar = sar;
    *prev_af = af;

    return sar;
}
