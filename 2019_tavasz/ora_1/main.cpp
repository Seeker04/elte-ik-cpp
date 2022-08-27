#include <iostream>
#include "math.h"

namespace Geometry { int x = 10; }

int main()
{
	struct Point {int a; int b;};

	int a(10);

	std::cout << PI << std::endl;

	Geometry::Point p = {10, 20};
	Geometry::Line  l = { {-20, 5}, {12, -2} };

	std::cout << p.x    << " " << p.y << std::endl;
	std::cout << l.p1.x << " " << l.p1.y << std::endl;
	std::cout << l.p2.x << " " << l.p2.y << std::endl;
}

