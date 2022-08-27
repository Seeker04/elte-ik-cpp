#include <iostream>

class A {
};

class B {
	char buffer[16];
};

class C {
	virtual void f();
};

class D {
	virtual void f();
	char buffer[16];
};

class E : public D {
	char buffer[8];
};

int main()
{
	void * ptr;
	std::cout << "pointer size: " << sizeof(ptr) << "\n\n";

	std::cout << sizeof(A) << "\n";
	std::cout << sizeof(B) << "\n";
	std::cout << sizeof(C) << "\n";
	std::cout << sizeof(D) << "\n";
	std::cout << sizeof(E) << "\n";
}

