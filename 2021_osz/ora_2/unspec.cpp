#include <iostream>

#include <stdint.h>

int x = 10;

void f(int a, int b)
{
	std::cout << a + b << "\n";
}

// Ez olvassa x globalist
int g()
{
	if (0 < x)
		return 5;
	else
		return 10;
}

// Ez irja x globalist
int h()
{
	x = -20;
	return 42;
}

int main()
{
	f(g(), h()); // Output: 47 vagy 52? Nincs helyes valasz!
	             // Fv parameterek kiertekelesi sorrendje unspecified behavior
	             // Ezert sem szeretjuk pl. a globalis valtozokat
}

