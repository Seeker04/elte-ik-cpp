#include <iostream>

class Person {

public:
	Person(const std::string& name) : _name(name)
	{
		std::cout << _name << " is created!" << std::endl;
	}

	~Person()
	{
		std::cout << _name << " is destroyed!" << std::endl;
	}

	static void sayHello() { std::cout << "Hello!" << std::endl; }

private:
	std::string _name;
};

int main()
{
	Person * p1 = new Person("Valaki"); // Valaki is created!

	Person::sayHello(); // Hello!

	if (1) {
		Person p2("Masik valaki"); // Masik valaki is created!
	}                                  // Masik valaki is destroyed!

	delete p1; // Valaki is destroyed
}

