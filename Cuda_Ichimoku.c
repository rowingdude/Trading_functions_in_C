#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define TPB 256

__global__ void ichimoku_kernel(float *h, float *l, float *c, float *tenkan, float *kijun, float *senkou_a, float *senkou_b, int N, int k, int s) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N) return;

    // Calculate Tenkan-sen
    float high = -INFINITY;
    float low = INFINITY;
    for (int i = 0; i < k; i++) {
        int j = idx - i;
        if (j < 0) break;
        high = fmaxf(high, h[j]);
        low = fminf(low, l[j]);
    }
    tenkan[idx] = (high + low) / 2.0f;

    // Calculate Kijun-sen
    high = -INFINITY;
    low = INFINITY;
    for (int i = 0; i < s; i++) {
        int j = idx - i;
        if (j < 0) break;
        high = fmaxf(high, h[j]);
        low = fminf(low, l[j]);
    }
    kijun[idx] = (high + low) / 2.0f;

    // Calculate Senkou Span A
    senkou_a[idx + s] = (tenkan[idx] + kijun[idx]) / 2.0f;

    // Calculate Senkou Span B
    high = -INFINITY;
    low = INFINITY;
    for (int i = 0; i < k; i++) {
        int j = idx - i - s;
        if (j < 0) break;
        high = fmaxf(high, h[j]);
        low = fminf(low, l[j]);
    }
    senkou_b[idx + s] = (high + low) / 2.0f;
}

void ichimoku(float *h, float *l, float *c, float *tenkan, float *kijun, float *senkou_a, float *senkou_b, int N, int k, int s) {
    float *d_h, *d_l, *d_c, *d_tenkan, *d_kijun, *d_senkou_a, *d_senkou_b;
    cudaMalloc(&d_h, N * sizeof(float));
    cudaMalloc(&d_l, N * sizeof(float));
    cudaMalloc(&d_c, N * sizeof(float));
    cudaMalloc(&d_tenkan, N * sizeof(float));
    cudaMalloc(&d_kijun, N * sizeof(float));
    cudaMalloc(&d_senkou_a, N * sizeof(float));
    cudaMalloc(&d_senkou_b, N * sizeof(float));
    cudaMemcpy(d_h, h, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_l, l, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, N * sizeof(float), cudaMemcpyHostToDevice);

    int blocks = (N + TPB - 1) / TPB;
    ichimoku_kernel<<<blocks, TPB>>>(d_h, d_l, d_c, d_tenkan, d_kijun, d_senkou_a, d_senkou_b, N, k, s);
}
cudaDeviceSynchronize();
cudaMemcpy(tenkan, d_tenkan, N * sizeof(float), cudaMemcpyDeviceToHost);
cudaMemcpy(kijun, d_kijun, N * sizeof(float), cudaMemcpyDeviceToHost);
cudaMemcpy(senkou_a, d_senkou_a, N * sizeof(float), cudaMemcpyDeviceToHost);
cudaMemcpy(senkou_b, d_senkou_b, N * sizeof(float), cudaMemcpyDeviceToHost);

cudaFree(d_h);
cudaFree(d_l);
cudaFree(d_c);
cudaFree(d_tenkan);
cudaFree(d_kijun);
cudaFree(d_senkou_a);
cudaFree(d_senkou_b);
, d_senkou_a, d_senkou_b, N, k, s);
cudaDeviceSynchronize();

scss

cudaMemcpy(tenkan, d_tenkan, N * sizeof(float), cudaMemcpyDeviceToHost);
cudaMemcpy(kijun, d_kijun, N * sizeof(float), cudaMemcpyDeviceToHost);
cudaMemcpy(senkou_a, d_senkou_a, N * sizeof(float), cudaMemcpyDeviceToHost);
cudaMemcpy(senkou_b, d_senkou_b, N * sizeof(float), cudaMemcpyDeviceToHost);

cudaFree(d_h);
cudaFree(d_l);
cudaFree(d_c);
cudaFree(d_tenkan);
cudaFree(d_kijun);
cudaFree(d_senkou_a);
cudaFree(d_senkou_b);

}

int main() {
// Input data
float h[] = {117.24, 116.67, 116.75, 116.54, 117.40, 118.07, 117.81, 118.18, 118.19, 118.13, 118.31, 117.71, 118.16, 118.10, 118.29, 118.88, 118.87, 118.62, 118.64, 118.34};
float l[] = {116.84, 116.33, 116.57, 116.22, 116.74, 117.42, 117.49, 117.85, 117.73, 117.70, 117.72, 117.31, 117.89, 117.80, 118.03, 118.59, 118.52, 118.44, 118.42, 118.19};
float c[] = {117.06, 116.45, 116.66, 116.34, 117.15, 117.81, 117.61, 118.00, 117.90, 117.79, 118.00, 117.54, 117.98, 117.88, 118.07, 118.66, 118.58, 118.45, 118.48, 118.26};
int N = sizeof(h) / sizeof(h[0]);
int k = 9;
int s = 26;
// Output data
float *tenkan = (float *)malloc(N * sizeof(float));
float *kijun = (float *)malloc(N * sizeof(float));
float *senkou_a = (float *)malloc(N * sizeof(float));
float *senkou_b = (float *)malloc(N * sizeof(float));

ichimoku(h, l, c, tenkan, kijun, senkou_a, senkou_b, N, k, s);

printf("Tenkan-sen:\n");
for (int i = 0; i < N; i++) {
    printf("%.2f\n", tenkan[i]);
}

printf("Kijun-sen:\n");
for (int i = 0; i < N; i++) {
    printf("%.2f\n", kijun[i]);
}

printf("Senkou Span A:\n");
for (int i = 0; i < N; i++) {
    printf("%.2f\n", senkou_a[i]);
}

printf("Senkou Span B:\n");
for (int i = 0; i < N; i++) {
    printf("%.2f\n", senkou_b[i]);
}

free(tenkan);
free(kijun);
free(senkou_a);
free(senkou_b);

return 0;
