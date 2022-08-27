#include <iostream>

template <int i>
struct Fact {
	static const int value = i * Fact<i-1>::value; // itt, osztaly torzsben inicializalni csak static const adattagokat lehet
};

template <> // template specializacio, megadjuk egy konkret "eset" (template parameter) eseten az osztaly definiciot
struct Fact<0> {
	static const int value = 1;
};

int main()
{
	std::cout << Fact<4>::value << std::endl;
	std::cout << Fact<10>::value << std::endl; // a fordito legeneralja a Fact<10>, Fact<9>,..., Fact<0> osztalyokat

	// forditasi idoben kiszamoltatjuk a forditoval a 4! es 10! ertekeket, futasi idoben csak kiiratjuk ezeket (ami konstans ideju)
	// Elonyok: helytelen kod le se fordul, release verzioba be se tud kerulni, sokminden csak ezzel oldhato meg (<functional>, boost lib,...)
	// Hatranyok: forditasi ido nagyobb, statikus idoben ismertnek kell lennie a parameternek (nem fugghet inputtol),
	// bonyolult kod, nehezen megfejtheto hiba uzenetek, nemigen lehet debuggolni
}

