#include <iostream>

// A statikus adattag (mas neven: "osztaly szintu" adattag) nem fog szerepelni
// minden peldany memoria teruleten. Egyszer lesz memoriaba irva: a statikus memoriaba
// (mint a globalis valtozok) es igy a program futas vegeig el
// Az osszes osztaly peldany eleri es tudja hasznalni, sot ha public, akkor "kivulrol"
// is hasznalhato
//
// Statikus tagfuggveny: nem peldanyokon lehet hivni, nincs is igy implicit this
// parameter. Ezert nyilvan nem is hasznalhat nem static adattagokat/tagfuggvenyeket.
// Osztaly szintu fuggveny, melyet ugy hivhatunk mint globalis fuggvenyeket,
// csak kell az osztalynev prefix, illetve nala is szamit a lathatosag (private/public).

class MyClass {
private:
	static int object_count; // ez csak deklaracio!
public:
	MyClass() { ++object_count; }  // konstruktor
	~MyClass() { --object_count; } // destruktor

	static int getObjectCount() { return object_count; } // publikus statikus tagfv.
};

int MyClass::object_count = 0; // erre a definiciora mindenkepp szukseg van (lasd: ODR)
                               // lathatjuk, hogy olyan mint egy globalis valtozo osztalynev prefixszel
                               // de lathatosag is hat ra, csak most pont public

int main()
{
	std::cout << MyClass::getObjectCount() << "\n"; // 0

	{
		MyClass a; // letrehozunk egy peldanyt, lefut a default konstruktor

		std::cout << MyClass::getObjectCount() << "\n"; // 1

		MyClass * b = new MyClass; // itt is, mint elobb, csak nem a stack-re, hanem a heap-re kerul

		std::cout << MyClass::getObjectCount() << "\n"; // 2

		if (true) {
			MyClass c;
			std::cout << MyClass::getObjectCount() << "\n"; // 3
		} // itt megsemmisul c, lefut a destruktora

		std::cout << MyClass::getObjectCount() << "\n"; // 2

		delete b; // megsemmisul b, lefut a destruktora

	} // megsemmisul a, lefut a destruktora

	//MyClass::object_count = 2000; ilyet nem tudnek, mert object_count az privat!

	std::cout << MyClass::getObjectCount() << "\n"; // 0

}

