#include <iostream>

class Rational {
private:
	int _sz;
	int _n;
public:
	Rational(int sz = 1, int n = 1) : _sz(sz), _n(n) {}
	// A tulterheles ezeket a prototipusokat generalja:
	// Rational()
	// Rational(int) -> lesz implicit konverzio int-rol Rational-ra
	// Rational(int, int)

	//explicit Rational(int sz = 1, int n = 1) : _sz(sz), _n(n) {}
	//^ ha ezt hasznaljuk, akkor az 1 parameteres ktor megkapja az explicitast
	// -> le lesz tiltva az implicit konverzio int-rol Rational-ra
	// (de explicit tipus kiirassal es kasztolassal azert fog menni)

	void print() { std::cout << _sz << "/" << _n << "\n"; }

	// Egy implicit konverzios operator -> menni fog a konverzio implicit
	operator float() { return (float)_sz / _n; }

	// Egy explicit konverzios operator -> csak explicit kasztolassal lehet konvertalni ezze
	explicit operator double() { return (double)_sz / _n; }
};

void f(Rational r) { r.print(); }
void g(float x) { std::cout << x << "\n"; }
void h(double x) { std::cout << x << "\n"; }

int main()
{
	Rational p;         // 1/1
	Rational q(10);     // 1/10
	Rational r(20, 30); // 20/30
	p.print();
	q.print();
	r.print();

	Rational a = 42; // OK, 1 param ktor miatt, az fog lefutni
	f(128);          // OK, 1 param ktor miatt, az fog lefutni
	// Ezzel ekvivalens: f(Rational(128));

	// Ha kint lenne az 1 param ktor elott az explicit, akkor csak igy lennenek helyesek:
	Rational a2 = Rational(42);
	f(Rational(128));

	// A Rational tipusnal (mivel szamokat reprezental) kenyelmes, hogy
	// rejtett modon tud int-kent viselkedni, de sok tipusnal nem biztos, hogy szep lenne:
	// Pl. vector ktor ha 1 int-et kap, akkor az e kezdo meretet allitja be:
	// vector v(10); // szep
	// vector = 10;  // csunya!
	// Ezert a legtobb osztalynal, ha van 1 parameteres ktor, ki szoktuk irni ele az explicit-et

	a.print();
	a2.print();

	// Mondjuk az std::string-nel is kapora jon ez a szemantika:
	std::string str = "hello";
	//                ^
	//                const char[6]
	// Azert mukodik, mert van az std::string-nek egy nem-explicit
	// 1 parameteres ktor-ja, ami char tombot var:
	// std::string::string(const char*)
	//
	// Hasonloan ez is menne: f_that_takes_a_string("world");

	// -----------------------------

	Rational rat(1, 3);

	// Implicit konverziok konv. operatorral
	float x = rat;
	std::cout << x << "\n";
	g(rat); /* Rational::operator float() hivasanak eredmenyet adja */

	// Explicit konverziok konv. operatorral
	double y = (double)rat;
	std::cout << y << "\n";
	h((double)rat); /* Rational::operator double() hivasanak eredmenyet adja */

}

