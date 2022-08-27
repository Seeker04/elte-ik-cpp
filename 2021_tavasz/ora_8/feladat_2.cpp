#include <iostream>
#include <vector>

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

int main()
{
	Person * pers = new Person("Valaki");

	// Copy
	std::string fetched_name_copy = pers->getNameCopy(); // eml.: ezt jelenti: (*pers).getNameCopy();

	// Ref
	const std::string& fetched_name_ref = pers->getNameRef();

	// Itt ref-et ad vissza, de masolas lesz, hiszen egy uj string-et konstrualok
	//std::string fetched_name = pers.getNameRef();

	delete pers;

	std::cout << fetched_name_copy << "\n"; // OK
	std::cout << fetched_name_ref  << "\n"; // segfault, mert a hivatkozott adattag mar torolve lett,
	                                        // amikor toroltem a peldanyt a memoriabol (invalid reference)
}

// Ezert oda kell figyelni az objektumaink elettartamara es hogy ki mikor kire hivatkozik/mutat,
// mert az invalidda valt referenciak, illetve a logo pointerek (dangling pointers) konnyen crash-hez vezethetnek!

