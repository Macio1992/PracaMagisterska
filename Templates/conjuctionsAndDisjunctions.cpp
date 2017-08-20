//Conjuctions and Disjunction
//Conjuctions to && dwa koncepty zwracają prawdę
//Disjunctions to || jeden lub oba zwracają prawdę
#include <iostream>

using namespace std;

struct foo {
    int a(){}
};

struct bar {
    int b(){}
};

template<typename T>
concept bool have_a(){
    return requires(T t){
        { t.a() } -> int;
    };
}

template<typename T>
concept bool have_b(){
    return requires(T t){
        { t.b() } -> int;
    };
}

template<typename T>
requires have_a<T>()
void do_stuff(T fn){
}

template<typename T>
requires have_b<T>()
void do_stuff_2(T fn){}

template<typename T>
concept bool have_ab(){
    return have_a<T>() && have_b<T>();
}

template<typename T>
requires have_ab<T>()
void do_stuff_3(T fn){}

struct macio {
    int a(){};
    int b(){};
};

int main(){

    foo x;
    do_stuff<foo>(x);

    macio m;
    do_stuff_3<macio>(m);

    return 0;
}

//Jeśli mamy strukturę która ma pole - funkcję która zwraca np. int i piszemy do tego koncept który zwraca prawdę 
//jeśli struktura posiada daną funkcję. Np stworzyłem strukturę foo, która ma funkcję a() i teraz jesli sobie stworze
//inną strukturę np, 'macio', która nie bedzie miala funkcji a() i bede chcial stworzyć jakąś funkcję 'do_stuff'
//opierająca się o koncept to kompilator zwróci mi błąd czytelny 'constraints not satisfied'