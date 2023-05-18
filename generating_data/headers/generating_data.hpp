#ifndef _GENERATING_DATA_
#define _GENERATING_DATA_

#include <limits>

#include "gen_rand_data.hpp"
#include "structer.hpp"

namespace gen_matr_type {
template <typename T>
using num_lim = std::numeric_limits<T>;

template <typename T>
void fill(Mtrx<T>& matrix, const double& sparsity = 1.0,
          const T& min = num_lim<T>::min(), const T& max = num_lim<T>::max()) {
  if (matrix.empty()) return;

  gen_rand_data::Generator<T> gen(min, max);

  std::mt19937_64 genSparsity{std::random_device{}()};
  std::uniform_real_distribution<double> distSparsity(0.0, 1.0);

  for (size_t i = 0; i < matrix.height; ++i)
    for (size_t j = 0; j < matrix.width; ++j) {
      if (sparsity >= distSparsity(genSparsity)) do {
          matrix(i, j) = gen();
        } while (matrix(i, j) == static_cast<T>(0));

      else
        matrix(i, j) = static_cast<T>(0);
    }
}

template <layout Layout>
void fill(Image<Layout>& image, const double& sparsity = 1.0,
          const uint8_t& min = num_lim<uint8_t>::min(),
          const uint8_t& max = num_lim<uint8_t>::max()) {
  if (image.empty()) return;

  gen_rand_data::Generator<uint8_t> gen(num_lim<uint8_t>::min(),
                                        num_lim<uint8_t>::max());

  std::mt19937_64 genSparsity{std::random_device{}()};
  std::uniform_real_distribution<double> distSparsity(0.0, 1.0);

  for (size_t i = 0; i < image.height; ++i)
    for (size_t j = 0; j < image.width; ++j) {
      if (sparsity >= distSparsity(genSparsity))
        image(i, j) = Color<Layout>(gen(), gen(), gen(), gen());

      else
        image(i, j) = Color<Layout>(0, 0, 0, 0);
    }
}
}  // namespace gen_matr_type

#endif  // _GENERATING_DATA_
