/*
 * Példa egy egyirányú, fejelemes, egészeket tároló egyszerű láncolt lista
 * implementációja.
 * Bemutatja az osztály írást, dinamikus memória kezelést, függvény túlterhelést,
 * konstansság fogalmát, kivételkezelést, az adatabsztrakció és adatelrejtés
 * elvét, valamint a sablonok használatát.
 *
 * Fordítás: g++ main.cpp
 * Futtatás: ./a.out (Linux)
 *           a.exe   (Windows)
 *
 * Memória szivárgás tesztelése: valgrind ./a.out
 * (Linuxon, pl. a Caesar szerveren van valgrind telepítve)
 *
 */

// Most a tagfüggvény definíciók az osztálytörzsben lesznek megadva.
// Erre azért van szükség, mert már a tárgykód generálási lépés során a fordítónak
// szüksége van a teljes osztálytörzsre, hogy le tudja generálni az osztály
// teljes definícióját (illetve, hogy tudjon rajta statikus ellenőrzéseket futtatni).
//
// Indoklás #1:
// A main.cpp-ben az első "LinkedList<int> varname;" alakú változó deklaráció
// esetén a fordítónak le kell generálnia a T=int sablonparaméter behelyettesítéssel
// az osztály teljes definícióját, amik magába foglalják a tagfüggvény törzseket is
// (lásd: lejjebb ebben a fájlban van ahol használva van a T függvény törzsön belül)
//
// Indoklás #2:
// A T=int, T=double, T=std::string, stb. sablonparaméter behelyettesítések esetén
// a legenerált osztály kódokat le kell fordítania, ami statikus ellenőrzéseket
// is megkövetel. Például ha egy olyan típussal próbálunk meg LinkedList osztályt
// legeneráltatni, melyet nem lehet default konstruálni (nincs def ktor), vagy
// nem lehet std::ostream-re kiíratni az operator<<-tal, akkor fordítási hibát
// kapunk. Ezek a követelmények a tagfüggvény definíciókból jönnek, ezért ezekre
// értelem szerűen szükség van már a fordítási (vagy más szóval: tárgykód generálási)
// lépésnél.
//
// Ez az oka annak, hogy az összeszerkesztési (linkelési) lépéskor már késő
// lenne megkapni a tagfüggvény definíciókat, így nem lehet külön fordítási egységbe
// (.cpp) kiszervezni őket.
// Így viszont, hogy minden a fejállományban van, a main.cpp mindent megkap az
// #include segítségével.
//
// Megjegyzés: Ha mégis külön fájlba szeretnénk írni a tagfv def-eket, akkor lásd:
// a vector_template példában alkalmazott trükk.

#ifndef LINKED_LIST__H // Include guard, pl. az ODR megsértésének kivédésére
#define LINKED_LIST__H // (többszörösen ne include-oljuk)

#include <ostream>

template <typename T> // Sablon osztály lesz, a T sablon paraméter a listában tárolt elemek típusa
class LinkedList { // Definiáljuk a LinkedList típusunkat

public: // Osztályon kívülről is láthatóak lesznek

	// Kivétel típusok
	class IndexOutOfBoundsError{};     // Ezeknek is publikusnak kell lenniük, hogy a "külvilág"
	class OperationOnEmptyListError{}; // egyáltalán tudjon létezésükről, így elkaphatók legyenek


	// Konstruktorok (más-más a szignatúra, ezért OK a függvény túlterhelés)

	// Default konstruktor
	LinkedList() :
		_head(new Node {T{}, nullptr}),
		_size(0)
	{
	}

	// Alapértelmezett értékekkel feltöltő konstruktor
	LinkedList(const T& default_value, unsigned int size) :
		_head(new Node {T{}, nullptr}),
		_size(size)
	{
		Node * current = _head;
		while (size--) {
			current->next = new Node {default_value, nullptr};
			current = current->next;
		}
	}

	// Tömbből másoló konstruktor
	LinkedList(T * src_array, unsigned int size) :
		_head(new Node {T{}, nullptr}),
		_size(size)
	{
		Node * current = _head;
		for (unsigned int i=0; i<_size; ++i) {
			current->next = new Node {src_array[i], nullptr};
			current = current->next;
		}
	}

	// Másoló konstruktor (nem akarunk shallow copy-t!)
	LinkedList(const LinkedList<T>& src) : // természetesen LinkedList<float> csak LinkedList<float>-ot kaphat
		_head(new Node {T{}, nullptr}),
		_size(src._size)
	{
		copy_from_other_list(src);
	}

	// Destruktor (kell írni a dinamikusan allokált memória törléséhez)
	~LinkedList()
	{
		delete_list();
	}

	// Értékadás operátor (nem akarunk shallow copy-t!)
	LinkedList& operator=(const LinkedList<T>& src) // itt is fontos, hogy egyezzen a this és az src sablonparam-ja
	{
		if (&src == this)     // Nem akarunk semmit csinálni, ha ugyanazt a listát
			return *this; // akarjuk önmagának értékül adni, pl. my_list = my_list;
		delete_list();
		_size = src._size;
		_head = new Node {T{}, nullptr};
		copy_from_other_list(src);
		return *this;
		// Megj.: Azért térünk vissza az objektumra hivatkozó referenciával, hogy
		// lehessen pl. ilyet: list1 = list2 = list3; Az operator= jobboldali
		// asszociativitása miatt ez így fog kiértékelődni: list1 = (list2 = list3);
	}

