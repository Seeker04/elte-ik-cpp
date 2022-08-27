#include <iostream>

class Point3D {
	int x;
	const int y; // ezek nem kaphatnak uj erteket! (ktor torzseben sem)
	const int z; // oket init listaban KELL inicializalni!

public:
	Point3D(int p_x, int p_y, int p_z) :
		x(p_x), // init lista
		y(p_y), // ezekkel az ertekekkel lesznek INICIALIZALVA
		z(p_z)  // ezek valtozo konstrualasok
	{
	}

	/*
	Point3D(int p_x, int p_y, int p_z)
	// itt nincs init lista => minden adattag default konstrualva lesz
	// (default ktor-ok futnak le)
	{
		std::cout << "this from ctor: " << this << "\n";

		x = p_x; // ezek mar letezo objektumoknak ERTEKADASOK
		y = p_y; // hiba lenne
		z = p_z; // hiba lenne
	}
	*/

	void setX(int p_x)
	{
		// this tipusa: Point3D*
		this->x = p_x; // vagy: (*this).x = p_x;
		x = p_x;

		// a this "tovabb lesz adva"
		printSelf();
		this->printSelf();
	}

	void printSelf() const // ez konstans tagfv -> garantalja, hogy a hivo objektum allapota nem valtozik
	{
		// this tipusa: const Point3D*
		/*
		Ez ford hiba lenne igy:
		x = 128;
		this->x = 128; // === (*this).x = 128
		*/
		std::cout << "this: " << this << "\n";
		std::cout << x << "\n";
		std::cout << y << "\n";
		std::cout << z << "\n";
		std::cout << this->x << "\n"; // (*this).x
		std::cout << this->y << "\n";
		std::cout << this->z << "\n";

		//setX(-20);
		//this->setX(-20);
		// ugyanaz a problema: a this tovabb adasa kozben a
		// 'const' qualifier el lenne hagyva
		// const Point3D* -> Point3D* nem megengedett!
	}
};

int main()
{
	Point3D p(10, 42, -5);
	std::cout << "p cime: " << &p << "\n";
	p.printSelf(); // this-be bekerul &p, ami Point3D*
	// Point3D* -> const Point3D* konverzio OK (const-ot lehet kapni)

	const Point3D cp(10, 20, 30);
	cp.printSelf(); // this-be bekerul &cp, ami const Point3D*

	p.setX(256); // OK

	//cp.setX(256); // HIBA
	// this tipusa: const Point3D*-ot nem lehet Point3D*-ra konvertalni,
	// const nem veszhet el!
}

