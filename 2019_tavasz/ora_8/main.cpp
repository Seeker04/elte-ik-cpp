// Pelda forrasa: http://www.cplusplus.com/doc/tutorial/polymorphism/

#include <iostream>

int main ()

// Gyakorlo peldak ------------------------------------------------------------

// 1.
{
	int x = 10;
	if (1) {
		int x = 20; // -Wshadow kapcsolo figyelmeztet az ilyenre
		std::cout << x << std::endl;
	}
	std::cout << x << std::endl;

// 2.
	struct S {
		int a=2, b=4, c=6, d=8;
	};

	S s;
	S * p = &s;
	std::cout << *(((int*)p)+2) << std::endl;

}

