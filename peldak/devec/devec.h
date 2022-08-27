#ifndef DEVEC__H // include guard a többszörös include miatt
#define DEVEC__H

#include <iterator> // std::iterator használatához
#include <vector>

template <typename T> // T típusú elemeket fogunk tárolni
class devec
{
private:

	int _capacity; // allokált memóriaterület mérete (fix, konstruáláskor derül ki)
	int _front;    // aktuális soron következő index az objektum "elején"
	int _back;     // aktuális soron következő index az objektum "végén"
	T * _buffer;   // dinamikus tömb címét fogja tárolni (a tömb _capacity méretű lesz és T típusú elemeket tárol)

public:

	// Konstruktor (capacity : lefoglalandó memória terület mérete)
	devec(int capacity) :
		_capacity(capacity),
		_front(_capacity / 2 - 1),
		_back(_capacity / 2),
		_buffer(new T[_capacity]) // _capacity méretű dinamikus tömb létrehozása a new operátorral,
	{}                                // amire a _buffer fog mutatni

	// Copy konstruktor
	devec(const devec<T>& other) : // const referenciaként vesszük át a másikat -> nincs másolás és read-only
		_capacity(other._capacity), // másolatot készítünk a másik objektum állapota alapján
		_front(other._front),
		_back(other._back),
		_buffer(new T[_capacity]) // a _buffer pointer-t NEM másoljuk így: _buffer(other._buffer),
	{                                 // hiszen az új példánynak saját allokált területet szeretnénk (lásd: shallow vs deep copy)
		for (int i=_front+1; i<_back-1; ++i)
			_buffer[i] = other._buffer[i]; // átmásoljuk a tömb "értelmes" értékeit
	}

	// Destruktor
	~devec()
	{
		delete[] _buffer; // dinamikusan allokált memória felszabadítása a delete[] operátorral
	}                         // az objektum életciklusának végén

	// Eddig feltöltött rész mérete
	int size() const // konstans tagfv, hogy hívható legyen konstans objektumokon is
	{
		return _back - _front - 1;
	}

	// Elem beszúrása a végére
	void push_back(const T& elem) // elem konstans referencia -> lokális másolat nélkül,
	{                             // de read-only módon vesszük át -> hatékony
		_buffer[_back++] = elem; // postfix increment operátor növel, de az eredeti értékkel tér vissza
	}

	// Elem beszúrása az elejére
	void push_front(const T& elem)
	{
		_buffer[_front--] = elem; // postfix decrement operátor csökkent, de az eredeti értékkel tér vissza
	}

	// Elem lekérdezése
	T& at(int index) // nem-konstans referenciát adunk vissza a belső elemről (mutable)
	{
		return _buffer[_front + index + 1];
	}

	// Elem lekérdezése (read-only)
	const T& at(int index) const // konstans referenciát adunk vissza a belső elemről (read-only)
	{                            // + konstans tagfv -> hívható lesz konst objektumon
		return _buffer[_front + index + 1];
	}

	// Megjegyzés: A két at tagfüggvénynél a túlterhelés helyes,
	// a fordító mindig tudni fogja, hogy mely fv prototípust kell meghívni
	// Indoklás: Szemmel nem látszik, de más-más a formális paraméter lista
	// az implicit this paraméter (hívó objektum címét tárolja) miatt
	// A nem-const és const at esetén a teljes szignatúra rendre:
	//     at(      devec<T> * this, int index)
	//     at(const devec<T> * this, int index)
	// Ezért nem-konstans példányokon mindig az első, míg konstansokon mindig
	// a második prototípus lesz meghívva
	// A következő két fv prototípusnál (operator[] túlterhelése) is ugyanez
	// a helyzet

	// Elem lekérdezése
	T& operator[](int index) // at függvényhez hasonló
	{
		return _buffer[_front + index + 1];
	}

	// Elem lekérdezése (read-only)
	const T& operator[](int index) const // konstans at függvényhez hasonló
	{
		return _buffer[_front + index + 1];
	}

