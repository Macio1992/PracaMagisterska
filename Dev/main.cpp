#include <iostream>

using namespace std;

template<class T>
concept bool Integral = is_integral<T>::value;

template<class T>
concept bool SignedIntegral = Integral<T> && T(-1) < T(0);

template<class T>
concept bool UnsignedIntegral = Integral<T> && T(0) < T(-1);

template<class T>
void f(T const& t){
	cout<<"Not integral: "<<t<<endl;
}

void f(Integral) = delete;

void f(SignedIntegral i){
	cout<<"SignedIntegral: "<<i<<endl;
}

void f(UnsignedIntegral i){
	cout<<"Unsigned Integral: "<<i<<endl;
}

int main(int argc, char** argv) {
	
	f(42);
	f(1729u);
	f("Hello World");
	enum {
		bar
	};
	f(bar);
	f('a');
	f(L'a');
	f(U'a');
	f(true);
	
	return 0;
}
