#include <iostream>
#include <locale>
#include <list>
#include <algorithm>

using namespace std;
using namespace std::literals;

/*
    szablony klas, szablony funkcji i nieszablonowe funkcje (zwykle skladowe szablonow klas) moga byc powiazane
    z 'ograniczeniem', ktore okresla wymagania na argumenty szablonu, ktore moze byc uzyte do wybrania najbardziej
    odpowiednich przeciazen funkcji i specjalizacji szablonu.
    Ograniczenia moga byz tez uzyte do ograniczenia automatycznej dedukcji typow w deklaracji zmiennych i typach
    zwracanych przez funkcje do tylko takich typow ktore spelniaja okreslone wymagania.
    Nazwane zestawy takich wymagan to KONCEPTY. Kazdy koncept to predykat, oceniony, oszacowany(evaluated) w
    czasie kompilacji i staje sie czescia interfejsu szablonu gdzie jest uzyty jako ograniczenie:
*/

/*
    deklaracja konceptu 'EqualityComparable' ktory jest spelniony przez kazdy typ T taki ze dla wartosci a i b typu T
    wyrazenie a==b kompiluje sie i wynik tego wyrazenia jest konwertowalny do bool
*/

template<typename T>
concept bool EqualityComparable = requires(T a, T b){
    { a == b} -> bool;
};

void f(EqualityComparable &&){} // deklaracja ograniczone funkcji szablonu
//template<typename T>
//void f(T&&) requires EqualityComparable<T>; // dluga forma tego samego

int main(){

    f("std"); // Ok: string jest EqualityComparable
    // f(use_facet<ctype<char>>(locale{}));// blad: nie EqualityComparable

    /*
        Naruszenia ograniczen sa wykrywane w czasie kompilacji, wczesnie w procesie tworzenia instancji, co
        prowadzi do latwego rozpoznawania bledow
    */

    // list<int> l = {3, -1, 10};
    sort(l.begin(), l.end());

    /*
        diagnostyki kompilatora bez konceptow:
        invalid operands to binary expression ('std::_List_iterator<int>' and
        'std::_List_iterator<int>')
        std::__lg(__last - __first) * 2);
        ... 50 linii wyniku ...

        diagnostyki z konceptami
        error: cannot call std::sort with std::_List_iterator<int>
        note:  concept RandomAccessIterator<std::_List_iterator<int>> was not satisfied

        Cel konceptow to modelowanie semantycznych kategorii(Number, Range, RegularFunction) bardziej niz
        syntaktycznych restrykcji (HasPlus, Array). Odnoszac sie do ISO C++ core guideline T.20:
        "Zdolnosc do okreslania znaczacej semantyki to definiowanie wlasciwosci prawdziwego konceptu
        w przeciwienstwie do syntaktycznego ograniczenia"
    */

    return 0;
}