#include <iostream>

using namespace std;

template<typename T>
concept bool ParameterizedConstraint = requires(T a, T b){
    a == b;
    a != b;
};

int main(){

    return 0;
}