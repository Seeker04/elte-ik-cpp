#include <iostream>
#include <set>

int main()
{
	std::set<int> mySet = { 10, 20, 30, 42 };

	typename std::set<int>::const_iterator it = mySet.cbegin();
	while (it != mySet.cend()) {
		std::cout << *it << std::endl;
		++it;
	}
}

