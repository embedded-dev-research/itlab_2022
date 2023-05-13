#include <arm_neon.h>

#include <iostream>

int main() {
  Image<bgr> a(1, 1);
  float32_t* A = new float32_t[360000];
  float32_t* B = new float32_t[360000];
  float32_t* C = new float32_t[360000];

  void (*q)(float32_t*, int, int) = print_matrx;

  Benchmark<void (*)(float32_t*, float32_t*, float32_t*, int, int, int),
            float32_t*, float32_t*, float32_t*, int, int, int>
      b(matrix_multiply_2x2_neon_float, A, B, C, 600, 600, 600);
  b.run();
  b.info();
  return 0;
}