	// Belső típus definíció: devec<T>::iterator
	// Az egyszerűség kedvéért Forward iterátor lesz (a devmain.cpp-hez elég ez)
	// Megjegyzés:
	//     Lehetne Bi-directional (std::bidirectional_iterator_tag), ekkor kellene a két operator--
	//     Lehetne Random access (std::random_access_iterator_tag), kellene operator+, operator-, stb
	class iterator : public std::iterator<std::forward_iterator_tag, T> // std::iterator-ból öröklődik
	{                                                                   // sablon paraméterek: iterátor típusa és adat típusa
	private:
		T * _current; // az aktuális elem címét tárolja (T* típusú lesz)
	public:
		// A követkző tagfüggvényeket kell implementálni:
		explicit iterator(T * current) : _current(current) {} // iterátor konstruktora, egy elem címet vár
		iterator& operator++() { ++_current; return *this; } // prefix increment, megnöveli és új értékkel vissza
		iterator operator++(int) { iterator retval = *this; ++(*this); return retval; } // postfix increment, régi értékkel tér vissza
		bool operator==(iterator other) const { return _current == other._current; } // tárolt címeket hasonlítjuk össze
		bool operator!=(iterator other) const { return !(*this == other); } // negáljuk az előbb megírt operator==-t
		T& operator*() const { return *_current; } // a csillag operátor referenciát ad vissza az aktuális elemről
	};                                                 // (dereferálni kell a pointert)

	// Belső típus definíció: devec<T>::const_iterator
	// Majdnem ugyanaz, mint a sima iterator (érdemes copy/paste-elni a kódot)
	// Különbség, hogy ez konstans pointerrel tárolja az aktuális elem címét és
	// ebből adódóan (*_current konstanst ad) konstans referenciát ad vissza a csillag operátora (read-only elem elérés)
	class const_iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	private:
		const T * _current; // konstans pointer -> garantált a read-only-ság
	public:
		explicit const_iterator(const T * current) : _current(current) {}
		const_iterator& operator++() { ++_current; return *this; }
		const_iterator operator++(int) { const_iterator retval = *this; ++(*this); return retval; }
		bool operator==(const_iterator other) const { return _current == other._current; }
		bool operator!=(const_iterator other) const { return !(*this == other); }
		const T& operator*() const { return *_current; } // konstans referenciát ad vissza
	};

	// Megjegyzés: a _current pointer megnövelése (++ operátorral) eltolja
	// a címet sizeof(T)-vel, lásd: pointer aritmetika

	// Adatszerkezet első eleme
	iterator begin()
	{
		return iterator(&_buffer[_front + 1]); // átadjuk az iterátorunk konstruktorának az első
	}                                              // értelmes elem címét majd visszatérünk az iterátor példánnyal

	// Adatszerkezet első eleme (read-only)
	const_iterator cbegin() const // ez lehet konstans tagfv, mert const_iterator-t fog visszaadni
	{                             // -> konstans objektumokon ezt használva lehet majd végig iterálni
		return const_iterator(&_buffer[_front + 1]);
	}

	// Adatszerkezet "utolsó utáni", extremális eleme
	// Ezen nem definiált viselkedés operator*-ot hívni
	iterator end()
	{
		return iterator(&_buffer[_back]);
	}

	// Adatszerkezet "utolsó utáni", extremális eleme (read-only)
	const_iterator cend() const
	{
		return const_iterator(&_buffer[_back]);
	}

	// Megjegyzés: Most már, hogy megvannak ezek a tagfüggvények, végig lehet
	// iterálni egy devec példányon pl. a következő módon:
	// for (devec<int>::iterator it = dev.begin(); it != dev.end(); ++it) { std::cout << *it; }
	// A devmain.cpp-ben használt std::accumulate és std::count algoritmusok is
	// ehhez hasonló sémát használva járnak be tetszőleges kapott adatszerkezetet

	// Implicit (nincs kiírva elé az explicit kulcssó) konverziós operátor,
	// ami egy megfelelő std::vector<T>-re konvertálja devec példányunkat
	operator std::vector<T>() const
	{
		return std::vector<T>(cbegin(), cend());
		// Trükk: az std::vector-nak van olyan konstruktora, ami egy range-et vár
		// (iterátorokkal -tól -ig), ezt felhasználhatjuk, hiszen épp az imént
		// írtunk saját iterátort, cbegin-t és cend-et a devec-nek
		// Megjegyzés: const tagfv, így konstans devec példány is tud majd
		// std::vector objektumra konvertálódni
	}
}; // osztály definíció vége

#endif // DEVEC__H include guard vége

