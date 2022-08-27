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
	std::cout << Fact<10>::value << "\n";
	// 3628800, a ford. legeneralja a Fact<10>, Fact<9>,..., Fact<0> osztalyokat
}

