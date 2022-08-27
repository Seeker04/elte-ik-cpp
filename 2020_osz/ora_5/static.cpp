#include <iostream>

class MyClass {
private:
	static int object_count; // ez csak deklaracio, osztaly szintu adattag lesz, tehat
	                         // nem fog minden peldany kulon rendelkezni vele, hanem fixen a
	                         // statikus memoriaban lesz, mint pl. a globalis valtozok vagy fv-ek static valtozoi
				 // de privat, ezert kivulrol nem tudom eleni, pl ilyet nem tudok MyClass::object_count = 10;
public:
	MyClass() { ++object_count; }  // konstruktor, peldanyositaskor fut le
	~MyClass() { --object_count; } // destruktor, peldany megsemmisulesekkor fut le

	static int get_object_count() { return object_count; } // static tagfv, nem peldanyokon tudom meghivni =>
	                                                       // nincs implicit "this" param, ami a hivo obj cimet tarolna
	                                                       // ezert nyilvan nem tudja hasznalni a nem-static adattagokat
	                                                       // mivel public, tudom kivulrol hivni, csak osztaly nevprefix kell
};

int MyClass::object_count = 0; // erre a definialasra mindenkepp szukseg van!

int main()
{
	std::cout << MyClass::get_object_count() << "\n";

	MyClass obj; // peldanyositas => lefut MyClass::MyClass() ktor

	std::cout << MyClass::get_object_count() << "\n";
	std::cout << obj.get_object_count() << "\n"; // igy is megengedett a hivas, de ez kisse felrevezeto, mert
	                                             // ranezesre ugy nez ki, mintha az obj peldanyon hivnam, pedig NEM!

	//MyClass::object_count = 1000; ilyet nem tudok, mert az object_count privat valtozo!

	if (true) {
		MyClass obj2;
		std::cout << MyClass::get_object_count() << "\n";
	}
	// az if blokkjanak a vegen az osszes lokalis valtozoja megsemmisul, lefut
	// a MyClass::~MyClass() dtor az obj2 peldanyon

	std::cout << MyClass::get_object_count() << "\n";

	MyClass * pObj3 = new MyClass; // ugyanugy peldanyositas, csak a dinamikus memoriaba (heap) kerul

	std::cout << MyClass::get_object_count() << "\n";

	delete pObj3; // kezzel kell megsemmisitenem => ugyanugy dtor lefut

	std::cout << MyClass::get_object_count() << "\n";
}
// a main fv lefutasa vegen meg fog semmisulni az o lokalis obj valtozoja is

