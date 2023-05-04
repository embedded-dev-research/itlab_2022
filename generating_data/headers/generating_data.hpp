#ifndef _DATA_RENDER_
#define _DATA_RENDER_

#include <ctime>
#include <random>

namespace data_render {
template <typename T>
void get_random(T& source, int size, int mmax = 256) {
  srand(time(0));

  for (int i = 0; i < size; ++i) source[i] = (unsigned char)(rand() % mmax);
}
}  // namespace data_render

#endif  // _DATA_RENDER_