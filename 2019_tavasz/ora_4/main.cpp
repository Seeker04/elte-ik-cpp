#include <iostream>

// 1. Függvények

// érték szerinti paraméter átadás
void f(int);  // deklaráció
void f(int x) // definíció
{
	x = 30;	
}

// cím átadása
void g(int * x) // deklaráció és definíció történhet egyszerre
{
	*x = 30;
}

// referencia
void h(int& x)
{
	x = 13;
}



// 2. Operátor overloading
struct Point {
	int x;
	int y;
};

Point operator+(const Point& p1, const Point& p2)
{
	Point p3;
	p3.x = p1.x + p2.x;
	p3.y = p1.y + p2.y;
	return p3; // érték szerint adódik vissza (másolat)

	//return Point{p1.x + p2.x, p1.y + p2.y}; így rövidebb
}

int main()
{
	int x = 42;

	f(x); // érték szerint
	std::cout << x << std::endl; // 42, mert érték szerint lett átadva, másolat készült

	g(&x); // cím szerint
	std::cout << x << std::endl; // 30, mert a "külső" címen tárolt int lett módosítva

	h(x); // referencia szerint
	std::cout << x << std::endl; // 13, mert a "külső" változóra hivatkozik a referencia

	// struct inicializálás
	Point p1 = {10, 20}; //Point p1 {10, 20}; egyenloseg jel elhagyhato
	Point p2 = {8, 130}; //Point p2 {8, 130};

	std::cout << (p1+p2).x << " " << (p1+p2).y << std::endl;
}

