#include <iostream>

// Sablon osztalyok

template <typename T, typename Transform> // sablon osztaly ket parameterrel
void foreach(T * array, int size)
{
	Transform transform;
	for (int i=0; i<size; ++i)
		transform(array[i]);
}

template <typename T, int amount = 2> // T egy tipus, amount parameter egy integralis ertek default ertekkel
struct MultiplyBy {
	void operator()(T& item) { item *= amount; }; // e miatt lesz funktor
};

class PrefixWith {
public:
	PrefixWith(const std::string& prefix) : _prefix(prefix){}
	void operator()(std::string& item) { item = _prefix + item; }; // e miatt lesz funktor
private:
	std::string _prefix;
};

struct PrefixWithHello : public PrefixWith {
	PrefixWithHello() : PrefixWith("Hello "){}
};

struct PrefixWithHi : public PrefixWith {
	PrefixWithHi() : PrefixWith("Hi "){}
};

//-----------------------------------------------------------------------------

int main () {

// Sablon osztalyok

	int nums[]          = {10, 73, -12, 28, -51};
	double dnums[]      = {.4, 2.42, .11};
	std::string names[] = {"John", "Jonathan", "Joe"};

	foreach<int, MultiplyBy<int>>(nums, 5);

	for (int i=0; i<5; ++i) std::cout << nums[i] << " ";
	std::cout << std::endl;

	foreach<double, MultiplyBy<double, 10>>(dnums, 3);

	for (int i=0; i<3; ++i) std::cout << dnums[i] << " ";
	std::cout << std::endl;

	foreach<std::string, PrefixWithHello>(names, 3);

	for (int i=0; i<3; ++i) std::cout << names[i] << std::endl;

	foreach<std::string, PrefixWithHi>(names, 3);

	for (int i=0; i<3; ++i) std::cout << names[i] << std::endl;

}

// megjegyzes: Hasonlo mukodest el tudunk erni fuggveny pointer-ek hasznalataval is
//             C-ben azt hasznalhatnank
//             Funktorok abban "tobbek" a fv pointereknel, hogy allapotot tudnak orizni/valtani
//             es tipuskent szerepelhetnek sablon parameterekkent
//
// megjegyzes: Ha egy funktornak az operator() muvelete bool-t ad vissza, akkor azt predikatumnak is szoktuk nevezni

