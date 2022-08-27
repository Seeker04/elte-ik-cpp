#include <iostream>

class IsDisivisbleBy {
	int divider;
public:
	IsDisivisbleBy(int d) : divider(d) {}

	bool operator()(int num) { return num % divider == 0; } // maradekkepzo operator
};

int main()
{
	IsDisivisbleBy isEven(2);
	IsDisivisbleBy isDivisibleByThree(3);

	std::cout << isEven(-4) << "\n";             // true
	std::cout << isEven(13) << "\n";             // false
	std::cout << isDivisibleByThree(20) << "\n"; // false
	std::cout << isDivisibleByThree(99) << "\n"; // true
}

