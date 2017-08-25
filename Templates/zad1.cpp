#include <iostream>

using namespace std;
/*
    template<int i>
    class LOOP{
        public:
            static inline void EXEC(){
                cout <<"A-"<<i<<" ";
                LOOP<i-1>::EXEC();
                cout<<"B-"<<i<<" ";
            }
    };

    template<>
    class LOOP<0>{
        public:
            static inline void EXEC(){
                cout<<"A-"<<0;
                cout<<"\n";
                cout<<"B-"<<0;
            }
    };

    template<bool Condition>
    class IF {
        public:
            static inline void EXEC(){
                cout<<"Statement is true";
            }
    };

    template<>
    class IF<false> {
        public:
            static inline void EXEC(){
                cout<<"Statement is false";
            }
    };

    template<int _case>
    class SWITCH {
        public:
            static inline void EXEC(){
                cout<<"SWITCH-default ";
            }
    };

    template<>
    class SWITCH<1> {
        public:
            static inline void EXEC(){
                cout<<"SWITCH - 1 ";
            }
    };

    template<>
    class SWITCH<2> {
        public:
            static inline void EXEC(){
                cout<<"SWITCH - 2 ";
            }
    };
*/

void print(int i){
    cout<<i<<endl;
}

void print(const string &i){
    cout<<i<<endl;
}

void print(double i){
    cout<<i<<endl;
}

void print(bool i){
    cout<<i<<endl;
}

int main () {
    
    /*SWITCH<2> x;
    x.EXEC();
    IF<false>::EXEC();
    x.EXEC();*/

    return 0;
}
