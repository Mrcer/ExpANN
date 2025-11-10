#ifndef EXPANN_H
#define EXPANN_H

#include <expann/utils.hpp>

#include <memory>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>

namespace expann {

/** Entry of ExpANN.
 * 
 * To simplify implementation, only anns on vectors of floats would be considered currently.
 * As a minimal demo, I use Flat index directly now.
 */
template <idx_t D>
class ExpANN {
public:
    using Vector = Vector<D>;

    explicit ExpANN()
        :_is_trained(false) {}
    ~ExpANN() {};

    /** Perform training on a representative set of vectors*/
    void train(const std::vector<Vector>& x);

    /** Add n vectors to the index. Id is generated as size()*/
    void add(const std::vector<Vector>& x);

    /** Retrive vector from index */
    std::unique_ptr<Vector> get(const idx_t id);

    /** query n vectors of dimension d to the index.
     *
     * return at most k vectors. If there are not enough results for a
     * query, the result array is padded with -1s.
     *
     * @param x           input vectors to search
     * @param k           number of extracted vectors
     * @return            retrived vector id with its distance, sorted ascending by distance
     */
    std::unique_ptr<std::vector<std::pair<idx_t, float>>>
    search(const Vector& x, const idx_t k);

    bool is_trained() { return _is_trained; }
    idx_t size() { return _db.size(); }
private:
    bool _is_trained;
    std::vector<Vector> _db;
};

} // namespace expann

//============ IMPLEMENTATION ============

namespace
{

struct LessPair {
    bool operator()(
            const std::pair<expann::idx_t, float>& a,
            const std::pair<expann::idx_t, float>& b) const {
        return a.second < b.second;
    }
};

} // namespace

namespace expann {

template <idx_t D>
void ExpANN<D>::train(const std::vector<Vector>& x) {
    // Flat index has no training process
    _is_trained = true;
}

template <idx_t D>
void ExpANN<D>::add(const std::vector<Vector>& x) {
    idx_t size_append = x.size();
    if(size_append == 0) {
        return;
    }
    idx_t size_old = _db.size();
    _db.resize(size_old + size_append);
    std::copy(x.begin(), x.end(), _db.begin() + size_old);
}

template <idx_t D>
std::unique_ptr<Vector<D>> ExpANN<D>::get(const idx_t id) {
    assert(id < _db.size());
    return std::unique_ptr<Vector>(_db[id]);
}

template <idx_t D>
std::unique_ptr<std::vector<std::pair<idx_t, float>>>
ExpANN<D>::search(const Vector& x, const idx_t k) {
    std::priority_queue<
        std::pair<idx_t, float>,
        std::vector<std::pair<idx_t, float>>,
        LessPair
        > heap;
    idx_t szdb = _db.size();
    for(idx_t ni = 0; ni < std::min(k, szdb); ni++) {
        heap.emplace(ni, x.distance(_db[ni]));
    }
    for(idx_t ni = k; ni < szdb; ni++) {
        auto d = x.distance(_db[ni]);
        if(d < heap.top().second) {
            heap.pop();
            heap.emplace(ni, x.distance(_db[ni]));
        }
    }
    auto ret(std::make_unique<std::vector<std::pair<idx_t, float>>>());
    while(!heap.empty()) {
        ret->push_back(heap.top());
        heap.pop();
    }
    std::reverse(ret->begin(), ret->end());
    return ret;
}

} // namespace expann

#endif