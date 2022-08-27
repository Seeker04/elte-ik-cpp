#include <array>
#include <iostream>

#include <algorithm> // count
#include <numeric> // accumulate

template <typename T>
T multiply(T left, T right) { return left * right; }

int main()
{
	const std::array<int, 13> t = { 1, 2, 3, 4, 1, 5, 6, 7, 8, 9, 1, 10};

	// Alapertelmezetten operator+-ot hasznal (egysegelemnek a 0 kell)
	std::cout << std::accumulate(t.cbegin(), t.cend(), 0) << "\n";

	// Most szorozni szeretnem oket (egysegelemnek az 1 kell)
	std::cout << std::accumulate(t.cbegin(), t.cend(), 1, multiply<int>) << "\n";

	//-------------------------------

	std::array<std::string, 3> st = { "hello", "world", "c++" };

	// std::string eseten az operator+ konkatenalni fog
	std::cout << std::accumulate(st.cbegin(), st.cend(), std::string("")) << "\n";
	// Erdekesseg: harmadik parameternek nem lenne eleg a "", mert akkor
	// const char*-gal probalna meg legeneralni a sablon fuggvenyt, amivel
	// nem menne. Ezert explicit ki kell irnom, hogy: std::string("")

	// Ha explicit kiirom a sablon parameter listat, akkor igy nez ki:
	std::cout << std::accumulate<std::array<std::string, 3>::const_iterator, std::string>(st.cbegin(), st.cend(), "") << "\n";
	// Erdekesseg: ebben az esetben a harmadik param lehet siman "",
	// az explicit kiirt sablon parameter listabol latni fogja a fordito,
	// hogy oda std::string kell, ezert implicit azza fogja konvertalni a
	// const char* ot (implicit azt konstrual belole): "" -> std::string("")

	// Szamlalas - kenyelmesen:
	std::cout << std::count(t.cbegin(), t.cend(), 1) << "\n";

	// Szamlalas - kenyelmetlenul:
	int cnt = 0;
	for (int i=0; i<t.size(); ++i)
		if (t[i] == 1) ++cnt;
	std::cout << cnt << "\n";
}

