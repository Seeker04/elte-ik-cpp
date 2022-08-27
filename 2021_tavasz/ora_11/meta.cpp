#include <iostream>

template <int i> // az int egy integralis tipus, ezert lehet sablon param
struct Fact {
	static const int value = i * Fact<i-1>::value; // static es const => inline lehet inicializalni
};

// Template specializacio: egy konkret sablon param esetere (i=0) irok egy kulon sablont
template <>
struct Fact<0> {
	static const int value = 1;
};

int main()
{
	std::cout << Fact<4>::value << "\n";

	// Fact<4>::value = 4 * Fact<3>::value = 4 * 3 * Fact<2>::value = ... = 4 * 3 * 2 * 1 * 1

	std::cout << Fact<10>::value << "\n";
	// 3628800, a ford. legeneralja a Fact<10>, Fact<9>,..., Fact<0> osztalyokat

	// Nem fordul le, miert?
	int x;
	std::cin >> x;
	std::cout << Fact<x>::value << "\n";
	// Template-ek ~ Forditasi ideju polimorfizmus (compile time polymorphism)
	// a fordito futasi idoben mar nem jatszik, o nem latja, hogy mi lesz az x
	// a dinamikus idoben
}

