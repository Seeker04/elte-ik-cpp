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

#include <iostream>

#include "linkedlist.h" // teljes osztály definíciót tartalmazza

template <typename T> // csak sablonfüggvény kaphat tetsz. sablonparaméterű sablonosztályt paraméterül
void print_list_info(const LinkedList<T>& list, const std::string& list_name)
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

// Függvény forward deklarációk, hogy a main-be már elérhetőek legyenek
void testcase_int();
void testcase_double();
void testcase_string();

int main()
{
	testcase_int();
	std::cout << "=====================================================\n";
	testcase_double();
	std::cout << "=====================================================\n";
	testcase_string();
}

// Megjegyzés: lényegében mind a három testcase fv ugyanaz, csak más-más
// típusokkal, mint sablonparaméterekkel, ill. más-más elemekkel
// Csak a legelsőbe (int-es) írtam kommenteket, azok a többire is érvényesek

void testcase_int()
{
	// Default konstruálás
	LinkedList<int> list_defktor;
	print_list_info(list_defktor, "list_defktor");

	// Alapértelmezett értékekkel feltöltés (nemnulla méret)
	LinkedList<int> list_defval_nonempty(42, 8);
	print_list_info(list_defval_nonempty, "list_defval_nonempty");

	// Alapértelmezett értékekkel feltöltés (0 méret)
	LinkedList<int> list_defval_empty(42, 0);
	print_list_info(list_defval_empty, "list_defval_empty");

	// Tömbértékekből konstruálás
	int array[] = { 10, 20, 30, 40, 50 };
	LinkedList<int> list_fromarray(array, 5);
	print_list_info(list_fromarray, "list_fromarray");

	// Másoló konstruktor
	LinkedList<int> list_copy(list_fromarray); // az előző listát másoljuk
	print_list_info(list_copy, "list_copy (list_fromarray-ből másoltunk)");
	// Megj.: Ez is másoló konstruálás lenne: LinkedList<int> list_copy = list_fromarray;
	//        és NEM értékadás operátor!

	// Értékadás operátor
	list_fromarray = list_defval_nonempty; // Már létező listának adunk új értéket
	print_list_info(list_fromarray, "list_fromarray (miután értékül adtuk neki list_defval_nonempty-t)");

	// Elemek beszúrása (előre/hátra)
	LinkedList<int> list;
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

	const LinkedList<int> clist(list); // konstans lista objektum (csak konstans tagfv-ek hivhatók rajta)
	// Másoló ktor-ral átmásoljuk a list állapotát, de később nem tudjuk átírni a const miatt
	print_list_info(clist, "clist (list-ből másoltuk)"); // OK, mert konst ref-et vár

	// Elem lekérdezés (read-only módon)
	std::cout << "clist.item_at(0) : " << clist.item_at(0) << "\n\n";
	// Itt a konstans item_at fv prototípus lesz meghívva, mert az átadott
	// hívó objektum címe konstans pointer (lásd: implicit const LinkedList<int> * this paraméter)
	// Ez a prototípus pedig már nem referenciát ad vissza, hanem érték szerint tér
	// vissza egy objektum másolattal (ami most int típusú), ezért ilyet nem is lehetne írni:
	// clist.item_at(0) = 42; (hiszen egy temporális rvalue nem kaphat új értéket)

	// Kivételek tesztelése
	// 1. remove_front on empty list
	try {
		LinkedList<int> list_empty; // üres lista
		list_empty.remove_front();
	}
	catch (const LinkedList<int>::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_front called on an empty list!\n";
	}
	// 2. remove_back on empty list
	try {
		LinkedList<int> list_empty; // üres lista
		list_empty.remove_back();
	}
	catch (const LinkedList<int>::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_back called on an empty list!\n";
	}
	// 3. remove_at with wrong index
	try {
		LinkedList<int> list(42, 3); // a lista: [42, 42, 42]
		list.remove_at(4); // túlindexelés
	}
	catch (const LinkedList<int>::IndexOutOfBoundsError& e) {
		std::cerr << "Error: remove_at called with an incorrect index!\n";
	}
	// 4. item_at with wrong index
	try {
		LinkedList<int> list(42, 5); // a lista: [42, 42, 42, 42, 42]
		std::cout << list.item_at(128) << "\n"; // túlindexelés
	}
	catch (const LinkedList<int>::IndexOutOfBoundsError& e) {
		std::cerr << "Error: item_at called with an incorrect index!\n";
	}

	// Itt lefut a testcase_int összes lokális változójának a destruktora, ezért
	// az összes láncolt listával meg lesz hívva a LinkedList<int>::~LinkedList
	// Így minden dinamikusan allokált Node-hoz meg lesz hívva a delete,
	// nincs memory leak (pl. valgrind-dal lehet ellenőrizni)
	//
	// Megjegyzés:
	// Nem véletlen írtam így: LinkedList<int>::~LinkedList
	//                         ~~~~~~~~~~~~~~~
	//                         ^
	// Hiszen a LinkedList önmagában csak egy osztálysablon, és NEM egy valid
	// típus (így nyilván nem is lehet névprefix, nem lehet destruktora sem)
	// EZEK már konkrét valid típusok:
	// LinkedList<int>, LinkedList<char *>, LinkedList<std::map<int, int>>,...
}

