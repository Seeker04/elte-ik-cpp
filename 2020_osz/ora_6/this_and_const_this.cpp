#include <iostream>

struct Point {
	int x;
	int y;

	int f() { x+=50; return 42; } // nem const tagfv => az implicit this parameter
	                              // nem const pointer => modosithat a hivo objektum allapotan!

	void print() const // a const miatt a this tipusa: const Point* => nem lesz modosithato a hivo objektum allapota!
	{
		x = 30; // ford. hiba!
		this->x = 30; // ekvivalens az elozo sorral
		// itt az a gond, hogy ez ekvivalens ezzel:
		// (*this).x = 30; es mivel az implicit this egy const pointer (mert a tagfv const),
		// a dereferalo * operator const Point-ot ad vissza

		std::cout << x       << ", " << y       << "\n"; // az olvasas OK
		std::cout << this->x << ", " << this->y << "\n"; // ekvivalens az elozo sorral

		f(); // ford. hiba! ekvivalens a kovetkezovel:
		this->f(); // hasonlo a gondolatmenet, mint a cp.print() eseten...
		           // const metodus nem hivhat egy nem-const metodust, mert
		           // itt a this egy const pointer, amit nem tud atadni egy nem-const pointer-t
		           // varo masik tagfv-nek (a "const" soha nem veszhet el!)

		std::cout << this << "\n"; // onellenorzes: tenyleg a hivo objektum cimet tarolja, "arra mutat"

		// Osszefoglalva:
		// A nem-static tagfv-ekben az implicit this parameter mindig
		// a hivo objektum cimet tarolja, de nem szukseges kiirni
		// tehat itt Point* tipusu pointer
		// memberVar    === this->memberVar
		// memberFunc() === this->memberFunc()
		// eml.: this->x === (*this).x
		// Illetve konstans tagfv-ek eseten ez egy konstans pointer,
		// igy garantalja, hogy nem valtoztatja meg a hivo objektum allapotat
		// Ezert konstans objektumokon csak konstans tagfv hivhato!
	}
};

int main()
{
	Point p {10, 20};

	std::cout << &p << "\n"; // p& tipusa: Point*

	p.print(); // Point::print(&p) <-- igy is el lehet "kepzelni"

	const Point cp {100, 200};
	cp.x = 30; // ford. hiba: cp konstans objektum!
	cp.f(); // ford. hiba: &cp tipusa: const Point*, de f nem konst tagfv, igy az sima Point*-ot varna
	        // de const Point* -> Point* nem helyes, mert const qualifier nem veszhet el!
	        // lasd: konstanssag fogalma es konstans pointerek
	cp.print(); // ez mar OK, mert print egy konstans tagfv,
	            // de maga a print fv nem fog lefordulni 4 sor miatt (indoklas a fv torzsben...)
}

// Megjegyzes: a hibas sorok kikommentezese utan ki lehet probalni a futtatast is

