#include <algorithm>
#include <cmath>
#include "structer.hpp"

int interval(int val, int mmin, int mmax) {
  int ans;
  if (val < mmin)
    ans = mmin;
  else if (val > mmax)
    ans = mmax;
  else
    ans = val;

  return ans;
}

template <layout Layout>
Image<Layout> Filter(const Image<Layout>& sourceImage);

template <layout Layout>
Color<Layout> SobelX(const Image<Layout>& im, int x, int y);

template <layout Layout>
Color<Layout> SobelY(const Image<Layout>& im, int x, int y);

template <layout Layout>
Image<Layout> Filter(const Image<Layout>& sourceImage) {
  Image<Layout> resIm(sourceImage.height, sourceImage.width);

  Image<Layout> resImX(sourceImage.height, sourceImage.width);
  for (int i = 0; i < resImX.height; i++) {
    for (int j = 0; j < resImX.width; j++) {
      resImX(i, j) = SobelX(sourceImage, i, j);
    }
  }

  Image<Layout> resImY(sourceImage.height, sourceImage.width);
  for (int i = 0; i < resImY.height; i++) {
    for (int j = 0; j < resImY.width; j++) {
      resImY(i, j) = SobelY(sourceImage, i, j);
    }
  }

  for (int i = 0; i < resIm.height; i++) {
    for (int j = 0; j < resIm.width; j++) {
      float resultR = sqrt(resImX(i, j).R() * resImX(i, j).R() +
                           resImY(i, j).R() * resImY(i, j).R());
      float resultG = sqrt(resImX(i, j).G() * resImX(i, j).G() +
                           resImY(i, j).G() * resImY(i, j).G());
      float resultB = sqrt(resImX(i, j).B() * resImX(i, j).B() +
                           resImY(i, j).B() * resImY(i, j).B());
      resIm(i, j).R() = interval((unsigned char)resultR, 0, 255);
      resIm(i, j).G() = interval((unsigned char)resultG, 0, 255);
      resIm(i, j).B() = interval((unsigned char)resultB, 0, 255);
    }
  }

  return resIm;
}

template <layout Layout>
Color<Layout> SobelX(const Image<Layout>& im, int x, int y) {
  int radiusX = 1;
  int radiusY = 1;

  Mtrx<int> kernelX(3, 3);
  kernelX(0, 0) = -1;
  kernelX(0, 1) = 0;
  kernelX(0, 2) = 1;

  kernelX(1, 0) = -2;
  kernelX(1, 1) = 0;
  kernelX(1, 2) = 2;

  kernelX(2, 0) = -1;
  kernelX(2, 1) = 0;
  kernelX(2, 2) = 1;

  float resultR = 0;
  float resultG = 0;
  float resultB = 0;

  for (int l = -radiusY; l <= radiusY; l++) {
    for (int k = -radiusX; k <= radiusX; k++) {
      int idX = interval(x + l, 0, im.height - 1);
      int idY = interval(y + k, 0, im.width - 1);
      Color<Layout> neighborColor = im(idX, idY);
      resultR += neighborColor.R() * kernelX(l + radiusX, k + radiusY);
      resultG += neighborColor.G() * kernelX(l + radiusX, k + radiusY);
      resultB += neighborColor.B() * kernelX(l + radiusX, k + radiusY);
    }
  }

  return Color<Layout>(interval((unsigned char)resultR, 0, 255),
                       interval((unsigned char)resultG, 0, 255),
                       interval((unsigned char)resultB, 0, 255));
}

template <layout Layout>
Color<Layout> SobelY(const Image<Layout>& im, int x, int y) {
  int radiusX = 1;
  int radiusY = 1;

  Mtrx<int> kernelY(3, 3);
  kernelY(0, 0) = -1;
  kernelY(0, 1) = -2;
  kernelY(0, 2) = -1;

  kernelY(1, 0) = 0;
  kernelY(1, 1) = 0;
  kernelY(1, 2) = 0;

  kernelY(2, 0) = 1;
  kernelY(2, 1) = 2;
  kernelY(2, 2) = 1;

  float resultR = 0;
  float resultG = 0;
  float resultB = 0;

  for (int l = -radiusY; l <= radiusY; l++) {
    for (int k = -radiusX; k <= radiusX; k++) {
      int idX = interval(x + l, 0, im.height - 1);
      int idY = interval(y + k, 0, im.width - 1);
      Color<Layout> neighborColor = im(idX, idY);
      resultR += neighborColor.R() * kernelY(l + radiusX, k + radiusY);
      resultG += neighborColor.G() * kernelY(l + radiusX, k + radiusY);
      resultB += neighborColor.B() * kernelY(l + radiusX, k + radiusY);
    }
  }

  return Color<Layout>(interval((unsigned char)resultR, 0, 255),
                       interval((unsigned char)resultG, 0, 255),
                       interval((unsigned char)resultB, 0, 255));
}
