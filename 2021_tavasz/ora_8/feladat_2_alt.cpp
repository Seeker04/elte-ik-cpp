#include <iostream>
#include <vector>

std::vector<const std::string*> str_ptrs;

class Person {
	std::string _name;

public:
	Person(const std::string& name) :
		_name(name)
	{}

	std::string getNameCopy() const // ertekkel terek vissza, masolat lesz a memoriaban a hivas helyere
	{
		return _name;
	}

	const std::string& getNameRef() const // (read-only) hivatkozast ad vissza az adattagrol, hatekony, mert nincs masolas
	{
		return _name;
	}
};

// Ha referenciaval hatekonyabb, akkor miert nem feltetlen mindig azt hasznaljuk?
// Feladat: probaljunk kitalalni egy olyan szituaciot, amiben problemaba utkozunk,
// ha referenciat adunk vissza!

// Ebben a peldaban kicsit talan jobban megbujik a hiba:

void f()
{
	//...
	Person pers("Valaki mas"); // lokalis valtozoja az f fuggvenynek => hivasi verembe kerul
	//...
	str_ptrs.push_back( &(pers.getNameRef()) ); // beleteszem a globalis tombbe a _name adattagom cimet
	//...
	// az f fuggveny vegen torolve lesz a stack frame-jerol minden => pers torolve lesz
}

int main()
{
	f();
	//...
	std::cout <<  str_ptrs[0] << "\n"; // van 0-as indexu elem, hiszen beletettuk a memoria cimet, ez itt latszik
	std::cout << *str_ptrs[0] << "\n"; // ha viszont megprobalom dereferalni, akkor az undefined behavior
	                                   // (segfault a gyakorlatban), hiszen a mutatott string objektum mar torolve lett
}

// Ezert oda kell figyelni az objektumaink elettartamara es hogy ki mikor kire hivatkozik/mutat,
// mert az invalidda valt referenciak, illetve a logo pointerek (dangling pointers) konnyen crash-hez vezethetnek!

