#include <iostream>

int gt[3]; // globalis tomb -> static memory-ba megy -> program teljes futasa alatt el
           // (lifetime es scope is a teljes futas)

int main()
{
	// TOMBOK FOGALMA

	// Fix a tarolt tipus, osszes eleme ugyanolyan tipusu
	// +
	// Elem tipus merete ismert (lasd: statikusan tipusos nyelv)
	// => Fix a tomb valtozo osszmerete
	// Raadasul statikus tombok eseten ennek statikus (forditasi) idoben ismertnek kell lennie
	// (Dinamikus tombokrol - amik a heap-re kerulnek new hivassal - kesobb...)

	// Dinamikusan tipusos nyelvekben sokszor lehet ilyesmiket: (pl. Python)
	// t = [ 42, "text", false ] <-- nincs deklaracio, mas-mas elem tipusok (mereteik is mas-masok)
	// t.append(10)              <-- futasi idoben meg adunk hozza elemet
	// Ilyeneket C++-ban nem lehet, lasd: statikus tipusossag
	// Dinamikusan tipusos nyelvekben miert lehet? Az interpreter "elabsztraktalja"
	// ezek kezeleset, de a fedo alatt persze ezeknel is processzor utasitasok, kozvetlen memoria
	// kezeles lesz, viszont a "lazasagok" miatt magas futasi ideju koltsegek lesznek
	// Pl. ha sokszor append-elunk, akkor sokszor elofordulhat, hogy mar nincs szabad cim
	// a tomb vege mogott, ezert az egeszet at kell masolni, de-allokalni es ujra-allokalni...
	// Ezeket mind az interpreter kezeli a sajat memoriajaban, de ennek a kezelesnek
	// koltsegei vannak -> + processor ido -> lassabb...

	//---------------------------------------------------------------------

	// INICIALIZALATLAN TOMBOK, SIZEOF OPERATOR

	int t[3]; // lokalis valtozoja a main fv-nek -> stack memory-ba kerul

	std::cout << t[0] << "\n";
	std::cout << t[1] << "\n";
	std::cout << t[2] << "\n";

	std::cout << gt[0] << "\n";
	std::cout << gt[1] << "\n"; // inicializalatlan, de globalis -> zero inicializalta az elemeket
	std::cout << gt[2] << "\n"; // (hiszen static memory beallitasanak nincs futasi ideju koltsege)

	std::cout << sizeof(t) << "\n";

	std::cout << sizeof(t) / sizeof(t[0]) << "\n"; // tomb osszmerete / elem merete = elemek szama
	std::cout << sizeof(t) / sizeof(*t)   << "\n"; // ugyanaz, miert?

	//---------------------------------------------------------------------

	// POINTER ARITMETIKA, OSSZEFUGGES A TOMBOKKEL, TOMB INICIALIZALAS

	int   x = 42;
	int * p = &x; // "ramutat", x cimet tarolja le
	std::cout << *p  << "\n"; // mutatott int erteke
	std::cout << p   << "\n"; // maganak a pointer valtozonak az erteke (memory address hexa formatumban)
	std::cout << p+1 << "\n"; // pointer aritmetika: eltoljuk a cimet 1xsizeof(int)-tel
	// (mert int a mutatott tipus) - NEM 1 bajttal! - (lasd: tomb szemantika)

	double l = 42.42;
	double* q = &l;
	std::cout << *q  << "\n";
	std::cout << q   << "\n";
	std::cout << q+1 << "\n"; // hasonlo, de most mivel double-re mutat, ezert
	// sizeof(double) az eltolas merteke (pl. 8)

	int t2[] = { 10, 20, 30, 40}; // tomb inicializalas, nem kell most meret,
	// mert az init list-bol ki tudja deriteni
	//int t_nosize[]; // ez mar rossz! mekkora legyen? a C++ standard tiltja a
	// meret nelkuli valtozokat
	// (fun fact: class Valami {}; <-- meg egy ilyen ures osztaly
	// peldanyanak is lesz 1 bajt merete, memoriaban kell lennie, kell cim)

	std::cout << t2        << "\n"; // kezdo elem cime, mindig azt tarolja a tomb valtozo
	std::cout << *(t2 + 0) << "\n"; // 0-val  tolom el a cimet es dereferalom -> 1. elem
	std::cout << *(t2 + 1) << "\n"; // 1-gyel tolom el a cimet es dereferalom -> 2. elem
	std::cout << *(t2 + 2) << "\n"; // 2-vel  tolom el a cimet es dereferalom -> 3. elem
	// Ezert indexelunk 0-tol, mert az index az eltolas merteke

	// Ugyanaz, masik szintaxissal:
	std::cout << t2[0] << "\n"; // ekvivalens *(t2 + 0)-val
	std::cout << t2[1] << "\n";
	std::cout << t2[2] << "\n";

	// De az osszeadas kommutativ, nem?
	//
	// *(t2 + 1) == *(1 + t2)
	//   ||             ||
	//  t2[1]    ==    1[t2] ???

	// Igen...
	std::cout << "\n";
	std::cout << 1[t2] << "\n"; // hack

}

