# Algorithm Analysis: Naive Classical vs Pure Strassen Matrix Multiplication

## Theoretical Complexity

### Naive Classical Matrix Multiplication
- **Time Complexity**: O(n³)
- **Space Complexity**: O(n²)
- **Description**: Standard triple-nested loop approach with no optimizations
- **Advantages**: Simple implementation, predictable performance
- **Disadvantages**: Poor asymptotic performance for large matrices

### Pure Strassen's Matrix Multiplication
- **Time Complexity**: O(n^2.807) ≈ O(n^2.81)
- **Space Complexity**: O(n²)
- **Description**: Pure divide-and-conquer algorithm with 7 recursive multiplications
- **Advantages**: Better asymptotic complexity, demonstrates algorithmic improvement
- **Disadvantages**: Higher constant factors, recursion overhead, memory allocation overhead

## Results
### Without Compiler Optimization
| Size  | Classical (ms) | Strassen (ms) |
|-------|----------------|---------------|
| 1024  | 4478           | 3571          |
| 2048  | 35754          | 25258         |
| 4096  | 1454365        | 669666        |

### With Optimization Enabled (-O3)
| Size  | Classical (ms) | Strassen (ms) |
|-------|----------------|---------------|
| 1024  | 65             | 90            |
| 2048  | 517            | 662           |
| 4096  | 4287           | 4697          |

### Observations
• Compiler optimizations dramatically change the performance landscape.
• Constant factors matter more than asymptotic complexity for realistic input sizes.
• Recursive overhead and memory allocation costs impact Strassen significantly.

### A good reminder that:
• Big-O complexity does not automatically guarantee better real-world performance.
• Performance sits at the intersection of:
Algorithms × Compiler × Memory × Hardware