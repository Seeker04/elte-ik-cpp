#ifndef GLOBALS__H
#define GLOBALS__H

extern int a;
extern int b;
extern int c;
//...
extern int z;

// Ezek csak deklaraciok, hiszen az extern azt mondja "ez masik forditasi egysegben
// van definialva" (kulso szerkesztesu == external linkage)
//
// Ami ezt include-olja, az hasznalhatja ezeket a valtozokat, le fog fordulni,
// hiszen a fordito tudja majd ellenorizni a felhasznalasok tipushelyesseget,
// illetve fog tudni gepi kodot generalni belole
//
// A valtozok definicioira majd csak a linkelesi lepesnel lesz szukseg,
// azokat celszeru egy kulon erre dedikalt forditasi egysegbe csoportositani,
// lasd: globals.cpp

#endif // GLOBALS__H
