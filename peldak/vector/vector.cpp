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


#include "vector.h" // Itt fogjuk definialni a Vector tipus tagfuggvenyeit, melyek "vector.h"-ban vannak
                    // deklaralva, illetve maga a Vector tipus is az iment emlitett header-ben van
                    // deklaralva (es reszben-definialva), ezert szukseges, hogy mar a targykod generalasi
                    // lepesnel ismertek legyenek peldaul a kovetkezo szimbolumok: Vector, Vector::_size, Vector::_t, stb.
                    // ezert kell ide elore bemasolni a "vector.h" tartalmat az #include preprocesszor direktivaval

Vector::Vector() : // default konstruktor
	_capacity(1), // inicializalo lista
	_size(0),
	_t(new int[_capacity]) // dinamikus tombhoz memoria foglalasa a new operatorral,
	                       // ami a lefoglalt tarhely kezdocimevel (azaz a 0. elem cimevel) ter vissza
{}

Vector::Vector(const int * src, int srcSize) :
	_capacity(1),
	_size(srcSize),
	_t(nullptr)
{
	while (_capacity < _size)
		_capacity *= 2;
	_t = new int[_capacity];
	for (int i=0; i<_size; ++i)
		_t[i] = src[i];
}

Vector::Vector(const Vector& src) : // masolo konstruktor
	_capacity(src._capacity), // hozzaferhetunk kozvetlenul a masik peldany privat adattagjaihoz is,
	_size(src._size),         // hiszen lathatosag szempontjabol a Vector osztalyon "belul vagyunk"
	_t(new int[_capacity])
{
	for (int i=0; i<_size; ++i)
		_t[i] = src._t[i];
}

Vector::~Vector()
{
	delete[] _t; // a delete[] operator felszabaditja a _t pointer/tomb altal mutatott tarhelyet,
	             // ez kell, hogy ne legyen memoria szivargas a programban!
}

void Vector::add(int data)
{
	if (_size == _capacity) {
		_capacity *= 2;
		int * tmp = new int[_capacity];
		for (int i=0; i<_size; ++i)
			tmp[i] = _t[i];
		delete[] _t;
		_t = tmp;
	}
	_t[_size++] = data; // postfix inkrementalas noveli eggyel, de a regi erteket adja vissza
}

void Vector::pop(int data)
{
	int * tmp = new int[_capacity];
	for (int i=0, j=0; i<_size; ++i)
		if (_t[i] != data)
			tmp[j++] = _t[i];
		else
			--_size;
	delete[] _t;
	_t = tmp;
}

int Vector::getSize() const
{
	return _size;
}

Vector& Vector::operator=(const Vector& src) // ertekadas operator
{
	if (this == &src) // osszehasonlitjuk a ket objektum cimet
		return *this; // azert kell, hogy ne csinaljunk felesleges masolgatast ilyen esetekben: a = a;

	_capacity = src._capacity;
	_size = src._size;

	delete[] _t;
	_t = new int[_capacity];

	for (int i=0; i<_size; ++i)
		_t[i] = src._t[i];

	return *this; // visszaterunk a hivo objektumra valo hivatkozassal (lasd: visszateresi tipus referencia)
	              // ez azert kell, hogy tudjuk akar igy is hasznalni: a = b = c;
	              // hiszen az ertekadas operatorok jobb-asszociativak, igy az elozo ekvivalens ezzel: a = (b = c);
		      // std::cout << (a = b);
}

int& Vector::operator[](int index) // referenciat (hivatkozast) adunk vissza a megfelelo "belso" elemrol,
                                   // igy azt "kintrol" modosithatjuk is, pl. myVector[4] = 10;
{
	if (index < 0 || _size <= index)
		throw OutOfBoundsException(); // kivetelt dobunk rossz index eseten, itt a fv vezerlese megszakad
	return _t[index];
}

// Tagfuggvenyeknel a konstanssag is a szignatura resze, igy ez a const metodus mas
// szignaturaju, mint az elobbi nem-const prototipus, ezert megfelelo a tulterheles (overloading)
const int& Vector::operator[](int index) const
{
	if (index < 0 || _size <= index)
		throw OutOfBoundsException();
	return _t[index];
}
// const referenciat adhat vissza const metodus,
// igy read-only modon olvashatjuk ki az adott indexu elemet,
// ezert pl. konstans vektorbol is tudunk kiolvasni elemet,
// ezt a fv prototipust fogja meghivni a fordito a this parameter const Vector * tipusa miatt

