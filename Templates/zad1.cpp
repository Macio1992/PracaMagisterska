#include <iostream>

using namespace std;

concept EqualityComparable<typename T>
{
	bool operator==(const T& x, const T& y);
}

int main () {
	
	
}
