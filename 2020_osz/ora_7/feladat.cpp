#include <iostream>

class DynArrayHolder {

private:
	int size;
	int * array;

public:
	DynArrayHolder(int s) :
		size(s),
		array(new int[size])
	{}
	// a new operator visszaadja az allokalt es inicializalt
	// (size db int objektum lett default konstrualva)
	// memoria terulet kezdo cimet, azzal inicializalom az array pointert
	//
	// megj.: az array inicializalasa hasznalja a size adattagot, ezert fontos,
	// hogy az mar inicializalva legyen ekkor. Ez garantalt, mert az osztaly
	// definicioban a size adattag hamarabb (feljebb) szerepel, mint az array,
	// igy memoriaban is "elorebb" lesz es hamarabb is lesz inicializalva
	// Tehat EZ szamit es NEM az init listaba irt sorrend!

	~DynArrayHolder()
	{
		delete[] array;
	}
	// deallokalja a dinamikus tomb osszes elemet
	// elotte az osszesen hiv destruktort is (ha van,
	// int objektumokhoz persze nem kell dtor)
	// roviden: torli az osszes din. allokalt objektumot

	int operator[](int i) const
	{
		return array[i];
	}
	// ertek szerint ter vissza, konstrualni fog egy temp int objektumot
	// (masolas) a hivas helyere => ezzel csak olvasni tudjuk az elemeket
	// => lehet const tagfv => az implicit atvett this egy const pointer =>
	// meg lehet hivni const peldanyokon is, ami nyilvan logikus, mert csak
	// lekerdezunk egy elemet
};

int main()
{
	// Addig olvasok be kivant mereteket es hozok letre DynArrayHolder
	// peldanyokat, amig 0-at nem olvasok
	while (true) {
		int s;
		std::cout << "Size: "; std::cin >> s;
		if (s==0)
			break;

		DynArrayHolder dah(s); // egyszeru lokalis valtozoja a while blokknak
		                       // hivasi verembe kerul (stack)

		for (int i=0; i<s; ++i)
			std::cout << dah[i]; // ellenorzes
		std::cout << "\n";

		//delete[] dah.array; // <-- ilyet nyilvan nem tudnek irni, mert
		                      //     az array egy privat tag!

		// itt a blokk osszes lokalis valtozoja megsemmisul (s, dah) es
		// ekkor persze lefut az osszes destruktora (mar aminek van)
		// => DynArrayHolder::~DynArrayHolder fel fogja szabaditani a
		// tarolt pointere altal mutatott dinamikus tarhelyet => nincs memory leak
	}
}

