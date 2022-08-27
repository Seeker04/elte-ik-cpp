#include <iostream>

struct Person; // osztaly (forward) deklaracio, cyclic dependency miatt

struct Car { // osztaly definicio
	Person * owner; // public a struct kulcsszo miatt
	                // kellett a struct Person deklaracio, hogy ez leforduljon!
			// hiszen itt tudnia kell, hogy Person egy tipusnev
};

class Person {
	const int id; // konstans adattag, ktor init listajaban kell inicializalni, erteket nem kaphat
	Car * car;    // privatak a class kulcsszo miatt
public:
	Person(int i) :
		id(i) // itt kell inicializalni az init listaban, mert itt lesz az id konstrualva
	{
		//id = i; // ez mar egy ertekadas lenne a mar megkonstrualt id valtozonak,
		          // de az nem megengedett, mert read-only a const kulcsszo miatt!
	                  // nyilvan e miatt setter-t sem fogok tudni neki irni
	}

	int getId() { return id; } // getter, ertek szerint ter vissza (-> temp rvalue objektum)
};

struct Point3D {
	int x;
	int y;
	int z;
};

int main()
{
	Point3D point {10, 20, 30}; // minden adattag public, lehet igy inicializalni

	std::cout << point.x << "\n"; // tag szelektor . operator hasznalata
	std::cout << point.y << "\n";
	std::cout << point.z << "\n";

	int x = 10; // valojaban nem ertekadas operator,
	            // hanem parameteres konstruktor lesz
	            // hivva
	int y(10);  // ^a ketto teljesen ekvivalens

	x = 20; // ez mar operator= hivas, mert letezo valtozonak adunk uj erteket

	Person pers(42); // objektum konstrualas parameteres konstruktor hivassal

	std::cout << pers.getId() << "\n"; // tagfuggveny hivas, out: 42

	Car car = { &pers }; // minden adattag public => tudom igy inicializalni (egy Person* kell neki)
	std::cout << car.owner << "\n"; // kiirom az adattagot, nincs dereferalas a pointer-en,
	                                // ezert csak a memoria cimet irja ki
	std::cout << &pers << "\n"; // ...ami nyilvan egyezik ezzel
}

