#include <iostream>

int * create_array(int n)
{
	return new int[n];
}

int * create_array42(int n)
{
	int * t = new int[n];

	for (int i=0; i<n; ++i)
		t[i] = 42;

	return t;
}

int main()
{
	int n = 5;

	int * array = create_array42(n);

	std::cout << array[2] << std::endl;

	delete[] array;
}

