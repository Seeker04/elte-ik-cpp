// Forditsuk/futtassuk ezekkel:
// g++ -fsanitize=address,leak,undefined -O3 -Wall -Wextra -Werror tools_example.cpp
// ./a.out
// clang-tidy tools_example.cpp --
// valgrind ./a.out
//
// Megj.: a valgrind-os futtatas elott forditsuk -fsanitize nelkul, mert
// a valgrind nem "szereti" a sanitizer-t!

#include <iostream>

struct Test {
	int * p;
	Test() { p = new int(42); std::cout << *p << "\n"; delete p; }
	~Test() { delete p; } // double free -> undefined behavior!
};

int main()
{
	int t[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	for (int i=0; i<=10; ++i)
		std::cout << t[i] << "\n"; // i==10-nel kiindexelek => u.b!

	Test test_obj;

	int i = 42;
	int j = 0;
	std::cout << i/j << "\n"; // 0-val valo osztas => u.b!

	const int k = 42;
	const int l = 0;
	std::cout << k/l << "\n"; // ezt mar a fordito/static kod analizalo is
	                          // eszreveszi, mert ford. ideju konstans az l

	float * fptr = nullptr;
	std::cout << *fptr << "\n"; // nullptr dereferalas => u.b!

	delete &i; // delete hivasa olyan objektum cimevel, ami nem is a heap-en van => u.b!

	// valgrind: "Conditional jump or move depends on uninitialised value(s)" hiba
	int x;
	if (100 < x)
		std::cout << "bigger\n";
	else
		std::cout << "smaller\n";

	int *y = new int(117); // ehhez hianyzik a delete! -> memory leak
}

