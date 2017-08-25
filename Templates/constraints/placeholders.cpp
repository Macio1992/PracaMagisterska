/*
    Nieograniczony placeholder auto i ograniczone placeholdery ktore maja forme concept_name<template-argument-list(optional)>
    sa placeholderami typu, ktory ma byc wydedukowany.
    Placeholdery moga pojawic sie w deklaracji zmiennej (w ktorym to przypadku sa dedukowane z inicjatora) lub w typach zwracajacych
    funkcji(w ktorym to przypadku sa dedukowane ze zwracanych deklaracji(statements))
*/

#include <iostream>

using namespace std;

template<typename T>
concept bool Sortable = true;

template<typename T>
concept bool EqualityComparable = requires(T a, T b){
    { a == b} -> bool;
};

void f(EqualityComparable &&){}

int main (){

    pair<auto, auto> p2 = make_pair(0, 'a'); //pierwsze auto to int, drugie to char

    EqualityComparable x = 4; // typ x jest dedukowany z typu jaki jest do niego przypisany, kompiluje sie tylko
    //jesli typ spelnia ograniczenia EqualityComparable
    
    int e = 4;
    auto e -> EqualityComparable;
}