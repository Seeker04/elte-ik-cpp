#include <iostream>

// Felsorolasi tipus
enum Valami {
	A,      // 0
	B = 42,
	C,      // 43
	D = 42  // Nem gond, hogy egyezik Valami::B-vel (bar a legtobb enum usecase eseten ezt kerulni szoktuk)
};

int main()
{
	std::cout << Valami::A << "\n";
	std::cout << Valami::B << "\n";
	std::cout << Valami::C << "\n";
	std::cout << Valami::D << "\n";
}

