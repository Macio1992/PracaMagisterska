#include <iostream>
// #include <origin-master/origin/core/concepts.hpp>
#include "origin-master/origin/core/concepts.hpp"

using namespace std;
using namespace origin;

template<typename T, typename S>
requires Equality_comparable<T>()
void find(T t){}

int main () {


    return 0;
}