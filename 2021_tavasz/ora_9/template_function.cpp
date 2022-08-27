#include <iostream>

/*
// C-ben
int max_i(int x, int y)       { return (x > y ? x : y); }
int max_f(float x, float y)   { return (x > y ? x : y); }
int max_d(double x, double y) { return (x > y ? x : y); }
Esetleg:
#define MAX(X, Y) ((x) > (y) ? (x) : (y))

// C++-ban (overloading)
int max(int x, int y)       { return (x > y ? x : y); }
int max(float x, float y)   { return (x > y ? x : y); }
int max(double x, double y) { return (x > y ? x : y); }
*/

// C++-ban (template)
template <typename T>
T max(T x, T y) { return (x < y ? y : x); } // igy csak egyszer kellett leirnom a definiciot
                                            // refakt eseten csak egy helyen kell atirni...

struct Person {
	int id;
	std::string name;
};

bool operator<(const Person& p1, const Person& p2)
{
	return p1.id < p2.id;
}

template <typename T>
void f()
{
	T obj;
}

int main()
{
	std::cout << max<int>(10, 20)        << "\n";
	std::cout << max<float>(10.3f, .19f) << "\n";

	// Itt el is lehet hagyni a sablonparameterek kiirasat, mert a fv
	// parameter listabol latja a fordito a T tipust
	std::cout << max(10, 20)      << "\n";
	std::cout << max(10.3f, .19f) << "\n";

	// Mukordik sajat tipussal is, ha van operator< tulterhelve hozza
	Person p1 { 100, "asd" };
	Person p2 { 200, "valaki" };
	Person maxp = max(p1, p2);
	std::cout << maxp.id << "\n";

	//f();    // ford. hiba, mert itt nem tudja kikovetkeztetni a T sablonparametert
	f<int>(); // igy mar ok
}

