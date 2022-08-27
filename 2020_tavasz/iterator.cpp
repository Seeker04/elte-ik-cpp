#include <iostream>
#include <set>
#include <vector>

/*
class set {
	class iterator {...};
	static int iterator;
};
*/

int main()
{
	/*
	std::vector<int> elems; // halmaz típus, ami string objektumokat fog tárolni

	elems.push_back(10);
	elems.push_back(20);
	elems.push_back(30);
	elems.push_back(10);

	typename std::vector<int>::iterator it = elems.begin();
	while (it != elems.end()) {
		*it *= 2;
		std::cout << *it << std::endl;
		++it;
	}
	*/

//----------------------------

	const std::vector<std::string> strs = {
		"test elem",
		"almafa",
		"asd asd asd"
	};

	typename std::vector<std::string>::const_iterator it = strs.cbegin();
	while (it != strs.cend()) {
		//*it += "asdasd";
		std::cout << *it << "\n";
		++it;
	}

	std::cout << "\n";

	for (
	  typename std::vector<std::string>::const_iterator it = strs.cbegin();
	  it != strs.cend();
	  ++it
	) {
		std::cout << *it << "\n";
	}

}
