#include <iostream>

//Type constraints - ograniczenia typu - ograniczają przez ograniczenie akceptowanego typu.
//Dzięki temu możesz tylko akceptować typy, które zawierają jakieś właściwości lub zestawy
//podtypów

using namespace std;

//Variable concept
template<typename T>
concept bool TypeHasTypeVar = requires { typename T::type; };

//Function concept
template<typename T>
concept bool TypeHasTypeFn (){
    return requires { typename T::type; };
}

//struktura foo_type ma C++11 'typedef', rowniez znany jako 'using'. To wprowadza nowy typ zwany 'type' w foo_type
struct foo_type{
    using type = int;
};

//Zastapienie T T::type gdzie T = foo_type, przyniesie poprawny typ. foo_type::type jest poprawnym typem, i kompilacja
//pojdzie dalej bo to ograniczenie jest zaspokojone
//Jesli bylby autorem biblioteki mozesz uzyc ograniczen typu by dostac wczesne wiadomosci bledow dla twoich uzytkownikow
//jesli ich uzytkownicy dostarczyli typy ktore nie implementuja wymaganych zestawow typow
//Wiekszosc kontenerow STL ma 'key_type' lub 'value_type'. Jesli wymagasz takiego typu mozesz go wymagac z ograniczeniem typu

//funkcja ktorej parametr spelnia koncept 'TypeHasTypeVar'
void do_stuff(TypeHasTypeVar t){}

//Implicit conversion constraints - Niejawne ograniczenia konwersji
//sprawdzają czy operacja pomiedzy dwoma konceptami daje rezultat w innym type bez wyraznego okreslania typu
//tu nie okreslamu typow a i b ale ma wyjsc bool

template<typename T>
concept bool ImplicitBoolVar = requires(T a, T b){
    { a == b } -> bool;
};

//porownanie a == b musi dac w wyniku wartosc boolowska

template<typename T>
concept bool ImplicitBoolFn(){
    return requires(T a, T b){
        { a == b } -> bool;
    };
};

template<typename T>
requires ImplicitBoolVar<T>
void do_stuff2(T a, T b){}

int main(){

    foo_type ft;

    //wywolanie funkcji z parametrem typu foo_type zadziala
    do_stuff(ft);

    //wywolanie funkcji z parametrem typu int nie zadziala, bo int nie ma podtypu
    // do_stuff(5)

    do_stuff2(false, true);
    // do_stuff2(b1, 3);

    return 0;
}