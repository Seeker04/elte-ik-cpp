#include <iostream>

class Owner; // forward declaration

class Car {
	Owner * owner;
};

class Owner {
	Car * car;
};

int main()
{
}

