#include "globals.h"

void g() { int local = b; }

// Lefordul, mert az include miatt megkapja b deklaraciojat, igy tudja, hogy a
// b szimbolum egy int tipusu valtozo

