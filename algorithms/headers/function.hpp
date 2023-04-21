#ifndef _FUNCTION_
#define _FUNCTION_

#include <omp.h>
#include <arm_neon.h>

#define cllps 3
#define thr 4

template <typename T>
T multiplication_omp(const T& data1, const T& data2, int N, int M, int L) {
    int row1 = N;
    int row2 = M;
    int col1 = M;
    int col2 = L;
    T res(row1, col2, 0);
    omp_set_num_threads(thr);
#pragma omp parallel for collapse(cllps)
    for (int i = 0; i < row1; ++i)
        for (int j = 0; j < col2; ++j)
            for (int k = 0; k < col1; ++k)
                res[i * col2 + j] += data1[i * col1 + k] * data2[k * col2 + j];
    return res;
}

void matrix_multiply_4x4_neon_float(float32_t* A, float32_t* B, float32_t* C, int N, int M, int L);
void matrix_multiply_2x2_neon_float(float32_t* A, float32_t* B, float32_t* C, int N, int M, int L);


#endif