#include <iostream>

class Person {
	std::string _name;
	int _age;
public:
	Person() :
		_name("Default name"),
		_age(30)
	{}
};

int main()
{
	// Mi a kulonbseg a ketto kozott?
	Person * p1 = new Person; // ktor is fut
	Person * p2 = (Person*)malloc(sizeof(Person)); // ktor nem fut

	// Es ezek kozott?
	delete p1; // dtor is fut (ha van)
	free(p2); // dtor nem fut

	// A malloc es a free rendszerhivasok csak N darab bajtot allokal, ill.
	// deallokal, mast nem csinalnak
	//
	// A new es a delete operatorok a dinamikus memoria allokalas/deallokalas mellett
	// a C++-os osztaly altal definialt objektumot letrehozzak
	// (constructor is fut), illetve megsemmisitik (destructor is fut, ha van).
}

