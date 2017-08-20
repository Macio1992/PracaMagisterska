#include <iostream>

using namespace std;

template<typename T>
concept bool function_concept(){
    return true;
}

template<typename T>
requires function_concept<T>()
void do_stuff(T fc){
    cout<<fc<<endl;
}

template<function_concept T>
void do_stuff_2(T fc){
    cout<<fc<<endl;
}

void do_stuff_3(function_concept fc){
    cout<<fc<<endl;
}

int main () {



    return 0;
}