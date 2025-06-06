# Matrix Inverter

A high-performance C library for computing matrix inverses using the **Gauss-Jordan elimination** algorithm.

## 🔍 Overview

This library provides efficient matrix inversion capabilities for square matrices of any size. It uses the numerically stable Gauss-Jordan elimination method with partial pivoting to handle both regular and near-singular matrices.

## ⚡ Features

- **Fast & Efficient**: Optimized Gauss-Jordan elimination algorithm
- **Numerically Stable**: Handles near-zero pivots and partial pivoting
- **Memory Safe**: Proper memory allocation and cleanup
- **Error Handling**: Graceful handling of singular matrices and memory failures
- **Clean Code**: Well-documented and maintainable implementation

## 🚀 Algorithm

The implementation uses **Gauss-Jordan elimination** with the augmented matrix approach:

1. **Create augmented matrix**: `[A | I]` where `A` is input matrix and `I` is identity
2. **Apply row operations**: Transform left side to identity matrix
3. **Extract result**: Right side becomes `A⁻¹`

### Mathematical Foundation
```
If [A | I] → [I | B] through row operations, then B = A⁻¹
```

## 📋 API Reference

### Core Functions

#### `int inv_mat(double **inp_MAT, unsigned int order, double **op_MAT)`
Computes the inverse of a square matrix.

**Parameters:**
- `inp_MAT`: Input matrix (n×n)
- `order`: Matrix dimension (n)
- `op_MAT`: Output matrix to store the inverse

**Returns:**
- `0`: Success
- `99`: Memory allocation failure

#### `void gauss_jordan(double **A, unsigned int R, unsigned int C)`
Performs Gauss-Jordan elimination on augmented matrix.

#### `int swap_rows(unsigned int row_num, double **A, unsigned int row, unsigned int column)`
Swaps rows for numerical stability when pivot is near zero.

## 💻 Usage Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "invert.h"  // Include your header

int main() {
    int n = 3;  // 3x3 matrix
    double **matrix, **inverse;
    
    // Allocate memory
    matrix = (double**)malloc(n * sizeof(double*));
    inverse = (double**)malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
        inverse[i] = (double*)malloc(n * sizeof(double));
    }
    
    // Initialize test matrix
    matrix[0][0] = 2; matrix[0][1] = 1; matrix[0][2] = 1;
    matrix[1][0] = 1; matrix[1][1] = 2; matrix[1][2] = 1; 
    matrix[2][0] = 1; matrix[2][1] = 1; matrix[2][2] = 2;
    
    // Compute inverse
    int result = inv_mat(matrix, n, inverse);
    
    if(result == 0) {
        printf("Matrix inversion successful!\n");
        // Print inverse matrix
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                printf("%.4f ", inverse[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Matrix inversion failed!\n");
    }
    
    // Free memory
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
        free(inverse[i]);
    }
    free(matrix);
    free(inverse);
    
    return 0;
}
```

## 🔧 Compilation

```bash
gcc -o matrix_inverter invert.c main.c -lm
```

## 📊 Performance

- **Time Complexity**: O(n³)
- **Space Complexity**: O(n²)
- **Numerical Precision**: Double precision (15-16 significant digits)

## ⚠️ Important Notes

- **Input Requirements**: Matrix must be square and invertible
- **Singular Matrices**: Near-singular matrices are handled by setting small pivot values (1e-15)
- **Memory Management**: Caller is responsible for allocating input/output matrix memory
- **Thread Safety**: Functions are not thread-safe due to shared temporary variables

## 🔬 Numerical Stability Features

- **Partial Pivoting**: Row swapping when pivot < 1e-15
- **Epsilon Tolerance**: Uses `fabs()` for floating-point comparisons
- **Graceful Degradation**: Continues computation for near-singular matrices

## 📚 Mathematical Background

The Gauss-Jordan method transforms a matrix to reduced row echelon form (RREF) through elementary row operations:
1. **Row scaling**: `R₁ ← R₁/c`
2. **Row addition**: `R₁ ← R₁ + cR₂`
3. **Row swapping**: `R₁ ↔ R₂`

These operations preserve the mathematical relationships while systematically solving `AX = I` for `X = A⁻¹`.

## 🏗️ Project Structure

```
matrix_inverter/
├── invert.c          # Main implementation
├── README.md         # This file
└── examples/         # Usage examples
```

## 📄 License

This project is open source. Feel free to use, modify, and distribute.

---

**Built with ❤️ for numerical computing**
