#include <iostream>
#include <vector>

// Feladat 1: irjuk meg a foreach fuggveny sablont, amivel tetszoleges tipust
// tarolo tombok elemeire tudunk futtatni fuggvenyeket

// Feladat 2: szeretnenk ezt hasznalni std::vector-okkal is. Hogyan oldhatnank meg?

void triple(int& i) { i *= 3; }

void to_upper(char& ch) { ch -= 32; }

void prefix_with_length(std::string& str) { str = std::to_string(str.length()) + ":" + str; }

template<typename T>
void foreach(T *arr, int n, void(*f)(T&)) {
    for (int i = 0; i < n; ++i) {
        f(arr[i]);
    }
}

template<typename T> void
foreach(std::vector<T>& vec, void(*f)(T&)) {
    for (int i = 0; i < vec.size(); ++i) {
        f(vec[i]);
    }
}

int main()
{
	int ia[] = { 10, -5, 2, 42 };

	char ca[] = { 'a', 'c', 'k', 'z' };

	std::string sa[] = { "C++", "Java", "Haskell" };

	foreach(ia, 4, triple);
	foreach(ca, 4, to_upper);
	foreach(sa, 3, prefix_with_length);

	// Ellenorzes
	for (int i=0; i<4; ++i)
		std::cout << ia[i] << "\n";
	for (int i=0; i<4; ++i)
		std::cout << ca[i] << "\n";
	for (int i=0; i<3; ++i)
		std::cout << sa[i] << "\n";

//----------------------------

	std::vector<int> iv = { 10, -5, 2, 42 };

	std::vector<char> cv = { 'a', 'c', 'k', 'z' };

	std::vector<std::string> sv = { "C++", "Java", "Haskell" };

	foreach(iv, triple);
	foreach(cv, to_upper);
	foreach(sv, prefix_with_length);

	// Megjegyzes: hasznalhatom a tomboset is a vector-ral:
	/*
	foreach(iv.data(), iv.size(), triple);
	foreach(cv.data(), cv.size(), to_upper);
	foreach(sv.data(), sv.size(), prefix_with_length);
	*/

	// Ellenorzes
	for (int i=0; i<4; ++i)
		std::cout << iv[i] << "\n";
	for (int i=0; i<4; ++i)
		std::cout << cv[i] << "\n";
	for (int i=0; i<3; ++i)
		std::cout << sv[i] << "\n";
}

