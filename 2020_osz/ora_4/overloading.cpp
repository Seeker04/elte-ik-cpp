#include <iostream>

// visszateresi tipus fv nev     formalis param lista (parameterek szama + rendre azok tipusai)
// v                  v          v
// T                  func_name (T1, T2, T3);
//                    ----------------------
//                    szignatura = nev + form. param lista

// Fv tulterheles (overloading)
int max(int, int);
float max(float, float);
// Kulonbozo szignaturak -> ketto fv prototipus:
// max(int,int)
// max(float,float)
// A fordito az aktualis param lista elemeibol mindig ki tudja kovetkeztetni, hogy
// mely fv prototipust kell az adott kodreszen majd meghivni
// (az aktualis parameterek tipusai mindig ford. idoben adottak, lasd: statikus tipusossag)

// Definiciok:
int max(int x, int y)       { return x > y ? x : y; }
float max(float x, float y) { return x > y ? x : y; }

// Ez ford. hiba, mert ugyanaz a szignaturaja, mint az int max(int,int)-nek
const char* max(int x, int y) { return "hello"; }

// Default parameterek:
void f(int, int = 20, int = 20); // deklaracional kellenek, a param listaban jobboldalon szerepelnek
void f(int x, int y, int z)
{
	std::cout << x+y+z << "\n";
}
// Fordito general prototipusokat:
// f(int,int,int)
// f(int,int)
// f(int)
// Tehat ez egy implicit fv tulterheles

int f(int asd) { return 42; } // Ez ford. hiba, mert konfliktusos a harmadikkal

int main()
{
	std::cout << max(10, 20) << "\n"; // elso prototipus fut le

	std::cout << max(.314f, 10.5f) << "\n"; // masodik prototipus fut le

	max(20, 30); // itt pl. nem lehetne a visszateresi tipusbol kikovetkeztetni barmit is...

	f(10, -5, -2);
	f(10, -5);
	f(10);

	int n;
	std::cin >> n;
	std::cout << (0<n ? "igen" : false) << "\n"; // ford. hiba, futasi (dinamikus) idoben nem dolhet el
	// egy (resz)kifejezes tipusa! lasd: statikus tipusossag
}

