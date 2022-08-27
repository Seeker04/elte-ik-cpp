#include <iostream>

union Converter {
	int num; // sizeof(int) == 4
	char ch; // sizeof(char) == 1
};

//       c.ch
//       v
// -----[----]------
//       ^^^^
//       c.num

int main()
{
	Converter c;

	std::cout << c.ch << "\n";
	std::cout << c.num << "\n";

	c.ch = 'f';

	std::cout << c.ch << "\n";
	std::cout << c.num << "\n";

	c.num = 87;

	std::cout << c.ch << "\n";
	std::cout << c.num << "\n";
}

