#include <iostream>

// Fv tipusokat a visszateresi tipus es a formalis parameter lista hatarozza meg
// Pl. ezek mas-mas fv tipusok:
//   void(int,int)
//   bool(const char *)
//   long&()

void doubleInt(int& i)  { i*= 2; } // referencia az aktualis paramra -> at tudja irni
void invertSign(int& i) { i*=-1; }

//void foreach(int *t, int size, void (*p)(int&)) <--- t[] helyett *t is ok, ugyanaz
void foreach(int t[], int size, void (*p)(int&)) // var egy int tombot, a meretet es egy
{                                                // fv pointert, ami int referenciat var
	for (int i=0; i<size; ++i)               // es nem ter vissza semmivel
		p(t[i]);  // meghivja a p altal mutatott fv-t a t[i]-vel (ref szerint adja at)
		          // (ki lehetet volna irni a dereferalast: *p(t[i]), de fv pointernel nem kell
}

int gt[3]; // globalis tomb -> static memory-ba megy -> program teljes futasa alatt el
           // (lifetime es scope is a teljes futas)

int main()
{
	// FUGGVENY POINTEREK

	int array[4] = { 10, -5, 42, 3 };

	foreach(array, 4, &doubleInt); // atadom a tombot (pointer-t),
	                               // a meretet (mennyivel szabad max eltolni,
	                               // es a fuggveny cimet (tipushelyes, mert void(int&)

	std::cout << array[0] << "\n";
	std::cout << array[1] << "\n";
	std::cout << array[2] << "\n";
	std::cout << array[3] << "\n";

	foreach(array, 4, invertSign); // a referalo & operatort fv elol el is lehet hagyni

	std::cout << array[0] << "\n";
	std::cout << array[1] << "\n";
	std::cout << array[2] << "\n";
	std::cout << array[3] << "\n";

	//---------------------------------------------------------------------

	// REFERENCIAK

	// Valtozoval
	int v = 10;
	int& v_nonconst_ref = v;    // OK, int-re hivatkozhat int&
	v_nonconst_ref += 10;       // OK, hivatkozott valtozot modositjuk
	const int& v_const_ref = v; // OK, int-re hivatkozhatunk const int&-vel (read-only ref)
	//v_const_ref += 10;          // hiba, const referencian keresztul nem modosithatunk!

	// Konstanssal
	const int c = 20;
	//int& c_nonconst_ref = c;    // hiba, const int-re nem hivatkozhat int&, csak const int&
	const int& c_const_ref = c; // OK, const int-re hivatkozhat const int&
	//c_const_ref += 10;          // hiba, const referencian keresztul nem modosithatunk!

	//---------------------------------------------------------------------

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
	std::cout << t[2] << "\n"; // inicializalatlan tomb -> memoria szemetek

	std::cout << gt[0] << "\n";
	std::cout << gt[1] << "\n"; // inicializalatlan, de globalis -> zero inicializalta az elemeket
	std::cout << gt[2] << "\n"; // (hiszen static memory beallitasanak nincs futasi ideju koltsege)

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

	//---------------------------------------------------------------------

	// DINAMIKUS TOMBOK

	// De ha ford idoben ismertnek kell lennie az elemszamnak, akkor hogyan
	// tudok pl. valamilyen input-tol fuggo meretu tombot letrehozni?
	int size;
	std::cin >> size;
	int t3[size]; // NEM STANDARD, lasd: forditas -pedantic kapcsoloval
	              // par fordito lehet, hogy tamogatja (pl. g++), de ez nem garantalt!

	const int size2 = 42;
	int t4[size2]; // a size2 itt egy un. forditasi ideju konstans, OK, ford. idoben ismert a meret

	// De akkor hogyan lehet standard C++-ban user input meretu tombot?

	// Valasz: dinamikus tombbel
	int dynSize;
	std::cout << "Kerem a meretet: ";
	std::cin >> dynSize;
	int * dynt = new int[dynSize]; // ez mar OK, heap-re (dynamic memory-ba) kerul
	// a new operator allokal dynSize * sizeof(int) bajtot a heap-en es
	// konstrual dynSize db int objektumot, majd a kezdo elem kezdo bajtjanak cimevel
	// ter vissza -> int* tipussal ter vissza, amit ertekul adok egy pointernek
	// igy a pointeren keresztul elerem es ugyanugy hasznalhatom, mint a statikus tomboket...

	std::cout << "dynt sizeof: " << sizeof(dynt) << "\n"; // miert mindig 8?
	// A sizeof egy un. forditasi ideju operator, statikus meretet ad vissza
	// Nem is lehetne barmit feltetelezni a dynt pointer-rol, hiszen az futasi
	// idoben derulhet ki, hogy mire mutat, csak egy memoria cim van benne,
	// nincs interpreter kornyezet, ami barmit szamon tartana rola! (hatekonysag ellen menne)
	// Pl. nem tudhatjuk elore, hogy a dynt milyen cimet fog tarolni:
	// if (...)
	// 	dynt = nullptr;
	// else if (...)
	// 	dynt = &x;
	// else
	// 	dynt = new int[...]
	//
	std::cout << dynt[0] << "\n";
	std::cout << dynt[1] << "\n"; // ezek a sorok nyilvan akkor lesznek biztonsagosak,
	std::cout << dynt[2] << "\n"; // ha a beolvasott dynSize >=3

	// Celszerubb igy:
	for (int i=0; i<dynSize; ++i)
		std::cout << dynt[i] << "\n";

	delete[] dynt; // Ez kell, hogy felszabaditsuk a heap-re allokalt tombot
	// hiszen a main fuggveny lefutasa vegen csak a dynt (int* pointer),
	// mint lokalis valtozo lesz torolve a stack memory-bol, az nem amire o a heap-en
	// mutat
	// Nem is lehetne feltetelezni, hogy o mutat-e egy ertelmes, meg fel nem szabaditott
	// tarteruletre a fentebbi gondolatmenet miatt (futasi idoben dolhet el, ill megvaltozhat,
	// hogy mire mutat). Ha megis meg szeretnenk jegyezni, hogy o mutat-e valamire
	// (pl. tombre), akkor az plusz memoria + CPU igeny lenne, ami ellenmegy a C++
	// filozofianak! Tehat errol nekunk kell gondoskodni.

	//---------------------------------------------------------------------

	// VIZUALIZACIO

	// int   x = 42;
	// int * p = &x;
	//
	// Ertek          42   220.
	//      ---------------------------------------->
	//      |    |    x     p   |
	// Cim  0   143. 220.      856.              8GB

	// int t[3];
	//
	//      | Folyamatunknak fenntartott memory |
	// ------------------------------------------------------->
	//      |     |o|o|o|        ^              |    ^
	//           t t+1 t+2      t+20              t+80000
	// Deref eseten:       pl.mem szemet         pl.segfault
	//                     (ez a ketto undefined behavior)

	//---------------------------------------------------------------------

	// STRUCT, GEPI SZO, PADDING

	struct Test {
		int x;  // sizeof impl. fuggo, most 4 byte
		int y;  // 4 byte
		char c; // 1 byte
	}; // osszesen 9?
	// Memoriaban rendre fognak szerepelni az adattagok egymast kovetoen

	Test test;
	std::cout << "char: " << sizeof(char) << "\n";
	std::cout << "int:  " << sizeof(int)  << "\n";
	std::cout << "Test: " << sizeof(Test) << "\n"; // minden tipusnak ismert a merete ford. idejen!
	std::cout << "test: " << sizeof(test) << "\n"; // ugyanaz, objektummal is jo

	// sizeof(Test) miert 12? Padding-gel ki lett toltve, hogy a gepi szo tobbszorose legyen:
	//
	// --------------------------->
	//    | x  | y  |c|   |
	//                 ^padding
}

