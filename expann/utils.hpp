#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <array>

namespace expann {

using idx_t = uint64_t;
using vec_t = float;

template <idx_t D>
struct Vector {
    std::array<vec_t, D> v;

    /// L2 distance
    float distance(const Vector &another) const;
};

} // namespace expann

//============ IMPLEMENTATION ============

#include <cmath>

namespace expann {

template <idx_t D>
inline float Vector<D>::distance(const Vector& another) const{
    float delta;
    float sum = 0;
    auto pa = this->v.begin();
    auto pb = another.v.begin();
    for(int _ = 0; _ < D; _++) {
        delta = *pa - *pb;
        sum += delta * delta;
        pa++;
        pb++;
    }
    return std::sqrt(sum);
}

} // namespace expann

#endif