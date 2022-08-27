#include <iostream>

class NeptunProfile; // osztaly forward deklaralas

class Person {
	NeptunProfile * neptProfile;
};

class NeptunProfile {
	Person * owner;
};

// megjegyzes: az mas kerdes, hogy mennyire celszeru ilyen design decision-t
//             hozni, hogy ket osztaly egymas dependenciaja legyen ilyen modon

int main()
{
}

