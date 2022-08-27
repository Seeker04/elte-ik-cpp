// 2. pluszminusz (alternativ)

#include <iostream>

struct Point {
	int x;
	int y;
};

class Circle {

public:

	Circle(const Point& point, int radius = 10) :
		_origo(point),
		_radius(radius){}

	// getters
	Point getOrigo() const { return _origo; }
	int getRadius() const { return _radius; }

	// setters
	void setOrigo(const Point& point) { _origo = point; }
	void setRadius(int radius) { _radius = radius; }

private:

	Point _origo;
	int _radius;

};

int main()
{
	Point p1 {10, 20};
	Point p2 {5, -4};

	const Circle c1(p1, 30);
	      Circle c2(p2);

	std::cout << c1.getRadius() << ", " << c2.getRadius() << std::endl; // 30 10

	Point p = c1.getOrigo();
	std::cout << p.x << ", " << p.y << std::endl; // 10 20

	c2.setRadius(50);
	c2.setOrigo({42, -10});
}

