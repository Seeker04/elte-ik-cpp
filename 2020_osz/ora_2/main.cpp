#include <iostream>

#include "globals.h"

int i = 42;

void f(int a, int b) {
	if (a > 0)
		std::cout << "igen\n";
	else
		std::cout << "nem\n";
}

int g() { if (i == 42) return 10; else return -20; } // olvassa i globalis valtozot
int h() { i = 100; return 20; }                      // irja i globalis valtozot
// => nem mindegy, melyik fut le elobb!

int  fv_return_by_value()  { return 42; } // ertekkel ter vissza, temporary object lesz, ami rvalue
int& fv_return_reference() { return i;  } // referenciaval ter vissza, ami egy globalis valtozora hivatkozik, lehet lvalue

int main()
{
	std::cout << x << "\n"; // mivel a forditashoz deklaralva vannak (lasd: #include "globals.h"),
	std::cout << y << "\n"; // hasznalhatom a masik ford. egysegben definialt
	std::cout << z << "\n"; // valtozokat

	//---------------------------------------------------------------------

	// NEM SPECIFIKALT / NEM DEFINIALT / IMPL ALTAL DEFINIALT VISELKEDES

	f( g(), h() ); // nem specifikalt viselkedes: parameterek kiertekelesenek sorrendje
	               // a standard nem irja elo, lehet hogy g(),h() vagy h(),g() - de a ketto kozul valamelyik
	               // a kimenet lehet "igen" es "nem" is...
	               // pl ezert nem szeretjuk a globalis valtozokat

	int array[3] = {10, 20, 30};

	std::cout << array[0] << "\n";
	std::cout << array[1] << "\n";
	std::cout << array[2] << "\n";
	std::cout << array[3] << "\n"; // nem definialt viselkedes, a standard nem ir elo semmit errol,
	                               // tortenthet barmi
	                               // memoria szemet lesz kiirva, vagy crash (szegmentacios hiba)
	std::cout << array[300000] << "\n"; // ez a memoria cim mar jo esellyel nem is az en folyamatomhoz tartozik!

	std::cout << sizeof(int) << "\n"; // implementacio fuggo viselkedes, rendszerenkent elterhet

	//---------------------------------------------------------------------

	// LVALUE VS RVALUE

	int asd;

	asd = 30;  // OK, asd balertek (lvalue)
	30 = asd;  // Hiba, 30 jobbertek (rvalue), ertekadasban csak jobboldalt szerepelhet!
	asd = fv_return_by_value();  // OK, asd balertek (lvalue), f() jobbertekkel (rvalue) ter vissza

	fv_return_by_value()  = 128;  // Hiba, a fv temporary object-et keszit, nem lehet lvalue!
	fv_return_reference() = 128;  // OK, referenciat ad vissza egy globalis valtozora, aminek van
	                              // jol definialt elettartama, ezert kaphat uj erteket

	std::cout << i << "\n"; // tenyleg 128 lett

	// A referenciaval valo visszaterest gyakran hasznaljuk, ha pl valamilyen gyujtemeny
	// elemet szeretnem elerni es akar modositani egy tagfuggvenyen (vagy operatoron) keresztul
	// Pl.
	// obj.at(10) = 100
	// vector[20] = asd;

	//---------------------------------------------------------------------

	// POINTEREK

	int var = 42;

	int * p = &var; // referalo operator memoria cimet ad vissza: & : T -> T*
	                // p a var cimet tarolja, "ramutat"

	char * p2 = &var; // Tipus hiba: & az int-bol int*-ot csinal, ami nem tipushelyes a char*-gal
	//         (int*)

	std::cout << 10 + *p << "\n"; // dereferalo operator, visszater a megadott cimen tarolt objektummal:
	                              // * : T* -> T

	const int casd = -10; // read-only valtozo
	int * p3 = &casd; // Hiba, nem tipushelyes, mert & : const T -> const T* (a const nem veszhet el!)
	//      (const int*)                        es int* nem kaphat erteket const int*-tol (forditva ok)
	//*p3 += 20; // ide igy el sem jut a fordito

	// Ki lehet-e cselezni? Valasz: nem
	const int * cp = &casd; // ez igy mar OK, tipushelyes, const pointer mutathat const object-re
	*cp += 20;              // itt viszont mar gond van, mert * : const T* -> const T,
	                        // igy egy const object-et probalna megvaltoztatni a += operator! -> nem fordul le

}

