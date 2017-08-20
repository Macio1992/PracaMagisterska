#include <iostream>
#include "assert.h"

using namespace std;

/*
    Type traits - sa bardzo uzywane metaprogramowaniu szablonow. Daje ogromne korzysci jesli chcesz napisac generyczny kod
    wielokrotnego uzytku. Gdy uzywasz szablonow, masz mozliwosci tworzenia prawdziwych generycznych akcji. To blogoslawienstwo
    dla wielouzytkowosci kodu bo pozwala ci pisac kod raz i uzywac go potem w wielu sytuacjach. Swietnym przykladem jest cala
    biblioteka STL. Masz dostep do klas jak vector czy map, ktore pozwalaja ci tworzyc arbitralne(bezwzgledne, nieznoszace sprzeciwu)
    listy i tablice danych bez wzgledu na to jakie to dane. Jednakze, sa sytuacje gdzie potrzebujesz wiekszej kontroli nad typami
    szablonu w celu pisania bardziej efektywnego i poprawnego kodu.
*/

/*
    Np. powiedzmy ze piszesz funkcje ktore zamienia bity. Niewazne czy dostajesz 32-bitowy integer czy 64, wiec starasz sie
    napisac generyczna funkcje by to zrobic. Naiwna implementacja:
*/
/*
template<typename T>
T byte_swap(T value){
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&value);
    for(size_t i = 0; i < sizeof(T); i += 2){
        //wez wartosc z lewej i zamien ja z wartoscia po prawej
        unsigned char v = bytes[i];
        bytes[i] = bytes[i+1];
        bytes[i+1] = v;
    }
    return value;
}*/

/*
    Jesli przekazesz 32-bitowa wartosc 0x11223344 dostaniesz 0x22114433, lub jesli przekazesz 16-bitowa wartosc 0x1122
    dostaniesz 0x2211. Zgadza sie, prawda? No, nie do konca. Przechodzimy do sedna sprawy jesli chodzi o programowanie
    szablonow. W tej postaci nie masz kontroli nad tym jaki typ zostanie przekazany. Mozesz rownie dobrze przekazac
    double do funkcji i przejdzie. Lub gorzej, mozesz przekazac char i tez przejdzie przekazujac bajty randomowej pamieci
    do ktorej nie powinno dotrzec, prawdopodobnie powodujac krakse.
*/

/*
    Jednym rozwiazaniem jest czesciowe okreslanie szablonu. Mozesz stworzyc wersje funkcji ktore okreslaja typy, ktore maja
    sie w okreslony sposob zachowywac. Np.
*/
/*
template<>
double byte_swap(double value){
    assert(false && "Illegal to swap double");
    return value;
}

template<>
char byte_swap(char value){
    assert(false && "Illegal to swap chars");
    return value;
}*/

/*
    Teraz jesli wywolywacz probuje przekazac double lub char, dostanie wersje funkcji ktora assertuje i nieszkodliwie
    zwraca value. No ale co jak uzytkownik przekaze float albo unsigned char lub wskaznik? Latwo zauwazyc jak ta prosta
    funckja musialaby byc okreslana, wszystko by chronic uzytkownika.
    Tu z pomoca przychodza Type traits. Jest to sposob by dostac informacje o typie przekazywanym do aergumentow szablonu
    w czasie kompilacji, bys mogl bardziej inteligentnie zdecydowac. Podstawy Type traits:
    
    - uzywasz szablonowej struktury, zazwyczaj nazwanej z type trait ktorego szukasz (np. is_integer, is_pointer, is_void)
    - struktura posiada statyczna stala boolowska 'value' ktora robi domyslnym wrazliwy stan (which defaults to a sensible
    state)
    - tworzysz okreslenie struktury reprezentujace traits(cechy) ktore chcesz wystawic i ustawia ich boolowska wartosc
    na wrazliwy stan
    - uzywasz type trait sprawdzajac jego wartosc(value) jak my_type_trait<T>::value
*/

/*
    Np. zrobmy type trait ktory decyduje czy wartosc jest swappable(zamienna). W tym przypadku jedyne poprawne typy danych
    jakie chcemy rozpatrywac to signed i unsigned shorts, longs i long longs.
*/


    template<typename T>
    struct is_swappable{
        static const bool value = false;
    };

    template<>
    struct is_swappable<unsigned short>{
        static const bool value = true;
    };

    template<>
    struct is_swappable<short>{
        static const bool value = true;
    };

    template<>
    struct is_swappable<unsigned long>{
        static const bool value = true;
    };

    template<>
    struct is_swappable<long>{
        static const bool value = true;
    };

    template<>
    struct is_swappable<unsigned long long>{
        static const bool value = true;
    };

    template<>
    struct is_swappable<long long>{
        static const bool value = true;
    };


/*
    Teraz mozemy zastapic nasza funkcje by uzywala naszego type trait
    template<typename T>
*/

/*
template<typename T>
T byte_swap(T value){
    assert(is_swappable<T>::value && "Cannot swap this type");
    return value;
}
*/

/*
    Mamy strukture 'is_swappable' i domyslnie nic nie jest swappable wiec value=false.
    Potem mamy okreslenia dla wszystkich nie-char, nie-bool, nie-integer typow danych
    ktore ustawiaja wartosc na true. Gdy chcemy uzyc type trait, pytamy strukture o value
    i kompilator dowiaduje sie do ktorej struktury przekazac wartosc z okreslen szablonu.
    Teraz mozesz myslec sobie: "ale teraz jest wiecej kodu, i nadal nie ma zabezpieczenia
    bo moge sobie przekazac cokolwiek chce", i masz racje. Na szczescie jest kilka ratujacych
    lask. w C++11 jest standarowy STL-owy header 'type_traits' i zawiera traits dla prawie 
    wszystkiego. Sa traity ktore mowia ci podstawowe typy danych, czy cos jest wskaznikiem,
    czy tablica, czy stala(const) itd. Sa nawet traity do usuwania traitow, jak przesztalcanie
    wskaznika na wartosc, czy stala na nie-stala. Istnieje w C++11 rowniesz funkcjonalnosc 
    'static_assert', ktora uzywa wyrazen stalych czasu kompilacji jako sposob generowania bledow.
    Np. nasza byte_swap mozglaby wygladac w C++11 tak:
*/

template<typename T>
T byte_swap(T value){
    static_assert(is_integral<T>::value && sizeof(T) >= 2, "Cannot swap this type");
    return value;
}

/*
    is_integral type trait jest częścią standardu C ++ 11, ale zawiera także typy char i bool. 
    Sprawdzamy więc, czy rozmiar przekazanego typu ma co najmniej dwa bajty. Jeśli którykolwiek 
    z tych testów nie powiedzie się, assert zostanie uruchomiony w czasie kompilacji, generując 
    komunikat o błędzie "Cannot swap this type".
    Niezaleznie od tego, type traits są niewiarygodnie potęznym narzedziem do uzywania podczas 
    programowania szablonow. Pozwala na bardziej precyzyjne sterowanie funkcjonalnoscia szablonu, 
    zapewniajac, ze nikt przypadkiem naduzyje go cichym błędem.
    Inną rzeczą, o której warto pamiętać, jest to, że type traits mogą korzystać z innych type traits. 
    Więc jeśli chcesz stworzyć type trait is_swapable do użycia w wielu funkcjach, możesz to zrobić tak:
*/
/*
template<typename T>
struct is_swappable{
    static const bool value = is_integral<T>::value && sizeof(T) >= 2;
}*/

int main(){

    short f = 0;
    byte_swap<short>(f);

    return 0;
}