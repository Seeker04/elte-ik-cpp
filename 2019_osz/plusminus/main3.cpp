#include <iostream>

struct Point {
	double x;
	double y;
};

class Circle {

public:

	Circle(Point center, double radius) :
		_center(center),
		_radius(radius)
	{}

	double getRadius() const { return _radius; }
	Point getCenter() const { return _center; }

	void setRadius(double radius) { _radius = radius; }

	void shiftCenter(double xshift, double yshift)
	{
		_center.x += xshift;
		_center.y += yshift;
	}

	static void printPI() { std::cout << "PI is 3.14\n"; }

private:

	Point _center;
	double _radius;

};

// Bonus task
std::ostream& operator<<(std::ostream& out, const Circle& circle)
{
	out << "(" << circle.getCenter().x
	    << ", " << circle.getCenter().y
	    << ", " << circle.getRadius() << ")";
	return out;
}

int main()
{
	Point point = {10, 4.8};

	// Non-const circle
	Circle circle1(point, 10.25);

	std::cout << "Radius: " << circle1.getRadius() << "\n";
	std::cout << "Center: " << circle1.getCenter().x << ", " << circle1.getCenter().y << "\n\n";

	circle1.setRadius(8);
	circle1.shiftCenter(-5.5, 3);

	std::cout << "Radius: " << circle1.getRadius() << "\n";
	std::cout << "Center: " << circle1.getCenter().x << ", " << circle1.getCenter().y << "\n\n";

	// Const circle
	const Circle circle2(point, .75);
	std::cout << "Radius: " << circle2.getRadius() << "\n";
	std::cout << "Center: " << circle2.getCenter().x << ", " << circle2.getCenter().y << "\n\n";

	// Static method
	Circle::printPI();

	// Bonus task
	std::cout << circle1 << "\n";
	std::cout << circle1 << "\n" << circle2 << "\n";
}

