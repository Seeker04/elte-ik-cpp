#include <iostream>
#include <vector>

// Alias template tipust tudunk definialni a using kulcsszoval: (typedef-fel nem lehet)
template <typename T> using Vect = std::vector<T>;

int main()
{
	Vect<int> v = { 10, 20, 30 }; // ugyanaz, mintha std::vector<int>-et irnek

	//-------------------------

	// Miert nem szerencses lebegopontos ertekeket osszehasonlitani?
	// Gepi szamabrazolas: csak veges sok erteket tudunk reprezentalni
	// (vegtelen pontossagot nem lehet veges memoriaval!)
	// Az abrazolasbol adodoan vannak numerikusan instabil muveletek,
	// pl. kivonas/osztas kerekitesi hibakhoz vezethetnek, foleg 0-hoz kozeli ertekeknel
	// Ezert sokszor nem is szoktunk direktbe ==-vel osszehasonlitani lebegopontos tipusokat
	// (inkabb azt vizsgaljuk, hogy eleg kozel vannak-e egymashoz (pl. 0.0001 kozelsegben)
	//
	// Reszleteket lasd: numerikus modszerek oran
	//
	// Ezert sem engedi a C es a C++ standard, hogy lebegopontos tipusu valtozot
	// irjunk switch kifejezesbe, hiszen az az == operatorral vizsgalja az eseteket
	//
	// Nehany pelda ennek demonstralasara:

	std::cout.precision(10); // alapertelmezetten csak 6 tizedesjegyre kerekitve irta ki

	float x = 1.0f - (1.0f / 3.0f); // 1 - 1/3 = 2/3
	float y = (1.0f / 3.0f) * 2.0f; // 1/3 * 2 = 2/3

	std::cout << x << "\n"; // 2/3 elvben, az en gepemen 0.6666666269 a kimenet
	std::cout << y << "\n"; // 2/3 elvben, az en gepemen 0.6666666865 a kimenet

	// Persze nem is lesznek ezert egyenloek:
	if (x == y) {
		std::cout << "Egyenlok!\n";
	}
	else {
		std::cout << "Nem egyenlok!\n";
	}

	// Tipp: Ha szeretnenk az ilyen kodrol figyelmeztetest kapni, akkor
	// hasznaljuk a g++ fordito -Wfloat-equal kapcsolojat!
}

