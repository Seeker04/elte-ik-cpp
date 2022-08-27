#include <iostream>

/*
  Feladat:
  Vannak globalis valtozoim:
  int a;
  int b;
  int c;
  ...
  int z;
  amiket szeretnek tobb kulonbozo forrasfajlban is elerni es hasznalni
  Hogyan oldhatnam ezt meg?
  + nem szeretnek nagyon sokat gepelni...
  Forrasok: main.cpp, a.cpp, b.cpp
*/

#include "globals.h" // innen megkapom a valtozo deklaraciokat a forditashoz
// A globals.cpp-bol generalt targykodot pedig eleg lesz ha majd a linker
// hozzaszerkeszti a main.o-hoz, hogy a definiciok is meglegyenek...

int y = -20;

int f() { return 10; }
// temporalis objektum lesz legyartva (mint a literalok), amit visszaad
// -> jobbertek (rvalue)
// -> ertekadasban csak a jobboldalon szerepelhet

int& g() { return y; }
// referenciat ad vissza egy globalis valtozorol, aminek van rendesen definialt
// elettartama (lifetime) -> balertek (lvalue) -> szerepelhet ertekadas baloldalan is
//
// Real usecase:
// pl. std::vector eseten az at() es operator[] tagfuggvenyek
// int& at(int index) {...}
// std::vector<int> vec = {10, 20, 30, 40, 50, 60, 70};
// vec.at(2) = 40
// vec[3] = 80

const int asd = 128;

int main()
{
	std::cout << a << " " << z << "\n"; // jol mukodik, elerem az a (16) es z-t (32)

	if (true) {
		int x; // lokalis valtozo: az if blokk vegeig el -> van jol
		       // definialt elettartam -> balertek (lvalue)
		x = 42;	// lvalue -> szerepelhet ertekadas baloldalan
		x = f();

		//42 = x;  // hiba, 42 egy literal, jobbertek (rvalue)
		//f() = x; // hiba, f() is jobbertek

		g() = x; // ez ok, mert a g() egy balertek referenciat ad vissza
		std::cout << y << "\n"; // valoban az y globalis lett atirva

		// Referencia letrehozasa
		x = 128;
		int& ref = x; // egy "alnev" lesz,
		              // ahova ot irom, olyan mintha x-et irtam volna
		std::cout << ref << "\n";
	}
}

