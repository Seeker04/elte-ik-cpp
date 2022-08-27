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

#include "linkedlist.h" // a tárgykód generáláshoz szükségünk lesz a teljes osztály def-re

// Default konstruktor
LinkedList::LinkedList() :
	_head(new Node {0, nullptr}),
	_size(0)
{
}

// Alapértelmezett értékekkel feltöltő konstruktor
LinkedList::LinkedList(int default_value, unsigned int size) :
	_head(new Node {0, nullptr}),
	_size(size)
{
	Node * current = _head;
	while (size--) {
		current->next = new Node {default_value, nullptr};
		current = current->next;
	}
}

// Tömbből másoló konstruktor
LinkedList::LinkedList(int * src_array, unsigned int size) :
	_head(new Node {0, nullptr}),
	_size(size)
{
	Node * current = _head;
	for (unsigned int i=0; i<_size; ++i) {
		current->next = new Node {src_array[i], nullptr};
		current = current->next;
	}
}

// Másoló konstruktor
LinkedList::LinkedList(const LinkedList& src) :
	_head(new Node {0, nullptr}),
	_size(src._size)
{
	copy_from_other_list(src);
}

// Destruktor
LinkedList::~LinkedList()
{
	delete_list();
}

// Értékadás operátor
LinkedList& LinkedList::operator=(const LinkedList& src)
{
	if (&src == this)     // Nem akarunk semmit csinálni, ha ugyanazt a listát
		return *this; // akarjuk önmagának értékül adni, pl. my_list = my_list;
	delete_list();
	_size = src._size;
	_head = new Node {0, nullptr};
	copy_from_other_list(src);
	return *this;
	// Megj.: Azért térünk vissza az objektumra hivatkozó referenciával, hogy
	// lehessen pl. ilyet: list1 = list2 = list3; Az operator= jobboldali
	// asszociativitása miatt ez így fog kiértékelődni: list1 = (list2 = list3);
}

// Elem beszúrása a lista elejére
void LinkedList::push_front(int value)
{
	_head->next = new Node {value, _head->next};
	++_size;
}

// Elem beszúrása a lista végére
void LinkedList::push_back(int value)
{
	Node * current = _head;
	while (current->next)
		current = current->next;
	current->next = new Node {value, nullptr};
	++_size;
}

// Elem törlése a lista elejéről
void LinkedList::remove_front()
{
	if (_size == 0)
		throw OperationOnEmptyListError();
	Node * old_head = _head;
	_head = old_head->next;
	delete old_head;
	--_size;
}

// Elem törlése a lista végéről
void LinkedList::remove_back()
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
void LinkedList::remove_at(unsigned int index)
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
int& LinkedList::item_at(unsigned int index)
{
	if (!is_index_valid(index))
		throw IndexOutOfBoundsError();
	Node * current = _head->next;
	while (index--)
		current = current->next;
	return current->value; // itt nem kell sehogy jelezni, hogy referenciát adunk vissza
}

// Megadott indexű elem lekérdezése (másolatot ad)
int LinkedList::item_at(unsigned int index) const
{
	if (!is_index_valid(index))
		throw IndexOutOfBoundsError();
	Node * current = _head->next;
	while (index--)
		current = current->next;
	return current->value; // egy temporáris objektumot fog gyártani és azt adja vissza (lásd: rvalue)
}

bool LinkedList::is_empty() const
{
	return _size == 0;
}

unsigned int LinkedList::get_size() const
{
	return _size;
}

// Segédfüggvények ------------------------------------------------------------

void LinkedList::copy_from_other_list(const LinkedList& src)
{
	Node * current = _head;
	Node * src_current = src._head->next;
	while (src_current) {
		current->next = new Node {src_current->value, nullptr};
		current = current->next;
		src_current = src_current->next;
	}
}

void LinkedList::delete_list()
{
	Node * current = _head;
	while (current) {
		Node * next = current->next;
		delete current;
		current = next;
	}
	_size = 0;
}

bool LinkedList::is_index_valid(unsigned int index) const
{
	return index < _size; // Megj.: ha _size 0, akkor ez mindig hamissal tér vissza
}

// Barátfüggvény --------------------------------------------------------------

// Ez a barátfüggvény (jelen esetben egy operátor túlterhelés) definíciója
std::ostream& operator<<(std::ostream& out, const LinkedList& list)
{
	out << "[";
	LinkedList::Node * current = list._head->next; // A barátság miatt látszódik a
	                                               // privát Node típus és a _head adattag
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

