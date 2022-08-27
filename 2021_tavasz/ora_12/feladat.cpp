#include <iostream>
#include <list>

// [10][next] -> [-3][next] -> [42][next]
//                                 |                        -> [7][nullptr]
//                                 v                       /
//                                [1024][next] -> [-19][next]

int main()
{
	std::list<int> list = { 10, -3, 42, 1024, -19, 7 };

	// Torolni szeretnek minden paros elemet a listabol es utana kiiratni a
	// megmaradt elemeket
	// De ez futasnal segmentation fault-ot dob! Hol a hiba?

	// Hibas ciklus
	for (typename std::list<int>::iterator it = list.begin(); it != list.end(); ++it) {
		if (*it % 2 == 0) {
			list.erase(it);
			// Ha erase-zel torlom az elemet, amin az it iterator all,
			// akkor az it mar nem lesz valid (gondoljunk csak bele:
			// a lancolt listaban a node torolve lesz a next pointerevel egyutt, "ki lesz fuzve")
			// Ezert a kovetkezo iteraciohoz a ++it kifejezesben
			// a lepteteshez megprobalja a next-et elerni egy mar torolt node-on -> segfault
		}
	}

	// Helyes ciklus #1
	for (typename std::list<int>::iterator it = list.begin(); it != list.end();) { // <- kiszedtem innen a ++it kifejezest
		if (*it % 2 == 0) {
			list.erase(it++);
			// Postfix increment: lepteti az it-t a kovetkezo elemre,
			// majd visszaad egy masolatot amiben meg az eredeti iterator ertek van
			// Hasonlo modon:
			// int x = 5;
			// std::cout << x++; // output: 5, de x innentol mar 6 lesz
			// Igy it-t raleptettem a kovetkezo elemre, meg mielott toroltem az elozot
		}
		else {
			++it;
			// Ha nem torlok elemet, akkor csak leptetni kell
		}
	}

	// Helyes ciklus #2
	for (typename std::list<int>::iterator it = list.begin(); it != list.end();) { // <- itt sincs ++it a for ciklus vegen
		if (*it % 2 == 0) {
			it = list.erase(it); // az erase visszaad egy iteratort, ami a torolt elem utan all
			                     // (lehet == .end()-del, ha a torolt elem mar az utolso volt)
		}
		else {
			++it;
		}
	}

	// Ezzel mar csak kiiratom a listat ellenorzeskepp
	for (typename std::list<int>::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
		std::cout << *it << "\n";
	}

	// Tanulsag: ha iteracio kozben akarok elemet torolni az adatszerkezetbol,
	// akkor oda kell figyelni, hogy ne maradjak invalid iteratorral, amit
	// mar nem lehet tovabb leptetni!
}

