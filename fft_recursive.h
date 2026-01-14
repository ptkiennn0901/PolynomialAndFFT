#ifndef FFT_RECURSIVE_H
#define FFT_RECURSIVE_H

#include <vector>
#include <cmath>
#include "complex_number.h"

std::vector<cd> recursive_fft(std::vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1) {
        return a;
    }

    double angle = 2.0 * PI / n * (invert ? -1 : 1);
    cd w_n(cos(angle), sin(angle));
    cd w(1);

    std::vector<cd> a0, a1;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) a0.push_back(a[i]);
        else            a1.push_back(a[i]);
    }

    std::vector<cd> y0 = recursive_fft(a0, invert);
    std::vector<cd> y1 = recursive_fft(a1, invert);

    std::vector<cd> y(n);
    for (int k = 0; k < n / 2; k++) {
        cd t = w * y1[k];
        y[k] = y0[k] + t;
        y[k + n / 2] = y0[k] - t;
        if (invert) {
            y[k] /= 2;
            y[k + n / 2] /= 2;
        }
        w = w * w_n;
    }
    return y;
}

#endif