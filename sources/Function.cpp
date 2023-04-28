#include "Function.hpp"

void matrix_multiply_4x4_neon_float(float32_t* A, float32_t* B, float32_t* C,
                                    int N, int M, int L) {
  int A_indx;
  int B_indx;
  int C_indx;

  // remainder of dividing matrix sizes by 4
  int N_mod = N % 4;
  int M_mod = M % 4;
  int L_mod = L % 4;

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

  for (int i = 0; i < N - N_mod; i += 4) {
    for (int j = 0; j < L - L_mod; j += 4) {
      // zero accumulators before matrix op
      C0 = vmovq_n_f32(0);
      C1 = vmovq_n_f32(0);
      C2 = vmovq_n_f32(0);
      C3 = vmovq_n_f32(0);

      for (int k = 0; k < M - M_mod; k += 4) {
        // compute base index to 4x4 block in matrix B
        A_indx = i * M + k;
        B_indx = k * L + j;

        A0 = vld1q_f32(A + A_indx);
        A1 = vld1q_f32(A + A_indx + M);
        A2 = vld1q_f32(A + A_indx + 2 * M);
        A3 = vld1q_f32(A + A_indx + 3 * M);

        B0 = vld1q_f32(B + B_indx);
        B1 = vld1q_f32(B + B_indx + L);
        B2 = vld1q_f32(B + B_indx + 2 * L);
        B3 = vld1q_f32(B + B_indx + 3 * L);

        // multiply accumulate 4x4 blocks< i. e. each column C
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
      C_indx = i * L + j;

      vst1q_f32(C + C_indx, C0);
      vst1q_f32(C + C_indx + L, C1);
      vst1q_f32(C + C_indx + 2 * L, C2);
      vst1q_f32(C + C_indx + 3 * L, C3);
    }
  }

  // multiplicaiton of matrix elements
  // that could not be calculated using the 4x4 blocks
  for (int i = 0; i < N - N_mod; i++) {
    for (int j = 0; j < L - L_mod; j++) {
      for (int k = M - M_mod; k < M; k++) {
        C[i * L + j] += A[i * M + k] * B[k * L + j];
      }
    }

    for (int j = L - L_mod; j < L; j++) {
      for (int k = 0; k < M; k++) {
        C[i * L + j] += A[i * M + k] * B[k * L + j];
      }
    }
  }

  for (int i = N - N_mod; i < N; i++) {
    for (int j = 0; j < L; j++) {
      for (int k = 0; k < M; k++) {
        C[i * L + j] += A[i * M + k] * B[k * L + j];
      }
    }
  }
}

void matrix_multiply_2x2_neon_float(float32_t* A, float32_t* B, float32_t* C,
                                    int N, int M, int L) {
  int A_indx;
  int B_indx;
  int C_indx;

  // remainder of dividing matrix sizes by 2
  int N_mod = N % 2;
  int M_mod = M % 2;
  int L_mod = L % 2;

  float32x2_t A0;
  float32x2_t A1;

  float32x2_t B0;
  float32x2_t B1;

  float32x2_t C0;
  float32x2_t C1;

  for (int i = 0; i < N - N_mod; i += 2) {
    for (int j = 0; j < L - L_mod; j += 2) {
      C0 = vdup_n_f32(0);
      C1 = vdup_n_f32(0);

      for (int k = 0; k < M - M_mod; k += 2) {
        A_indx = i * M + k;
        B_indx = k * L + j;

        A0 = vld1_f32(A + A_indx);
        A1 = vld1_f32(A + A_indx + M);

        B0 = vld1_f32(B + B_indx);
        B1 = vld1_f32(B + B_indx + L);

        C0 = vfma_lane_f32(C0, B0, A0, 0);
        C0 = vfma_lane_f32(C0, B1, A0, 1);

        C1 = vfma_lane_f32(C1, B0, A1, 0);
        C1 = vfma_lane_f32(C1, B1, A1, 1);
      }
      C_indx = i * L + j;

      vst1_f32(C + C_indx, C0);
      vst1_f32(C + C_indx + L, C1);
    }
  }

  // multiplication of matrix elements
  // that could not be calculated using the 2x2 blocks
  for (int i = 0; i < N - N_mod; i++) {
    for (int j = 0; j < L - L_mod; j++) {
      for (int k = M - M_mod; k < M; k++) {
        C[i * L + j] += A[i * M + k] * B[k * L + j];
      }
    }

    for (int j = L - L_mod; j < L; j++) {
      for (int k = 0; k < M; k++) {
        C[i * L + j] += A[i * M + k] * B[k * L + j];
      }
    }
  }

  for (int i = N - N_mod; i < N; i++) {
    for (int j = 0; j < L; j++) {
      for (int k = 0; k < M; k++) {
        C[i * L + j] += A[i * M + k] * B[k * L + j];
      }
    }
  }
}
