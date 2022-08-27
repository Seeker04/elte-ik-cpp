#include <iostream>

// 1. pluszminusz

using namespace std;

int main()
{
	const int t[] = { 10, 4, 3, 8, 1 };

	int * const p = &t[1]; cout << *(&(*p)); // forditasi hiba
	int * q = &t[2]; cout << *q;             // forditasi hiba
	cout << *(t+3);                          // 8
	cout << t[6]-3;                          // undefinded behavior
	int const * r = t; cout << *r;           // 10
}

