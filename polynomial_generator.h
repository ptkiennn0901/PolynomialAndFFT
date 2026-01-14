#ifndef POLYNOMIAL_GENERATOR_H
#define POLYNOMIAL_GENERATOR_H

#include <vector>
#include <random>

std::vector<int> generateRandomPolynomial(int degree) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    std::vector<int> poly(degree + 1);
    for (int i = 0; i <= degree; i++) {
        poly[i] = dis(gen);
    }
    return poly;
}

#endif