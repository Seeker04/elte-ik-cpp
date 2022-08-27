#include <iostream>

struct Point {
	int x;
	int y;
};

// operator+ tulterhelese a Point tipushoz:
Point operator+(Point p, Point q)
{
	Point s = {p.x + q.x, p.y + q.y };
	return s;
}

int main()
{
	Point p1 = {10, 20}; // a ketto inicializalas teljesen ekvivalens
	Point p2   {-5, 3};  // azert lehet ilyen felsorolassal, mert az osszes
	                     // adattag public (a struct kulcsszo hasznalata miatt)

	Point psum = p1 + p2;

	std::cout << psum.x << "\n";
	std::cout << psum.y << "\n";
}

