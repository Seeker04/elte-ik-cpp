#include <iostream>

class MyClass {
public:
	MyClass() {}
	MyClass(int x) {}
	void sayHello() { std::cout << "hello!\n"; }
};

int main()
{
	MyClass obj1(42); // parameteres konstruktor hivas

	MyClass obj2;     // default konstrualas, nincs ures zarojel!

	int f();
	MyClass obj3(); // ez egy olyan fv-t deklaralna, aminek
	                // obj a neve, MyClass a visszateresi tipusa es nem var
	                // egyetlen parametert sem!

	obj1.sayHello();
	obj2.sayHello();

	obj3.sayHello(); // non-class type ford. hiba, hiszen o egy fv!
}

