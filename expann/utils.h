#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <array>
#include <cstdio>
#include <algorithm>

namespace expann {

using idx_t = int64_t;
using vec_t = float;

#define EXPANN_ASSERT(X)                                 \
    do {                                                 \
        if (!(X)) {                                      \
            fprintf(stderr,                              \
                    "ExpANN assertion '%s' failed in %s "\
                    "at %s:%d\n",                        \
                    #X,                                  \
                    __PRETTY_FUNCTION__,                 \
                    __FILE__,                            \
                    __LINE__);                           \
            abort();                                     \
        }                                                \
    } while (false)

/// L2 distance
inline float l2dist(const float* a, const float* b, idx_t d) {
    float delta;
    float sum = 0;
    auto pa = a;
    auto pb = b;
    for(int _ = 0; _ < d; _++) {
        delta = *pa - *pb;
        sum += delta * delta;
        pa++;
        pb++;
    }
    return std::sqrt(sum);
}

} // namespace expann

#endif