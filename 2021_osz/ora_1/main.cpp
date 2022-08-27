#include <iostream>

extern int y;
extern int z;

static void print_int(int i);
static void print_int(int i)
{
	using std::cout;
	cout << "hello\n";
}

int main()
{
	int x = y;
	std::cout << "y: " << y << "\n";
	std::cout << "z: " << z << "\n";
	print_int(42);
}

