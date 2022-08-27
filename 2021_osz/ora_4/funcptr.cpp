#include <iostream>

void f(char x) { std::cout << "f: " << x << "\n"; }
void g(char y) { std::cout << "g: " << y << "\n"; }

// ^Ezeknek a tipusa: void (*)(char)

int main()
{
	void (*p)(char) = &f; // p az f fuggvenyre mutat

	(*p)('z');

	// dereferalassal megkapjuk a mutatott fv-t, amit
	// meghivunk egy karakter literallal

	p = &g; // most mar a g fv-re mutat a p pointer

	(*p)('k');

}

// Megj.: a referalo es dereferalo operatorokat el lehet hagyni fv pointerek eseten
//
// Tehat ez is valid:
int main2()
{
	void (*p)(char) = f;

	p('z');

	p = g;

	p('k');
}

