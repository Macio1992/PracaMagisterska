#include <iostream>

using namespace std;

template<typename T>
concept EqualityComparable()
{
	return requires{
		bool operator==(const T& x, const T& y);
	};
	
}

int main () {
	
	
}
