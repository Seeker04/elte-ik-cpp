#include <iostream>
#include <vector>

void f(int n)
{
	n += 10;
	std::cout << n << "\n";
}

void g(int& n)
{
	n += 10;
	std::cout << n << "\n";
}

void printVector(const std::vector<int>& v)
{
	for (int i=0; i<v.size(); ++i)
		std::cout << v[i] << "\n";
}

int main()
{
	int x = 42;

	f(x); // csak masolat keszul az aktualis paramrol
	std::cout << x << "\n";

	g(x); // a fv parameter hivatkozik az atadott objektumra
	std::cout << x << "\n";

	const std::vector<int> vect = { 10, 20, 30, 40, 50, 60 };

	printVector(vect); // mivel const referenciakent veszi at, adhatok neki konstans objektumot
}

