// Pelda forrasa: http://www.cplusplus.com/doc/tutorial/polymorphism/

#include <iostream>

// OOP (pelda)

class Polygon { // absztrakt szulo osztaly (nem peldanyosithato)
public:
	Polygon (int w, int h) : _width(w), _height(h) {}
	virtual ~Polygon(){} // virtualis destruktor ures torzzsel
	virtual int area() = 0; // tisztan virtualis metodus, e miatt absztrakt az osztaly
	void printarea()
	{
		std::cout << area() << std::endl;
	}

protected:
	int _width, _height;
};

class Rectangle: public Polygon { // gyerek osztaly
public:
	Rectangle(int w, int h) : Polygon(w, h) {} // szulo konstruktoranak hivasa
	int area() // virtualis metodus feluldefinialasa
	{
		return _width * _height;
	}
};

class Triangle: public Polygon {
public:
	Triangle(int w, int h) : Polygon(w, h) {}
	int area()
	{
		return _width * _height / 2;
	}
};

//-----------------------------------------------------------------------------

// Sablon fuggvenyek

// Elofeltetel: size >= 1
template <typename T> // sablon fuggveny
T max(const T * const array, int size)
{
	T max = array[0];
	for (int i=1; i<size; ++i)
		if (max < array[i])
			max = array[i];
	return max;
}

struct Person {
	int age;
	int height;
	std::string name;
};

bool operator<(const Person& p1, const Person& p2) { return p1.name < p2.name; }

std::ostream& operator<<(std::ostream& out, const Person& p)
{
	out << "[" << p.name << ", age: " << p.age << ", height: " << p.height << "]" << std::endl;
	return out;
}

//-----------------------------------------------------------------------------

int main () {
// Gyakorlo pelda

#if 0

class Student {
	std::string _name;
public:
	Student(const std::string& name) : _name(name){}
	const std::string& getName() const { return _name; }
};

// Vigyazat #1
Student * p = new Student("Valaki");
const std::string& str = p->getName();
delete p;
std::cout << str << std::endl; // invalid reference, undefined behavior

// Vigyazat #2
const std::string * strp;
if (1) {
	Student p2("Valaki2");
	strp = &p2.getName();
} // itt p2 megsemmisul
std::cout << *strp << std::endl; // invalid memoria teruletre mutat, undefined behavior

#endif

//-----------------------------------------------------------------------------

// OOP (pelda)

	Polygon * poly1 = nullptr; // pointer a szulo osztalyra (javasolt inicializalni, ha masra nem, legalabb nullra)

	char choice;
	std::cout << "What to create?" << std::endl;
	std::cin >> choice;

	if (choice == 'r') // futasi/dinamikus idoben dol el a tipus
		poly1 = new Rectangle(4, 5); // altipusos/futási ideju polimorfizmus
	else if (choice == 't')
		poly1 = new Triangle(4, 5);

	Polygon * poly2 = new Triangle(4, 5);

	// poly2 statikus tipusa: Polygon*
	// poly2 dinamikus tipusa: Triangle*

	poly1->printarea(); // szulotol orokolt metodus meghivasa
	poly2->printarea(); // poly1 es poly2 a dinamikus tipus szerinti area() fv-t hasznaljak

	delete poly1; // dinamikus memoriat nekunk kell de-allokalni (nincs garbage collection)
	delete poly2;

//-----------------------------------------------------------------------------

// Sablon fuggvenyek

	int nums[]          = {10, 73, -12, 28, -51};
	double dnums[]      = {.4, 2.42, .11};
	char chars[]        = {'k', 'c', 'v', 'b', 'r', 'd'};
	std::string names[] = {"John", "Jonathan", "Joe"};
	Person people[]     = {{10, 141, "Paul"}, {27, 180, "Will"}, {35, 174, "Emma"}};

	std::cout << max<int>(nums, 5)          << std::endl; // 73
	std::cout << max<double>(dnums, 3)      << std::endl; // 2.42
	std::cout << max<char>(chars, 6)        << std::endl; // v
	std::cout << max<std::string>(names, 3) << std::endl; // Jonathan
	std::cout << max<Person>(people, 3)     << std::endl; // [Will, age: 27, height: 180]

}

