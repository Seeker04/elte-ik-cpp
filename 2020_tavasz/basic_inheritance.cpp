#include <iostream>

class A {
	int a;
	int b;
	char c;

public:
	A() { std::cout << "A ktor\n"; }
	~A() { std::cout << "A dtor\n"; }
};

class B : public A {
	double d;

public:
	B() { std::cout << "B ktor\n"; }
	~B() { std::cout << "B dtor\n"; }
};

class C : public B {
	int e;

public:
	C() { std::cout << "C ktor\n"; }
	~C() { std::cout << "C dtor\n"; }
};

int main()
{
	A objA;
	std::cout << "=========\n";
	B objB;
	std::cout << "=========\n";
	C objC;

	std::cout << "--- end of main ---\n";
}

// Megjegyzes: debugger-rel (pl. gdb) lehez nezegetni a leszarmazott osztalypeldanyok tagjait