	// Elem beszúrása a lista elejére
	void push_front(const T& value)
	{
		_head->next = new Node {value, _head->next};
		++_size;
	}

	// Elem beszúrása a lista végére
	void push_back(const T& value)
	{
		Node * current = _head;
		while (current->next)
			current = current->next;
		current->next = new Node {value, nullptr};
		++_size;
	}

	// Elem törlése a lista elejéről
	void remove_front()
	{
		if (_size == 0)
			throw OperationOnEmptyListError();
		Node * old_head = _head;
		_head = old_head->next;
		delete old_head;
		--_size;
	}

	// Elem törlése a lista végéről
	void remove_back()
	{
		if (_size == 0)
			throw OperationOnEmptyListError();
		Node * prev = _head;
		Node * current = prev->next;
		while (current->next) {
			prev = current;
			current = current->next;
		}
		prev->next = nullptr;
		delete current;
		--_size;
	}

	// Megadott indexű elem törlése
	void remove_at(unsigned int index)
	{
		if (!is_index_valid(index))
			throw IndexOutOfBoundsError();
		Node * prev = _head;
		Node * current = prev->next;
		while (index--) {
			prev = current;
			current = current->next;
		}
		prev->next = current->next; // Kifűzzük az elemet a listából
		delete current;
		--_size;
	}

	// Megadott indexű elem lekérdezése (referenciát ad)
	// hivatkozást ad vissza, így ezt használva módosíthatjuk az elemet, pl. item_at(12) = 42;
	T& item_at(unsigned int index)
	{
		if (!is_index_valid(index))
			throw IndexOutOfBoundsError();
		Node * current = _head->next;
		while (index--)
			current = current->next;
		return current->value; // itt nem kell sehogy jelezni, hogy referenciát adunk vissza
	}

	// Megadott indexű elem lekérdezése (másolatot ad)
	// Érték szerint tér vissza => csak olvasásra használható
	// Megj.: NEM a visszatérési típus miatt OK a túlterhelés,
	// hanem a tagfv konstanssága miatt (az része a szignatúrának)
	T item_at(unsigned int index) const
	{
		if (!is_index_valid(index))
			throw IndexOutOfBoundsError();
		Node * current = _head->next;
		while (index--)
			current = current->next;
		return current->value; // egy temporáris objektumot fog gyártani és azt adja vissza (lásd: rvalue)
	}

	// Üres-e a lista
	bool is_empty() const
	{
		return _size == 0;
	}

	// Lista méretét adja vissza
	unsigned int get_size() const
	{
		return _size;
	}


	// A << operátor barátfüggénye lesz az osztálynak, így láthatja a privát tagokat
	friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list) // Ez egy operátor túlterhelés
	{
		out << "[";
		Node * current = list._head->next; // A barátság miatt látszódik a privát Node típus és a _head adattag
		while (current) {
			out << current->value << (current->next ? ", " : ""); // Nem kell a vessző, ha már nincs következő elem
			current = current->next;
		}
		out << "]";
		return out; // Azért térünk vissza az output stream-re hivatkozó referenciával,
		            // hogy lehessen majd ilyet: std::cout << list1 << list2 << "\n";
		            // Ez így zárójeleződik: ((std::cout << list1) << list2) << "\n";
	}
	// Megj.: Ez a barátságkötés elkerülhető lett volna a listához készített
	// getter-eknek hála. Így viszont hatékonyabban tudtuk ezt az algoritmust implementálni.
	// Kérdés: miért?


private: // Osztályon kívülről nem láthatóak

	// Privát segédfüggvények (csak saját metódusok használhatják őket)

	void copy_from_other_list(const LinkedList<T>& src)
	{
		Node * current = _head;
		Node * src_current = src._head->next;
		while (src_current) {
			current->next = new Node {src_current->value, nullptr};
			current = current->next;
			src_current = src_current->next;
		}
	}

	void delete_list()
	{
		Node * current = _head;
		while (current) {
			Node * next = current->next;
			delete current;
			current = next;
		}
		_size = 0;
	}

	bool is_index_valid(unsigned int index) const
	{
		return index < _size; // Megj.: ha _size 0, akkor ez mindig hamissal tér vissza
	}


	// Privát, belső adattípus típusdefiníciója a láncolt lista reprezentálására
	struct Node {
		T value;     // tárolt érték, a típusát a sablonparaméter határozza meg
		Node * next; // következő elem címe
	};


	// Adattagok
	Node * _head;       // lista fejeleme
	unsigned int _size; // méret (azért tároljuk és frissítjük, hogy a méret
	                    // lekérdezése esetén ne kelljen mindig újra végig
	                    // lépegetni a teljes listán, így lineáris helyett
	                    // konstans időigényű lesz a get_size és az
	                    // is_index_valid tagfüggvények)

};

#endif // LINKED_LIST__H

