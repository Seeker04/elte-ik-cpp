#include <iostream>

// Dinamikus tombot kezelo osztaly (mint pl. az std::vector)

class DynArrayHolder {
private:
	int _size;    // tomb merete
	int * _array; // dinamikus tombre fog mutatni
public:
	DynArrayHolder(int size) :
		_size(size),
		_array(new int[_size])
	{}

	// Masolo ktor (uj peldany letrehozasa masolassal)
	DynArrayHolder(const DynArrayHolder& other) :
		_size(other._size),
		//_array(other._array) NEM ezt akarom!
		_array(new int [_size]) // igy mar sajat tombje lesz
	{
		for (int i=0; i<_size; ++i)
			_array[i] = other._array[i]; // tombelem ertekeket masolom at
	}
	// ^Ez mar deep copy

	// Ertekadas operator (mar letezo peldanynak ertekul adunk egy masikat)
	DynArrayHolder& operator=(const DynArrayHolder& other)
	{
		if (&other == this) { // d1 = d1 esetet le kell kezelni! mi tortenne, ha nem kezelnenk le?
			return *this;
		}

		_size = other._size;

		delete[] _array; // az eddigi tombot ki is dobhatjuk

		_array = new int[_size]; // uj dinamikus tomb kell
		for (int i=0; i<_size; ++i)
			_array[i] = other._array[i]; // ertekek masolasa

		return *this;
	}

	// Destruktor
	~DynArrayHolder()
	{
		delete[] _array; // fel kell szabaditani a dinamikusan foglalt memoria teruletet!
		                 // minden new hivashoz kell egy delete par!
	}
};

int main()
{
	if (true) {
		// ...
		DynArrayHolder d1(2);
		DynArrayHolder d2(5);
		DynArrayHolder d3(3);
		// ...
	}
	// ^ itt a d1 torolve lesz -> d1._size es d1._array torolve lesznek
	// ha nem lenne destruktorunk, akkor d1._array pointer torlesevel el is veszne
	// a mutatott dinamikus memoriara -> memory leak
	//
	// De a pointer torlesekkor miert nem torli a mutatott objektumot is?
	//
	// Mert nem biztos, hogy mutat barmire akkor... lehet nullptr, mutathat
	// mar torolt objektumra vagy olyan objektumra, ami nem is a heap-en van,...
	// A fordito nem feltetelezheti elore, hogy futasi idoben eppen fog-e majd
	// mutatni a megsemmisuleskor valamire az _array pointer
	// Ez egyes futasi esetenkent (futasi agankent) mas-mas is lehet, pl.
	// if (...)
	//   _array = valami
	// else
	//   _array = nullptr
	// A "..." resz pedig fugghet pl user input-tol, valami fajlbol olvasott ertektol, stb.
	//
	// Megjegyzes: ha megis szeretnenk valami automatizmust, akkor annak persze
	// (minimalis) koltsegei lehetnek. Ha ez nem gond, hasznalhatunk "smart pointer"-eket...

	//----------------

	DynArrayHolder d1(10);
	DynArrayHolder d2(d1); // copy constructor
	// ^
	// A ford. altal generaltak csak shallow copy-t csinalna, de nekunk deep copy kell!
	// v
	d1 = d2; // ez mar nem konstrualas, hanem ertekadas, azaz
	         // operator= hivas
	// konvencio: terjen mindig vissza a baloldallal
	// azaz mukodjenek ezek is:
	// a = b = c; ekvivalens ezzel: a = (b = c);
	// f(a = b);

	d1 = d1; // ez se okozzon gondot! mindig keszuljunk a legrosszabbra: hogy a kodunkat felhasznalo ugyefogyott
	         // minel kisebb esellyel torhet el az osztalyunk hasznalat kozben, annal konnyebben ujrafelhasznalhato lesz

	std::cout << "hello\n";
}

