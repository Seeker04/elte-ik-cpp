#include <iostream>

int x = 10;

void f(int a, int b) { std::cout << a + b << "\n"; }
int g() { if (0 < x) return 5; else return 10; }
int h() { x = -20; return 42; }

int main()
{
	// Nem specifikalt viselkedes: a parameterek kiertekelesenek a sorrendje
	// nincs eloirva, lehet: g(), h() vagy h(), g()
	f(g(), h());
	// Ebben a peldaban mashogy mukodik a program mas-mas sorrend eseten
	// A problema okozoja, hogy (nem-const) globalis valtozot hasznalok,
	// amit a g olvas, a h atir... ezert sem szeretjuk a (nem-const) globalis
	// valtozokat...

	// Binaris operatorok eseten is hasonlo a helyzet az operandusok kiertekelesenel:
	int x = 0;
	std::cout  << ++x << ++x << "\n";
	// Zarojelezve: lehet hogy a zarojeles resz, lehet,
	// hogy a jobboldali resz fog hamarabb lefutni
	(std::cout << ++x) << ++x << "\n";
	//       I.           II.
	//
	//  I,II : 1 2
	//  II,I : 2 1
}

