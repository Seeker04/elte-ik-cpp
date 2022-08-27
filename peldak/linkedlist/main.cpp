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

#include <iostream>

#include "linkedlist.h"

void print_list_info(const LinkedList& list, const std::string& list_name)
{
	std::cout << list_name << "\n";
	std::cout << "  size: " << list.get_size() << "\n";
	std::cout << "  empty: " << (list.is_empty() ? "true" : "false") << "\n";
	std::cout << "  content: " << list << "\n\n";

	// Csak egy konstans hivatkozást veszünk át a listáról, ezért csak
	// konstans tagfv-ek hívhatóak a list param-on, amik biztosítják a
	// read-only-ságot
	// Felhasználjuk a get_size, az is_empty tagfüggvényeket, illetve az
	// operator<< túlterhelést, amit írtunk
}

int main()
{
	// Default konstruálás
	LinkedList list_defktor;
	print_list_info(list_defktor, "list_defktor");

	// Alapértelmezett értékekkel feltöltés (nemnulla méret)
	LinkedList list_defval_nonempty(42, 8);
	print_list_info(list_defval_nonempty, "list_defval_nonempty");

	// Alapértelmezett értékekkel feltöltés (0 méret)
	LinkedList list_defval_empty(42, 0);
	print_list_info(list_defval_empty, "list_defval_empty");

	// Tömbértékekből konstruálás
	int array[] = { 10, 20, 30, 40, 50 };
	LinkedList list_fromarray(array, 5);
	print_list_info(list_fromarray, "list_fromarray");

	// Másoló konstruktor
	LinkedList list_copy(list_fromarray); // az előző listát másoljuk
	print_list_info(list_copy, "list_copy (list_fromarray-ből másoltunk)");
	// Megj.: Ez is másoló konstruálás lenne: LinkedList list_copy = list_fromarray;
	//        és NEM értékadás operátor!

	// Értékadás operátor
	list_fromarray = list_defval_nonempty; // Már létező listának adunk új értéket
	print_list_info(list_fromarray, "list_fromarray (miután értékül adtuk neki list_defval_nonempty-t)");

	// Elemek beszúrása (előre/hátra)
	LinkedList list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	list.push_front(-42);
	list.push_front(-84);
	print_list_info(list, "list (push_back és push_front hívások után)");

	// Elemek törlése (elölről/hátulról/tetszőleges indexről)
	list.remove_front();
	print_list_info(list, "list (remove_front() után)");
	list.remove_back();
	print_list_info(list, "list (remove_back() után)");
	list.remove_at(2);
	print_list_info(list, "list (remove_at(2)) után");

	// Elem lekérdezés (átírható módon)
	list.item_at(1) += 3; // referenciát ad vissza a belső int-ről
	print_list_info(list, "list (list.item_at(1) += 3; utasítás után)");

	const LinkedList clist(list); // konstans lista objektum (csak konstans tagfv-ek hivhatók rajta)
	// Másoló ktor-ral átmásoljuk a list állapotát, de később nem tudjuk átírni a const miatt
	print_list_info(clist, "clist (list-ből másoltuk)"); // OK, mert konst ref-et vár

	// Elem lekérdezés (read-only módon)
	std::cout << "clist.item_at(0) : " << clist.item_at(0) << "\n\n";
	// Itt a konstans item_at fv prototípus lesz meghívva, mert az átadott
	// hívó objektum címe konstans pointer (lásd: implicit const LinkedList * this paraméter)
	// Ez a prototípus pedig már nem referenciát ad vissza, hanem érték szerint tér
	// vissza egy objektum másolattal (ami most int típusú), ezért ilyet nem is lehetne írni:
	// clist.item_at(0) = 42; (hiszen egy temporális rvalue nem kaphat új értéket)

	// Kivételek tesztelése
	// 1. remove_front on empty list
	try {
		LinkedList list_empty; // üres lista
		list_empty.remove_front();
	}
	catch (const LinkedList::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_front called on an empty list!\n";
	}
	// 2. remove_back on empty list
	try {
		LinkedList list_empty; // üres lista
		list_empty.remove_back();
	}
	catch (const LinkedList::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_back called on an empty list!\n";
	}
	// 3. remove_at with wrong index
	try {
		LinkedList list(42, 3); // a lista: [42, 42, 42]
		list.remove_at(4); // túlindexelés
	}
	catch (const LinkedList::IndexOutOfBoundsError& e) {
		std::cerr << "Error: remove_at called with an incorrect index!\n";
	}
	// 4. item_at with wrong index
	try {
		LinkedList list(42, 5); // a lista: [42, 42, 42, 42, 42]
		std::cout << list.item_at(128) << "\n"; // túlindexelés
	}
	catch (const LinkedList::IndexOutOfBoundsError& e) {
		std::cerr << "Error: item_at called with an incorrect index!\n";
	}

	// Itt lefut a main összes lokális változójának a destruktora, ezért
	// az összes láncolt listával meg lesz hívva a LinkedList::~LinkedList
	// Így minden dinamikusan allokált Node-hoz meg lesz hívva a delete,
	// nincs memory leak (pl. valgrind-dal lehet ellenőrizni)
}

