#include <iostream>
#define REQUIRES(...) typename enable_if<(__VA_ARGS__), int>::type = 0

using namespace std;

template<class T, REQUIRES(is_integral<T>())>
void increment(T& x){
    ++x;
}

template<class T>
void twice(T& x){
    increment(x);
    increment(x);
}

struct foo {};
/*
template<class T>
struct is_incrementable
: integral_constant<bool, (
    is_integral<T>() && is_floating_point<T>() && is_pointer<T>()
)>{};*/

template<class T, class Enable=void>
struct is_incrementable : false_type {};

template<class T>
struct always_void{
    typedef void type;
};

template<class T>
struct is_incrementable<T, typename always_void<decltype(declval<T&>)>::type> : true_type{};

int main () {

    int i = 1;
    struct foo f;
    twice(i);
    cout<<i<<endl;

    return 0;
}