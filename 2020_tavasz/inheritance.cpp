#include <iostream>

class Animal {
private:
	int size;
	int weight;
public:
	Animal(int s, int w) : size(s), weight(w)
	{
		std::cout << "Animal constructed\n";
	}
	~Animal()
	{
		std::cout << "Animal destructed\n";
	}
};

class Mammal : public Animal {
private:
	int numberOfLegs;
public:
	Mammal(int s, int w, int nol) :
		Animal(s, w),
		numberOfLegs(nol) // szulo osztaly parameteres ktor-jat itt kell hivni az init listaban
	{
		std::cout << "Mammal constructed\n";
	}
	~Mammal()
	{
		std::cout << "Mammal destructed\n";
	}
};

class Dog : public Mammal {
private:
	std::string color;
public:
	Dog(int s, int w, std::string c) :
		Mammal(s, w, 4),
		color(c)
	{
		std::cout << "Dog constructed\n";
	}
	// Ez kell, ha a gyerek dtor-jat is szeretnenk hogy dinamikus kotesen keresztul meg legyen hivva
	virtual ~Dog()
	{
		std::cout << "Dog destructed\n";
	}

	// Polimorf lesz az osztaly (-> _vptr), futasi idoben a pointer dinamikus tipusa
	// szerinti bark() fog lefutni (a megfelelo altipuse)
	virtual void bark() { std::cout << "*barking*\n"; }
};

class AngryDog : public Dog {
public:
	AngryDog(int s, int w, std::string c) :
		Dog(s, w, c)
	{
		std::cout << "AngryDog constructed\n";
	}
	~AngryDog()
	{
		std::cout << "AngryDog destructed\n";
	}

	// Feluldefinialas
	void bark() { std::cout << "*angry barking*\n"; }
};

class CalmDog : public Dog {
public:
	CalmDog(int s, int w, std::string c) :
		Dog(s, w, c)
	{
		std::cout << "CalmDog constructed\n";
	}
	~CalmDog()
	{
		std::cout << "CalmDog destructed\n";
	}

	void bark() { std::cout << "*no barking*\n"; }
};

int main()
{
	// 1.
	Dog * dog1 = new Dog     (10, 5, "black"); // Statikus tipus: Dog, dinmaikus tipus: Dog
	Dog * dog2 = new AngryDog(20, 8, "brown"); // Statikus tipus: Dog, dinmaikus tipus: AngryDog
	Dog * dog3 = new CalmDog (15, 6, "white"); // Statikus tipus: Dog, dinmaikus tipus: CalmDog

	std::cout << "done\n";

	dog1->bark();
	dog2->bark(); // a virtual kulcsszo nelkul nem mukodne a dinamikus kotes
	dog3->bark();

	delete dog1; // fel kell szabaditani a heap-re allokalt memoriat!
	delete dog2;
	delete dog3;

	std::cout << "================================\n";


	// 2. Pelda futasi idobelisegre
	Dog * dog = nullptr; // statikus tipusa a pointernek: Dog

	std::cout << "What type of dog should I create?\n";
	std::cout << "d - Dog\n";
	std::cout << "a - AngryDog\n";
	std::cout << "c - CalmDog\n";
	char ch;
	std::cin >> ch;
	if (ch == 'd')
		dog = new Dog(10, 20, "asdasd"); // dinamikus tipusa a pointernek: Dog
	else if (ch == 'a')
		dog = new AngryDog(10, 20, "asdasd"); // dinamikus tipusa a pointernek: AngryDog
	else if (ch == 'c')
		dog = new CalmDog(10, 20, "asdasd"); // dinamikus tipusa a pointernek: CalmDog

	if (dog != nullptr) {
		dog->bark();
		delete dog; // fel kell szabaditani a heap-re allokalt memoriat!
	}

	std::cout << "================================\n";


	// 3.
	// Mehetnek persze stack memoriaba is az objektumok, de igy nem tudunk
	// #2-ben latott futasi ideju polimorfizmust alkalmazni
	Dog bdog(10, 20, "asd");
	AngryDog adog(10, 20, "asd");
	CalmDog cdog(10, 20, "asd");
	// Itt a main fuggveny hivasi vermebe kerulnek az objektumok (automatikus tarolas)

	bdog.bark();
	adog.bark();
	cdog.bark();
}

