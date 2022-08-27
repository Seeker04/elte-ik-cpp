#include <iostream>

class Person {
public:
	Person(int id, std::string name) :
		// init lista
		_id(id),
		_name(name)
		// az x itt most nincs inicializalva, ezert o default konstrualva lesz
	{
		// ktor torzseben lehet egyeb kod...
		_name += "...";
	}
private:
	const int _id;     // kotelezo inicializalni az init listaban, uj erteket nem kaphat
	std::string _name;
	int x;
};

int main()
{
	Person person(42, "Asd"); // parameteres konstrualas
}

