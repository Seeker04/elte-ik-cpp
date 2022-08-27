#include <iostream>

class MyClass {
	int _y; // objektum konstrualasnal az adattagok konstrualasi sorrendje mindig az, ahogy
	int _x; // a memoriaban szerepelnek, azaz amilyen sorrendben itt deklaralva vannak
public:
	MyClass() :
		_x(42), // hiaba ez a sorrend lett irva az init listaba...
		_y(_x)  // <-- ez fut le hamarabb, de itt _x még inicializálatlan!
	{}
};

int main()
{
	MyClass m;
}

