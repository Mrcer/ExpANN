#include <expann/expann.h>

#include <iostream>

int main() {
    expann::ExpANN ann(2);

    float x[] = {
        1,0,
        2,0,
        3,0,
        4,0
    };
    float q[] = {0, 2.5};
    std::pair<expann::idx_t, float> results[2];

    ann.add(4, x);
    ann.search(1, q, 2, results);

    for(auto r: results) {
        std::cout << r.first << " " << r.second << std::endl;
    }
    return 0;
}