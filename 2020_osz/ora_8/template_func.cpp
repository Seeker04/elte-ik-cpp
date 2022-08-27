#include <iostream>

// C-ben:
// int   max_i(int   x, int   y) {...}
// float max_f(float x, float y) {...}
// Nem tul kenyelmes (bar kikenyszeriti az explicitast)

// C++-ban: ovarloading (lehet ugyanaz a fv nev)
// int   max(int   x, int   y) {...}
// float max(float x, float y) {...}
// (A fordito a param listabol latja, hogy mely prototipust kell ott meghivni majd)
// Meg mindig nem tul kenyelmes, mert a fv torzset mindnel kulon le kell irni,
// ha egy ujfajta tipussal szeretnenk hasznalni, irni kell mindig egy uj prototipust...

// C++-ban: sablonfuggveny
template <typename T>
T max(const T& x, const T& y) {
	return (x < y ? y : x);
}
// Ez NEM egy valid fv tipus, csak egy SABLON hozza, amibol a fordito (nyilvan forditasi
// idoben) le tud generalni - sablonparameter behelyettesitessel - fv definiciokat,
// amiket utana rendesen le is fordit <-- ezert hivjak compile time polymophism-nek
// Pl. max<int>(...)  --> int max(const int& x, const int& y)    fv prototipus
//     max<long>(...) --> long max(const long& x, const long& y) fv prototipus

struct Point {
	int x;
	int y;
};

// Erre az operator overload-ra szukseg lesz, ha szeretnenk a max-ot hasznalni
// Point tipusokkal, kulonben nem fordulna le a T=Point-tal legeneralt fv kodja,
// mert nem talalna operator< prototipust, ami ketto Point objektumot varna
bool operator<(Point p1, Point p2) { return p1.x < p2.x; }

int main()
{
	// A fordito le fogja generalni a fv kodjat T helyere int-et helyettesitve
	std::cout << max<int>(11, 23) << "\n";
	std::cout << max<float>(3.14f, 10.1f) << "\n";
	std::cout << max<long long>(39348273498LL, 213213432389234LL) << "\n";

	// El is lehet hagyni a template param listat, mert most ki tudja
	// kovetkeztetni a fordito a fv param listabol
	std::cout << max(11, 23) << "\n";
	std::cout << max(3.14f, 10.1f) << "\n";
	std::cout << max(39348273498LL, 213213432389234LL) << "\n";

	Point x {10, 20};
	Point y {5, 30};
	Point bigger = max<Point>(x, y);
	std::cout << bigger.x << "," << bigger.y << "\n";
	// Az operator overload miatt ^ez is mukodik, illetve barmi tipussal
	// hasznalhato, aminek peldanyai osszehasonlithatoak operator<-vel...
	// A fv kodjat pedig csak egyetlen egyszer kellett leirnom, ill. egy
	// helyen kell modositanom, ha refaktoralni kene kesobb...
}

