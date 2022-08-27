#include <iostream>

class Person {

public:

	Person(std::string name, int age) :
		_name(name),
		_age(age)
	{
		std::cout << "New person: " << _name << " (" << _age << ")" << std::endl;
	}

	Person(int age) :
		_name("Anonym"),
		_age(age)
	{
		std::cout << "New person: " << _name << " (" << _age << ")" << std::endl;
	}

	std::string get_name() const { return _name; }
	void set_name(std::string new_name) { _name = new_name; }

private:

	std::string _name;
	int _age;

};

int main()
{
	/*
	if ("hello" = "hello")
		// ...

	if ("hello" == "hello")
		// ...
	*/

	Person p1("John Doe", 30);
	Person p2(24);


}

