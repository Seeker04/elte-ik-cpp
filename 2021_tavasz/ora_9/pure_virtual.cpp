#include <iostream>

struct Shape {
	virtual int area() = 0; // nincs definicioja => abstract class
};

struct Rectangle : public Shape {
	int _width;
	int _height;

	Rectangle() : _width(5), _height(10) {}
	int area() { return _width * _height; } // override
};

struct Triangle : public Shape {
	int _width;
	int _height;

	Triangle() : _width(5), _height(10) {}
	int area() { return _width * _height / 2; } // override
};

struct Circle : public Shape {
	int _rad;

	Circle() : _rad(5) {}
	int area() { return _rad * _rad * 3.14f; } // override
};

int main()
{
	/*
	Shape shp; // abstract class => nem peldanyosithato!
	shp.area(); // nem lenne szerencses def nelkuli fv-t meghivni
	*/

	Shape * sh = nullptr; // pointer a szuloosztalyra, statikus tipusa Shape* lesz
	char choice;
	std::cout << "What should I create?" << std::endl;
	std::cin >> choice; // bolvasunk egy karaktert
	if (choice == 't')
		sh = new Triangle; // dinamikus (futasi) idoben dol el -> dinamikus tipus Triangle lesz
	else if (choice == 'r')
		sh = new Rectangle; // dinamikus (futasi) idoben dol el -> dinamikus tipus Rectangle lesz
	else if (choice == 'c')
		sh = new Circle; // dinamikus (futasi) idoben dol el -> dinamikus tipus Rectangle lesz
	else
		sh = nullptr;

	if (sh) {
		std::cout << sh->area() << "\n";
		delete sh; // felszabaditjuk a dinamikus mem. teruletet, ha lett lefoglalva
	}
	// Emlekezteto: minden new operatornak kell, hogy legyen egy delete parja!

}

