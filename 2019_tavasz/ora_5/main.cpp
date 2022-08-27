#include <iostream>

void swap1(int& x, int& y) // referencia szerinti átadás
{
	int tmp = x;
	x = y;
	y = tmp;
}

void swap2(int * x, int * y) // cím átadása
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void swap3(int& x, int& y) // tmp nélkül
{
	x += y;
	y = x - y;
	x -= y;
}

void swap4(int& x, int& y) // hack
{
	x ^= y ^= x ^= y;
}

//void f(int a, int b = a) {...} nem működik, miért? paraméterek kiértékelési sorrendje nem specifikált

enum Color {
	WHITE = 0x000000,
	BLACK = 0xffffff,
	RED   = 0xff0000,
	GREEN = 0x00ff00
};

int main()
{
// 1. Gyakorlás
	int a = 5, b = 10;

	//swap1(a, b);
	//swap2(&a, &b);
	//swap3(a, b);
	swap4(a, b);

	std::cout << "a: " << a << ", b: " << b << std::endl;

// 2. Vezérlési szerkezetek
	// for ciklus
	for (int i=0, j=10; (i+j*10)<1000; ++i, j+=5)
		std::cout << i << " " << j << std::endl;

	// goto - NE HASZNÁLJUK!
	int count = 0;
	begin:
	if (count < 5) {
		std::cout << ++count << std::endl;
		goto begin;
	}

// 3. Típus szinonímák

	// típus szinoníma
	typedef unsigned long int ul_int; // régi C-s megoldás
	using ul_int = unsigned long int; // C++11-től (támogat template-eket)
	ul_int x = 2837462874623;

// 4. Felsorolási típus

	// enum használata
	std::cout << Color::WHITE << std::endl;
	std::cout << Color::BLACK << std::endl;
	std::cout << Color::RED   << std::endl;
	std::cout << Color::GREEN << std::endl;

// 5. Osztályok (part 1)

	struct Point; // deklarálás

	struct Point { // definíció (történhet deklaráláskor egyből)
		int x;
		int y;
		int z; // adattagok (member variables)
	};

	Point p1;                 // példányosítás (objektum létrehozása az osztályból)
	Point p2 = {10, 30, -5};  // inicializálás (list-initialization)
	Point p3 {100, 200, 300}; // egyenlőségjel el is hagyható

	std::cout << p1.x << " " << p1.y << " " << p1.z << std::endl; // memória szemét íródik ki
	std::cout << p2.x << " " << p2.y << " " << p2.z << std::endl; // 10 30 -5
	std::cout << p3.x << " " << p3.y << " " << p3.z << std::endl; // 100 200 300

}

