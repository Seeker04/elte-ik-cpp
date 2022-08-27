#include <iostream>

class Prefixer {
	std::string _prefix;

public:
	Prefixer(const std::string& p) :
		_prefix(p)
	{}

	void setPrefix(const std::string& p)
	{
		_prefix = p;
	}

	void operator()(std::string& str) // ref. szerinti átadás
	{
		str = _prefix + str;
	}
};

int main()
{
	// objektum példányosítás
	Prefixer prefix_with_king("King ");

	std::string name = "Kong";
	prefix_with_king(name);
	// úgy használjuk az objektumot, mint egy függvényt

	std::cout << name; // out: King Kong

	// később a setPrefix-szel meg is változtathatjuk a használt prefixet
	// tudunk más-más prefixer objektumokat is létrehozni...

}

