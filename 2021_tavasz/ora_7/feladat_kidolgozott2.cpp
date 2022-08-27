#include <iostream>

class C {
public:
	int x = 10;
	int y = 20;
private:
	int z = 30; // top secret!
};

int main()
{
	char ch = 'a';
	char ch2 = 'H';
	char * cp = &ch;

	std::cout << cp << "\n"; // amig nem talal egy 0-as bajtot egeszen addig memoria szemetet ir
	                         // ez undefined behavior! (segfault-olhat is tole)
	                         // erdekesseg: az 'a' betu utan 'H'-t ir ki: innen lehet latni, hogy
	                         // a stack memoriaba tenyleg egymas utan kerulnek a lokalis valtozok

	//---------------------

	char p[] = "hello";
	/* 1 */ std::cout << p << "\n";

	/* 2 */ std::cout << "hello" + 1 << "\n";
	//               const char[6] = {'h', 'e', 'l', 'l', 'o', '\0'}
	//                                 ^
	//                                      ^ +1

	/* 3 */ std::cout << *("hello" + 1) << "\n";
	// * : const char* -> const char, ami konkretan az 'e' betu

	/* 4 */ std::cout << "hello"[1] << "\n";

	/* 5 */ std::cout << (1 + "hello") + 2 << "\n";

	//--------------------------------------------------------------

	/*
	class C {
		public:
			int x = 10;
			int y = 20;
		private:
			int z = 30; // top secret!
	};
	*/

	std::cout << "sizeof(int): " << sizeof(int)  << "\n";  // 4
	std::cout << "sizeof(long): " << sizeof(long) << "\n"; // 8

	C c;

	//       c.x   c.y  c.z
	// ------[----|----|----]-------------
	//        ^         ^
	//       &c        (int*)&c + 2

	/* 6 */ std::cout <<      *( (int*)&c + 2) << "\n";

	/* 7 */ std::cout <<      *((long*)&c + 1) << "\n";

	/* 8 */ std::cout << (int)*((long*)&c + 1) << "\n";

	*((int*)&c + 2) *= 4;

	/* 9 */ std::cout << *((int*)&c + 2) << "\n";
}

