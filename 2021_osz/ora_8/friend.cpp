#include <iostream>

class Person {
	std::string _name;
	int _age;
public:
	Person(const std::string& n, int a) : _name(n), _age(a) {}

	friend std::ostream& operator<<(std::ostream& out, const Person& person); // barát fv. lesz

	friend class SomeClass; // ilyet is lehet
};

std::ostream& operator<<(std::ostream& out, const Person& person) // megadjuk a barát fv. definícióját
{
	out << "Name: " << person._name << ", "     // a barátság miatt láthatja a privát
	    << "Age: "  << person._age << std::endl; // _name és _age tagokat
	return out;
}

int main()
{
	Person p1("Valaki", 24);
	Person p2("Másik valaki", 39);

	std::cout << p1 << p2 << std::endl;

	// azért kellett az std::ostream& referenciával visszatérni, hogy
	// tudjuk így láncolni, záróleket kiírva: ((std::cout << p1) << p2) << std::endl;
	// output:
	// Name: Valaki1, Age: 24
	// Name: Másik valaki, Age: 39

}

