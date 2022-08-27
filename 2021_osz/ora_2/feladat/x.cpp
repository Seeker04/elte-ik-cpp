#include "globals.h"

void f() { int local = a; }

// Lefordul, mert az include miatt megkapja a deklaraciojat, igy tudja, hogy az
// a szimbolum egy int tipusu valtozo

