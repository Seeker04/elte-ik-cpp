#include <iostream>

int main()
{
	int x = 10;

	if (true) {
		int x = 42;

		std::cout << x << "\n"; // output: 42
	}

	std::cout << x << "\n"; // output: 10
}

