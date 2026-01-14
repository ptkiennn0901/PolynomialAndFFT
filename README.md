# Polynomial Multiplication Benchmark

Performance comparison of polynomial multiplication algorithms: Naive, Recursive FFT, and Iterative FFT.

## Project Structure

```
├── complex_number.h          # Complex number type definitions
├── memory_utils.h            # Memory measurement utilities
├── polynomial_generator.h    # Random polynomial generator
├── fft_recursive.h           # Recursive FFT implementation
├── fft_iterative.h           # Iterative FFT implementation
├── polynomial_multiply.h     # Polynomial multiplication methods
├── benchmark.h               # Benchmarking and performance measurement
└── main.cpp                  # Main program
```

## Algorithms

**Naive Multiplication**: Direct multiplication O(n²)

**Recursive FFT**: Fast Fourier Transform with recursion O(n log n)

**Iterative FFT**: Fast Fourier Transform with iteration O(n log n)

## Compilation

```bash
g++ -std=c++11 main.cpp -o benchmark
```

## Execution

```bash
./benchmark
```

The program tests polynomial degrees: 10, 100, 1000, 5000, 10000, 100000

Each test case runs 5 times and calculates the average.

## Output

Displays a comparison table showing execution time (ms) and memory usage (KB) for each algorithm.