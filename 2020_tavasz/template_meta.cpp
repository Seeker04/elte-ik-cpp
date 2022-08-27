#include <iostream>

template <int i> // az int egy integrális típus, ezért lehet template paraméter int típusú
struct Fact {
	static const int value = i * Fact<i-1>::value; // itt osztály törzsben inicializálni csak static
};                                                     // const adattagokat lehet

template <> // template specializáció, megadjuk egy konkrét "eset" (sablonparaméter) esetén az osztálytörzset
struct Fact<0> {
	static const int value = 1; // ez lesz a rekurzió alapesete
};

int main()
{
	std::cout << Fact<4>::value << "\n"; // 24
	std::cout << Fact<10>::value << "\n"; // 3628800, a ford. legenerálja a Fact<10>, Fact<9>,..., Fact<0> osztályokat
}

