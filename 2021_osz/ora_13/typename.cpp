#include <iostream>

struct Test {
	static const int iterator; // ez csak deklaracio!
	class iterator {};

	// static adattagnak es belso tipusnak is ugyanaz a neve...
	// mindkettot igy lehet meghivatkozni: Test::iterator
};

const int Test::iterator = 42; // definiciora szukseg van!

template <typename T>
void f() { std::cout << "tipusos\n"; } // ez tipusnevet var sablon parameternek

template <int I>
void f() { std::cout << "int-es\n"; } // ez int-et var sablon parameternek

int main()
{
	std::cout << Test::iterator << "\n"; // itt egyertelmu: csak az adattagnak van ertelme

	f<Test::iterator>(); // itt mar nem egyertelmu, de a static adattagnak van precedenciaja

	f<typename Test::iterator>(); // ha a tipusnevet akarom hasznlani, akkor ki kell irni a typename kulcsszavat
}

