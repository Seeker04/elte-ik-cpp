#include <iostream>

int main()
{
	while (true) {
		int * t = new int[1000000];
		std::cout << t << std::endl;

		char ch;
		std::cin >> ch;

		delete[] t; // igy mar nincs memoria szivargas
	}
}

