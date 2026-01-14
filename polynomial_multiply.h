#ifndef POLYNOMIAL_MULTIPLY_H
#define POLYNOMIAL_MULTIPLY_H

#include <vector>
#include <cmath>
#include "complex_number.h"
#include "fft_recursive.h"
#include "fft_iterative.h"

std::vector<int> naive_multiply(const std::vector<int>& a, const std::vector<int>& b) {
    int n = a.size();
    int m = b.size();
    std::vector<int> result(n + m - 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i + j] += a[i] * b[j];
        }
    }
    
    return result;
}

std::vector<int> fft_multiply(const std::vector<int>& a, const std::vector<int>& b, bool use_recursive) {
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }

    std::vector<cd> fa(a.begin(), a.end());
    std::vector<cd> fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    if (use_recursive) {
        fa = recursive_fft(fa, false);
        fb = recursive_fft(fb, false);
    } else {
        fa = iterative_fft(fa, false);
        fb = iterative_fft(fb, false);
    }

    std::vector<cd> fy(n);
    for (int i = 0; i < n; i++) {
        fy[i] = fa[i] * fb[i];
    }

    std::vector<cd> y_complex;
    if (use_recursive) {
        y_complex = recursive_fft(fy, true);
    } else {
        y_complex = iterative_fft(fy, true);
    }

    std::vector<int> result;
    for (int i = 0; i < n; i++) {
        result.push_back(round(y_complex[i].real()));
    }

    return result;
}

#endif