#include <iostream>
#include <iterator>
#include <vector>
// #include <origin-master/origin/core/concepts.hpp>
// #include "origin-master/origin/core/concepts.hpp"

using namespace std;
// using namespace origin;/

template<typename T>
concept bool NewConcept() {
    return requires(T t){
        axiom Consistency(T x, T y) {
        (x == y) <=> !(x != y);
        }
    };
};

int main () {


    return 0;
}