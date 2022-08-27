#include <iostream>

#include "header.h"  // a preprocessor a tenyleges C++ forditas elott ide fogja masolni
#include "header2.h" // ezen fajlok tartalmait

//class MyClass; //dekl
//class MyClass { ... }; //def

int x; // x <- int tipus hozzarendeles, ezert dekl
       // def is, mert e sor hatasara memoriaba fog kerulni a valtozo

void f(int); // f <- void(int) tipus, dekl
void f(int); // f <- void(int) tipus, dekl
void f(int); // f <- void(int) tipus, dekl

void f(int n) // def, csak 1x lehet!
{

}

int g(char c) { return 0; } // lehet fv-t egyszerre dekl + def

extern int a; // extern: masik ford egysegben van a def -> ez csak dekl lesz

//extern int c; // linkeleskor lenne hiba, mert sehol nincs c definialva

namespace X { int a = 30; } // nevprefixek, igy nincs nevutkozes
namespace Y { int a = 40; }

void hello(); // tipus: void()

//extern int priv; // linkeleskor lenne hiba, mert nincs kulso szerkesztesu priv valtozo
                   // (ami az a.cpp-ben van az static, igy "el van rejtve" mas ford. egysegek elol)

namespace X {
	void h() {
		int a = 128; // learnyekolas: "a" a lokalis scope valtozojat hivatkozza
		std::cout << a << " " << ::a << "\n";
	};
}

int main()
{
	int x = 10; // ez: dekl + def + init
	std::cout << x << "\n";

	std::cout << a << "\n";
	//std::cout << c << "\n";

	hello();
	//std::cout << priv << "\n";

	std::cout << X::a << "\n";
	std::cout << Y::a << "\n";

	X::h();

	std::cout << z << "\n";
	out();
}

