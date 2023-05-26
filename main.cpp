#include <arm_neon.h>

#include <iostream>

#include "benchmark.hpp"
#include "filter.hpp"
#include "function.hpp"
#include "structer.hpp"

using namespace cv;

int main() {
  Image<bgr> a(1, 1);
  a.readPicture("clock.jpg");
  Image<bgr> b = Filter(a);
  b.writePicture("clockXY.jpg");
  Mat m = imread("clock.jpg", m1);
  Sobel(m, m1, CV_32F, 1, 1);
  imwrite("clockCV11.jpg", m1);
  return 0;
}
