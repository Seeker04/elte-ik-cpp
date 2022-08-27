#include <iostream>

class Animal { /*...*/ };
class Dog : public Animal { /*...*/ };

void eat(Animal a) { std::cout << "eat\n";  }
void bark(Dog d)   { std::cout << "bark\n"; }

int main()
{
	Animal animal;
	Dog dog;

	eat(animal);  // OK, megfelelő a típus
	bark(animal); // Ford. hiba, mert a fv Dog-ot vár és nem Animal-t,
	              // nem lehet implicit downcast-olni

	eat(dog);  // OK, mert implicit megy az upcast szülő típusba
	bark(dog); // OK, megfelelő a típus
}

