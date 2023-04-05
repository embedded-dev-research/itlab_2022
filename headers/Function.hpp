#ifndef _FUNCTION_
#define _FUNCTION_

#include <omp.h>
#include <arm_neon.h>

#define cllps 3
#define thr 4

template <typename T>
T multiplication_omp(const T& data1, const T& data2) {
    int row1 = data1.height;
    int row2 = data2.height;
    int col1 = data1.width;
    int col2 = data2.width;
    T res(row1, col2, 0);
    omp_set_num_threads(thr);
#pragma omp parallel for collapse(cllps)
    for (int i = 0; i < row1; ++i)
        for (int j = 0; j < col2; ++j)
            for (int k = 0; k < col1; ++k)
                res[i * col2 + j] += data1[i * col1 + k] * data2[k * col2 + j];
    return res;
}


template <typename T>
void multiplication_neon_float_4x4(const T& A, const T& B, const T& C) {
    int row1 = data1.height;
    int row2 = data2.height;
    int col1 = data1.width;
    int col2 = data2.width
    
    int A_indx;
    int B_indx;
    int C_indx;

    // remainder of dividing matrix sizes by 4
    int row1_mod = row1 % 4;
    int col1_mod = col1 % 4;
    int col2_mod = col2 % 4;

    float32x4_t A0;
    float32x4_t A1;
    float32x4_t A2;
    float32x4_t A3;

    float32x4_t B0;
    float32x4_t B1;
    float32x4_t B2;
    float32x4_t B3;

    float32x4_t C0;
    float32x4_t C1;
    float32x4_t C2;
    float32x4_t C3;

    for (int i = 0; i < row1 - row1_mod; i += 4){
        for (int j = 0; j < col2 - col2_mod; j += 4) {
            // zero accumulators before matrix op
            C0 = vmovq_n_f32(0);
            C1 = vmovq_n_f32(0);
            C2 = vmovq_n_f32(0);
            C3 = vmovq_n_f32(0);

            for (int k = 0; k < col1 - col1_mod; k += 4) {
                //compute base index to 4x4 block in matrix B
                A_indx = i * col1 + k;
                B_indx = k * col2 + j;

                A0 = vld1q_f32(A + A_indx);
                A1 = vld1q_f32(A + A_indx + col1);
                A2 = vld1q_f32(A + A_indx + 2 * col1);
                A3 = vld1q_f32(A + A_indx + 3 * col1);

                B0 = vld1q_f32(B + B_indx);
                B1 = vld1q_f32(B + B_indx + col1);
                B2 = vld1q_f32(B + B_indx + 2 * col1);
                B3 = vld1q_f32(B + B_indx + 3 * col1);

                // multiply accumulate 4x4 blocks i.e. each column C
                C0 = vfmaq_laneq_f32(C0, B0, A0, 0);
                C0 = vfmaq_laneq_f32(C0, B1, A0, 1);
                C0 = vfmaq_laneq_f32(C0, B2, A0, 2);
                C0 = vfmaq_laneq_f32(C0, B3, A0, 3);

                C1 = vfmaq_laneq_f32(C1, B0, A1, 0);
                C1 = vfmaq_laneq_f32(C1, B1, A1, 1);
                C1 = vfmaq_laneq_f32(C1, B2, A1, 2);
                C1 = vfmaq_laneq_f32(C1, B3, A1, 3);

                C2 = vfmaq_laneq_f32(C2, B0, A2, 0);
                C2 = vfmaq_laneq_f32(C2, B1, A2, 1);
                C2 = vfmaq_laneq_f32(C2, B2, A2, 2);
                C2 = vfmaq_laneq_f32(C2, B3, A2, 3);

                C3 = vfmaq_laneq_f32(C3, B0, A3, 0);
                C3 = vfmaq_laneq_f32(C3, B1, A3, 1);
                C3 = vfmaq_laneq_f32(C3, B2, A3, 2);
                C3 = vfmaq_laneq_f32(C3, B3, A3, 3);
            }
            C_indx = i * col2 + j;

            vst1q_f32(C + C_indx, C0);
            vst1q_f32(C + C_indx + col2, C1);
            vst1q_f32(C + C_indx + 2 * col2, C2);
            vst1q_f32(C + C_indx + 3 * col3, C3);
        }
    }

    // multiplication of matrix elements
    // that could not be calculated using the 4x4 blocks
    for (int i = 0; i < row1 - row1_mod; ++i) {
        for (int j = 0; j < col2 - col2_mod; ++j)
            for (int k = col1 - col1_mod; k < col1; ++k)
                C[i * col2 + j] += A[i * col1 + k] * B[k * col2 + j];
        for (int j = col2 - col2_mod; j < col2; ++j)
            for (int k = 0; k < col1; ++k)
                C[i * col2 + j] += A[i * col1 + k] * B[k * col2 + j];
    }

    for (int i = row1 - row1_mod; i < row1; ++i)
        for (int j = 0; j < col1; ++j)
            for (int k = 0; k < col1; ++k)
                C[i * col2 + j] += A[i * col1 + k] * B[k * col2 + j];
}

template <typename T>
void multiplication_neon_float_2x2(const T& data1, const T& data2, const T& C) {
    int row1 = data1.height;
    int row2 = data2.height;
    int col1 = data1.width;
    int col2 = data2.width;

    int A_indx;
    int B_indx;
    int C_indx;

    // remainder of dividing matrix sizes by 2
    int row1_mod = row1 % 2;
    int col1_mod = col1 % 2;
    int col2_mod = col2 % 2;

    float32x2_t A0;
    float32x2_t A1;

    float32x2_t B0;
    float32x2_t B1;

    float32x2_t C0;
    float32x2_t C1;

    for (int i = 0; i < row1 - row1_mod; i += 2){
        for (int j = 0; j < col2 - col2_mod; j += 2) {
            C0 = vdup_n_f32(0);
            C1 = vdup_n_f32(0);

            for (int k = 0; k < col1 - col1_mod; k += 2) {
                A_indx = i * col1 + k;
                B_indx = k * col2 + j;

                A0 = vld1_f32(A + A_indx);
                A1 = vld1_f32(A + A_indx + col1);

                B0 = vld1_f32(B + B_indx);
                B1 = vld1_f32(B + B_indx);

                C0 = vfma_lane_f32(C0, B0, A0, 0);
                C0 = vfma_lane_f32(C0, B1, A0, 1);

                C1 = vfma_lane_f32(C1, B0, A1, 0);
                C1 = vfma_lane_f32(C1, B1, A1, 1);
            }
            C_indx = i * col2 + j;
            vst1_f32(C + C_indx, C0);
            vst1_f32(C + C_indx + col2, C1);
        }
    }

    // multiplication of matrix elements
    // that could not be calculated using the 2x2 blocks
    for (int i = 0; i < row1 - row1_mod; ++i) {
        for (int j = 0; j < col2 - col2_mod; ++j)
            for (int k = col1 - col1_mod; k < col1; ++k)
                C[i * col2 + j] += A[i * col1 + k] * B[k * col2 + j];
       
        for (int j = col2 - col2_mod; j < col2; ++j)
            for (int k = 0; k < col1; ++k)
                C[i * col2 + j] += A[i * col1 + k] * B[k * col2 + j];
    }

    for (int i = row1 - row1_mod; i < row1; ++i)
        for (int j = 0; j < col2; ++j)
            for (int k = 0; k < col1; ++k)
                C[i * col2 + j] += A[i * col1 + k] * B[k * col2 + j];
}


#endif