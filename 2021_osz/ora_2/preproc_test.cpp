#include <iostream>

#include "preproc_test.h"

// Parameteres makrok
#define ABS(X) ((X)<0 ? -1*(X) : (X))
#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))

#define MAGIC_NUMBER 42

int main()
{
	std::cout << "y: " << y << "\n";
	std::cout << "z: " << z << "\n";

	int x = MAGIC_NUMBER;
	std::cout << "x: " << x << "\n";

	std::cout << ABS(5) << "\n";
	std::cout << ABS(-42) << "\n";

	std::cout << MIN(10, 20) << "\n";
	std::cout << MIN(10, -20) << "\n";

	std::cout << 10/0 << "\n"; // nem forditasi hiba, de Undefined Behavior!
	                           // (legtobb rendszeren core dump-hoz vezet)
}

// Tipp: g++ -E forditassal nezzuk meg, hogy mit keszit ebbol a preprocesszor
// probaljuk ki ugy is, hogy kiszedjuk a #define VALAMI sort a header-bol

