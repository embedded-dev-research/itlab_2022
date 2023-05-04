#ifndef __BMP__
#define __BMP__

#include <fstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <iostream>

#pragma pack(push, 1)
struct BMPFileHeader {
  uint16_t file_type{0x4D42};
  uint32_t file_size{0};
  uint16_t reserved1{0};
  uint16_t reserved2{0};
  uint32_t offset_data{0};
};

struct BMPInfoHeader {
  uint32_t size{0};
  int32_t width{0};
  int32_t height{0};

  uint16_t planes{1};
  uint16_t bit_count{0};
  uint32_t compression{0};
  uint32_t size_image{0};
  int32_t x_pixels_per_meter{0};
  int32_t y_pixels_per_meter{0};
  uint32_t colors_used{0};
  uint32_t colors_important{0};
};

struct BMPColorHeader {
  uint32_t red_mask{0x00ff0000};
  uint32_t green_mask{0x0000ff00};
  uint32_t blue_mask{0x000000ff};
  uint32_t alpha_mask{0xff000000};
  uint32_t color_space_type{0x73524742};
  uint32_t unused[16]{0};
};

int count_channels = 3;

void check_color_header(BMPColorHeader& bmp_color_header) {
  BMPColorHeader expected_color_header;
  if (expected_color_header.red_mask != bmp_color_header.red_mask ||
      expected_color_header.blue_mask != bmp_color_header.blue_mask ||
      expected_color_header.green_mask != bmp_color_header.green_mask ||
      expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {
    throw std::runtime_error(
        "Unexpected color mask format! The program expects the pixel data to "
        "be in the BGRA format");
  }
  if (expected_color_header.color_space_type !=
      bmp_color_header.color_space_type) {
    throw std::runtime_error(
        "Unexpected color space type! The program expects sRGB values");
  }
}
#pragma pack(pop)
#endif  // __BMP__
