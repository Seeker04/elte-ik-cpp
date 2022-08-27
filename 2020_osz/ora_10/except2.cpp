#include <iostream>

class SizeIsZero{};

int* create_array(int size)
{
	if (size==0)
		throw SizeIsZero();
	return new int[size];
}

class Example {
private:
	int s1, s2, s3; // meretek
	int * array1; // dinamikus tombok lesznek
	int * array2;
	int * array3;

public:
	Example(int s1, int s2, int s3) :
		array1(nullptr), // ezek az inicializalasok fontosak lesznek
		array2(nullptr), // kesobb, hogy kovetheto legyen, mely din. tomb(ok)
		array3(nullptr)  // lett(ek) letrehozva es mely(ek) nem
	{
		this->s1 = s1; // megj.: az s1,s2,s3 lokalis parameterek learnyekoljak
		this->s2 = s2; // az adattagok neveit, de a this-> explicit kiirasat
		this->s3 = s3; // felhasznalva ez nem okoz gondot
		try {
			array1 = create_array(s1);
			array2 = create_array(s2);
			array3 = create_array(s3);
			// ^Barmelyik create_array hivas dobhat SizeIsZero kivetelt!
		}
		catch (const SizeIsZero& e) {
			// Ha pl. a masodik create_array hivas dobott kivetelt,
			// akkor is fel tudom szabaditani a mar leallokalt din. tombot,
			// amire array1 mutat
			if (array1 != nullptr) { delete[] array1; array1 = nullptr; }
			if (array2 != nullptr) { delete[] array2; array2 = nullptr; }
			if (array3 != nullptr) { delete[] array3; array2 = nullptr; }
			// Az is fontos, hogy amin hivtam delete/delete[] operatort,
			// azt celszeru nullptr-re allitani, hiszen ebben a peldaban
			// a dtor is megprobalna torolni, ha nem nullptr
			// A double delete pedig undefined behavior! (segfault-hoz vezet)
		}
	}

	~Example()
	{
		// A felszabaditasokat eleg (de legkesobb ekkor kell!) megtenni itt
		// Ha ezt igy megtesszuk a dtor-ban, akkor a ktor-bol ki is lehetne
		// venni a felszabaditos reszeket, ha nem celunk ott az osszeset
		// mar akkor felszabaditani...
		if (array1) delete[] array1;
		if (array2) delete[] array2;
		if (array3) delete[] array3;
		// eml.: a pointer tipusok tudnak implicit bool-ra konvertalodni:
		// ha 0/NULL/nullptr, akkor false, minden mas esetben true lesz
	}
};

int main()
{
	Example ex(10, 0, 30);
}

	// Fontos tanulsag: mivel kivetel eseten a konstruktor nem fut le
	// vegig, ezert tekinthetjuk az objektumot "reszben megkonstrualtnak"
	// es ezzel vigyazni kell! Megtortenhet, ha a ktor torzseben barmi
	// olyan fv-t hivunk, ami dobhat (vagy kaphat mas fv hivastol) kivetelt
	// A peldaban lathato modon, pl. elofordulhat, hogy vannak olyan pointer
	// adattagok, melyek mar mutatnak allokalt memoria teruletre, vannak
	// olyanok, amik pedig nem. Ezert celszeru lehet (legkesobb) a dtor-ban
	// figyelni, hogy egyaltalan mutat-e valamire az ilyen adattag...
	// Illetve sok esetben nem is szeretnenk hasznalni ilyen "reszben megkonstrualt"
	// objektumokat, igy ez detektalhato, lehet ra dobni kivetelt, stb...
	//
	// Szinten fontos: bar "reszben megkonstrualtnak" neveztem, de lathattuk,
	// hogy annak ellenere, hogy nem futott le vegig a ktor, az objektum
	// megis rendesen memoriaba kerult es letrejott, majd a destruktora is lefutott kesobb
	// Miert?
	// Az objektum letrehozasa vazlatosan igy tortenik:
	// - sizeof(T) byte allokalasa memoriaba
	// - adattagok konstrualasa deklaraciojuk "fontrol lefele" sorrendjeben:
	//     * ha az adattag szerepel az init listaban, akkor a megfelelo ktor-ral
	//     * ha nem, akkor default konstrualassal (= param nelkuli ktor hivasa, ha van)
	// > ezen a ponton mar rendesen, inicializalva szerepel az objektum a memoriaban
	// - konstruktor torzs futtatasa a letrehozott objektumon, ekkor mar
	//   teljesen valid a this altal mutatott hivo objektum
	//
	// Ezert is veszelyes az ilyen, hogy potencialisan nem fut vegig a ktor
	// egy kivetel miatt, mert nehezen megtalalhato hibakhoz vezethet, ha
	// azt feltetelezzuk, hogy mindig vegig lefut!
	// Ezert sem annyira celszeru tul hosszura es komplikaltra (sok fv hivassal)
	// megirni a ktor-okat, mert oda kell figyelni ezekre!
	//
	// Masik pelda: van egy fajlt kezelo osztalyunk, ami a ktor-ban megnyit
	// egy file deszkriptort (pl. fopen()-nel), a dtor-ban pedig lezarja azt
	// (pl. fclose()-zal). Ha a ktor valamiert elhasalt egy kivetel miatt meg
	// az elott, hogy a FILE * f adattag ramutatott az fopen() altal visszaadott
	// cimre, akkor kesobb se hasznalni nem tudom rendesen, illetve
	// legkesobb a dtor-ban, de el fog hasalni a program is, ha fclose()-t
	// probal hivni egy cimen, amin nem kene...

