#include <iostream>

class Rational {
public:
	int szaml;
	int nevezo;

	Rational(int sz, int n) : szaml(sz), nevezo(n) {}
	Rational(int sz) : szaml(sz), nevezo(1) {}
	Rational() : szaml(1), nevezo(1) {}

	//Rovidebb:
	//Rational(int sz = 1, int n = 1) : szaml(sz), nevezo(n) {}

	explicit operator float() { return (float)szaml/(float)nevezo; }
	//operator double() { return (double)szaml/(double)nevezo; }
};

void printRational(Rational r)
{
	std::cout << "sz: " << r.szaml << ", n: " << r.nevezo << "\n";
}

void printFloat(float f) { std::cout << f << "\n"; }

class Car {
	int weight;
public:
	explicit Car(int w) : weight(w) {}
};

int main()
{
	//Car myCar = 10; // error! mert ki van irva az explicit az 1 param ktor ele

	Rational x(10, 3); // 10/3 racionalis szam
	Rational a(8);     // 8/1 racionalis szam
	Rational b{24};    // 24/1 racionalis szam
	Rational c = 12;   // 12/1, itt is az egyparameteres ktor van meghivva es NEM az ertekadas operator!
	Rational d; // default konstrualas

	//int var = 42;
	//int var(42);

	printRational(x);
	printRational(a);
	printRational(b);
	printRational(c);
	printRational(d);

	// implicit
	printRational(42); // temp object-et csinal, ez fut le: Rational::Rational(42)
	// explicit
	printRational(Rational(42)); // ha explicit lenne az 1 param ktor, akkor ez kene

	// konverzios operator hivas
	float f = (float)x;
	printFloat((float)x);
	printFloat((float)a);

	// konverzios operator hivas implicit modon
	//printFloat(x); // error! le kell szedni az explicit kulcsszot a konv operator elol, hogy mukodjon
}

