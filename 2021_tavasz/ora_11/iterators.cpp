#include <iostream>
#include <set>

int main()
{
	const std::set<int> mylist = { 10, 20, 30, 42, 50 }; // ez alatt egy binaris keresofa van

	// Igy nem tudok iteralni rajta, mert nincs operator[]
	// Konvencio: ha nem lehet const futasi idejut implementalni, ne is legyen
	/*
	for (int i=0; i<mylist.size(); ++i)
		std::cout << mylist[i] << "\n";
	*/

	typename std::set<int>::const_iterator it = mylist.cbegin();
	while (it != mylist.cend()) {
		std::cout << *it << std::endl;
		++it;
	}

	// Iteralas for ciklussal:
	for (typename std::set<int>::const_iterator it = mylist.cbegin(); it != mylist.cend(); ++it) {
		std::cout << *it << std::endl;
	}
}

