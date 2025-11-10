#include <expann/expann.hpp>

#include <iostream>

int main() {
    expann::ExpANN<2> ann;

    std::vector<expann::Vector<2>> x = {
        {1},
        {2},
        {3},
        {4}
    };
    expann::Vector<2> q{{{0,1}}};

    ann.add(x);
    auto ret = ann.search(q, 2);

    for(auto p: *ret) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    return 0;
}