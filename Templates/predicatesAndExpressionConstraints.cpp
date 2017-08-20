#include <iostream>

//predicates and expression constraints

using namespace std;

//predicate constraints - sprawdzają wyrażenie czy spełnia kryteria. Ten predykat sprawdza czy typ T jest 32 bitowy - ma
//rozmiar 4
template<typename T>
concept bool Size32 = sizeof(T) == 4;

//Ta metoda zaakceptuje wszystko co ma rozmiar 4 bajtów
void test_size32(Size32 s){}

//expression constraints - różnią się od predicate constraints. Expression constraints zamieniają parametr szablonu
//i sprawdzają czy wyrażenia są dopuszczalne
//Jeśli chcesz sprawdzić czy typ dopuszcza zwiększanie prefiksu. To zadziała jeśli T = int, dla string wywali błąd
//constraints not satisfied
template<typename T>
concept bool PrefixIncrement = requires(T t){
    ++t;
};

void test_prefix(PrefixIncrement p){}

int main () {

    int x = 4;
    double xx = 5.6;
    string c = "maciek";

    test_size32(x); //ok
    //test_size32(xx); // nie ok, double za duzy rozmiar

    test_prefix(x);
    test_prefix(c);

    // cout<<++c<<endl;

    return 0;
}