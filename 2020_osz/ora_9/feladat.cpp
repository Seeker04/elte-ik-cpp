#include <iostream>

// Feladat: altalanos foreach sablon fv megirasa

void triple(int& x) // at akarjuk irni az atadott elemet => referenciakent vesszuk at
{
	x *= 3;
}

void printBool(const bool& b) // csak olvasni akarjuk => konst referenciakent => konst objektummal is hivhato
{
	std::cout << (b ? "true" : "false") << "\n";
}

// Ezzel tetszoleges tipusu elemeket tarolo tomb elemein vegre tudunk hajtani tetszoleges fv-t
// Az elemeket meg is tudja valtoztatni, mivel referenciakent veszi at oket az f fv
template <typename T>
void foreach (T * array, int size, void(f)(T&)) {
	for (int i = 0; i < size; ++i) {
		f(array[i]);
	}
}

// Itt egy masik (sablon-)fv prototipus (mas a szignatura!), mely hasznalhato konstans tombokkel is,
// hiszen const T*-ot var parameterul es az f olyan fv-ekre mutathat, mely konstans
// referenciakent (azaz read-only modon) veszik at az elemeket
template <typename T>
void foreach (const T * array, int size, void(f)(const T&)) {
	for (int i = 0; i < size; ++i) {
		f(array[i]);
	}
}

int main()
{
	int ia[] = { 10, 20, 42, -2 };

	const bool ba[] = { true, false, true };

	foreach<int>(ia, 4, triple); // elso param: int*, harmadik: void(int&) =>
	                             // az elso fv prototipus sablonjabol lesz generalva a kod =>
	                             // atirhato hasznalat lefordul es mukodik

	for (int i=0; i<4; ++i)
		std::cout << ia[i] << "\n";

	foreach<bool>(ba, 3, printBool); // elso param: const bool*, harmadik: void(const bool&) =>
	                                 // a masodik fv prototipus sablonjabol lesz generalva a kod
	                                 // read-only hasznalat lefordul es mukodik

	// Megjegyzes #1: itt most el is hagyhatom a sablon parameterek kiirasat,
	// mert a fordito a fv parameter listakbol ki tudja kovetkeztetni a T-t,
	// hiszen szerepel bennuk
	foreach(ia, 4, triple);
	foreach(ba, 3, printBool);

	// Megjegyzes #2: a peldaban minden fv pointeres resznel elhagytam a
	// pointer deklaracios *-ot, referalo, dereferalo operatorokat, hiszen
	// ezt megengedi a standard
	// De ki is lehet oket irni, pl.
	// void(f)(T&)                  ===  void(*f)(T&)
	// f(array[i])                  ===  *f(array[i])
	// foreach<int>(ia, 4, triple)  ===  foreach<int>(ia, 4, &triple)
	// Izlesen/kodolasi konvencion mulik, hogy kiirjuk-e vagy sem ezeket...
}

