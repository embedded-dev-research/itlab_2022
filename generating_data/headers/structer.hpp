#ifndef _MTRX_
#define _MTRX_

#include "bmp.hpp"
#include "color.hpp"

#ifdef WITH_OPENCV2
#include <opencv2/opencv.hpp>
#endif  // WITH_OPENCV2


template <typename ValType>
class Mtrx {
 protected:
  ValType* data = nullptr;

 public:
  int height;
  int width;
  Mtrx(){};
  Mtrx(int height_m, int width_m, ValType element = 0);
  Mtrx(const Mtrx& mtrx_m);  // copy constructor
  Mtrx(Mtrx&& mtrx_m);
  ValType* DData() { return data; }

  ~Mtrx() { delete[] data; }  // destructor

  ValType det();

  Mtrx<ValType>& operator=(const Mtrx<ValType>& mtrx_m);  // assignment operator
  Mtrx<ValType>& operator=(Mtrx<ValType>&& mtrx_m);       // assignment operator
  ValType& operator[](int position_m);                    // access
  const ValType& operator[](int position_m) const;        // const access
  ValType& operator()(int i, int j);
  const ValType& operator()(int i, int j) const;

  // scalar operation
  Mtrx<ValType> operator*(const ValType& val);  // multiply by a scalar
  Mtrx<ValType> operator/(const ValType& val);  // division by a scalar

  // matrix operation
  template <typename T>
  friend Mtrx<T> operator*(const Mtrx<T>& mtrx_left,
                           const Mtrx<T>& mtrx_right);  // multiplication

  template <typename T>
  friend Mtrx<T> Adamar(const Mtrx<T>& mtrx_left,
                        const Mtrx<T>& mtrx_right);  // comp. multiplication

  // input-output
  template <typename T>
  friend std::ostream& operator<<(std::ostream& out, const Mtrx<T>& mtrx_m);
};

template <layout Layout>
class Image : public Mtrx<Color<Layout>> {
 public:
  Image(int height_m, int width_m, Color<Layout> color_m = 0)  // constructor
      : Mtrx<Color<Layout>>(height_m, width_m, color_m) {}
  Image(const char* fname) : Mtrx<Color<Layout>>() { readBMP(fname); }

  unsigned char* splitR();  // split component R
  unsigned char* splitG();  // split component G
  unsigned char* splitB();  // split component B
  unsigned char* getMemory(int a, int b);
  void readBMP(const char* fname);

#ifdef WITH_OPENCV2
  void readPicture(const char* fname);  // reading a three-channel bgr image, if
                                        // Opencv is linked
#endif                                  // WITH_OPENCV2
};

///
///
/// Mtrx
///
///

template <typename ValType>  // contructor
Mtrx<ValType>::Mtrx(int height_m, int width_m, ValType element)
    : height(height_m), width(width_m) {
  data = new ValType[height * width];
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      data[i * width + j] = element;
    }
  }
} /*-------------------------------------------------------------------------*/

