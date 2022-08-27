#include <iostream>

void triple(int& x) { x *= 3; }
void invert(int& x) { x *= -1; }
void addExlMark(std::string& str) { str += "!"; }

// A foreach fv sablon az atadott tomb osszes elemen
// hivja meg az atadott fv-t

template <typename T>
void print(const T& obj) { std::cout << obj << "\n"; } // read-only ref-kent veszi az a parametert

// Fv sablon mutable foreach-hez
template <typename T>
void foreach(T * array, int array_size, void(*function)(T&))
{
    for (int i=0; i<array_size; ++i) {
        function(array[i]);
    }
}

// Fv sablon read-only foreach-hez
template <typename T>
void foreach(const T * array, int array_size, void(*function)(const T&))
{
    for (int i=0; i<array_size; ++i) {
        function(array[i]);
    }
}

int main()
{
	int t[] = { 10, -20, 30, 42 };

	std::string strs[] = { "hello", "world", "asd" };

	// Explicit mindent kiirva
	/*
	foreach<int>(t, 4, &triple);
	foreach<int>(t, 4, &invert);
	foreach<std::string>(strs, 3, &addExlMark);

	foreach<int>(t, 4, &print<int>);
	foreach<std::string>(strs, 3, &print<std::string>);
	*/

	// Implicit, fv pointereknel nem kell ref/deref operator (&/*),
	// a T sablon parametereket pedig ki tudja kovetkeztetni a ford. a fv param listabol
	// (a print-es peldaban lathatjuk, hogy ez itt tobblepcsosen is megy)
	foreach(t, 4, triple);
	foreach(t, 4, invert);
	foreach(strs, 3, addExlMark);

	foreach(t, 4, print);
	foreach(strs, 3, print);
}

