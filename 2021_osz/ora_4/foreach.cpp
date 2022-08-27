#include <iostream>

void pretty_print(int x) { std::cout << "Number: " << x << "\n"; } // csak olvassa

void invert_sign(int& x) { x *= -1; } // irja

// tomb atadasa:
// int *t
// int t[]

// fv pointer param explicit kiirva:
// void (*function)(int))

// Ez konstkent veszi at a tombot -> garantaltan csak olvasni tudja
// -> hivhato const tombbel is
// + olyan fv-t hasznal, ami csak ertek szerint veszi at az adott int-et
void foreach(const int array[], int size, void function(int))
{
	for(int i = 0; i < size; i++) {
		function(array[i]);
	}
}

// Az array nem const, ezert csak nem-const tomb adhato at
// + olyan fv-t hasznal, ami referenciakent veszi at az adott int-et -> tudja modositani
void foreach(int array[], int size, void function(int&))
{
	for(int i = 0; i < size; i++) {
		function(array[i]);
	}
}

int main()
{
	int numbers[] = { 1, -2, 3, -4 };

	const int cnumbers[] = { 10, 20, 30, 42, -10 };

	foreach(numbers, 4, &invert_sign);
	foreach(numbers, 4, &pretty_print);

	foreach(cnumbers, 5, &invert_sign); // FORD. HIBA (lasd feljebb), ki kell kommentezni, hogy leforduljon
	foreach(cnumbers, 5, &pretty_print);
}

// Megj.: STL-ben van std::foreach az <algorithm> header-ben
//
// Megj.: modern C++-ban hasznalhatjuk az std::function-t a <functional> header-bol
//        nyers fv pointer helyett

