#include <iostream>
#include <type_traits>

using namespace std;

template<class T>
concept bool Integral = is_integral<T>::value;

template<class T>
concept bool SignedIntegral = Integral<T> && T(-1) < T(0);

int main () {
	
	
	
	return 0;
}
