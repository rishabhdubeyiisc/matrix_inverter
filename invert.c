#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function declarations
int inv_mat(double **,unsigned int,double **);

void gauss_jordan(double **, unsigned int  ,unsigned int );

int swap_rows(unsigned int , double **, unsigned int ,unsigned int );

int inv_mat(double **inp_MAT, unsigned int order, double **op_MAT)
{
    unsigned int i, j;
    double **A;
    
    // Allocate memory for augmented matrix [A | I]
    A = (double **)malloc(order * sizeof(double *));
    if (A == NULL) {
        printf("Memory allocation failed for rows\n");
        return 99;
    }
    
    for (i = 0; i < order; i++) {
        A[i] = (double *)malloc(2 * order * sizeof(double));
        if (A[i] == NULL) {
            printf("Memory allocation failed for columns\n");
            // Free previously allocated memory
            for (unsigned int k = 0; k < i; k++) {
                free(A[k]);
            }
            free(A);
            return 99;
        }
    }
    
    // Initialize augmented matrix [A | I]
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            A[i][j] = inp_MAT[i][j];              // Copy input matrix
            A[i][j + order] = (i == j) ? 1.0 : 0.0;  // Identity matrix
        }
    }
    
    // Perform Gauss-Jordan elimination
    gauss_jordan(A, order, 2 * order);
    
    // Extract inverse matrix from right half
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            op_MAT[i][j] = A[i][j + order];
        }
    }
    
    // Free memory
    for (i = 0; i < order; i++) {
        free(A[i]);
    }
    free(A);
    
    return 0;
}

void gauss_jordan(double **A, unsigned int R, unsigned int C)
{
    double div_val;
    unsigned int i, j, k;
    
    for (i = 0; i < R; i++) {
        div_val = A[i][i];
        
        // Handle near-zero pivot
        if (fabs(div_val) < 1e-15) {
            if (swap_rows(i, A, R, C) == 1) {
                // Matrix is singular, set small value to continue
                A[i][i] = 1e-15;
            }
            div_val = A[i][i];
        }
        
        // Scale current row to make pivot = 1
        for (j = 0; j < C; j++) {
            A[i][j] /= div_val;
        }
        
        // Eliminate other rows
        for (k = 0; k < R; k++) {
            if (k != i) {
                div_val = A[k][i];
                for (j = 0; j < C; j++) {
                    A[k][j] -= div_val * A[i][j];
                }
            }
        }
    }
}

int swap_rows(unsigned int row_num, double **A, unsigned int row, unsigned int column)
{
    unsigned int i, j;
    double *temp_row;
    
    temp_row = (double *)malloc(column * sizeof(double));
    if (temp_row == NULL) {
        return 1; // Memory allocation failed
    }
    
    // Find a row with non-zero element in the pivot column
    for (i = row_num + 1; i < row; i++) {
        if (fabs(A[i][row_num]) > 1e-15) {
            // Swap rows
            for (j = 0; j < column; j++) {
                temp_row[j] = A[i][j];
                A[i][j] = A[row_num][j];
                A[row_num][j] = temp_row[j];
            }
            free(temp_row);
            return 0; // Successful swap
        }
    }
    
    free(temp_row);
    return 1; // No suitable row found for swapping
}
