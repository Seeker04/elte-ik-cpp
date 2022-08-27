#include <iostream>

struct MyClass {
	int x;
	int y;
	long l;
private:
	int secret;
public:
	int z;
public:
	void printSecret() { std::cout << secret << "\n"; }
};

int main()
{
	MyClass obj;

	// Feladat: irjuk at valahogy obj.secret-et 42-re, hogy azt kapjuk kimenetnek
	// (mivel private, ezert az obj.secret = 42; nem fog menni)
	// Csak ide lehet kodot beirni, az osztaly kodjan nem szabad valtoztatni!

	obj.z = 100;

	*(int*)(&(obj.l) + 1) = 42;

	obj.printSecret();

	std::cout << obj.z << "\n";
}

