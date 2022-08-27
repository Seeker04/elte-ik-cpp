// dinamic_memory.cpp gondolatainak folytatasa:

#include <iostream>
#include <fstream>

void h()
{
	//...
	throw std::string("Valami gond van!"); // kivetelt dob (try {} catch ()-vel lehetne kezelni)
	// ...
}

void g() { h(); } // olyan fv-t hiv, ami kivetelt dobhat, de ezt ezen a szinten nem kezeljuk...

int main()
{
	FILE * f = fopen("test.txt"); // file megnyitas: fizikai eroforrast foglalok

	int x;
	std::cin >> x;

	// A kivetel miatt problemas ismet!
	g(); // Ha dob, akkor ez a fv is meg lesz szakitva es f sose lesz fclose()-zal lezarva!

	if (10 < x) {
		std::cout << "Tul nagy!\n";
		fclose(f); // mar megint oda kell figyelnem, hogy minden futasi agon le legyen zarva...
		return 1;
	}
	else if (x < 0) {
		std::cout << "Negativ!\n";
		fclose(f); // mar megint oda kell figyelnem, hogy minden futasi agon le legyen zarva...
		return 2;
	}

	fclose(f); // le kell zarni a fajl deszkriptort!
}

int main_2()
{
	std::ifstream fs("test.txt");

	int x;
	std::cin >> x;

	g();

	if (10 < x) {
		std::cout << "Tul nagy!\n";
		return 1;
	}
	else if (x < 0) {
		std::cout << "Negativ!\n";
		return 2;
	}
}

// Nincs sehol semmifele close. De nem is kell! Se a vegere, se a return-ok ele, sehova
//
// Az std::ifstream osztaly kezeli az eroforrast helyettunk, ezt a feladatot
// elabsztraktalja, azaz elrejti
//
// Hogyan teszi ezt?
//
// fs konstruktor: megnyitja a file-t
// fs destruktor: lezarja a file-t
// Az fs egy lokalis valtozo -> biztos, hogy torolve lesz, mindegy, hogy hol
// terminal a fv. Meg akkor is, ha egy kezeletlen kivetel miatt terminal a fv!
//
// RAII: Resource Acquisition is Initialization
// Lenyegeben azt tesszuk, hogy a file resource hasznalati idejet osszekotjuk az
// objektumunk elettartamaval
// - Az objektumok minden altaluk hasznalt eroforrast inicializalaskor foglaljanak le
// - Megsemmisuleskor pedig az osszeset szabaditsak fel
//
// Pl. az std::vector is ezt csinalja. Egy dinamikus tombot kezel elrejtve
// (privat adattag) es az std::vector objektum torlesekkor az oaltala kezelt
// din. tombot is torli magaval
// Igy kenyelmesen es hiba lehetoseg nelkul hasznalhatjuk -> kevesebb es jobb minosegu
// kod -> maintain-elhetobb -> jobban skalazodik -> idot/penzt sporolunk + jobb kodbazisunk lesz

