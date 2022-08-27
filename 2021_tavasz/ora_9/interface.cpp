#include <iostream>

struct Printable {
	virtual std::string toString() = 0;
};

struct Serializable {
	virtual std::string toJson() = 0;
};

class Point3D : public Printable, public Serializable { // tobbszoros oroklodes
private:
	int _x;
	int _y;
	int _z;
public:
	Point3D(int x, int y, int z) :
		_x(x), _y(y), _z(z) {}

	std::string toString()
	{
		return "(" + std::to_string(_x) + "," +
		             std::to_string(_y) + "," +
		             std::to_string(_z) + ")";
	}

	std::string toJson()
	{
		return std::string("{\n") +
		       "\"x\":" + std::to_string(_x) + ",\n" +
		       "\"y\":" + std::to_string(_y) + ",\n" +
		       "\"z\":" + std::to_string(_z) + "\n}";
	}
};

int main()
{
	Point3D p(10, 42, -30);

	std::cout << p.toString() << "\n";
	std::cout << p.toJson()   << "\n";
}

