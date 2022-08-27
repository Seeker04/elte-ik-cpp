#include <iostream>
#include <vector>

class Animal {

};

class Dog : public Animal {
public:
	Dog(const std::string& n) : _name(n){}
	void bark() { std::cout << "I am " << _name << "!"; }
private:
	std::string _name;
};

void f(Animal * a){}
void g(Dog * d){ d->bark(); }

int main()
{
	Animal myAnimal;
	Dog myDog("Buksi");

	f(&myAnimal);
	f(&myDog);

	g(&myDog);

	std::vector<int> nums = { 10, 98, -30, 15, 42 };

	for (typename std::vector<int>::const_iterator it = nums.cbegin(); it != nums.cend(); ++it)
		std::cout << *it << " ";
}

