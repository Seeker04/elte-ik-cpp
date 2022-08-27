#include <iostream>

void triple(int& x) { x *= 3; }

template <typename T>
void foreach(T * array, int size, void(*func)(T&))
{
	for (int i=0; i<size; ++i)
		func(array[i]);
}

int main()
{
	int array[] = { 10, 3, -2 };

	foreach(array, 3, triple);

	for (int i=0; i<3; ++i)
		std::cout << array[i] << "\n";
}

