#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <cmath>
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

/** Manage top-k with max-heap
 * 
 * Arrays passed in are deemed as borrowed. They would be initialized and managed till TopK::reorder
 * TopK::add after TopK::reorder is undefined.
 */
struct TopK {
    using Ele = std::pair<idx_t, float>;

    idx_t _k;
    Ele* _results;

    inline void init(idx_t k, Ele* results) {
        _k = k;
        _results = results;
        std::fill(results, results + k, std::make_pair<>(-1, std::numeric_limits<float>::max()));
    }

    inline void add(Ele el) {
        if(el.second < _results[0].second) {
            std::pop_heap(_results, _results + _k, Cmp);
            _results[_k - 1] = el;
            std::push_heap(_results, _results + _k, Cmp);
        }
    }

    inline void reorder() {
        std::sort_heap(_results, _results + _k, Cmp);
    }

    static bool Cmp(const Ele& a, const Ele& b) {
        return a.second < b.second;
    }
};

} // namespace expann

#endif