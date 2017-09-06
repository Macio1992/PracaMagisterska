#include <iostream>
#include <iterator>
#include <vector>
// #include <origin-master/origin/core/concepts.hpp>
// #include "origin-master/origin/core/concepts.hpp"

using namespace std;
// using namespace origin;/

int main () {

    vector<int> v {3,1,4};
    auto v1 = v.begin();

    advance(v1, 2);

    cout<<*v1<<endl;

    return 0;
}