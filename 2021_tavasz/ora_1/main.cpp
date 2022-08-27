#include <iostream>

void f();
void f();
void f(); // ezek mind csak deklaraciok, f -> void() fv tipus hozzarendeles
void f();

void f() { std::cout << "hello\n"; } // ez mar definicio, ezt csak egyszer lehet

extern int y;
extern int z; // masik ford. egysegben vannak definialva -> ezek csak deklaraciok
extern int priv;

extern void g(const char*); // fuggvenyeknek nem fontos kiirni az extern-t,
void g(const char*);        // mert oket alapbol kulso szerkesztesunek tekinti

namespace A {
	int x = -10; // megkapja az A:: nevprefixet
}

namespace A {
	int y = -20; // barmely forditasi egyseg barmely pontjan irhatok a nevterbe
}

int main()
{
	g("hello world");

	int x; // ez deklaracio es definicio is egyszerre

	std::cout << x << "\n";
	std::cout << y << "\n";
	std::cout << z << "\n";

	// std::cout << priv << "\n";
	// ez a sor hibat dobna, mert a priv az a.cpp-ben static,
	// igy mas forditasi egysegek elol el van rejtve!
}

