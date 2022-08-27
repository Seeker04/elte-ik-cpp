#include <iostream>
#include <set>

struct Person {
	int id;
	std::string name;
	unsigned int age;
};

struct CmpPerson {
	bool operator()(const Person& p1, const Person& p2) const {
		return p1.id < p2.id;
	}
}; // ez egy predikatum, lasd: funktorok, predikatumok

// Ha van operator< definialva hozza, akkor az std::set sablonparameter
// listajabol el is hagyhatom a CmpPerson-t, mert akkor default-olni
// fog a parameter az std::less<Person>-ra, ami operator<-ot hiv...
bool operator<(const Person& p1, const Person& p2) {
	return p1.id < p2.id;
}

int main()
{
	// Az std::set egy binaris faval dolgozik. Elem beszurasa eseten a gyokerbol
	// indulva megnezi, hogy az uj elem kisebb vagy nagyobb-e az aktualisnal
	// es aszerint a bal vagy a jobb reszfaba szurja be. Ez addig tart, mig el nem
	// er a level szintre, ahova beszurja VAGY nem talal olyan elemet, amivel
	// ekvivalens mar van a faban, ami esetben az elem nem kerul beszurasra.
	// Eml.: a es b ekvivalensek, ha:
	// !(a < b) && !(b < a)
	//
	// Ket Person akkor lesz ekvivalens, ha egyezik az id adattagjuk
	//
	// Megj.: ebbol adodik, hogy a legtobb muvelet log n komplexitasu

	// Peldanyositas
	std::set<Person, CmpPerson> s = {
		Person{ 10, "Asd1", 20 },
		Person{ 42, "Asd2", 25 },
		Person{  5, "Asd3", 10 },
		Person{  9, "Asd4", 40 },
		Person{ 42, "Asd5", 25 }, // ekvivalens elem mar van! -> nem lesz beszurva
		Person{  1, "Asd6", 99 },
	};

	// Uj elem beszurasa
	s.insert( Person{ 30, "hello world", 35 } );

	// Iteralas
	std::set<Person>::iterator it = s.begin();
	while (it != s.end()) {
		std::cout << (*it).id   << "\n";
		std::cout << (*it).name << "\n";
		std::cout << it->age    << "\n"; // szintaktikus atiras, itt is lehet hasznalni
		std::cout << "--------\n";
		++it;
	}
	// A kiiratasok sorrendjen latszik, hogy tenyleg id szerint
	// vannak rendezve az objektumok az adatszerkezetben
}

