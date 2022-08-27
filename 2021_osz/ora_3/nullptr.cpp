#include <iostream>

void f(int i)   { std::cout << "int\n";   }
void f(char* c) { std::cout << "char*\n"; }

int main()
{
	int number = NULL;     // lefordul
	int number2 = nullptr; // nem fordul le, mert nem tipushelyes (nullptr az nullptr_t tipusu)

	f(0);    // int-es fut le
	f(NULL); // hiba, nem egyertelmu

	f(nullptr); // char* prototipus lesz meghivva

	int * ptr;
	if (ptr != nullptr) {}
	// ekvivalensek
	if (ptr) {}
}

