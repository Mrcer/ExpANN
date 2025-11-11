#ifndef EXPANN_H
#define EXPANN_H

#include <expann/utils.h>

#include <memory>
#include <vector>
#include <array>

namespace expann {

/** Entry of ExpANN.
 * 
 * To simplify implementation, only anns on vectors of floats would be considered currently.
 * As a minimal demo, I use Flat index directly now.
 */
class ExpANN {
public:
    explicit ExpANN(idx_t d)
        :_d(d),
        _ntotal(0),
        _is_trained(false) {}
    ~ExpANN() {};

    /** Perform training on a representative set of vectors
     *
     * @param n      nb of training vectors
     * @param x      training vecors, size n * d
     */
    void train(idx_t n, const float* x);

    /** Add n vectors of dimension d to the index.
     *
     * Vectors are implicitly assigned labels ntotal .. ntotal + n - 1
     * This function slices the input vectors in chunks smaller than
     * blocksize_add and calls add_core.
     * @param n      number of vectors
     * @param x      input matrix, size n * d
     */
    void add(idx_t n, const float* x);

    /** Retrive vector from index
     * 
     * @param n         number of vectors
     * @param labels    input labels of vectors
     * @param x         output matrix, size n * d
     */
    void get(idx_t n, const idx_t* labels, float* x);

    /** query n vectors of dimension d to the index.
     *
     * return at most k vectors. If there are not enough results for a
     * query, the result array is padded with -1s.
     *
     * @param n           number of vectors
     * @param x           input vectors to search, size n * d
     * @param k           number of extracted vectors
     * @param results     output pairs of label and distance, size n*k
     */
    void search(
        idx_t n,
        const float* x,
        idx_t k,
        std::pair<idx_t, float>* results) const;

    bool is_trained() { return _is_trained; }
    idx_t size() { return _ntotal; }
private:
    idx_t _d;
    idx_t _ntotal;
    bool _is_trained;
    std::vector<float> _db;
};

} // namespace expann

#endif