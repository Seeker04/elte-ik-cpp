#include <iostream>

int main()
{
	// tfh. most gepi szo    == 4 byte
	// tfh. most sizeof(int) == 4 byte

	struct S1 {
		char c[2];  // 2
		            // itt lesz egy 2 byte-os "hole"
		int x[2];   // 8
		char d[2];  // 2
		            // lesz meg 2 byte "padding" is a vegen
	};

	struct S2 {
		char c[2];  // 2
		char d[2];  // 2
		int x[2];   // 8
	};

	std::cout << "sizeof(S1): " << sizeof(S1) << "\n";
	std::cout << "sizeof(S2): " << sizeof(S2) << "\n";
	std::cout << "\n";

	// Lathatjuk, hogy S1 es S2 kozott csak a tagok sorrendje a kulonbseg,
	// S1 megis 16 byte, S2 pedig csak 12!
	//
	// Implementacio fuggo viselkedes: hatekonyabb, ha a tagok mind egy
	// "kerek" cimen kezdodnek, ami a gepi szo (word) tobbszorose
	// A forditok kapnak a standard-tol ennyi mozgasteret

	S1 s1;
	S2 s2;

	// Lehet pl. a tagok memoria cimet vizsgalva nezni, hogy melyik hol kezdodik
	std::cout << &(s1)   << "\n";
	std::cout << "----------\n";
	std::cout << &(s1.c) << "\n";
	std::cout << &(s1.x) << "\n";
	std::cout << &(s1.d) << "\n";

	std::cout << "\n";

	// Vizsgalhatjuk magukat az offset-eket a teljes objektum elejetol:
	std::cout << (char*)&(s1.c) - (char*)&(s1) << "\n";
	std::cout << (char*)&(s1.x) - (char*)&(s1) << "\n";
	std::cout << (char*)&(s1.d) - (char*)&(s1) << "\n";

	std::cout << "\n";

	// Kicsit kenyelmesebb eszkoz erre a debugger:
	// g++ -g sizeof.cpp
	// gdb ./a.out
	// (gdb) break 50
	// (gdb) run
	// (gdb) ptype /o s1
	// (gdb) ptype /o s2
}

