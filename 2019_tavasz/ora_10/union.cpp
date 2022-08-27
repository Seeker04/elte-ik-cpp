#include <iostream>

union CharIntConverter {
	char ch;
	int num;
};

int main()
{
	CharIntConverter c;

	c.num = 107;

	std::cout << c.ch << std::endl; // k
	std::cout << c.num << std::endl; // 107

	c.ch = 'Q';

	std::cout << c.ch << std::endl; // Q
	std::cout << c.num << std::endl; // 81

	c.num = 4500;

	std::cout << c.ch << std::endl; // invalid karakter kod, kiindexeltunk az ASCII kodtablabol
	std::cout << c.num << std::endl; // 4500

}

