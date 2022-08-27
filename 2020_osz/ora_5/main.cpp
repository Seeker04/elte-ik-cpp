#include <iostream>

struct Person; // osztaly (forward) deklaracio, korkoros dependencia miatt

struct Car { // definicio
	Person * owner; // public a struct kulcsszo miatt
	                // kellett a struct Person deklaracio, hogy ez leforduljon!
};

class Person {
	const int id;
	Car * car; // private a class kulcsszo miatt
public:
	Person(int i) :
		id(i) // itt kell inicializalni az init listaban, mert itt lesz az id konstrualva
	{
		//id = i; // ez mar egy ertekadas lenne a mar megkonstrualt id valtozonak,
		          // de az nem megengedett, mert read-only a const kulcsszo miatt!
	                  // nyilvan e miatt setter-t sem fogok tudni neki irni
	}

	int getId() { return id; } // getter
};

int main()
{
	int x = 10; // valojaban nem ertekadas operator,
	            // hanem parameteres konstruktor lesz
	            // hivva
	int y(10);  // ^a ketto teljesen ekvivalens

	x = 20; // ez mar operator= hivas, mert letezo valtozonak adunk uj erteket

	Person pers(42); // objektum konstrualas parameteres konstruktor hivassal

	std::cout << pers.getId() << "\n"; // tagfuggveny hivas, out: 42

	Car car = { &pers }; // minden adattag public => tudom igy inicializalni (egy Person* kell neki)
	std::cout << car.owner << "\n"; // kiirom az adattagot, nincs dereferalas,
	                                // ezert csak a memoria cimet irja ki
	std::cout << &pers << "\n"; // ...ami nyilvan egyezik ezzel az objektumeval
}

