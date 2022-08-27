#include <iostream>

int x = -10;

bool f()
{
	x = 42;
	std::cout << "f was called\n";
	return 0 < x;
}

enum Test {
	A, // 0
	B = 100,
	C  // 101
};

int main()
{
	if ((0 < x) && f()) // lusta kiertekeles: itt mar nem igaz, hogy akar a bal, akar a jobb
	                    // operandust is kiertekelheti hamarabb (lasd: fuggvenyeknel),
	                    // logikai operatoroknal mindig a baloldalit ertekeli ki elobb,
	                    // a jobboldalit pedig ki sem fogja, ha nem szukseges az ertekhez
		std::cout << "true\n";
	else
		std::cout << "false\n";

	std::cout << A << "\n";
	std::cout << B << "\n";
	std::cout << C << "\n";
}

