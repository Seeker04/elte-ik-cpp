#include <iostream>

// Az Array egy egyszeru dinamikus tombot tarolo osztaly, mely a ktor-ban kapja
// meg a tomb kivant meretet. Az elemek lekerdezesehez/felulirasahoz a get es a set,
// meret lekerdezeshez pedig a size tagfv-eket hasznalja
// Sablonosztaly, igy tetszoleges tipusu lehet a tarolt elemtipus

template <typename T>
class Array {
private:
	int _size;
	T * _a;
public:
	Array(int size) :
		_size(size),
		_a(new T[_size])
	{}

	~Array()
	{
		delete[] _a;
	}

	void set(int index, T value)
	{
		_a[index] = value;
	}

	T get(int index) const
	{
		return _a[index];
	}

	int size() const { return _size; }
};


// Mi van a T=bool esettel?
//
// A sizeof(bool) az legalabb 1 byte-nak kell hogy legyen...
// Hatekony-e igy, hogy 1 igaz/hamis ertek 1 egesz byte-on van tarolva?
// 00000000 - false
// 00000001 - true
// Valasz: nem
// Pl. tarolni akarok 5 bool erteket: [true, true, false, true, false]
// bajtonkent: 00000001|00000001|00000000|00000001|00000000
//                    ^        ^        ^        ^        ^
// bitenkent:  00001011
//                ^^^^^
// Sokkal hatekonyabb bitenkent, hiszen ugy 8n igaz/hamis ertek kodolasahoz eleg n bajt,
// azaz nyolcad annyi memoria
//
// Specializaljuk a sablon osztalyunkat a T=bool esetre!


template <>
class Array<bool> {
private:
	int _size;
	char * _a; // byte tomb, mert sizeof(char)==1 => 8 bit => 8 igaz/hamis
	           // ertek tarolhato egy tombelemen
public:
	Array(int size) :
		_size(size),
		_a(new char[(_size / 8) + (_size % 8 ? 1 : 0)]) // lenyegeben ceiling(size/8) bajt kell
	{}

	~Array()
	{
		delete[] _a;
	}

	// index/8 megmondja, hogy hanyadik bajton van az indexedik elem
	// index%8 megmondja, hogy a bajton belul hanyadik biten van

	void set(int index, bool value)
	{
		// Ha a beallitando ertek true, akkor 1-re allitom a megfelelo bajt megfelelo bitjet
		if (value)
			_a[index / 8] |= (1 << (index % 8));
			// 00000001 == 1        | pl ha index%8==3, akkor:
			// 00001000 == (1 << 3) | 3-mal lettek balra shift-elve a bitek
			// Ha ^ezt bitenkent hozzavagyolom a megfelelo bajthoz (|= operator), akkor
			// a megfelelo (itt pl harmadik) bit 1 lesz barmi is volt (1-gyel vagyolas)
			// az osszes tobbi marad, ami volt (0-val vagyolas)

		// Ha a beallitando ertek false, akkor 0-ra allitom a megfelelo bajt megfelelo bitjet
		else
			_a[index / 8] &= ~(1 << (index % 8));
			// 00000001 == 1         | pl ha index%8==5, akkor:
			// 00100000 == (1 << 5)  | 5-tel lettek balra shift-elve a bitek
			// 11011111 == ~(1 << 5) | komplementer vetel ~ operatorral ("bit flipping")
			// Ha ^ezt bitenkent hozzaesselem a megfelelo bajthoz (&= operator), akkor
			// a megfelelo (itt pl otodik) bit 0 lesz barmi is volt (0-val esseles)
			// az osszes tobbi marad, ami volt (1-gyel esseles)
	}

	bool get(int index) const
	{
		return _a[index / 8] & (1 << (index % 8));
		// 00000001 == 1        | pl ha index%8==3, akkor:
		// 00001000 == (1 << 3) | 3-mal lettek balra shift-elve a bitek
		// A kerdeses index/8. bajt tetszoleges bitekkel: abcdefgh
		// Bitenkent esseles:
		// abcdefgh
		//&00001000
		// 0000e000 <-- ha az e. bit 0 volt, =0 lesz az osszeredmeny
		//              ha ez e. bit 1 volt, >0 lesz az osszeredmeny
		// => Ez pontosan azzal fog visszaterni, hogy 1-re van-e allitva
		// a megfelelo bit, mely az indexedik logikai erteket reprezentalja
	}

	int size() const { return _size; }
};


int main()
{
	Array<int> testArray1(10);

	// Feltoltes
	for (int i=0; i<testArray1.size(); ++i)
		testArray1.set(i, (i<5 ? 42 : 128));

	// Lekerdezes
	for (int i=0; i<testArray1.size(); ++i)
		std::cout << testArray1.get(i) << "\n";

	//---------------------------------------------------------------------

	Array<bool> testArray2(10);
	// Ugyanugy hasznalom, mint tetszoleges T tipussal, de mivel erre lett
	// irva specializacio, igy annak a kodja lesz hasznalva ehhez az Array<bool> tipushoz
	// Kivulrol igy a hasznalonak nem is latszik, hogy ez alatt mas reprezentacio
	// (adatok + algoritmusok) vannak, ez el van absztraktalva
	// Visszaellenorizni, hogy valoban a masodik reprezentacio van-e hasznalatban
	// a testArray2-nel peldaul debuggerrel lehet (pl. gdb)

	// Feltoltes
	for (int i=0; i<testArray2.size(); ++i)
		testArray2.set(i, (i%2 ? true : false));

	// Lekerdezes
	for (int i=0; i<testArray2.size(); ++i)
		std::cout << testArray2.get(i) << "\n";

	// Megjegyzes: az std::vector<bool> is egy specializacio, mely alatt bitset-ek vannak
	// lasd: 
	// https://www.cplusplus.com/reference/vector/vector/
	// https://www.cplusplus.com/reference/vector/vector-bool/
}

