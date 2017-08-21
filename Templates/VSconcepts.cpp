#include <iostream>

using namespace std;

/*
    Koncepty obiecuja fundamentalna zmiane w sposobie tworzenia szablonow w C++. Sa teraz w TS(Technical Specification) jak
    Coroutines, Modules, Ranges.

    Koncepty pozwalaja na dodawanie wymagan do zestawu parametrow szablonu, glownie tworzac cos w rodzaju interfejsow.
    Spolecznosc C++ czekala lata by ta funkcjonalnosc dotarla do standardu. Bjarne Stroustrup napisal troche historii
    konceptow.

    Sa obecnie dostepne tylko w GCC6+.
*/

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
    cout<<"UnsignedIntegral: "<<i<<endl;
}

int main(){

    f(42);

    return 0;
}