/*
 * Példa egy egyirányú, fejelemes, egészeket tároló egyszerű láncolt lista
 * implementációja.
 * Bemutatja az osztály írást, dinamikus memória kezelést, függvény túlterhelést,
 * konstansság fogalmát, kivételkezelést, az adatabsztrakció és adatelrejtés
 * elvét.
 *
 * Fordítás: g++ main.cpp linkedlist.cpp
 * Futtatás: ./a.out (Linux)
 *           a.exe   (Windows)
 *
 * Memória szivárgás tesztelése: valgrind ./a.out
 * (Linuxon, pl. a Caesar szerveren van valgrind telepítve)
 *
 */

#ifndef LINKED_LIST__H // Include guard, pl. az ODR megsértésének kivédésére
#define LINKED_LIST__H // (többszörösen ne include-oljuk)

#include <ostream>

class LinkedList { // Definiáljuk a LinkedList típusunkat

public: // Osztályon kívülről is láthatóak lesznek

	// Konstruktorok (más-más a szignatúra, ezért OK a függvény túlterhelés)
	LinkedList();                                     // Default konstruktor
	LinkedList(int default_value, unsigned int size); // Alap értékekkel feltöltő konstruktor
	LinkedList(int * src_array, unsigned int size);   // Tömbből másoló konstruktor
	LinkedList(const LinkedList& src);                // Másoló konstruktor

	// Destruktor (kell írni a dinamikusan allokált memória törléséhez)
	~LinkedList();

	// Értékadás operátor
	LinkedList& operator=(const LinkedList& src);

	// Elemet beszúró tagfüggvények
	void push_front(int value);
	void push_back(int value);

	// Elemet törlő tagfüggvények
	void remove_front();
	void remove_back();
	void remove_at(unsigned int index);

	// Elem index szerinti lekérdezése
	int& item_at(unsigned int index); // hivatkozást ad vissza, így ezt használva
	                                  // módosíthatjuk az elemet, pl. item_at(12) = 42;

	// Elemet, ürességet és méretet lekérdező konstans tagfüggvények
	int item_at(unsigned int index) const; // Érték szerint tér vissza => csak olvasásra használható
	                                       // Megj.: NEM a visszatérési típus miatt OK a túlterhelés,
	                                       // hanem a tagfv konstanssága miatt (az része a szignatúrának)
	bool is_empty() const;
	unsigned int get_size() const;

	// Kivétel típusok
	class IndexOutOfBoundsError{};     // Ezeknek is publikusnak kell lenniük, hogy a "külvilág"
	class OperationOnEmptyListError{}; // egyáltalán tudjon létezésükről, így elkaphatók legyenek

	// A << operátor barátfüggénye lesz az osztálynak, így láthatja a privát tagokat
	friend std::ostream& operator<<(std::ostream& out, const LinkedList& list); // Ez egy deklaráció

private: // Osztályon kívülről nem láthatóak

	// Privát segédfüggvények (csak saját metódusok használhatják őket)
	void copy_from_other_list(const LinkedList& src);
	void delete_list();
	bool is_index_valid(unsigned int index) const;

	// Privát, belső adattípus típusdefiníciója a láncolt lista reprezentálására
	struct Node {
		int value;   // tárolt érték
		Node * next; // következő elem címe
	};

	Node * _head;       // lista fejeleme
	unsigned int _size; // méret (azért tároljuk és frissítjük, hogy a méret
	                    // lekérdezése esetén ne kelljen mindig újra végig
	                    // lépegetni a teljes listán, így lineáris helyett
	                    // konstans időigényű lesz a get_size és az
	                    // is_index_valid tagfüggvények)

};

#endif // LINKED_LIST__H

