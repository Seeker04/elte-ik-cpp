#include <iostream>

int main()
{
	int x = 42;

	int * p = &x; // & : T -> T*

	*p = 20;

	std::cout << p << "\n";
	std::cout << *p << "\n"; // * : T* -> T

	const int * cp = &x; // cp-n keresztul nem lehet irni a mutatott objektumot

	//*cp = 30;

	const int c = 50;

	//int * p2 = &c; // & : const T -> const T*
	//*p2 += 5;

	const int * cp2 = &c;
	std::cout << *cp2 << "\n"; // * : const T* -> const T
	
	int y = 128;

	p = &y;
	std::cout << *p << "\n";

	const int * const q = &x;
	//int const * const q = &x; igy is ok
	std::cout << *q << "\n";
	//q = &y;

	//int * r;
	//int* r;
	//int *r;

	//int* a, b; // a az int* lesz, b pedig int
	//int *a, b; // igy jobban latszik, hogy mi is lesz

	//------------------

	int z; int * p3 = &z;
	void * v = p3; // itt megy az implicit konverzió
	//std::cout << *v;
	std::cout << *(int*)v; // C-stílusú kasztolás
	// z nem lett inicializalva, memoria szemetet kapok!

	int * i_am_null = nullptr;
	if (i_am_null != nullptr)
	//if (i_am_null) // ez is eleg
		std::cout << *i_am_null << "\n";
}

