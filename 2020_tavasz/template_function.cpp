#include <iostream>

/*
// C-ben
int max_i(int x, int y) { return (x > y ? x : y); }
int max_f(float x, float y) { return (x > y ? x : y); }
int max_d(double x, double y) { return (x > y ? x : y); }

// C++-ban (overloading)
int max(int x, int y) { return (x > y ? x : y); }
int max(float x, float y) { return (x > y ? x : y); }
int max(double x, double y) { return (x > y ? x : y); }
*/

// C++-ban (template)
template <typename T>
T max(T x, T y) { return (x < y ? y : x); }

struct Person {
	int id;
	std::string name;
};

bool operator<(Person p, Person q) { return p.id < q.id; }

int main()
{
	std::cout << max<int>(10, 20)        << "\n";
	std::cout << max<float>(10.3f, .19f) << "\n";

	Person p1 { 100, "asd" };
	Person p2 { 200, "valaki" };

	Person maxp = max<Person>(p1, p2);
	std::cout << maxp.id << "\n";
}

