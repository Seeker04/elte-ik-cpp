#include <iostream>
int max(int x, int y) {
	std::cout << "int-es\n";
	return (x < y) ? y : x;
}

long max(long x, long y) {
	std::cout << "long-os\n";
	return (x < y) ? y : x;
}

float max(float x, float y) {
	std::cout << "float-os\n";
	return (x < y) ? y : x;
}

double max(double x, double y) {
	std::cout << "double-os\n";
	return (x < y) ? y : x;
}

int main()
{
	max(10, 20);
	max(10l, 20l);
	max(1.0f, 2.0f);
	max(1.0, 2.0);
}

namespace MyNamespace {
	int max(int x, int y) {}

	class MyClass {
	public:
		int max(int x, int y) {}
	};
}

class MyClass {
public:
	int max(int x, int y) {}
};

// Lefordul, mert nincs utkozes:
// A global scope-on a max fv-eknel a tulterheles helyes, mert az eltero
// parameter listak miatt mas-mas szignaturaink vannak
// -> mindig a megfelelo prototipus lesz meghivva
//
// max(int,int) szignaturajubol van tobb is, de mind mas-mas scope-on vannak,
// azaz mas-mas a teljes nevuk:
// - max(int,int)
// - MyClass::max(int,int)
// - MyNamespace::max(int,int)
// - MyNamespace::MyClass::max(int,int)

// Erdekesseg:
// objdump -t overloading.o
// paranccsal lathatjuk, hogy a fordito milyen szimbolum neveket general az
// egyes prototipusoknak -> valoban mindnek egyedi lesz -> meg lesz az egyertelmuseg

