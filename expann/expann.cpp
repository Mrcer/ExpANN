#include <expann/utils.h>
#include <expann/expann.h>
#include <algorithm>

namespace expann {

void ExpANN::train(idx_t n, const float* x) {
    // Flat index has no training process
    _is_trained = true;
}

void ExpANN::add(idx_t n, const float* x) {
    if(n == 0) {
        return;
    }
    _ntotal += n;
    idx_t size_append = n * _d;
    idx_t size_old = _db.size();
    _db.resize(size_old + size_append);
    std::copy(x, x + size_append, _db.begin() + size_old);
}

void ExpANN::get(idx_t n, const idx_t* labels, float* x) {
    if(n == 0) {
        return;
    }
    const idx_t* end = labels + n;
    auto xbegin = x;
    for(const idx_t* it = labels; it < end; it++) {
        idx_t idx = *it;
        auto vbegin = _db.begin() + idx * _d;
        auto vend = _db.begin() + (idx + 1) * _d;
        std::copy(vbegin, vend, xbegin);
        xbegin += _d;
    }
}

void ExpANN::search(
        idx_t n,
        const float* x,
        idx_t k,
        std::pair<idx_t, float>* results) const {
    const float* v_db = _db.data();
    std::vector<TopK> topks(n);
    for(idx_t ni = 0; ni < n; ni++) {
        topks[ni].init(k, results + k * ni);
    }
    for(idx_t i = 0; i < _ntotal; i++) {
        const float* v_x = x;
        for(idx_t ni = 0; ni < n; ni++) {
            float dist = l2dist(v_db, v_x, _d);
            topks[ni].add(std::make_pair<>(i, dist));
            v_x += _d;
        }
        v_db += _d;
    }
    for(idx_t ni = 0; ni < n; ni++) {
        topks[ni].reorder();
    }
}

} // namespace expann