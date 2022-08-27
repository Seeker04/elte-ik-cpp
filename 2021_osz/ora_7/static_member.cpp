#include <iostream>

class MyClass {
public:
	MyClass() { ++object_count; }  // konstruktor
	~MyClass() { --object_count; } // destruktor
	static int getObjectCount() { return object_count; }

private:
	static int object_count; // ez csak deklaracio!
};

int MyClass::object_count = 0; // erre a definialasra mindenkepp szukseg van!

int main()
{
	std::cout << MyClass::getObjectCount() << "\n"; // 0
	{
		MyClass a; // letrehozunk egy peldanyt, lefut a default konstruktor

		std::cout << MyClass::getObjectCount() << "\n"; // 1

		MyClass * b = new MyClass; // itt is, mint elobb, csak nem a stack-re, hanem a heap-re kerul

		std::cout << MyClass::getObjectCount() << "\n"; // 2

		if (1) {
			MyClass c;
			std::cout << MyClass::getObjectCount() << "\n"; // 3
		} // megsemmisul c, lefut a destruktora

		std::cout << MyClass::getObjectCount() << "\n"; // 2

		delete b; // megsemmisul b, lefut a destruktora

	} // megsemmisul a, lefut a destruktora

	std::cout << MyClass::getObjectCount() << "\n"; // 0
}
