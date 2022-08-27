#include <iostream>
#include <map>

int factorial(int n)
{
	static std::map<int, int> cache;

	std::map<int, int>::iterator search_result = cache.find(n);

	if (search_result == cache.end()) {
		int result = 1;
		for (int i=1; i<=n; ++i)
			result *= i;

		cache[n] = result;

		return result;
	}
	else {
		std::cout << "Result fetched from the cache\n";
		return search_result->second;
	}
}

int main()
{
	std::cout << factorial(0) << "\n";
	std::cout << factorial(1) << "\n";
	std::cout << factorial(2) << "\n";
	std::cout << factorial(3) << "\n";
	std::cout << factorial(4) << "\n";

	std::cout << factorial(1) << "\n";
	std::cout << factorial(3) << "\n";
}

