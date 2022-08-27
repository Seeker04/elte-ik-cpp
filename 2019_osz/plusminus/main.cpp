#include <iostream>

#include "header.h"

const int x = 10;

namespace Foo
{
	namespace Bar
	{
		int x = 128;
	}
}

int main()
{
	int x = -5;

	/* 1. */ std::cout << x           << std::endl;
	/* 2. */ std::cout << Foo::x      << std::endl;
	/* 3. */ std::cout << Foo::Bar::x << std::endl;
	/* 4. */ std::cout << y           << std::endl;
	/* 5. */ std::cout << ::x         << std::endl;

	/* +1 */ std::cout << *(&("asd123"[2])+2) << std::endl;

	return 0;
}

