#include <iostream>

// C-ben:
/*
int    max_i(int x, int y)       { return x>y ? x : y; }
float  max_f(float x, float y)   { return x>y ? x : y; }
double max_d(double x, double y) { return x>y ? x : y; }
*/

// C++-ban: (tulterheles/overloading) - adhoc polimorfizmus
/*
int    max(int x, int y)       { return x>y ? x : y; }
float  max(float x, float y)   { return x>y ? x : y; }
double max(double x, double y) { return x>y ? x : y; }
*/

// Szinten C++: forditasi ideju/parametrikus polimorfizmus fuggveny sablonnal
template <typename T>
T max(T x, T y) { return x>y ? x : y; }

// ^Ez NEM egy fv def, nincs olyan fuggvenyem, hogy "max"
// Ez csak egy fv sablon, amibol tud majd rendes fv def-et
// generalni a fordito
// Pl. T=int behelyettesitessel

template <typename T>
void f()
{
	T obj;
}

int main()
{
	std::cout << max<int>(10, 20)        << "\n";
	std::cout << max<float>(0.1f, 0.01f) << "\n";
	std::cout << max<double>(-2.5, 3.14) << "\n";
	// A ford. general 3 fv prototipust

	std::cout << "\n";

	// Nem kell kiirni a template parametert, mert a fv parameter listabol
	// ki tudja kovetkeztetni a fordito, hogy T milyen tipusu:
	std::cout << max(10, 20)      << "\n";
	std::cout << max(0.1f, 0.01f) << "\n";
	std::cout << max(-2.5, 3.14)  << "\n";

	f(); // hiba
	// itt mar nem egyertelmu a T, hiszen nem tudja a ford. kikovetkeztetni,
	// mert nem szerepel a fv param listaban!
	f<char>(); // igy mar jo
}

