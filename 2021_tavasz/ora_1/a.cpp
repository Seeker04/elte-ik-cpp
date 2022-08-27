
#include <iostream>

int y = 42;
int z = 128;

namespace A {
	extern int x; // jelzem, hogy ok mas forditasi egysegben vannak definialva
	extern int y;
	int z = -30;
}

namespace {
	int a;
	const bool l = false;
	void h();
	struct Point { int x; int y; }; // nevprefixet kaphat valtozo/konstans/fuggveny/tipus
}

void g(const char * message)
{
	std::cout << A::x << " " << A::y << " " << A::z << "\n";
	std::cout << message << "\n";
}

static int priv = 20; // mas forditasi egysegek nem hasznalhatjak, csak ez
                      // ha megis hasznalni probalnam, a linker fog hibat dobni...

