#include <iostream>

class MyClass {
private:
	int x;
	int y;
public:
	MyClass(){}

	void f()
	{
		// This tipusa: MyClass*
		std::cout << this << "\n";    // tenyleg a hivo objektum cimet tarolja
		std::cout << this->x << "\n";
		std::cout << this->y << "\n";

		this->g();

		// Eml.: this->x === (*this).x
	}

	void g() {}

	// Konst tagfv: garantalnia kell, hogy a hivo objektum
	// allapotat nem modositja
	void cf() const
	{
		// Itt a this tipusa: const MyClass*

		// Ford. hiba!
		x = 42;
		// azaz:
		this->x = 42;
		// azaz:
		(*this).x = 42
		// Ha a this const MyClass* pointer, akkor
		// a (*this) const MyClass, amin nem valtoztathatok
		//
		// Eml.: * : T* -> T
		//       * : const T* -> const T (a const mindig megmarad!)
	}

	// Konstans objektumokon csak konstans tagfv-eket hivhatok
	// mert ezek garantaljak, hogy nem valtoztatnak a hivo
	// objektumon (levezeteset lasd feljebb)
};

int main()
{
	// Rossz:
	MyClass obj(); // ez egy olyan fv-t deklaral, ami nem var parametert es egy MyClass objektummal ter vissza!

	// Helyes:
	MyClass obj;   // ez mar egy default konstrualas

	std::cout << &obj << "\n";

	obj.f();  // OK
	obj.cf(); // OK, cf() const MyClass*-ot var, &obj MyClass* tipusu, de
	          // az gond nelkul konvertalodik const MyClass*-ra ("kaphat const-ot")

	const MyClass const_obj;

	const_obj.cf(); // OK, mert cf() egy konstans tagfv

	const_obj.f(); // ford. hiba, mert f() nem konstans tagfv, ezert MyClass* tipusu this-t var,
	               // de a &const_obj az egy const MyClass*, ami nem tud sima MyClass*-ra konvertalodni,
	               // mert a const nem veszhet el

	// Megjegyzes:
	// C-ben az itt "this"-kent hasznalt parameternek explicit meg kell mindig jelennie,
	// hiszen ott nincsenek tagfuggvenyek, minden fv stand-alone
	// C-ben:
	//   void f(MyClass *this) {}
	//   void cf(const MyClass *this) {}
	//   /* MyClass pedig valami C-s struct tipikusan */
	//
	// Hasznalat:
	// C++-ban : obj.f();
	// C-ben   : f(&obj);
}

