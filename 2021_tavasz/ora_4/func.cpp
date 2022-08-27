#include <iostream>

/*
void f(int,int);
void f(int,int);
void f(int,int);
void f(int,int);

// szignatura = nev + form param lista

void f(int x, int y) { std::cout << x + y; }

void f(const char * str) { std::cout << str << "\n"; }
int  f(const char * str) { std::cout << str << "\n"; return 42; }
// ha csak a visszateresi tipus kulonbozik, akkor van utkozes,
// mert a szignatura egyezik!

// Ez a feature kapora johet:
int    max(int, int);
float  max(float, float);
double max(double, double);
...
// megj.: C-ben nincs

*/


void f(int x, int y = 42, int z = 84)
{
	std::cout << "x : " << x << "\n";
	std::cout << "y : " << y << "\n";
	std::cout << "z : " << z << "\n";
	std::cout << "\n";
}
// A ford. legeneral 3 prototipust:
//void f(int,int,int);
//void f(int,int);
//void f(int);

void h() {
	static int call_count = 0; // ez csak egyszer fut le
	std::cout << "I was called " << ++call_count << " times\n";
}

int main()
{
	h(); // output: I was called 1 times
	h(); // output: I was called 2 times
	h(); // output: I was called 3 times
	h(); // output: I was called 4 times

	//f(10, 20);

	//f("hello world");

	f(10, 20, 30);
	f(10, 20);
	f(10);
}
