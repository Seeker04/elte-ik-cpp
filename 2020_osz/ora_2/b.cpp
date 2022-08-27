#include <iostream>

#include "globals.h"

void b()
{
	std::cout << x << "\n" << y << "\n" << z << "\n";
}

// Ez lefordul, mivel a globals.h tartalma a file elejere lesz masolva (preprocesssor),
// igy az extern-es deklaraciok benne lesznek (x,y,z tipusai ismertek lesznek
// a forditashoz)
// Az pedig oke, hogy egy kulon forditasi egysegben vannak ok definialva, arra
// majd csak az osszeszerkesztesnel (linke-eles) lesz szukseg...