template <typename ValType>  // copy constructor
Mtrx<ValType>::Mtrx(const Mtrx<ValType>& mtrx_m)
    : height(mtrx_m.height), width(mtrx_m.width) {
  data = new ValType[height * width];

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      data[i * width + j] = mtrx_m[i * width + j];
    }
  }
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType>::Mtrx(Mtrx&& mtrx_m)
    : height(mtrx_m.height), width(mtrx_m.width), data(mtrx_m.data) {
  mtrx_m.data = nullptr;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType>& Mtrx<ValType>::operator=(const Mtrx<ValType>& mtrx_m) {
  if (this != &mtrx_m) {
    delete[] data;

    height = mtrx_m.height;
    width = mtrx_m.width;
    data = new ValType[height * width];

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        data[i * height + j] = mtrx_m[i * height + j];
      }
    }
  }
  return *this;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType>& Mtrx<ValType>::operator=(Mtrx<ValType>&& mtrx_m) {
  height = mtrx_m.height;
  width = mtrx_m.width;
  std::swap(data, mtrx_m.data);

  return *this;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
const ValType& Mtrx<ValType>::operator[](int position_m) const {
  return data[position_m];
} /*-------------------------------------------------------------------------*/

template <typename ValType>
ValType& Mtrx<ValType>::operator[](int position_m) {
  return data[position_m];
} /*-------------------------------------------------------------------------*/

template <typename ValType>
ValType& Mtrx<ValType>::operator()(int i, int j) {
  return data[i * width + j];
} /*-------------------------------------------------------------------------*/

template <typename ValType>
const ValType& Mtrx<ValType>::operator()(int i, int j) const {
  return data[i * width + j];
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType> Mtrx<ValType>::operator*(const ValType& val) {
  Mtrx<ValType> res(*this);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {
      res[i * width + j] *= val;
    }
  return res;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType> Mtrx<ValType>::operator/(const ValType& val) {
  Mtrx<ValType> res(*this);
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; j++) {
      res[i * width + j] /= val;
    }
  return res;
} /*-------------------------------------------------------------------------*/

template <typename T>
Mtrx<T> operator*(const Mtrx<T>& mtrx_left, const Mtrx<T>& mtrx_right) {
  Mtrx<T> mtrx_result(mtrx_left.height, mtrx_right.width);

  for (int i = 0; i < mtrx_left.height; i++) {
    for (int j = 0; j < mtrx_right.width; j++) {
      for (int k = 0; k < mtrx_left.width; k++) {
        mtrx_result.data[i * mtrx_result.width + j] += 
            mtrx_left.data[i * mtrx_left.width + k] * 
            mtrx_right.data[k * mtrx_right.width + j];
      }
    }
  }

  return mtrx_result;
} /*-------------------------------------------------------------------------*/

template <typename T>
Mtrx<T> Adamar(const Mtrx<T>& mtrx_left, const Mtrx<T>& mtrx_right) {
  Mtrx<T> mtrx_result(mtrx_left.height, mtrx_left.width);

  for (int i = 0; i < mtrx_result.height; ++i) {
    for (int j = 0; j < mtrx_result.width; ++j) {
      mtrx_result[i * mtrx_result.width + j] = 
          mtrx_left[i * mtrx_left.width + j] * 
          mtrx_right[i * mtrx_right.width + j];
    }
  }

  return mtrx_result;
} /*-------------------------------------------------------------------------*/

template <typename T>
std::ostream& operator<<(std::ostream& out, const Mtrx<T>& mtrx_m) {
  for (int i = 0; i < mtrx_m.height; ++i) {
    for (int j = 0; j < mtrx_m.width; ++j) {
      out << mtrx_m.data[i * mtrx_m.width + j] << ' ';
    }
    out << '\n';
  }
  return out;
} /*-------------------------------------------------------------------------*/

///
///
/// Image
///
///

template <layout Layout>
unsigned char* Image<Layout>::splitR() {
  unsigned char* R = new unsigned char[this->height * this->width];
  for (int i = 0; i < this->height * this->width; i++) {
    R[i] = this->data[i].R();
  }
  return R;
} /*-------------------------------------------------------------------------*/

template <layout Layout>
unsigned char* Image<Layout>::splitG() {
  unsigned char* G = new unsigned char[this->height * this->width];
  for (int i = 0; i < this->height * this->width; i++) {
    G[i] = this->data[i].G();
  }
  return G;
} /*-------------------------------------------------------------------------*/

template <layout Layout>
unsigned char* Image<Layout>::splitB() {
  unsigned char* B = new unsigned char[this->height * this->width];
  for (int i = 0; i < this->height * this->width; i++) {
    B[i] = this->data[i].B();
  }
  return B;
} /*-------------------------------------------------------------------------*/

template <layout Layout>
unsigned char* Image<Layout>::getMemory(int a, int b) {
  unsigned char* ret = new unsigned char[4 * (b - a)];
  for (int i = 0; i < b - a; i++) {
    unsigned char* tmp = this->data[i + a].getComp();
    for (int j = 0; j < 4; j++) {
      ret[i * 4 + j] = tmp[j];
    }
  }
  return ret;
}

template <>
void Image<bgr>::readBMP(const char* fname) {
  BMPFileHeader file_header;
  BMPInfoHeader bmp_info_header;
  BMPColorHeader bmp_color_header;

  std::ifstream inp{fname, std::ios_base::binary};
  if (inp) {
    inp.read((char*)&file_header, sizeof(file_header));
    if (file_header.file_type != 0x4D42) {
      throw std::runtime_error("Error! Unrecognized file format");
    }
    inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));

    // The BMPColorHeader is used only for transparent images
    if (bmp_info_header.bit_count == 32) {
      // Check if the file has bit mask color information
      if (bmp_info_header.size >=
          (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
        inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
        // Check if the pixel data is stored as BGRA and if the color space type
        // is sRGB
        check_color_header(bmp_color_header);
      } else {
        std::cerr << "Warning! The file \"" << fname
                  << "\"does not seem to contain bit mask information\n";
        throw std::runtime_error("Error! Unrecognized file format.");
      }
    }
    // Jump to pixel data location
    inp.seekg(file_header.offset_data, inp.beg);

    // Adjust the header fields for output.
    // Some editors will put extra info in the image file, we only save the
    // headers and the data.
    if (bmp_info_header.bit_count == 32) {
      bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
      file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) +
                                sizeof(BMPColorHeader);
      count_channels = 4;
    } else {
      bmp_info_header.size = sizeof(BMPInfoHeader);
      file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
      count_channels = 3;
    }
    file_header.file_size = file_header.offset_data;

    if (bmp_info_header.height < 0) {
      throw std::runtime_error(
          "The program can treat only BMP images with the origin in the bottom "
          "left corner!");
    }
    delete[] data;
    height = bmp_info_header.height;
    width = bmp_info_header.width;
    data = new Color<bgr>[width * height];

    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        inp.read((char*)(data) + (i * width + j) * 4, count_channels);
      }
      std::cout << "\n";
    }

    file_header.file_size += height * width * count_channels;
  } else {
    throw std::runtime_error("Unable to open the input image file");
  }
}

#ifdef WITH_OPENCV2
template <>
void Image<bgr>::readPicture(const char* fname) {
  cv::Mat a = cv::imread(fname);
  if (a.channels() == 3) {
    unsigned char* mat_data = a.data;
    delete[] data;
    height = a.rows;
    width = a.cols;
    data = new Color<bgr>[width * height];
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        data[i * width + j].B() = mat_data[(i * width + j) * 3];
        data[i * width + j].G() = mat_data[(i * width + j) * 3 + 1];
        data[i * width + j].R() = mat_data[(i * width + j) * 3 + 2];
      }
    }
  } else {
    std::cout << "Warning!!! Picture can`t be read as it is not three-channel"
              << std::endl;
  }
}

#endif  // WITH_OPENCV2
#endif  // _MTRX_
