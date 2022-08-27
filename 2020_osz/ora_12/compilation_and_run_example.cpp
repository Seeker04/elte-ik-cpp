// Forditsuk/futtassuk ezekkel:
// g++ -fsanitize=address,leak,undefined -O3 -Wall -Wextra -Werror 
// clang-tidy
// valgrind ./a.out

#include <iostream>

struct Test {
	int * p;
	Test() { p = new int; std::cout << *p << "\n"; delete p; }
	~Test() { delete p; } // a double free undefined behavior!
};

int main()
{
	int t[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	for (int i=0; i<11; ++i)
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
	delete fptr; // delete nullptr-en => u.b!
}

