#include <iostream>

class Animal {
public:
	virtual void walk() { std::cout << "General walking\n"; } // altalanos viselkedes, de feluldefinialhato
	                                                          // + a "virtual" miatt menni fog a dinamikus kotes is
private:
	char name[64];
};

class Dog : public Animal {
public:
	void walk() // feluldefinialjuk a szulo virtualis metodusat
	{
		if (angry) { // olyan adattagot hasznalunk, ami csak a Dog-nak van
			std::cout << "Running\n";
		}
		else {
			std::cout << "Walking\n";
		}
	}
private:
	bool angry; // ez meg bekerul az objektum vegere a megorokolt name adattag utan
};


void do_something_with_an_animal(Animal animal)
{
	// animal itt egy fixen Animal statikus tipusu valtozo
	// hiszen ertek szerint lett atadva -> fix meretu (N byte) masolat lett a stack-re irva
	// (objektum prefixet veszi + a _vptr-t atallitja Animal fv tablajara)
	animal.walk();
}

void do_something_with_an_animal_ptr(Animal * animal_ptr)
{
	// animal_ptr egy Animal-re vagy annak egy leszarmazottjara is mutathat
	// hiszen csak egy pointert adtunk at, ami csak egy memoria cim: ~8 byte
	// (nincs slicing, _vptr-t sem bantja, tovabbra is Dog fv tablajara mutat)
	animal_ptr->walk();
}

// Referenciaval is mukodni fog: (lenyegeben ugyanazzal lehet indokolni, mint a ptr esetet...)
void do_something_with_an_animal_ref(Animal& animal_ref)
{
	animal_ref.walk();
}

int main()
{
	Animal animal;
	Dog dog;

	do_something_with_an_animal(animal);
	do_something_with_an_animal(dog); // slicing fog tortenni, Dog -> Animal
	                                  // dog egy sima Animal-re lesz upcast-olva
	                                  // -> nincs polimorf viselkedes

	do_something_with_an_animal_ptr(&animal);
	do_something_with_an_animal_ptr(&dog); // csak cimet adunk at, igy nincs slicing
	                                       // -> polimorf viselkedes meglesz

	// Ezzel is mukodik:
	do_something_with_an_animal_ref(animal);
	do_something_with_an_animal_ref(dog);
}

