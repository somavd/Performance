# Matrix Multiplication Performance Optimization Study

**Classical Matrix Multiplication with Progressive Optimizations**

## Overview

This repository demonstrates the progressive optimization of classical matrix multiplication algorithms, focusing on memory access patterns and loop ordering. The study shows how simple changes can dramatically improve performance while maintaining the same O(n³) time complexity.

## Project Structure

```
matrix-multiplication/
├── src/
│   └── main.cpp                    # Main implementation with optimizations
├── results/
│   └── output_data.csv            # Benchmark results
├── docs/                          # Documentation
├── build/                         # Build artifacts
├── Makefile                       # Build automation
└── README.md                      # This file
```

## Evolution of Optimizations

### Git History & Tags

| Commit | Tag | Description | Performance Focus |
|--------|------|-------------|-------------------|
| `d63d922` | `array_memory_access` | Optimized + ikj loop order + array memory access | **Best Performance** |
| `b81200c` | `ikj_loop_order` | Optimized + ikj loop reorder | Memory Access Patterns |
| `54a5e52` | `optimised` | Optimized Approach [compile with -O3 flag] | Compiler Optimization |
| `b2038a7` | `baseline` | Initialize Matrix Benchmark structure | Baseline Implementation |
| `ec4ea72` | - | Add matrix multiplication implementation | Initial Setup |

## Benchmark Results

### Performance Comparison (Time in milliseconds)

| Matrix Size | Classical | Optimized | Optimized + ikj | Optimized + ikj + Memory Access |
|-------------|------------|------------|-------------------|------------------------------|
| 2×2 | 0 | 0 | 0 | 0 |
| 4×4 | 0 | 0 | 0 | 0 |
| 8×8 | 0 | 0 | 0 | 0 |
| 16×16 | 0 | 0 | 0 | 0 |
| 32×32 | 0 | 0 | 0 | 0 |
| 64×64 | 1 | 0 | 0 | 0 |
| 128×128 | 11 | 0 | 0 | 0 |
| 256×256 | 76 | 14 | 7 | **2** |
| 512×512 | 623 | 115 | 42 | **21** |
| 1024×1024 | 5229 | 1294 | 321 | **157** |
| 2048×2048 | 148380 | 21163 | 2576 | **1245** |
| 4096×4096 | 1351278 | 265520 | 20703 | **9952** |

### Performance Improvements

| Matrix Size | Classical → Final | Speedup |
|-------------|------------------|---------|
| 256×256 | 76ms → 2ms | **38× faster** |
| 512×512 | 623ms → 21ms | **29.7× faster** |
| 1024×1024 | 5229ms → 157ms | **33.3× faster** |
| 2048×2048 | 148380ms → 1245ms | **119.2× faster** |
| 4096×4096 | 1351278ms → 9952ms | **135.8× faster** |

## Optimization Techniques

### 1. Baseline Implementation
- Standard i-k-j loop ordering
- 2D vector representation
- No compiler optimizations

### 2. Compiler Optimization (-O3)
- Enabled compiler optimizations
- Loop unrolling
- Vectorization
- Instruction reordering

### 3. Loop Ordering (i-k-j → i-k-j)
- Changed to cache-friendly loop order
- Better spatial locality
- Reduced cache misses

### 4. Array Memory Access
- Flattened 2D arrays to 1D
- Improved cache line utilization
- Better memory access patterns
- Reduced pointer indirection

## Key Insights

### Performance Impact Analysis
1. **Small Matrices (≤64×64)**: All optimizations show minimal impact
2. **Medium Matrices (128×128–512×512)**: Significant improvements (20-40× speedup)
3. **Large Matrices (≥1024×1024)**: Dramatic improvements (30-135× speedup)

### Memory Access Patterns
- **Cache locality** is the most critical factor for large matrices
- **Loop ordering** dramatically affects performance
- **Array flattening** provides consistent benefits across all sizes

### Compiler vs Manual Optimization
- Compiler optimizations provide good baseline improvement
- Manual optimizations (loop ordering, memory layout) provide additional 10-50× improvement
- Combined effect is multiplicative, not additive

## Build and Run

### Prerequisites
- C++ compiler (g++ recommended)
- Make utility
- Git

### Quick Start
```bash
# Clone the repository
git clone <repository-url>
cd matrix-multiplication

# Build and run benchmark
make
./build/matrix_benchmark

# Generate visualizations
pip install -r requirements.txt
python visualize_results.py
```

### Visualization
The repository includes a Python script to visualize benchmark results:

```bash
# Install dependencies
pip install -r requirements.txt

# Generate all visualizations
python visualize_results.py
```

**Generated Visualizations:**
- `results/performance_comparison.png` - Performance comparison plots
- `results/speedup_comparison.png` - Speedup relative to classical implementation  
- `results/results_summary.png` - Summary table of results

### Manual Build
```bash
# Without optimization
g++ -std=c++11 src/main.cpp -o matrix_benchmark

# With optimization
g++ -std=c++11 -O3 src/main.cpp -o matrix_benchmark_opt
```

## Implementation Details

### Data Structure
- Uses 1D array representation for matrices
- `Matrix mat(n*n)` instead of `vector<vector<int>>`
- Index calculation: `mat[i*n + j]`

### Loop Ordering
```cpp
// Optimized ordering for cache efficiency
for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
        for (int j = 0; j < n; j++)
            C[i*n + j] += A[i*n + k] * B[k*n + j];
```

### Benchmarking Methodology
- 5 trials per matrix size
- Average of results
- Matrix sizes: 2^1 to 2^12 (2 to 4096)
- Random integer values (0-9)
- High-resolution timing with `std::chrono`

## Documentation

- [Results Data](results/output_data.csv) - Raw benchmark data

---

**Key Takeaway**: Proper memory access patterns and loop ordering can provide **100×+ performance improvements** while maintaining the same algorithmic complexity.
