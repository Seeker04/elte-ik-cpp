#include <iostream>

struct S1 {
	int x;
	char ch;
	int y;
	char ch2;
};

struct S2 {
	int x;
	int y;
	char ch;
	char ch2;
};

int main()
{
	std::cout << sizeof(S1) << std::endl;
	std::cout << sizeof(S2) << std::endl;
}

