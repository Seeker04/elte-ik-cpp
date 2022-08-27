#include <iostream>
#include <vector>

int x = 128;

int  g() { return 42; } // ertekkel ter vissza
int& f() { return x; }  // referenciaval ter vissza

int main()
{
	// Referencia hasznalata:
	int asd = 10;
	int& ref = asd;
	std::cout << ref << "\n"; // ugyanaz, mintha a hivatkozott asd valtozot irnam
	                          // a referencia egy masodik nevet vezetett be hozza

	g() = 4; // hiba, mert a visszaadott temporalis int az egy rvalue
	f() = 5; // OK, mert lvalue referenciat adtam vissza

	std::cout << x << "\n"; // tenyleg 5 lett

	// Mire jo ez?

	// Pl. std::vector esete:
	//
	std::vector<int> v = { 10, 20, 30 };

	v[1] = 42;
	v.at(1) = 42;

	const int y;      // ez hiba, mert nem inicializalom a konstanst
	const int z = 10; // ez OK
}

