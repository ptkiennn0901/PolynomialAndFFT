#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <vector>
#include <chrono>
#include "memory_utils.h"
#include "polynomial_multiply.h"

struct BenchmarkResult {
    std::string algorithm;
    int size;
    double time_ms;
    size_t memory_kb;
};

BenchmarkResult benchmark(const std::vector<int>& a, const std::vector<int>& b, 
                         const std::string& algo_name, int algo_type) {
    BenchmarkResult result;
    result.algorithm = algo_name;
    result.size = std::max(a.size(), b.size());
    
    size_t mem_before = getMemoryUsage();
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> res;
    if (algo_type == 0) {
        res = naive_multiply(a, b);
    } else if (algo_type == 1) {
        res = fft_multiply(a, b, true);
    } else {
        res = fft_multiply(a, b, false);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    size_t mem_after = getMemoryUsage();
    
    result.time_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
    result.memory_kb = mem_after - mem_before;
    
    return result;
}

#endif