#include <iostream>
#include <vector>
#include <iomanip>
#include "polynomial_generator.h"
#include "benchmark.h"

using namespace std;

int main() {
    cout << "================================================================\n";
    cout << "     SO SANH THUAT TOAN NHAN DA THUC (POLYNOMIAL MULTIPLICATION)\n";
    cout << "================================================================\n\n";

    vector<int> test_sizes = {10, 100, 1000, 5000, 10000, 100000};
    vector<BenchmarkResult> all_results;
    const int NUM_TESTS = 5;

    for (int size : test_sizes) {
        cout << "\n--- TEST CASE: Bac da thuc = " << size << " (Chay " << NUM_TESTS << " lan) ---\n";
        
        BenchmarkResult naive_avg = {"Naive", size, 0.0, 0};
        BenchmarkResult rec_avg = {"Recursive FFT", size, 0.0, 0};
        BenchmarkResult iter_avg = {"Iterative FFT", size, 0.0, 0};
        
        for (int test = 0; test < NUM_TESTS; test++) {
            cout << "  Lan " << (test + 1) << "/" << NUM_TESTS << "... " << flush;
            
            vector<int> poly1 = generateRandomPolynomial(size);
            vector<int> poly2 = generateRandomPolynomial(size);

            if (size <= 100000) {
                BenchmarkResult naive_res = benchmark(poly1, poly2, "Naive", 0);
                naive_avg.time_ms += naive_res.time_ms;
                naive_avg.memory_kb += naive_res.memory_kb;
            }

            BenchmarkResult rec_res = benchmark(poly1, poly2, "Recursive FFT", 1);
            rec_avg.time_ms += rec_res.time_ms;
            rec_avg.memory_kb += rec_res.memory_kb;

            BenchmarkResult iter_res = benchmark(poly1, poly2, "Iterative FFT", 2);
            iter_avg.time_ms += iter_res.time_ms;
            iter_avg.memory_kb += iter_res.memory_kb;
            
            cout << "Hoan thanh!\n";
        }
        
        if (size <= 100000) {
            naive_avg.time_ms /= NUM_TESTS;
            naive_avg.memory_kb /= NUM_TESTS;
            all_results.push_back(naive_avg);
        }
        
        rec_avg.time_ms /= NUM_TESTS;
        rec_avg.memory_kb /= NUM_TESTS;
        all_results.push_back(rec_avg);
        
        iter_avg.time_ms /= NUM_TESTS;
        iter_avg.memory_kb /= NUM_TESTS;
        all_results.push_back(iter_avg);
    }

    cout << "\n\n================================================================\n";
    cout << "                    KET QUA TONG HOP\n";
    cout << "================================================================\n\n";
    cout << left << setw(20) << "Thuat toan" 
         << setw(15) << "Bac da thuc"
         << setw(18) << "Thoi gian (ms)"
         << setw(18) << "Bo nho (KB)" << endl;
    cout << string(71, '-') << endl;

    for (const auto& res : all_results) {
        cout << left << setw(20) << res.algorithm
             << setw(15) << res.size
             << setw(18) << fixed << setprecision(3) << res.time_ms
             << setw(18) << res.memory_kb << endl;
    }

    return 0;
}