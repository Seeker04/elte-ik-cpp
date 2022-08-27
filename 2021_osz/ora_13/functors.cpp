#include <iostream>

class Prefixer {
	std::string _prefix;
public:
	Prefixer(const std::string& p) : _prefix(p) {}

	void setPrefix(const std::string& p) { _prefix = p; }

	void operator()(std::string& str) { str = _prefix + str; } // ref. szerinti atadas
};

int main()
{
	Prefixer prefix_with_king("King "); // objektum peldanyositas
	std::string name = "Kong";
	prefix_with_king(name); // ugy hasznaljuk az objektumot, mint egy fuggvenyt
	std::cout << name;      // out: King Kong
	// kesobb a setPrefix-szel meg is valtoztathatjuk a hasznalt prefixet
	// tudunk mas-mas prefixer objektumokat is letrehozni...

}

