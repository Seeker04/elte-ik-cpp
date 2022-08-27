#include <iostream>

#include <array>
#include <list>

#include <algorithm> // count
#include <numeric> // accumulate

template <typename T>
T multiply(T left, T right) { return left * right; }

int main()
{
	const std::array<int, 10> ints = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// Alapertelmezetten operator+-ot hasznal (egysegelemnek a 0 kell)
	std::cout << std::accumulate(ints.cbegin(), ints.cend(), 0) << "\n";

	// Most szorozni szeretnem oket (egysegelemnek az 1 kell, atadom a szorzo fuggvenyt)
	std::cout << std::accumulate(ints.cbegin(), ints.cend(), 1, multiply<int>) << "\n";

	//-------------------------------

	std::list<std::string> strs = { "hello", "world", "c++", "world", "world" };

	// std::string eseten az operator+ konkatenalni fog
	std::cout << std::accumulate(strs.cbegin(), strs.cend(), std::string("")) << "\n";
	// Erdekesseg: harmadik parameternek nem lenne eleg a "", mert akkor
	// const char*-gal probalna meg legeneralni a sablon fuggvenyt, amivel
	// nem menne. Ezert explicit ki kell irnom, hogy: std::string("")

	// Ha explicit kiirom a sablon parameter listat, akkor igy nez ki:
	std::cout << std::accumulate<std::list<std::string>::const_iterator, std::string>(strs.cbegin(), strs.cend(), "") << "\n";
	// Erdekesseg: ebben az esetben a harmadik param lehet siman "",
	// az explicit kiirt sablon parameter listabol latni fogja a fordito,
	// hogy oda std::string kell, ezert implicit azza fogja konvertalni a
	// const char* ot (implicit azt konstrual belole): "" -> std::string("")

	//-------------------------------

	// Szamlalas - kenyelmesen:
	std::cout << std::count(ints.cbegin(), ints.cend(), 4)       << "\n";
	std::cout << std::count(strs.cbegin(), strs.cend(), "world") << "\n";

	// Szamlalas - kenyelmetlenul:
	int cnt = 0;
	for (typename std::array<int, 10>::const_iterator it = ints.cbegin(); it != ints.cend(); ++it)
		if (*it == 4)
			++cnt;
	std::cout << cnt << "\n";
	cnt = 0;
	for (typename std::list<std::string>::const_iterator it = strs.cbegin(); it != strs.cend(); ++it)
		if (*it == "world")
			++cnt;
	std::cout << cnt << "\n";
}

