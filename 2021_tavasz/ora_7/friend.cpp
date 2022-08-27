#include <iostream>

class Point3D {
public:
	Point3D(int x, int y, int z) :
		_x(x),
		_y(y),
		_z(z)
	{}

	friend std::ostream& operator<<(std::ostream& out, const Point3D& p)
	{
		out << "x: " << p._x << ", "
		    << "y: " << p._y << ", "
		    << "z: " << p._z;

		return out;
	}

	friend class OtherClass;

private:
	int _x;
	int _y;
	int _z;

};

int main()
{
	Point3D point(10, 20, 42);

	std::cout << point << "\n";

	//(std::cout << point) << "\n";
}

