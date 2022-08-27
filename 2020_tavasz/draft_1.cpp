#include <iostream>
#include <vector>

struct Point {
	int x;
	int y;
};

// Operator tulterheles (overloading)
Point operator+(Point p, Point q) {
	Point r = {p.x+q.x, p.y+q.y};
	return r;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void swap2(int& a, int& b) {
	a ^= b ^= a ^= b; // ez konnyen bizonyithato, hogy mindig helyes
}

typedef std::string String;
typedef std::vector<int> IntVect;

//typedef std::vector Vect;

using IntVect = std::vector<int>;

template<typename T> using Vect = std::vector<T>; // alias template

int main()
{
	/*
	Vect<char> v = { 'v', 'a', 'b', 'b' };

	int x = 10, y = 20;

	swap2(x, y);

	std::cout << x << " " << y << "\n";

	Point p1 = {10, 20};
	Point p2 = {-1, -5};

	Point p3 = p1 + p2;

	std::cout << p3.x << " " << p3.y << "\n";

	std::cin >> x;
	std::cout << ((x < 20) ? "yes" : false); // error!

	std::cout << (++x, x+=15, 42) << "\n";
	std::cout << x << "\n";

	int tomb[] = { 10, 20, 30, 40, 50, 60 };

	std::cout << "Osszmeret: " << sizeof(tomb) << "\n";
	std::cout << "Elemszam: " << sizeof(tomb)/sizeof(tomb[0]) << "\n";

	int size;
	std::cin >> size;
	int * dyn_tomb = new int[size];
	std::cout << sizeof(dyn_tomb) << "\n"; // miert annyit ir ki, amennyit?
	delete[] dyn_tomb;
	*/

	struct MyClass;
	struct MyClass;

	struct MyClass {
		int x;
		int y;
		char str[10];
		float f;
		char c;
	};

	// |----|----|----------|----|-|
	//  x    y    str        f    c
	//  ^
	//&mObj

	MyClass mObj = {10, 20, "hello", 3.14f, 'z'};

	// mObj.str === "hello\0al0?"

	std::cout << mObj.str << "\n";

	std::cout << &mObj << "\n";

	std::cout << (char*)&mObj + 8 << "\n";
	std::cout << (char*)((int*)&mObj + 2) << "\n";

	mObj.y = 10;
	std::cout << "y: " << mObj.y << "\n";
	*((int*)&mObj + 1) = 20;
	std::cout << "y: " << mObj.y << "\n";

	struct Test {
		int pub;
	private:
		int priv;
	public:
		void printPriv() { std::cout << priv << "\n"; }
	};

	Test t;
	t.printPriv();
	*((int*)&t + 1) = 20;
	t.printPriv();
}