void testcase_double()
{
	LinkedList<double> list_defktor;
	print_list_info(list_defktor, "list_defktor");

	LinkedList<double> list_defval_nonempty(42.24, 8);
	print_list_info(list_defval_nonempty, "list_defval_nonempty");

	LinkedList<double> list_defval_empty(42.24, 0);
	print_list_info(list_defval_empty, "list_defval_empty");

	double array[] = { 0.1, 2., 0.3, .4, 5.5 };
	LinkedList<double> list_fromarray(array, 5);
	print_list_info(list_fromarray, "list_fromarray");

	LinkedList<double> list_copy(list_fromarray);
	print_list_info(list_copy, "list_copy (list_fromarray-ből másoltunk)");

	list_fromarray = list_defval_nonempty;
	print_list_info(list_fromarray, "list_fromarray (miután értékül adtuk neki list_defval_nonempty-t)");

	LinkedList<double> list;
	list.push_back(12.48);
	list.push_back(3.14);
	list.push_back(300.333);
	list.push_back(40.);
	list.push_front(-42.24);
	list.push_front(-84.8484);
	print_list_info(list, "list (push_back és push_front hívások után)");

	list.remove_front();
	print_list_info(list, "list (remove_front() után)");
	list.remove_back();
	print_list_info(list, "list (remove_back() után)");
	list.remove_at(2);
	print_list_info(list, "list (remove_at(2)) után");

	list.item_at(1) /= 2;
	print_list_info(list, "list (list.item_at(1) /= 2; utasítás után)");

	const LinkedList<double> clist(list);
	print_list_info(clist, "clist (list-ből másoltuk)");

	std::cout << "clist.item_at(0) : " << clist.item_at(0) << "\n\n";

	try {
		LinkedList<double> list_empty;
		list_empty.remove_front();
	}
	catch (const LinkedList<double>::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_front called on an empty list!\n";
	}
	try {
		LinkedList<double> list_empty;
		list_empty.remove_back();
	}
	catch (const LinkedList<double>::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_back called on an empty list!\n";
	}
	try {
		LinkedList<double> list(42.24, 3);
		list.remove_at(4);
	}
	catch (const LinkedList<double>::IndexOutOfBoundsError& e) {
		std::cerr << "Error: remove_at called with an incorrect index!\n";
	}
	try {
		LinkedList<double> list(24.42, 5);
		std::cout << list.item_at(128) << "\n";
	}
	catch (const LinkedList<double>::IndexOutOfBoundsError& e) {
		std::cerr << "Error: item_at called with an incorrect index!\n";
	}
}

void testcase_string()
{
	LinkedList<std::string> list_defktor;
	print_list_info(list_defktor, "list_defktor");

	LinkedList<std::string> list_defval_nonempty("asdASD", 8);
	print_list_info(list_defval_nonempty, "list_defval_nonempty");

	LinkedList<std::string> list_defval_empty("asdASD", 0);
	print_list_info(list_defval_empty, "list_defval_empty");

	std::string array[] = { "hello world", "asd", "teszt", "egy masik teszt", "almafa" };
	LinkedList<std::string> list_fromarray(array, 5);
	print_list_info(list_fromarray, "list_fromarray");

	LinkedList<std::string> list_copy(list_fromarray);
	print_list_info(list_copy, "list_copy (list_fromarray-ből másoltunk)");

	list_fromarray = list_defval_nonempty;
	print_list_info(list_fromarray, "list_fromarray (miután értékül adtuk neki list_defval_nonempty-t)");

	LinkedList<std::string> list;
	list.push_back("a");
	list.push_back("great");
	list.push_back("programming");
	list.push_back("language");
	list.push_front("is");
	list.push_front("C++");
	print_list_info(list, "list (push_back és push_front hívások után)");

	list.remove_front();
	print_list_info(list, "list (remove_front() után)");
	list.remove_back();
	print_list_info(list, "list (remove_back() után)");
	list.remove_at(2);
	print_list_info(list, "list (remove_at(2)) után");

	list.item_at(1) += "!!!";
	print_list_info(list, "list (list.item_at(1) += \"!!!\"; utasítás után)");

	const LinkedList<std::string> clist(list);
	print_list_info(clist, "clist (list-ből másoltuk)");

	std::cout << "clist.item_at(0) : " << clist.item_at(0) << "\n\n";

	try {
		LinkedList<std::string> list_empty;
		list_empty.remove_front();
	}
	catch (const LinkedList<std::string>::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_front called on an empty list!\n";
	}
	try {
		LinkedList<std::string> list_empty;
		list_empty.remove_back();
	}
	catch (const LinkedList<std::string>::OperationOnEmptyListError& e) {
		std::cerr << "Error: remove_back called on an empty list!\n";
	}
	try {
		LinkedList<std::string> list("asd", 3);
		list.remove_at(4);
	}
	catch (const LinkedList<std::string>::IndexOutOfBoundsError& e) {
		std::cerr << "Error: remove_at called with an incorrect index!\n";
	}
	try {
		LinkedList<std::string> list("asd2", 5);
		std::cout << list.item_at(128) << "\n";
	}
	catch (const LinkedList<std::string>::IndexOutOfBoundsError& e) {
		std::cerr << "Error: item_at called with an incorrect index!\n";
	}
}

