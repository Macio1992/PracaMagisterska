#include <iostream>

//Argument deduction constraints - Ograniczenia dedukcji/wnioskowania argumentow
//sa podobne Niejawnych ograniczen konwersji z wyjatkiem takim ze Ograniczenia dedukcji/wnioskowania argumentow
//maja jeden lub wiecej placeholderow (wyrazen, ktore moga byc zastapione przez jakas informacje) w polu typu zwracanego
// Symbol zastępczy jest słowem kluczowym auto używanym w liście argumentów szablonu z klauzulą 'requires' konceptu.

using namespace std;

//typ szablonu. akceptuje dwa parametry szablonu
template<typename T, typename U>
struct Pair{};

//uzywamy konceptu zwracajacego true
template<typename T>
concept bool C1() { return true; }

//tu mamy wykorzystanie Argument deduction constraints
template<typename T>
concept bool C2(){
    return requires(T t){
        { *t } -> Pair<C1&, auto>; //auto to placeholder
    };
}

//wiekszosc konceptow to po prostu standardowe koncepty funkcji
//interesujaca linia: {*t} -> Pair<C1&, auto>;
//requires dziala w nastepujacy sposob:
//1) dereferncja zmiennej t, {*t} musi spelniac Końcowy typ zwrotu wskazany przez ->
//2) wynik dereferencji musi dawać w rezultacie typ Pair<T,U>
//3) z Pair typ zmiennej T musi byc rownowazny C1&. To oznacza ze typ T musi byc typem referyncyjnym
//4) Drugi parametr U jest odlozony na pozniej przez auto, rowniez znanym jako argument dedukcji

//ten kod przekaze ograniczony argument dedukcji
template<C2 T> void arg_deduction(T){}

int main () {

    auto *pair = new Pair<int&, double>();
    arg_deduction(pair);
    //tak dlugo jak zmienna jest wskaznikiem Pair<T,U> i typ T jest referencja jest ok

    return 0;
}