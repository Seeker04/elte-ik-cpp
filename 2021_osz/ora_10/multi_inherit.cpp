#include <iostream>

struct Person {
	std::string name;
};

struct Student : public virtual Person {
	void study(){ std::cout << "Studying\n"; }
};

struct Teacher : public virtual Person {
	void teach(){ std::cout << "Teaching\n"; }
};

struct Demonstrator : public Student, public Teacher {

};

int main()
{
	Demonstrator d;

	d.study();
	d.teach(); // mindkét metódus hívható, mert meg lettek örökölve

	std::cout << d.name << "\n"; // itt már ütközés lenne, ha nem használtam volna virtuális öröklődést
}

