#include <iostream>

#include "globals.h"

// A globals.h include miatt megkapja a deklaraciokat
// igy az a es z szimbolumok ismert tipusu valtozok
// -> le tudja forditani
// (majd linkeleskor raer meglennie a definicioknak
// valamelyik masik ford. egyseg targykodjabol)

static void f()
{
	std::cout << a << z;
}

