#ifndef _DATA_RENDER_
#define _DATA_RENDER_

#include <random>
#include <ctime>

namespace data_render {
    template <typename T>
    void get_random(T& source, int size, int mmax = 256) {
        srand(time(0));

        for (int i = 0; i < size; ++i)
            source[i] = (unsigned char)(rand() % mmax);
    }
}

#endif  // _DATA_RENDER_