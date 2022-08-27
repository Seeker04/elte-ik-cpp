#include <iostream>
#include <map>

struct CmpByMod5 {
	bool operator()(int l, int r) { return (l % 5) < (r % 5); }
};

std::map<int, std::string, CmpByMod5> m = {
	{ 1, "c++"   },
	{ 2, "hello" },
	{ 6, "world" },
	{ 4, "!"     },
};

int main()
{
	for (typename std::map<int, std::string, CmpByMod5>::const_iterator it = m.cbegin(); it != m.cend(); ++it) {
		std::cout << "key: " << it->first << ", value: " << it->second << "\n";
	}

	std::cout << m[6] << "\n";
}

