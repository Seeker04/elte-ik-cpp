/*
 *  Pelda egy egyszeru, tomb-alapu, dinamikus kontener tipus implementaciojara
 *  az std::vector mintajara.
 *  Bemutatja az osztaly irast, dinamikus memoria kezelest, operator irast es
 *  tulterhelest, konstanssag fogalmat, kivetelkezelest, az adatabsztrakcio es
 *  az adatelrejtes elvet.
 *
 *  Forditas: g++ main.cpp vector.cpp
 *  Futtatas: ./a.out (Linux)
 *            a.exe   (Windows)
 */

#ifndef VECTOR__H // include guard, pl. az ODR megsertesenek kivedesere (tobbszorosen ne include-oljuk)
#define VECTOR__H

class Vector { // definialjuk a Vector tipusunkat

public: // osztalyon kivulrol is lathatoak

	Vector();                             // default konstruktor
	Vector(const int * src, int srcSize); // tombbol masolo konstruktor
	Vector(const Vector& src);            // masolo konstruktor
	~Vector();                            // destruktor

	void add(int data); // adat hozzaadasa a vektor vegehez
	void pop(int data); // torol minden adott erteku elemet a vektorbol

	int getSize() const; // meret lekerdezese

	Vector& operator=(const Vector& src); // ertekadas operator

	int& operator[](int index); // referenciat kell visszaadni, hogy tudjunk ilyet: myVector[4] = 30;
	const int& operator[](int index) const; // kell, hogy const vectornak is le tudjuk kerdezni (read-only modon), hogy
	                                        // mi a kilencedik eleme, pl.: const Vector& ref = myVector; std::cout << ref[9];

	class OutOfBoundsException{}; // belso tipus definicio kivetelkezeleshez,
	                              // hivatkozni ra igy lehet: Vector::OutOfBoundsException

private: // csak ezen osztaly metodusai latjak

	int _capacity;
	int _size;
	int * _t; // dinamikus tomb lesz a belso reprezentacio => meret valtoztatasa lehetseges futasi idoben

};

#endif // VECTOR__H

