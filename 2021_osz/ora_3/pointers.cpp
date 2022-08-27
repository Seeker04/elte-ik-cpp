#include <iostream>

int main()
{
	// const-ot lehet kapni (T* -> const T* OK)
	int x = 42;
	const int * p = &x;
	*p = 10; // ford. hiba, mert mutatott ertek nem valtozhat

	// const nem veszhet el (const T* -> T* NEM OK)
	const int c = 128;
	int * p2 = &c; // ford. hiba
	*p2 = 20;

	const int * const q = &x; // ez is valid

	int x = 30;
	int * p = &x;
	void * v = p; // itt megy az implicit konverzio
	std::cout << *v; // ford. hiba
	std::cout << *(int*)v << "\n"; // C-stilusu kasztolas, igy mar megy

}

