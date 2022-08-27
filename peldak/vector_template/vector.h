/*
 *  Pelda egy egyszeru, tomb-alapu, dinamikus sablon kontener tipus
 *  implementaciojara az std::vector mintajara.
 *  Bemutatja az osztaly irast, dinamikus memoria kezelest, operator irast es
 *  tulterhelest, konstanssag fogalmat, kivetelkezelest, az adatabsztrakcio es
 *  az adatelrejtes elvet, valamint a sablonok hasznalatat
 *
 *  Forditas: g++ main.cpp
 *  Futtatas: ./a.out (Linux)
 *            a.exe   (Windows)
 */

#ifndef VECTOR__H // include guard, az ODR megsertesenek kivedesere (tobbszorosen ne include-oljuk)
#define VECTOR__H

#include <ostream>

template <typename T> // sablon osztaly lesz 1 sablon parameterrel, ami tetszoleges tipus lehet
class Vector { // definialjuk a Vector tipusunkat

public: // osztalyon kivulrol is lathatoak, metodus deklaraciok

	Vector();                           // default konstruktor
	Vector(const T * src, int srcSize); // tombbol masolo konstruktor
	Vector(const Vector& src);          // masolo konstruktor
	~Vector();                          // destruktor

	void add(const T& data); // adat hozzaadasa a vektor vegehez
	void pop(const T& data); // torol minden adott erteku elemet a vektorbol

	int getSize() const; // meret lekerdezese

	Vector& operator=(const Vector& src); // ertekadas operator

	T& operator[](int index); // referenciat kell visszaadni, hogy tudjunk ilyet: myVector[4] = 30;
	const T& operator[](int index) const; // kell, hogy const vectornak is le tudjuk kerdezni (read-only modon), hogy
	                                      // mi a kilencedik eleme, pl.: const Vector& ref = myVector; std::cout << ref[9];

	class OutOfBoundsException{}; // belso tipus definicio kivetelkezeleshez,
	                              // hivatkozni ra igy lehet: Vector::OutOfBoundsException

	template <typename VectT>
	friend std::ostream& operator<<(std::ostream& out, const Vector<VectT>& vect);
	// barat fuggveny kiiratashoz lathatja a Vector privat tagjait is

private: // csak ezen osztaly metodusai latjak

	int _capacity;
	int _size;
	T * _t; // dinamikus tomb lesz a belso reprezentacio => meret valtoztatasa lehetseges futasi idoben
	        // tomb elemeinek tipusa a sablon parameterkent atvett tetszoleges tipus
	        // a template-ek forditasi idoben generalodnak le, igy ford. idoben ismert lesz ez a tipus,
	        // tehat nincs megsertve a nyelv statikus tipusossaga

};

#include "vector.tpp"

// A "vector.tpp" fajlba vannak benne a metodus definiciok, amiket az include direktivaval bemasolunk ide
// Ezt azert csak igy oldhatjuk meg, mert a sablon osztalybol/fuggvenybol valo kodgeneralas mar a targykod
// generalasi lepesben szukseges, mert ekkor a tipus teljes definiciojara szukseg van
// Nem lehet kulon forditasi egysegbe (.cpp) kiszervezni, mert az osszeszerkesztesi (linkelesi) lepes mar keso ehhez

#endif // VECTOR__H

