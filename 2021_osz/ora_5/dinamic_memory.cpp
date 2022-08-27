#include <iostream>

int* create_array()
{
	int * array = new int[10];

	return array;
}
// Dinamikus memoriat foglal: 10*sizeof(int)-et, default konstrual 10 db int objektumot
// erre a memoria teruletre -> dinamikus tomb
// Visszaadja a tomb pointer-t, azaz a legelso elem cimet

int main()
{
	int * t = create_array(); // eltaroljuk a dinamikus tombrol visszaadott cimet

	// ...
	// itt hasznalhatjuk a tombot t-n keresztul, pl. t[5] = 42;
	// ...

	delete[] t; // Fel kell szabaditani a dinamikusan foglalt tarteruletet!
}


// DE ez nem mindig teljesen trivialis! ---------------------------------------

int main_2()
{
	int * t = create_array();

	// ...

	int x;
	std::cin >> x;

	if (10 < x) {
		std::cout << "Tul nagy!\n";
		delete[] t; // a fv itt is terminalhat, "ido elott",
		return 1;   // ezert ide is be kell rakni a return ele a delete[]-t
	}                   // (vagy az egesz kodot teljesen at kene csoportositani...)
	else if (x < 0) {
		std::cout << "Negativ!\n";
		delete[] t;
		return 2; // hasonloan
	}

	// ...

	delete[] t; // Fel kell szabaditani a dinamikusan foglalt tarteruletet!
}

// Latszik, hogy eleg korulmenyesse valhat a helyzet, hiszen szamos helyre ki kell
// irni a delete[] t; utasitast, hosszu fv eseten konnyen lemaradhat valahonnan
// + ha kesobb valaki modosit a kodon, akkor lehet, hogy ez elkeruli a figyelmet
// -> konnyu uj hibat bevezetni -> nehezen maintain-elheto -> rosszul skalazodik a kod ->...


// Sajnos megrosszabb a helyzet! Mi van, ha... --------------------------------

void h()
{
	//...
	throw std::string("Valami gond van!"); // kivetelt dob (try {} catch ()-vel lehetne kezelni)
	//...
}
// Megrosszabb a helyzet: ezek a fuggvenyek lehet hogy valami mas fajlban
// vannak definialva -> megnehezebb latni a hibat...

void g() { h(); } // olyan fv-t hiv, ami kivetelt dobhat, de ezt ezen a szinten nem kezeljuk...

void f() { /*...*/ }

int main_3()
{
	int * t = create_array();

	f();

	int x;
	std::cin >> x;

	g(); // ez (nem feltetlen minden futas eseten, de) dobhat kivetelt,
	     // amit nem kezelek le -> ezen a ponton terminal ez a fv ugy, hogy
	     // delete[] t nem lett futtatva! -> memoria szivargashoz jutunk

	if (10 < x) {
		std::cout << "Tul nagy!\n";
		delete[] t;
		return 1;
	}
	else if (x < 0) {
		std::cout << "Negativ!\n";
		delete[] t;
		return 2;
	}

	delete[] t; // Fel kell szabaditani a dinamikusan foglalt tarteruletet!
}

// Akkor mi a megoldas?
// - Tegyuk a g(); hivast egy try{} catch() blokkba?
// - De mi van, ha pl. f() is dobhat kivetelt?
// - Legyen f()-nek is sajat try-catch blokkja?
// - Legyen egy nagyobb try blokk, amiben f(); es g() is benne van?
// - Ennyi erovel miert ne lehetne az egesz fv egy nagy try-catch blokkban?
// - Nem lenne "csunya" a kodban minden fv-t teleirni try-catch blokkokkal?
// - Mi van ha ma nem is dobhat f() es/vagy g() kivetelt, de holnap egy fejleszto
//   modosit valamelyiken es mar dobhat? Az osszes hasznalatat vegig kene neznie
//   a teljes kodbazison? Ha f() vagy g() egy dependenciaja valtozik (pl. fv, amit hiv,
//   akkor rekurzivan kene minden hasznalatot vegignezni?
// - Mi van ha nem is f() vagy g() tud kozvetlenul dobni, hanem valami dependenciajuk?
//   (Lasd: h() fv esete). Mi van ha a dependencia egy 3rd party lib-bol jon?
// - Mi van, ha nem egyedul dolgozok a kodbazison es ezt az 1000+1 dolgot mindenkinek
//   szem elott kell mindig tartania?
// - Ezek utan mennyi ido fog ilyen dolgokkal elmenni?
// - Ezek utan mennyire lesz a kodunk: robusztus? hibamentes? skalazhato? maintain-elheto?
// - ...

// Na jo, de akkor mi a tenyleges megoldas?
// RAII elv:
// Roviden:
// - keruljuk a nyers pointer-ek hasznalatat
// - helyettuk hasznaljunk olyan osztalyokat, amik osszekotik az altaluk kezelt
//   eroforrasok hasznalati idejet a sajat elettartamukkal
//   (pl. std::vector vagy mas STL kontenerek, smart pointer-ek, stb.)
//
// Ehhez lasd a kovetkezo (nagyon hasonlo) peldat: file_resource_handling_with_RAII.cpp

