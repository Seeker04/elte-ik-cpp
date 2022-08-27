#include <iostream>

int g = 20;

int& f()
{
	int x = 10;

	return g;
}

int main()
{
	f() = 42;
}
