<!--
MIT License
Copyright (c) 2019-2022 Barnabás Zahorán, see LICENSE
-->

# Fogalomtár a Programozási nyelvek C++ tantárgyhoz

A fogalomtár célja, hogy segítse a felkészülést a vizsga elméleti és programozás
részére egyaránt, a fontosabb fogalmak felsorolásával.
Csak a nyelv alapfogalmait, melyeket ismerni kell, tartalmazza (C++98-as szabványig).
Nem tartalmazza például a modernebb nyelvi feature-öket (auto kulcsszavat,
smart pointer típusokat, range based for loop-ot, lambdákat, stb).

Készítette: Zahorán Barnabás

Hiányosságot, hibákat, elírásokat, észrevételeket issue formájában vagy a következő email címen lehet jelezni:<br>
zahoranb [at] protonmail [dot] com

[Fogalmak felsorolása](fogalomtar.md)

----

# Alapfogalmak

## Deklaráció<a id='deklaracio'></a>

Névhez (azonosítóhoz) típust rendelünk.

Azonosító legalább egy hosszú szó, melyben lehetnek kisbetűk, nagybetűk, számok, aláhúzásjelek és nem kezdődhet számmal, valamint nem ütközhet lefoglalt kulcsszóval.

A nyelv case-sensitive: `x` és `X` nem ugyanaz az azonosító!

Egy entitást akárhányszor deklarálhatunk.

Példák:
```C++
int x;     // változó
void f();  // függvény, típusa: void()
class C;   // típus
```

## Definíció<a id='definicio'></a>

Egy entitás (változó/konstans/függvény/típus) teljes "jelentését" megadjuk.

Változók és konstansok a definíció miatt fognak memóriába kerülni (inicializált vagy inicializálatlan kezdeti értékekkel).

Függvények definíciója a törzsük megadása.

Típus definíció pl. osztályok esetén a teljes osztálytörzs megadása.

Megjegyzés: Deklaráció és definíció történhet egyszerre.

Példák:
```C++
int x;                               // változó
void f() { std::cout << "hello"; };  // függvény
class C { int x; int y; };           // típus
```

## Fordítási egység (translation unit)<a id='forditasiegyseg'></a>

A fordító által egy egységként tekintett kód. Gyakorlatban egy forrásfájl (pl. .cpp vagy .cxx kiterjesztéssel), az összes
include-olt fejállománnyal kibővítve.

A fordító ebből fog tudni tárgykódot generálni.

## One Definition Rule (ODR)<a id='odr'></a>

Egy entitást (változó/konstans/függvény/típus) csak egyszer definiálhatunk!

Ha például két külön fordítási egységben van ugyanolyan nevű változó definiálva, akkor linkeléskor fogunk hibát kapni.

## static kulcsszó (globális változóknál és függvényeknél)<a id='static'></a>

Globális változó/függvény láthatóságát korlátozza le a tartalmazó fordítási egységre.

Ha `static`-ok, akkor lehet két ugyanolyan nevű változó/függvény két külön fordítási egységben, nem lesz linkeléskor hiba, mindkettő a sajátját fogja csak látni és használni.

## extern kulcsszó<a id='extern'></a>

Deklaráció esetén az `extern` kulcsszóval jelezhetjük a fordítónak, hogy a változó/függvény más fordítási egységben van definiálva,
"külső szerkesztésű".

Erre akkor van szükség, ha egy másik fordítási egységben definiált változót szeretnénk használni, hiszen annak is deklarált változónak kell lennie (kell típus bejelentés a típus ellenőrzéshez és a kódgeneráláshoz is).

Megjegyzés: a függvények elé nem kell kirni, mert azok implicit módon külső szerkesztésűként működnek.

## Típusrendszer<a id='tipusrendszer'></a>

Minden entitást az azonosítója mellett a típusa határoz meg.

Különböző típusú változókat nem adhatunk értékül egymásnak, hacsak nincs köztük implicit konverzió vagy nem használunk explicit módon kasztolást.

Megjegyzés: függvényeknek is van típusa, pl. az
```C++
int max(int x, int y) { return (x > y ? x : y); }
```
függvény típusa: `int(int,int)`

Lásd: függvény pointerek

## Statikusan típusos nyelv<a id='statikusantipusos'></a>

A C++ típusrendszere statikusan típusos. Ez azt jelenti, hogy minden típusnak fordítási időben (más szóval: statikus időben) ismertnek kell lennie. (Ebből adódóan a változók mérete is ismert ekkor, vagyis, hogy hány bájton lesznek tárolva).

Ellenpéldául szolgálnak a dinamikusan típusos nyelvek, például: Python, Ruby, JavaScript, stb. Ezeknél változók típusai sokszor
csak futási (vagy más szóval: dinamikus) időben dőlnek el.

Python kód:
```Python
x = input()    # x egy beolvasott string lesz
if int(x) < 5: # ha x nem csak számjegyekből áll, konverziós hiba lesz
    x = 42     # innentől kezdve x típusa int lesz
else:
    x = False  # innentől kezdve x típusa bool lesz
print(x)
```

Figyeljük meg, hogy Python esetén az `x`-et nem is kellett deklarálni (nincs típus bejelentés), illetve futási időben dől el és változik, hogy éppen mi a típusa (ekkor a típusinformációt is tárolnia és frissítenie kell memóriában az interpreternek -> nem hatékony, valamint típushibák merülhetnek fel futási időben).

# Névterek

## namespace kulcsszó<a id='namespace'></a>

Névprefixszel láthatjuk el entitásainkat. Ezzel névütközéseket kerülhetünk el és logikailag jobban csoportosíthatjuk változóinkat, konstansainkat, függvényeinket és típusainkat.

Figyelem: a névtér az nem egy önálló entitás, a namespace-nek nincs deklarációja/definíciója! Tetszőleges fordítási egységben a kód tetszőleges pontján írhatunk bele dolgokat tetszőleges névtérbe, hiszen csak annyit jelent, hogy minden benne deklarált/definiált entitás kap egy névprefixet.

## névterek egymásba ágyazása (A::B::C)<a id='nevterekegymasba'></a>

Névtereket tetszőleges mélységig egymásba lehet ágyazni, ezzel egy hierarchiát kialakítva:

```C++
int x = 20;
namespace A {
	int x = 10;
	namespace B {
		int x = -5;
		namespace C {
			int x = 42;
		}
	}
}
...
std::cout << A::B::x; // -5
```

Így maguk a névprefixek között is elkerülhetőek névütközések, pl. lehet egy `xml::parser::run()` és egy `json::parser::run()` nevű függvényem is névütközés nélkül.

## ::x jelentése<a id='globalisnev'></a>

A globális scope `x` szimbólumát (változót/függvényt/típust) így hivatkozhatjuk meg névtéren belülről.
```C++
int x = 10;
namespace A { int x = ::x; }
```

## using namespace<a id='usingnamespace'></a>

Névprefix feloldását végezhetjük el vele:

```C++
namespace A { int x = 3; }
...
using namespace A;
std::cout << x; // 3
```
Vigyázat: Névütközésekhez vezethet! A standard könyvtár névterét `std::` ezért - és az explicitás miatt - nem is ajánlott feloldani!

Ha egy blokkon belül írjuk, akkor csak azon blokkban lesz hatása, például, ha csak a függvényünkben szeretnénk:

```C++
void f()
{
	using namespace std;
	...
}
// <- innentől már nincs hatása
```

## Névtelen névtér<a id='nevtelennevter'></a>

Minden benne deklarált entitás a fordítási egységben globális scope szerint lesz látható, viszont más fordítási egység elől rejtett lesz. (Olyan, mintha e helyett minden elé `static`-ot írtunk volna).

Szintaxis:
```C++
namespace { int x; void f(); }
```

Megjegyzés: ez a static-nál annyival többet tud, hogy ebbe lehet típus definíciókat is írni.
(Ilyeneket nem lehet: `static class {...`, `static enum {...`)

# Fordítás, futtatás

## Forrás fájl (source file)<a id='forrasfajl'></a>

C esetén .c, C++ esetén általában .cpp vagy .cxx kiterjesztésű fájl.

A fordítónak parancssori argumentumként adjuk át.

Egy fordítási egység kódját tartalmazza, esetleg include-okkal kiegészülve.

## Fejállomány (header file)<a id='fejallomany'></a>

Általában .h (vagy C++ esetén sokszor .hpp) kiterjesztésű fájl.

Legtöbbször csak deklarációkat, típus definíciókat tartalmaznak.

Rendeltetésük, hogy az `#include` direktívával bemásoljuk tartalmukat forrásfájlok elejére.

## Szabványok<a id='szabvanyok'></a>

Az ISO C++ különböző ún. szabványokkal írja elő a nyelv szintaxisát és szemantikáját, így a hozzá készített fordítók elvárt működését is.

Standardok: C++98, C++03, C++11, C++14, C++17, C++20, C++23 (tervezett)

## Fordító<a id='fordito'></a>

A használt C++ szabvány által előírt lexikális (tokenek), szintaktikus (helyes mondatformák) és szemantikus (program jelentés) szabályoknak megfelelő kódokból (forrásfájlok és fejállományok tartalmai) generál először tárgykódokat, majd ezeket összeszerkesztve (linkelés) futtatható bináris állományt a cél architektúrára (ez általában egyezik a platformmal, amin fordítunk).
## Fordítás parancssorból<a id='forditasparancssorbol'></a>

Elterjedt fordítók: g++, clang++, msvc++

Tárgykód előállítása:
```bash
$ g++ -c a.cpp # -> a.o
```

Tárgykódok összelinkelése:
```bash
$ g++ a.o b.o c.o # -> a.out/a.exe
```

Teljes build:
```bash
$ g++ a.cpp b.cpp c.cpp # ez így mindkét lépést megcsinálja
```

Megjegyzés: egy-két fájlnál nagyobb projekteknél már érdemes lehet [Makefile](https://www.gnu.org/software/make/)-t használni.

## Fordítási flag-ek<a id='forditasiflagek'></a>

A fordítónak speciális parancssori argumentumokként különböző beállításokat adhatunk meg:

`-std=` kapcsolóval a használandó szabványt állíthatjuk be, például:
```bash
$ g++ -std=c++11 a.cpp # fordítás a 2011-es standard szerint
```

`-o` az output (bináris vagy -c esetén tárgykód) nevét állítja be, például:
```bash
$ g++ -o MyProgram a.cpp
```

A warning flag-ek különböző figyelmeztetéseket kapcsolnak be: `-W`, `-Wall`, `-Wextra`, `-Wshadow`, `-Wconversion`, `-pedantic`, stb.

`-O` kapcsolókkal a kódoptimalizálás szintjét állíthatjuk be: `-O1`, `-O2`, `-O3`, `-Os`

`-g` kapcsoló debug szimbólumok generálását kapcsolja be.<br>
Tipp: a maximális debug élményért, ha gdb-vel szeretnénk debuggolni:<br>
`-Og -g3 -ggdb -fno-inline -fno-eliminate-unused-debug-symbols`

Megjegyzés: Részletekért, további infókért: `$ man g++`

## Fordítási hiba (error)<a id='hiba'></a>

A kódban található lexikális, szintaktikus és szemantikus hibák (amik a szabványnak ellent mondanak) váltják ki.

A fordító szövegesen jelzi a hiba okát és terminál kódgenerálás nélkül.

Megjegyzés: A `-Werror` kapcsolóval megmondhatjuk a fordítónak, hogy a figyelmeztetéseket is hibának kezelje.

## Fordítási figyelmeztetés (warning)<a id='figyelmeztetes'></a>

A kódban található nem súlyos hibákat, problémás kódrészeket figyelmeztetések formájában jelzi a fordító, de a tárgykódot le fogja generálni.

Sok esetben a nem definiált vagy nem specifikált viselkedést okozó kódra kapunk figyelmeztetést.

## Preprocesszor<a id='preprocesszor'></a>

A fordítás kezdetekkor az ún. preprocesszort futtatja a fordító. Ez a C++ nyelv szemantikáján kívül eső eszköz primitív (nyers)
szövegbeillesztéseket végez a kódon.

```
              _______________                             _____________
Forráskód -> | preprocesszor | -> előfeldolgozott kód -> | C++ fordító | -> tárgykód
              ---------------                             -------------
```

Tipp: Ha szeretnénk látni az előfeldolgozott kódot, használjuk a g++ `-E` kapcsolóját.

## Preprocesszor direktíva<a id='preprocesszordirektiva'></a>

A kódban `#` karakterrel kezdődő sorokkal tudunk a preprocesszornak utasításokat megadni.

Néhány példa: `#include`, `#define`, `#undef`, `#if`, `#ifdef`, stb.

Segítségével feltételes fordítást tudunk megvalósítani, pl.

```C++
#include <sys/stat.h>
#if defined(_WIN32) || defined(_WIN64)
	#include <direct.h> // _mkdir() ebben van Windows-on
#endif
...
int error = 0;
#if defined(_WIN32) || defined(_WIN64)
	error = _mkdir("testdir"); // Windows-on nincs POSIX mkdir(), ez van helyette
#else
	error = mkdir("testdir", S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
#endif
```

Megjegyzés: portabilis kód íráshoz szintén hasznos lehet:
```C++
$ man feature_test_macros
```

Megjegyzés: standard header-ekben szintén rengeteg preprocesszor feltételre lehet példát találni<br>
Pl. `#if __cplusplus >= 201703L` azt ellenőrzi, hogy a 2017-es vagy újabb standard van-e használatban.<br>
Linux-on az /usr/include/c++/<verzió>/ könyvtárban szoktak lenni.

## #include<a id='include'></a>

Ezzel a preprocesszor direktívával tudunk más fájlok tartalmait bemásoltatni a kódunk megfelelő pontjaira.

Tipikusan fejállományokat szoktunk include-olni.

Tranzitív: Ha A include-olja B-t, B pedig C-t, akkor A-ban benne lesz C tartalma is.

## Include guard<a id='includeguard'></a>

Ugyanannak a kódnak a többszörös include-olását (tranzitivitás miatt lehet például) védjük ki vele. Nem akarunk névütközéseket és ODR-t sérteni.

Fájl elejére:
```C++
#ifndef EGYEDI_SZIMBOLUM
#define EGYEDI_SZIMBOLUM
```
Fájl végére:
```C++
#endif // EGYEDI_SZIMBOLUM
```

## Makró<a id='makro'></a>

A preprocesszor `#define` direktívájával tudunk makrókat definiálni. A preprocesszor a kódban a makrószimbólum összes előfordulását le fogja cserélni a megadott szöveggel.

Például:

```C++
#define BUFFER_SIZE 128
char text[BUFFER_SIZE];
```

Megjegyzés: Amikor csak lehet, kerüljük használatukat, mert teljesen a C++ szemantikáján kívül esnek, nem típusozottak, nehezen debuggolhatóak, stb.

## Paraméteres makró<a id='parameteresmakro'></a>

Makróknak paramétereket is adhatunk.
Például:
```C++
#define ABS(X) ((X)<0 ? -1*(X) : (X))
#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))
...
ABS(-5);   // -> ((-5)<0 ? -1*(-5) : (-5));
MIN(4, 2); // -> ((4) < (2) ? (4) : (2));
```

Megjegyzés: ezek használatát méginkább érdemes kerülni! C++-ban az inline függvények, template-ek, lambdák, stb. nyelvi elemek mellett már egyébként sem adnak hasznot...

Gondoljunk csak bele, mi történne, ha egy mellékhatásos kódot: `f()` vagy `++x` írnánk be pl. a `MIN` paraméteres makrónkba... kétszer futna le a mellékhatás!

## Tárgykód<a id='targykod'></a>

A fordító fordítási egységből (ha hibamentes volt a fordítás) állítja elő a tárgykódot (objectfile). Kiterjesztése általában .o szokott lenni.

Ez már a lefordított gépi kód, mely tartalmazza még a linkeléshez szükséges szimbólumneveket (változók, függvények, stb).

Több programmal is meg lehet tekinteni ezeket a szimbólumneveket, például:
```Bash
$ objdump -t main.o  # .so (shared object) esetén -T kapcsolóval futtassuk
$ nm main.o
```

## Összeszerkesztés (linkelés)<a id='linkeles'></a>

A linker a kapott tárgykódokat felhasználva szerkeszti össze őket egy futtatható bináris állománnyá. Összeszerkesztéskor is történhet még hiba, például:
* két külön fordítási egység ugyanolyan nevű globális változót definiál
* egy `extern int x;`-ként deklarált, "beígért", változó egy fordítási egységben sincsen definiálva.

Megjegyzés: A fordító általában magától futtatja a linker-t is, hacsak nem mondjuk meg neki, hogy ne tegye (lásd: `-c` kapcsoló).

A GNU linker az `ld` nevű program, lásd: `$ man ld`.

## Futtatható bináris<a id='binaris'></a>

A sikeres összeszerkesztés végeztével kapjuk. Gépi kód, processzor utasításokat tartalmaz. A cél architektúrán futtathatjuk.

Megjegyzés: POSIX rendszereken ebből is sok információ kinyerhető pl. a `file` paranccsal:
```Bash
$ file a.out
a.out: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=b48378054fa50feeb119a9feb1bdf010a5660ff8, for GNU/Linux 4.4.0, with debug_info, not stripped
```

## main függvény<a id='main'></a>

Minden C és C++ program belépési pontjának egy `main` nevű függvénynek kell lennie (hiánya esetén fordítási hibát kapunk). Szignatúrája kétféle lehet:
```C++
int main();
int main(int argc, char * const argv[]);
```

## Parancssori argumentumok<a id='argumentumok'></a>

Parancssori argumentumokat a futtató szülő környezetből (pl. shell-ből) adhatunk át a programunknak. Az átadott paraméterek számát a szülő a `main()` függvény `argc` paraméterébe, magukat a argumentumokat pedig az `argv`-be fogja beleírni (az `argv` karaktertömbök tömbje, tehát lényegében szövegek listája).

## Hibakód<a id='hibakod'></a>

A `main()` függvény visszatérésével (`int`-et ad vissza) jelezhetjük a szülőnek (pl. shell) a futás sikerességét. Konvenció szerint a 0 jelzi a sikeres, egyéb értékek pedig a sikertelen futást. Az egyéb értékek különböző jelentéssel bíró hibakódok lehetnek.

Megjegyzés: shell-ben a következő módon kérhetjük le a futtatott program hibakódját:
```Bash
$ echo $?
```

Megjegyzés: Az újabb C és C++ szabványok már megengedik a `main()` függvényből elhagyni a `return` utasítást. Ekkor a fordítónak a dolga, hogy a `return 0;` sort a függvénytörzs végére írja.

## Futási hiba<a id='futasihiba'></a>

A sikeresen lefordított és összeszerkesztett program futása során is kaphatunk hibát. Ezt futási (vagy dinamikus) idejű hibának nevezzük.

A hiba lehet várt: lekezelt kivétel, vagy nem várt: kezeletlen kivétel, 0-val osztás, szegmentációs hiba, stb.

## Szegmentációs hiba<a id='szegmentacioshiba'></a>

Memóriakezeléssel kapcsolatos hibák esetén a futásunk a `Segmentation fault (core dumped)` szövegű hiba kiírásával és hibakód adásával terminál.

Okozója lehet például: null pointer dereferálása, tömbből való kiindexelés, nem elérhető memóriacím olvasása, double free/delete, stb.

Lásd: `SIGSEGV` szignál.

# Program viselkedés

## Nem definiált viselkedés<a id='undef'></a>

Olyan leforduló kód, melyről a szabvány nem mond semmit, így "bármi" történhet (fordítóra van bízva, hogy mit generál belőle).

Sokszor futási idejű hibához vezet (pl. szegmentációs hibához), máskor kevésbé súlyos, de mégis nemdeterminisztikus viselkedést idézhet elő, vagy akár olyan viselkedést, ami más-más rendszeren csinál más-mást.

Példák: kiindexelés, túlcsordulás, alulcsordulás, nullával való osztás, kétszer delete-elni egy objektumot,...

## Nem specifikált viselkedés<a id='unspec'></a>

Olyan kódviselkedés, melyet a standard nem ír elő pontosan, de tesz rá megszorításokat, szabályokat, esetleg felsorol lehetséges alternatívákat, hogy minek kell történnie. Nem annyira veszélyesek, mint a nem definiált viselkedés, de ezek is kerülendők, amennyire csak lehet!

Példák:

Függvény paraméterek kiértékelésének sorrendje: `f(g(), h());` esetén a `g()` és a `h()` függvények lefutásának sorrendje tetszőleges lehet (2 alternatíva).

Hasonló az eset a bináris operátorokkal is, ezért is nemdeterminisztikus a következő kód kimenete:
```C++
int x = 0; std::cout << ++x << ++x; // lehet "1 2" vagy "2 1"
```

Megjegyzés: Láthatjuk, hogy a nem specifikált viselkedések is könnyen problémássá válhatnak, ha nem vigyázunk! Ha a fenti példában `g()` és `h()`-nak is van mellékhatása, akkor a szekvenciájuk változásával más-más program állapothoz juthatunk (pl. ha közös globális változókat olvasnak/írnak, vagy output-ot írnak...)

## Implementáció által definiált viselkedés<a id='impldef'></a>

Olyan nem specifikált viselkedés, mely az adott gép architektúrájától (pl. x86 architektúra: 32/64 bites) függ.
Ezeket a standard szabályainak és az adott rendszer (CPU/OS) dokumentációjának összevetésével tudjuk csak egyértelműen megismerni.

Például:
* `int`, `float`, `double`, stb. típusok méretei
* gépiszó és padding mérete
* endianness (little-endian/big-endian bit sorrend)

Tehát az `std::cout << sizeof(int);` kód kimenete implementáció-függő.

Megjegyzés: Vannak azért megkötések, amiket a standard tesz, például:<br>
`sizeof(char) <= sizeof(int)`-nek teljesülnie kell.

# Beépített típusok

## Karakter típus<a id='char'></a>

```C++
char  // az ASCII kódtáblának el kell férnie rajta, C++-ban fixen 1 bájt
```

## Egész típusok<a id='egesztipusok'></a>

```C++
short
int
long
long long
```

## Lebegőpontos típusok<a id='lebegopontostipusok'></a>

```C++
float
double
long double
```

## Logikai típus<a id='bool'></a>

```C++
bool  // C-ben nincs, értéke 0 vagy 1, a false és true literállal reprezentálva
```

## Integrális típus<a id='integralis'></a>

Azon típusok, melyek típusértékhalmazainak elemei diszkréten felsorolhatóak, azaz tetszőleges elemnek (implementációtól függetlenül) meg tudjuk mondani az ő rákövetkezőjét.

Például: `char`, `int`, `long`, `bool`, stb.

## Méret szabályok<a id='meretszabalyok'></a>

Bájtokban kifejezve:
```C++
sizeof(char)  == 1
sizeof(char)  <= sizeof(short)     // pl. 2
sizeof(short) <= sizeof(int)       // pl. 4
sizeof(int)   <= sizeof(long)      // pl. 8
sizeof(long)  <= sizeof(long long) // pl. 8
```

```C++
sizeof(float)                         // pl. 4
sizeof(float)  <= sizeof(double)      // pl. 8
sizeof(double) <= sizeof(long double) // pl. 16
```

Minden típushoz, aminek van `signed` és `unsigned` változata (a fentiek közül csak a `bool`-nak nincs), az előjeles és anélküli változatok mérete megegyezik (különbség csak, hogy az előjeles tárolja az előjel értéket is).

Megjegyzés: ha a kódunkban mindenképp szeretnénk fix méretű változókat használni (viszonylag ritkán lehet feltétlen szükséges, de megeshet pl. bináris/üzenet protokolloknál), akkor a C-s `<stdint.h>` header-t használhatjuk:

`int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`,...

Ez a header C++ standardon kívül esik, illetve csak annyit garantál, hogy az architektúránk által támogatott méretek lesznek benne, de a gyakorlatban ezek a típusok meglesznek mai gépeken...<br>
**Edit:** C++11 óta már bent van a standardban a header: [\<cstdint\>](https://cplusplus.com/reference/cstdint/)

## Konverziók<a id='konverziok'></a>

Az aritmetikai típusok között szabadon konvertálhatunk implicit módon is, de a következő két dologra figyelnünk kell:
* Ha egy nagyobb típusról kisebrre próbálunk konvertálni, akkor adatvesztés történhet, pl. `int` -> `short`. Fordított esetben nincs probléma.
* Ha egy lebegőpontos számot egészre próbálunk konvertálni, akkor adatvesztés történhet, pl. `double` -> `int` esetén a törtrész le
fog vágódni. Fordított esetben nincs probléma.

# Változók

## Deklarálása, definíciója, inicializálása<a id='valtozo'></a>

Deklarálás: `<type> <identifier>;` alakban, pl. `int x;`

Definíció: Legtöbbször deklarációkor történik, kivéve az `extern int x;` esetet.

Inicializáló: Kezdőértékkel látjuk el a változót, pl. `char c = 'k';` (ezt nem kötelező megtenni).

Megjegyzés: Ha nem inicializálunk egy változót kezdeti értékkel, akkor nem mindig garantált, hogy nullára lesz inicializálva, memória szemét is maradhat benne.

Tipikusan a statikus tárolású változók 0-ra lesznek inicializálva (zero initialization), az auto tárolású (stack-re kerülő) változók viszont nem. Modern C++-ban az inicializálás elég bonyolult szabályok mentén megy. [Itt egy leírás](https://en.cppreference.com/w/cpp/language/initialization) azoknak, akiket érdekelnek a részletek és nem félnek egy kicsit szárazabb olvasmánytól.

## Globális változó<a id='globalisvaltozo'></a>

Változók, melyek láthatósága globális. Ők a statikus tárterületen fognak elhelyezkedni és a program teljes futása alatt élni fognak.

Megjegyzés: Lehetőleg kerüljük használatukat. A modularitást és az adatelrejtés elvét sértik és nehezen átlátható/debuggolható, nem várt mellékhatásokhoz vezethetnek!

Megjegyzés: A globális konstansok sokkal kevésbé veszélyesek, hiszen csak olvasni lehet őket, írni nem.

## Balérték (lvalue)<a id='lvalue'></a>

Olyan változó, mely rendelkezik állandó memóriaterülettel, jól definiált élettartammal.

Ezért szerepelhet értékadás baloldalán is (ha nem `const`).

Megjegyzés: Nem-temporális konstans objektumok is balértékek, annak ellenére, hogy ők sem lehetnek értékadás baloldalán!

## Jobbérték (rvalue)<a id='rvalue'></a>

Olyan változó, mely nem rendelkezik állandó memóriaterülettel, ezért értékadásban csak a jobboldalon szerepelhet.

Ilyenek a temporális objektumok, mint például a literálok.

Például:
```C++
int f() { return 42; }
int x;

x = 10;  // OK
10 = x;  // hiba
f() = 5; // hiba
```

## Temporális objektum<a id='temporalis'></a>

Nem rendelkezik állandó memóriaterülettel, definiált élettartammal. Ilyenek például a literálok vagy a függvények visszatérési értékei.

Megjegyzés: Sok esetben csak regiszterben fognak ők élni.

## Literál<a id='literal'></a>

	Literál           Típusa
	================================
	'a', 'b', 'c'     char
	-5, 10, 42        int (signed)
	471U              int (unsigned)
	23984767329L      long
	5698746394853LL   long long
	3.14, .2, 13.     double
	1E6, 5E-1         double (10^6 és 5*10^-1 értékek)
	3.14F, .2F, 13.F  float
	3.14L, .2L, 13.L  long double
	"hello"           const char[6] (a fordító a '\0' karaktert a végére teszi)
	true, false       bool

Megjegyzés: Az `U` módosítót nem csak az `int` literálhoz, hanem bármely más szám literálhoz odaírhatjuk, pl. `3.14FU`

	Literál           Számrendszer
	================================
	-5, 10, 42        decimális
	052, 012, 07      oktális
	0x34A, 0xF089BC   hexadecimális
	0b101101, 0b110   bináris (C++14 óta)

Megjegyzés: A számrendszer jelzéseket és az `U`, `L`, `F`, `LL` módosítókat egyszerre is használhatjuk.

Megjegyzés: Az összes módosító betűt lehet kisbetűvel is írni: `u`, `l`, `ll`, `e`, `x`, `b`.

Megjegyzés: A karakter tömb végére azért teszi a fordító a speciális `'\0'` termináló karaktert, hogy ezzel jelezze a szöveg végét a memóriában. Ezért nem kell a karaktertömb-kezelő függvényeknek átadni a tömb méretét, pl. `printf("Hello!")`;

## Értékadás<a id='ertekadas'></a>

Csak nem-konstans balértékeknek adhatunk értéket, melyek már definiált változók, például: `int x = 10;`

## Konstans<a id='konstans'></a>

A `const` kulcsszóval deklarált változók read-only-k lesznek, nem kaphatnak új értéket (azaz nem változhat meg a reprezentáló bitek egyike sem), pl. `const int x = 42;`

Konstansra csak const pointer mutathat rá és csak const referencia hivatkozhat (mert csak ezek garantálják, hogy rajtuk keresztül sem fog megváltozni az érték).

A konstansokat kötelező inicializálni (csak úgy van értelmük)!

## Láthatóság<a id='lathatosag'></a>

Entitások (változók/konstansok/függvények/típusok) láthatósága különbőzőek lehetnek.

Globális nem-statikus entitások mindenhol látszódnak, ahol nincsenek leárnyékolva.

Globális statikus és névtelen névtérben deklarált entitások csak a saját fordítási egységükben lesznek láthatóak.

Függvények paraméterei és egyéb lokális változói csak a függvény törzsben láthatóak, és egyéb kód blokkban deklarált entitások is
csak az adott blokkban láthatóak.

## Láthatóság leárnyékolása<a id='learnyekolas'></a>

Ha egy lokális deklarációban egy változó neve megegyezik egy külső névvel, akkor a lokális blokkban csak az új fog látszódni. Azt mondjuk, a külső név le van ekkor árnyékolva.

Például:
```C++
int x = 5;
if (1) {
	int x = 10;
	std::cout << x; // output: 10
} // ebben az elágazás blokkban a külső x nem látszódik
```

Megjegyzés: A `-Wshadow` fordítási kapcsolóval el tudjuk érni, hogy figyelmeztessen a fordító, ha olyan kódot írunk, melyben lenne leárnyékolás. Hasznos, hiszen nem mindig szándékos eredetű a leárnyékolás.

## Élettartam<a id='elettartam'></a>

Egy változó élettartama a definíciójának pillanatakor kezdődik.

Statikus tárterületen elhelyezett változók a program teljes futása alatt élni fognak (pl. ilyenek a globális változók).

Lokális változók az őket tartalmazó blokk végén semmisülnek meg.

Dinamikus memóriába (heap-re) írt változók a `new` és a `delete` (vagy `delete[]`) operátorhívások között élnek.

Fontos: Egy változó láthatósága és élettartama nem mindig egyezik meg (lásd pl. leárnyékolás)!

# Mutatók

## Memória cím<a id='memoriacim'></a>

A memória cím egy egyszerű szám, index a memórában.

Minden változó, konstans (sőt függvény is) a memóriában van, ezért rendelkezik memóriacímmel.

Mindig a kezdő bájt címét tároljuk, mert a változó típusából már fordítás időben kiderül, hogy onnan kezdve hány bájtot kell majd kiolvasni (lásd: statikusan típusos nyelv).

## Pointer típus<a id='pointer'></a>

A pointer típusú változók memória címeket tárolnak. Egy pointer típusa jelöli, hogy ő milyen típusú objektumra mutathat.

Például:
```C++
char *c; // c egy karakter címét fogja tárolni
int *n;  // n egy integer címét fogja tárolni
```

Ez azért fontos, hogy tudjuk, milyen típusként kell majd kiolvasni a címen tárolt értéket és így milyen típusú objektumot kell visszaadni. `*c` esetén egy `char`-t (1 bájt lesz kiolvasva a címről), `*n` esetén egy int-et (ha `sizeof(int)` annyi, akkor 4 bájt lesz kiolvasva).

Tetszőleges pointer típus konvertálható tetszőleges más pointer típusra (az érték minden esetben csak egy memória cím).

Megjegyzés: a három elterjedt deklaráció
```C++
int* p;
int * p;
int *p;
```
közül mind a három helyes, mert a `*` előtt és után akármennyi whitespace lehet (kivéve az `int*p` esetet). Elsőre az `int* p` tűnhet a leglogikusabb jelölésnek, hiszen a `*` a típust határozza meg. Ennek ellenére mégis az utolsó `int *p` jelölés a legelterjedtebb. Ennek oka, hogy a `*` szimbólum itt a névhez köt, azaz
```C++
int* p, q; // úgy néz ki, mintha két pointer-t deklarálnék
```
esetén `p` egy `int*` pointer lesz, `q` pedig egy sima `int`.

```C++
int *p, q; // így már jobban látszik, hogy csak az egyik lesz pointer
```

és ezért ezt kell írnom, hogy mindkettő az legyen:
```C++
int *p, *q;
```

## Referáló operátor: &<a id='referalas'></a>

Egy változó címét az `&` operátorral kérdezhetjük le.

`T`-ről `T*` típusra képez le.

`const T`-ről `const T*` típusra képez le (`const` nem veszhet el!)

Pongyolán fogalmazva: "rárakunk a típusra egy csillagot".

Például:
```C++
int x;
int *p = &x; // p rámutat x-re, ekkor p-ben az x változó memória címe kerül letárolásra
```

## Dereferáló operátor: \*<a id='dereferalas'></a>

Egy pointeren meghívva kiolvassa a tárolt memóriacímről az ott található változót.

`T*`-ról `T` típusra képez le.

`const T*`-ról `const T` típusra képez le (`const` nem veszhet el!)

Pongyolán fogalmazva: "leveszünk a típusról egy csillagot".

Például:
```C++
int x;
int *p = &x;
std::cout << *p; // kiolvassuk a p által mutatott int-et és kiírjuk azt outputra
```


## Konstans pointer (\* előtt)<a id='konstpointer1'></a>

Ha a pointer deklarációban a `*` karakter előtt áll a `const` kulcsszó, akkor a pointer típusa garantálni fogja, hogy rajta keresztül nem változik majd meg a mutatott változó. Azaz nem lehet majd ilyet: `*ptr = new_value`.

Példa:
```C++
int x = 42;
const int *p = &x;
*p = 10; // fordítási hiba, mert a mutatott érték nem változhat
```

Ennek az az oka, hogy mint korábban láthattuk, a `*` az `const T*`-ból `const T`-t csinál. `const T` pedig nem kaphat új értéket, hiszen konstans.

Megjegyzés: `const int *p` helyett `int const *p`-t is lehet írni, a lényeg, hogy a `*` karaktertől balra legyen a `const`.

## Konstans pointer (\* után)<a id='konstpointer2'></a>

Ha a pointer deklarációban a `*` karakter után áll a `const` kulcsszó, akkor maga a pointer - mint változó - lesz konstans.

Ez annyit jelent, hogy nem tárolhat más címet, csak azt, amire inicializáljuk (kötelező is inicializálni, lásd: konstansok).

Példa:
```C++
int x, y;
int * const p = &x;
p = &y; // fordítási hiba, mert p értéke nem változhat
```

Megjegyzés: egy pointer lehet egyszerre mindkét szempont szerint konstans, pl. `const int * const p = &x;`

## void\* pointer<a id='voidpointer'></a>

Olyan pointer, mely nem jelzi típusában, hogy ő milyen típusra mutat. Csak egy "nyers" memória címet tárol. Nem is lehet dereferálni, hiszen milyen típusú objektumot kéne visszaadni? `void*` -> `void`? `void` típusú objektumnak nincs értelme.

Dereferálás előtt viszont konvertálhatjuk más pointer típusra.

Például:
```C++
int x; int *p = &x;
void *v = p; // itt megy az implicit konverzió
std::cout << *(int*)v; // C-stílusú kasztolás
```

Konstanssági és egyéb pointer szabályok természetesen itt is játszanak.

Megjegyzés: C++-ban (főleg modern C++-ban) viszonylag ritkán használjuk közvetlenül. C-ben viszont elég gyakran előjön, pl. a `malloc()` ezt ad vissza, a `free()` pedig ilyen paramétert vár.

## Null pointer, NULL, nullptr<a id='null'></a>

Olyan pointert nevezünk null pointer-nek, mely egy speciális, extremális nulla címet tárol. Ennek a nullás címnek a szerepe az, hogy ezzel jelezzük, hogy éppen "nem mutatunk semmire".

A C-ből megörökölt `NULL` csak egy makró a `0`-ra.

Érdemesebb azonban a `nullptr` kulcsszavat (C++11 óta van) használni, mert az típusbiztosabb.<br>
Ilyet lehet:
```C++
int x = NULL;
```
mert a `NULL` csak `0`-ra lesz helyettesítve, ilyet viszont nem:
```C++
int x = nullptr;
```
mert a `nullptr` csak pointer típusokkal lesz típushelyes.

```C++
void f(int);
void f(char*);
```
függvény prototípusok közül az első lesz meghívva `f(NULL)` esetén, `f(nullptr)` esetén viszont - ahogy el is várnánk - a második.

Fontos: Null pointer dereferálása nem definiált viselkedéshez vezet (a gyakorlatban általában szegmentációs hiba lesz)!

Megjegyzés: a `nullptr` literál típusa: `nullptr_t`

## Pointer konverziója bool-ra<a id='pointerkonvbool'></a>

Egy pointer implicit konvertálódhat `bool` típusra.

Ha a pointer egy null pointer, akkor `false` lesz az érték, minden más esetben `true`.

## Függvény mutató<a id='fvpointer'></a>

Függvények címét is tárolhatja egy pointer. Hiszen bármilyen architektúrát veszünk, a programkód (azaz a CPU utasítások listája) is mindig a memóriába van töltve. A mutatott függvény dereferálás után meghívható. Itt nem csak a visszatérési típust, hanem a formális paraméter listát is meg kell adni a pointer-nek, mert azzal kapjuk meg a teljes függvény típust. A példán láthatjuk a pontos szintaxist.

Példa:
```C++
int f(char x) {...}
int g(char y) {...}
int (*p)(char) = &f; // p az f függvényre mutat
*p('z');
// dereferálással megkapjuk a mutatott függvényt, amit
// meghívunk egy karakter literállal
p = &g; // most már a g függvényre mutat a p pointer
```

Megjegyzés: A referáló és dereferáló operátorokat el is hagyhatjuk függvények esetén, a fordító "odaképzeli nekünk".<br>
Tehát lehetett volna `p('z');`-t és `p = g;`-t is írni.

Megjegyzés: Függvény pointer teljesen valid típus, így lehet olyat, hogy egy függvény egy másik függvény címét várja paraméterül, ezzel megvalósíthatóvá válik pl. egy foreach algoritmus C-ben és C++-ban egyaránt.

## Pointerre mutató pointer<a id='p2p'></a>

Pointerre mutathatunk pointerrel, hiszen a pointerek is egyszerű változók, melyek memória címeket tárolnak, de nekik is van címük.

Példa:
```C++
int x = 10;
int *p = &x;
int **q = &p;     // (int *)* q - olyan pointer, ami int-re mutató pointerre mutat
std::cout << **q; // output: 10 - dereferálva q-t, megkapjuk p-t, amit dereferálva megkapjuk x-et
// Valahogy így képzelhetjük el: 10 <- p <- q
```

Megjegyzés: A duplacsillagos pointert gyakran használják kétdimenziós tömbökhöz (pl. mátrixokhoz), főleg C-ben.

Megjegyzés: Innentől kezdve csak a képzelet szab határt, hogy milyen szörnyeket írhatunk:
```C++
const int * const *** const ** const p;
```
ez teljesen valid típus. Javaslat: ilyeneket azért ne nagyon írjunk, még `typedef`-fek mögé rejtve sem!

## -> operátor<a id='nyil'></a>

Ennek az operátornak mindössze a szintaktikus kényelem a szerepe. Osztályoktagok osztálypéldányra mutató pointereken keresztül történő meghivatkozására használjuk.

Jelentése: `pObject->member` ekvivalens `(*pObject).member`-rel.

Tehát kiváltja a pointert dereferáló `*`-ot és a tag szelektor `.` operátor kiírását.

Példa:
```C++
MyClass *obj = new MyClass; // pointer a heap-en létrehozott példányra
obj->member_var = 10;       // adattaggal
obj->member_func(10, 20);   // tagfüggvénnyel
delete obj;                 // fel kell szabadítani a dinamikusan lefoglalt memóriaterületet
```

## Dangling pointer<a id='danglingpointer'></a>

"Lógó mutató" vagy dangling pointer az olyan pointer, mely egy olyan memóriacímet tárol, ami már nem mutat valid objektumra.

Tipikusan akkor kapunk ilyet, ha rámutatunk egy objektumra, de az objektum élettartama hamarabb végetér, mint a rámutatott pointerünké és így az egy törölt objektum címére mutat.

Ezt a pointer-t veszélyes dereferálni: nem definiált viselkedés!

Pl.
```C++
int *p = nullptr;
if (true) {
	int x;
	p = &x; // rámutatunk x-re
}
// x törlődik, hiszen lokális objektuma az if blokkjának
std::cout << *p << "\n"; // p oda mutat, ahol x volt, de ezt a
                         // memória területet már nem biztonságos olvasni!
                         // -> undefined behavior
```

# Referenciák

## Deklarálása, definíciója, inicializálása<a id='ref'></a>

Referenciákkal egyszerű "álneveket" hozhatunk létre, melyekkel változókra hivatkozhatunk. Tulajdonképpen egy új nevet rendelünk (bind-olunk) egy változóhoz. Deklarálásakor a referált típus nevét és mögé egy `&` jelet kell írni.

Kötelező őket inicializálni, nincs olyan, hogy null reference!

Példa:
```C++
int x = 42;
int& ref = x;
std::cout << ref; // output: 42
```

A példában a `ref` egy "második név" lesz, ami ugyanarra a változóra utal, mint az `x` (ahova `ref`-et írok az olyan, mintha `x`-et írtam volna).

Fontos: Hasonló a működés de ne keverjük össze őket a pointerekkel!

Megjegyzés: C-ben nincsenek referenciák.

Megjegyzés: C++-ban amikor tehetjük érdemes lehet inkább őket használni pointerek helyett (nem kell referálgatni és dereferálgatni, és kevesebb a hibalehetőség velük).<br>
Tipikusan függvények paraméter átadásánál, visszatérésénél, illetve objektumok közötti hivatkozások kialakításánál használjuk. Ha egy "nincs érték" állapot is szükséges, akkor viszont kénytelenek vagyunk pointer-t használni (hiszen null pointer van, de null referencia nem), vagy modern C++-ban `std::optional`-t.

## Konstans referencia<a id='konstref'></a>

A sima referenciákkal ellentétben ők garantálják, hogy a hivatkozott változót nem lehet megváltoztatni rajtuk keresztül.

Példa:
```C++
int x = 42;
int& ref = x;        // referencia
const int& cref = x; // konstans referencia
ref  = 10; // OK
cref = 20; // fordítási hiba, mert konstans referencia
```

Fontos: Konstansra csak konstans referenciával tudunk hivatkozni (konstansság nem veszhet el)!

Sima változóra viszont lehet konstans referenciával is hivatkozni.

# Tömbök

## Fogalma<a id='tombok'></a>

A tömbök a memóriában szekvenciálisan (egymást követően) elhelyezkedő, azonos típusú változók fix méretű (elemszámú) csoportja.

## Deklarálása, definíciója, inicializálása<a id='tombdef'></a>

Deklarálása és egyben definíciója:
```C++
int t[10];
```
Ekkor a memóriában le lesz foglalva 10 egymást követő `int`-nyi terület, `10*sizeof(int)` bájt, és a `t` változó ennek a területnek a kezdőcímét (első `int` első bájtja) fogja eltárolni, mint egy pointer.

Inicializációja:
```C++
int t[4] = { -4, 10, 3, 11 };
```

Megjegyzés: inicializáció esetén nem kötelező kiírni a kívánt méretet, mert a fordító ki tudja következtetni a listából, tehát így is lehet:
```C++
int t[] = { -4, 10, 3, 11 };
```

Ez persze helytelen:
```C++
int t[]; // Mekkora legyen?
```

## Kapcsolat a mutatókkal (konverzió)<a id='tombpointer'></a>

A tömb változó konvertálódik első elemre mutató pointer-ré (hiszen, a tömbváltozó az első elem címét tárolja).

Például:
```C++
void f(int *array);
int t[4];
```
esetén valid a tömböt átadni: `f(t);`<br>
A tömb változó első elemre mutató pointerré konvertálódik (array to pointer decay).

A konverzió általánosan leírva: `T[]` -> `T*`

Megjegyzés: a függvényt így is lehet írni, ugyanaz: `void f(int array[]);`

## Konstans tömb<a id='konsttomb'></a>

Tömb deklarációkor a `const` kulcsszóval elérhetjük, hogy a tömb tárterülete read-only legyen.

Például:
```C++
const char str[6] = { 'h', 'e', 'l', 'l', 'o', '\0' };
```
vagy másképp:
```C++
const char str[6] = "hello"; // lásd: literálok
```

Ekkor nem fogjuk tudni felülírni egyetlen elemét sem.

Fontos: `const` tömböket - mint minden konstanst - kötelező inicializálni (nem is lenne értelme nem megtenni)!

Konstans tömbök az első elemre mutató konstans pointerré fognak konvertálódni, formálisan:<br>
`const T[]` -> `const T*` (hiszen a `const` nem veszhet el)!

## Pointer aritmetika<a id='pointeraritmetika'></a>

A pointer aritmetikával tudjuk elérni, hogy egy memóriacímet "léptessünk" előre (jobbra) vagy visszafelé (balra) a memóriában (most elképzelhetjük a memóriacímeket egy számegyenesnek).

```C++
int x = 10;
int *p = &x;
```
esetén `*x`-szel a letárolt int-et érhetjük el, míg `*(x+1)`-gyel a közvetlenül azt követő `int`-nyi bájtot (ez ebben a példában undefined behavior, mert nem tudunk semmit arról a területről, lehet, hogy nem is a mi processzünké lesz, ezért segfault-ol majd a program).

Úgy is elképzelhetjük, hogy a `p+N` (`p` pointer, `N` egy pozitív egész) esetén `N` egy offset-et határoz meg, hogy "mennyit ugorjunk a `p` címtől jobbra" (`p-N` esetén pedig balra). Mindig `N * sizeof(mutatott típus)`-t fogunk ugrani.

Megjegyzés: A `p+1` természetesen nem változtatja meg a `p`-ben tárolt címet, csak visszatér az eltolt címmel, ha meg akarjuk
változtatni, akkor így lehet: `p+=1` vagy `++p`, esetleg: `p++` (kivonás esetén hasonlóan).

Tömbök az első elem címét tárolják és az elemei szekvenciálisan vannak a memóriába, sőt azt is tudjuk, hogy az első elemre mutató pointerré konvertálódnak. Ezekből adódóan a következőképp érhetjük el az elemeket:

```C++
*t      // első elem (nullás index)
*(t+0)  // első elem (nullás index) - nem toltuk el semmivel
*(t+1)  // második elem (egyes index)
*(t+2)  // harmadik elem (kettes index)
*(t+3)  // negyedik elem (hármas index)
```

Megjegyzés: Ebből egyből láthatjuk, hogy miért 0-tól indexeljük a tömböket (az index az eltolás mértéke, az offset).

## [] operátor szemantikája tömbökre<a id='tombindex'></a>

A hagyományos pointer aritmetika szintaxisa nem túl szép és kényelmetlen (könnyű elírni). A C ezért bevezette a következő szintaxist:
```C++
t[3]; // negyedik (hármas indexű) elem elérése
```
Ez csak egy szintaktikus kiegészítés (szépítés), általánosan leírva: `t[N]` teljesen ekvivalens `*(t+N)`-nel.

De az értékadás kommutatív, ezért:
```C++
t[3] == *(t+3) == *(3+t) == 3[t]
```
Elvégre mindegy, hogy `0x7ffd3388908c`-t toljuk el `0x3`-mal, vagy `0x3`-at `0x7ffd3388908c`-vel.

## Statikus tömb<a id='statikustomb'></a>

Olyan tömbök, melyek méretének fordítási időben (más néven statikus időben) ismertnek kell lennie. Az összes tömb, mely a statikus tárterületen vagy a hívási veremben helyezkedik el ilyen.

Megjegyzés: Az eddigi tömbös példák mind statikus tömbök voltak.

Megjegyzés: Ilyet azért lehet:
```C++
const int size = 10;
int tomb[size];
```
mert `size` itt egy fordítási idejű konstans, ezért már fordítás idején ismert az értéke.

Ilyet már pl. nem lehetne:
```C++
int size;
std::cin >> size;
int tomb[size]; // fordítás idején még nem ismert a méret
```

Pontosítás: standard C++-ban nem lehet, pár fordító (pl. g++) lehet, hogy implementál egy bővítményt, ami ezt megengedi. Hogy az ilyen compiler által megengedett, de nem standard feature-öket kiszűrjük (nem túl portabilis), fordíthatunk a `-pedantic` kapcsolóval. A `-pedantic-errors` mégtöbb szigorítást ad. (Pl. ilyen nem-standard feature még a `#pragma` once is).

## Dinamikus tömb<a id='dinamikustomb'></a>

Olyan tömbök, melyek méretének elég futási időben (más néven dinamikus időben) eldőlnie. Ilyen tömböt csak a dinamikus tárterületen (heap-en) hozhatunk létre.

Példa:
```C++
int size;
std::cin >> size;
int *tomb = new int[size]; // OK, mert a new operátor a dinamikus memóriába allokál
...
delete[] tomb; // nekünk kell felszabadítani!
// Lásd: dinamikus memória kezelés
```

Megjegyzés: Dinamikus tömbre is igaz, hogy a létrehozása után már nem változhat a mérete.

Megjegyzés: Minden más fogalom (pointer aritmetika, konstansság, stb.) ugyanúgy érvényes a dinamikus tömbökre is, mint a statikusakra.

## Kiindexelés<a id='kiindexeles'></a>

Ha egy tömbből kiindexelünk (lásd: pointer aritmetika), ami lényegében azt jelenti, hogy rossz memóriacímről próbálunk adatot kiolvasni, akkor az nem definiált viselkedéshez vezet.

Például lehet, hogy memóriaszemetet olvasunk ki, vagy lehet, hogy szegmentációs hibát kapunk (mert például nem is a mi folyamatunké az a memória terület, amit olvasni próbálunk).

# Memória

## Bit<a id='bit'></a>

0 vagy 1 bináris érték a memóriában.

## Bájt<a id='bajt'></a>

Bitek 8-as csoportja, a számítógép memóriájának alapegysége.

Megjegyzés: Elvileg létezhet olyan architektúra, amin nem 8 bitből áll egy bájt, ezt nem tiltja a C és C++ standard (az szokott követelmény lenni, hogy az ASCII tábla ráférjen 1 bájtra), de a gyakorlatban ilyesmi miatt nemigen kell aggódnunk.

## Gépi szó<a id='word'></a>

A processzor a bájtokat nem egyesével, hanem csoportosítva
"szereti" kezelni (hatékonyabb, lásd: 32 és 64 bites architektúra).
Mérete tehát implementáció függő (sok esetben 4). Angol szakirodalomban: word.

## Padding<a id='padding'></a>

A fordító a változóknak, rekord struktúráknak méretét kitöltheti
plusz (használatlan) bájtokkal, hogy az összméret a gépi szó
többszöröse legyen. Ez egy példa az implementáció által definiált
viselkedésre.

Például:
```C++
// tfh. gépi szó == 4 bájt
struct S {
	int x;     // tfh. most sizeof(int) == 4
	char a, b; // 2*sizeof(char) == 2*1 == 2
};
sizeof(S); // 8 (utolsó 2 bájt a padding)
```

"Hole"-ok is kerülhetnek be két adattag közé, hogy minden adattag "kerek" (pl. 4 többszöröse) címen kezdődjön.

Megjegyzés: a gdb debugger-rel könnyen megvizsgálható egy struct memory layout-ja a következő paranccsal:
```
(gdb) ptype /o obj
```
ahol `obj` egy olyan típusú objektum, amilyen típust vizsgálni akarunk. Ne felejtsünk el `-g` kapcsolóval fordítani ehhez!

## Memória szemét<a id='memoriaszemet'></a>

Az inicializálatlan memóriaterületeket szoktuk memória szemétnek nevezni.

Ha a memóriaterület egyszer inicializálva lett, de később fel lett szabadítva (pl. lokális változó kifut a scope-ból vagy egy heap-re allokálton `delete`-et hívunk), akkor utána már nem definiált a tartalma, hiszen onnantól kezdve felül lehet írva, ezért onnan olvasni szintén memória szemét olvasásához vezethet.

## sizeof operátor<a id='sizeof'></a>

A `sizeof` operátorral le tudjuk kérdezni egy típus méretét (bájtokban), függvény szintaxissal tudjuk használni. Úgy is működik, ha egy változót írunk operandusnak.

Például:
```C++
char c;
sizeof(char); // 1
sizeof(c);    // 1
```

Megjegyzés: Statikus tömb elemszámát C-ben és C++-ban is le lehet kérdezni így:
```C++
sizeof(t)/sizeof(*t) // sizeof(t) a tömb összmérete
                     // sizeof(*t) elem típus mérete
```

Ez **csak statikus tömbökkel** működik!<br>
Miért? Mert a `sizeof` egy fordítási idejű operátor.

## Statikus memória (Static memory)<a id='statikusmem'></a>

A programunk globális változói, függvények statikus változói és osztályok statikus változói fognak ide kerülni. Ezek a változók élettartama a teljes program futás végéig tart.

## Dinamikus memória (Heap)<a id='dinamikusmem'></a>

Közvetlenül a programozó kezeli (allokál rá és deallokál onnan pointereken keresztül). Az itteni változók élettartama a `new` operátor hívásától a `delete` (vagy `delete[]`) operátor hívásáig tart.

## Hívási verem (Call stack)<a id='hivasiverem'></a>

Függvények és egyéb kód blokkok (pl ciklus vagy elágazás blokkja) lokális változói kerülnek ide. Az itteni változók definíciójuk idejétől addig élnek, amíg ki nem kerülnek scope-ból (azaz véget nem ér a saját blokkjuk futása).

Megjegyzés: A következő példa demonstrálja a hívási verem működését függvényekkel:
```C++
void h(char c) {...}
void g() { h('z'); }
int f(int x) { g(); }
int main() { f(10); }
```

Verem tartalma:<br>
`main -> main,f -> main,f,g -> main,f,g,h -> main,f,g -> main,f -> main`<br>
ahol a függvény nevek a saját paramétereiket, egyéb lokális változóikat és visszatérési értékeiket jelentenek a verem memóriájában.

# Dinamikus memória

## Memória allokálás, new operátor<a id='new'></a>

A `new` operátorral tudunk memóriát lefoglalni a heap-en.

A lefoglalt terület mérete a meghatározott típus méretétől függ (tömb létrehozása esetén a `sizeof(elemetípus) * elemszám` lesz). Ez az operátor egy memóriacímmel tér vissza, ami a lefoglalt terület első bájtja. Ezt rögtön egy pointer-nek adjuk értékül, hogy ne vesszen el a cím (tudjuk használni rajta keresztül, majd később deallokálni).

E mellett lefuttatja a típus megfelelő konstruktorát (lásd: osztályoknál), illetve dinamikus tömb létrehozása esetén az összes elemre a konstruktort.

Példa:
```C++
float *f = new float(3.14f); // float allokálása
bool *l = new bool[5];       // 5 elemű bool tömb allokálása
```

Megjegyzés: C-ben nincsen `new` operátor, ott az `<stdlib.h>` standard library `malloc()`, `calloc()` és `realloc()` függvényeivel tudunk hasonló dinamikus allokálást elérni, **de:**
* azok nem inicializálják a memóriát, mivel nem hívnak konstruktort! (lényegében nem hoznak létre objektumot, csak memóriát foglalnak).
* velük van plusz hibalehetőség, ha pl. rossz méretet adunk meg!
* függvény visszatérés vizsgálat helyett `std::bad_alloc` kivétel elkapással kezelhető, ha nem sikeres az allokálás.

## Memória deallokálás, delete és delete[] operátorok<a id='delete'></a>

Mivel a C++-ban nincsen szemétgyűjtő (hatékonyság ellen menne), nekünk kell felszabadítani az általunk allokált dinamikus memóriaterületeket, ha már nincs rájuk szükségünk. Sima változók esetén a `delete`, tömbök esetén pedig a `delete[]` operátorral tudjuk ezt elérni úgy, hogy a felszabadítandó memória terület címét adjuk át pointer formájában.

Példa az előző két változó felszabadítására:
```C++
delete f;   // sima változó deallokálása
delete[] l; // tömb deallokálása
```

A `delete` esetén le fog futni a típus destruktora is, `delete[]` esetén pedig a tömb összes elemére le fog futni a destruktora.

Megjegyzés: Lokális változók esetén nincs ilyesmivel dolgunk, mert a blokk végén megsemmisülnek (lefut a destruktoruk), statikus változók meg a programfutás végéig élnek.

Figyelem: mindig győződjünk meg róla, hogy csak olyan pointer-rel hívjuk meg a delete operátort, amely:
* valid, létező objektum címét tárolja, ami
* egy heap-en (`new`-val létrehozott) objektum
* és még nem hívtunk rajta `delete`-et

Minden más esetben nem definiált viselkedést kapunk!

Megjegyzés: C-ben nincsen `delete` vagy `delete[]` operátor, ott az `<stdlib.h>` standard library `free()` függvényével tudunk hasonló dinamikus deallokálást elérni.<br>
**De:** az nem hív destruktort/destruktorokat! (mivel nem objektumot töröl, csak memóriát deallokál).

Fontos:
* a `new`/`malloc()` és `delete`/`free()` hívásokat ne keverjük, azaz a `new`-val létrehozottat `delete`-tel szabadítsuk fel, a `malloc()`-kal létrehozottat pedig `free()`-vel!
* C++ esetén a `new`/`delete` párost használjuk, a C-s függvényeket pedig kerüljük, hacsak nincs valami speciális ok miatt azokra közvetlenül szükség!

## Memória szivárgás<a id='leak'></a>

Ha a programunkban nem szabadítunk fel dinamikusan lefoglalt memóriaterületet, akkor az memória szivárgáshoz vezethet!

Például:
```C++
if (...) {
	int * p = new int(42);
	std::cout << *p << "\n";
}
```

Nem írtunk `delete` operátorhívást és a `p` pointer (ami egy sima lokális változója az if blokknak) kifutott a scope-ból, ezért megsemmisült; így elveszítettük az egyetlen hivatkozásunkat a dinamikusan lefoglalt területre, ezért azt már később fel sem fogjuk tudni szabadítani. Memória szivárgáshoz jutottunk.

Érdemes úgy megjegyezni a dolgot, hogy "minden `new` operátorhíváshoz kell lennie valahol egy `delete` operátorhívásnak (párban kell lenniük)".

Ez akkor fog nagyobb gondot okozni, ha ez az ominózus if blokk a program futása alatt több ezerszer le fog futni. Egyre nagyobb lesz a memória használat.

Memória/erőforrás szivárgás kivédésére lásd: RAII (később).

# Függvények

## Deklarálása, definíciója<a id='fv'></a>

Deklarálás:
```C++
void f(int x, int y);
```

Itt el is lehet hagyni a paraméter neveket:
```C++
void f(int,int);
```

Definíció:
```C++
void f(int x, int y) {...}
```

Itt már nem lehet elhagyni a paraméter neveket.

Megjegyzés: Deklarálni akárhányszor lehet egy függvényt (akár ugyanazon fordítási egységen belül is), definiálni viszont csak egyszer lehet, hogy ne sértsük az ODR-t!

## Visszatérési típus<a id='visszateresitipus'></a>

A függvénynév elé írjuk a típusát és a függvénytörzsben a `return` kulcsszó után a konkrét értéket (objektumot), mellyel vissza akarunk térni.

## void visszatérési típus<a id='voidvisszateres'></a>

A `void` kulcsszóval jelezhetjük, hogy a függvény nem tér vissza semmivel (eljárásnak is szokás az ilyen függvényt nevezni).

A `return;` utasítást azonban használhatjuk a törzsben a függvény terminálására.

## Formális paraméter lista<a id='formparamlista'></a>

A függvény deklarációban (definíciónál is szerepel) a zárójelek közé írt paramétereket jelenti. A paraméterek száma és rendre azoknak típusai számítanak.

Például:
```C++
void f(int, const char*); // zárójel közötti rész
```

A formális paraméter lista elemeit formális paramétereknek nevezzük.

## Aktuális paraméter lista<a id='aktparamlista'></a>

Függvényhívás esetén a konkrét paramétereket (melyekkel a függvényt meghívjuk) nevezzük így.

Például:
```C++
f(10, nullptr); // zárójel közötti rész
```

Az aktuális paraméter lista elemeit aktuális paramétereknek nevezzük.

## Szignatúra<a id='szignatura'></a>

A szabvány a függvény szignatúrájának azon tulajdonságok összességét nevezi, mely beleszámít a túlterhelhetőségbe.

Ezek a következők: függvény neve, formális paraméter listája (és osztály tagfüggvények esetén a függvény konstanssága).

Tehát a `void f(int, const char*);` függvénynek a szignatúrája az `f(int, const char*)`.

Fontos: A visszatérési típus **nem** része a szignatúrának!

Például a következő két függvény szignatúrája megegyezik:
```C++
int f(char);
bool f(char); // ugyanaz a név és formális paraméter lista
```

## Függvény prototípus<a id='prototipus'></a>

Ha egy ugyanolyan nevű függvénynek két vagy több definíciója is van, melyek szignatúrája más-más akkor azokat függvény prototípusoknak nevezzük.

Különböző függvény prototípusokhoz juthatunk túlterheléssel vagy default paraméterek használatával.

## Függvény túlterhelés<a id='tulterheles'></a>

Ha ugyanolyan nevű függvényeket definiálunk, melyeknek más-más a
szignatúrája, akkor több különböző függvény prototípushoz jutunk. Ezt
a módszert túlterhelésnek (overloading) nevezzük. C-ben nincs.

Például:
```C++
int max(int,int);
float max(float,float);
...
max(10, 20);      // az első prototípus hívódik meg
max(3.14f, .15f); // a második prototípus hívódik meg
```

Fontos: Ha két függvénynek egyezik a szignatúrája (pl. csak a visszatérési típusban különbözik a deklarációjuk), akkor fordítási hibát fogok kapni, hiszen nem is lenne egyértelmű a fordítónak, hogy egy adott ponton melyik függvényt kell majd meghívni.

Megjegyzés: a következő paranccsal:
```Bash
$ objdump -t main.o
```
meg is tudjuk nézni, hogy milyen szimbólum nevet kaptak az egyes prototípusok, hogy a linker számára már egyértelmű legyen, hogy mi micsoda Pl. `_Z3maxii`, `_Z3maxff`

A parancs hasznos lehet, ha linkeléssel kapcsolatos hibát szeretnénk debuggolni (pl. undefined reference; multiple references hiba; vagy egy szimbólum nem abba az object-be került, amibe kéne; esetleg C-s függvény nevet kapott C++-os függvény vagy fordítva, stb...)

`objdump` helyett használhatjuk az `nm` nevű programot is ilyen listázásokra.

## Paraméter default értéke<a id='defparam'></a>

Függvények deklarálásakor alapértelmezett értéket adhatunk egyes
paramétereknek. Ez igazából egy implicit függvény túlterhelést jelent.

Például:
```C++
void f(int x, int y = 5, int z = 10);
```
Ez le fogja generálni a következő prototípusokat:
```C++
void f(int,int,int);
void f(int,int);
void f(int);
```
Ezért meg lehet hívni a következő három módon:
```C++
f(10, 20, 30);
f(10, 20);
f(10);
```

Fontos: Ha vannak default paraméterek, akkor azoknak a paraméter listában jobboldalon kell lenniük! Ilyet például nem lehet:
```C++
void f(int, float = 3.14, int);
```

Megjegyzés: deklarációnál default paraméter esetén sem szükséges nevet kiírni, ez rendben van: `float = 3.14`

Megjegyzés: Mivel túlterhelés sincsen a C-ben, ezért default paraméterek sincsenek. Ott ilyesmi hackeléssel lehet ezt megoldani:
```C++
int f2(int x, int y) {...}
int f1(int x) { return f2(x, 20); }
```

## Lokális változó<a id='lokalisvaltozo'></a>

Függvények lokális változói a paraméterei és a függvény törzsében deklarált változók. Ezen változók láthatósága és élettartama is csak a függvény törzsének végéig tart. Lásd: hívási verem működése.

## Statikus lokális változó<a id='fvstatikus'></a>

Speciálisan a `static` kulcsszavat kiírva a függvény lokális változója elé, tudjuk elérni, hogy az a változó ne a hívási verembe kerüljön, hanem a statikus tárterületre. Ebből következik, hogy élettartama a teljes program futására kiterjed, láthatósága viszont továbbra is csak a függvény blokkra korlátozódik. Az első függvényhíváskor inicializálódik az érték, később pedig minden függvényhívás esetén ugyanaz a tárterület lesz felhasználva.

Példa:
```C++
void f()
{
	static int call_count = 0; // ez csak egyszer fut le
	std::cout << "I was called " << ++call_count << "times";
}
...
f(); // output: I was called 1 times
f(); // output: I was called 2 times
f(); // output: I was called 3 times
f(); // output: I was called 4 times
```

## Rekurzió<a id='rekurzio'></a>

Ha egy függvény önmagát hívja meg, akkor azt rekurziónak nevezzük.

Például:
```C++
unsigned int fact(unsigned int n)
{
	return (n==0 ? 1 : n * fact(n-1));
}
```

Fontos: Sok rekurziós szint esetén gyorsan megtelik a hívási verem, ami memória és futási idő szempontjából sem hatékony, ezért is érdemesebb ciklussal implementálni azt, amit csak lehet. Ha rosszul írjuk meg a rekurziót (nem éri el a vezérlés garantáltan az alapesetet), akkor meg fog telni a hívási verem, stack overflow hibát kapunk.

## Érték szerinti paraméter átadás<a id='ertekparam'></a>

A paraméter átadás alap esetét nevezzük így. Ekkor minden paraméter egy-egy lokális másolata lesz az aktuális paraméternek (copy konstruktor lesz meghívva a másoláshoz).

Példa:
```C++
void f(int a, int b)
{
	a += 10;
	b += 20;
	std::cout << a + b;
}

int x = 10, y = 5;
f(x,y); // nem fog megváltozni x és y, mert csak érték
        // szerint lettek átadva, lokális másolat készült róluk.
```

## Referencia szerinti paraméter átadás<a id='refparam'></a>

Ha a formális paraméter listában a paraméter típusa mögé `&` jelet írunk, akkor az a paraméter egy referencia (második név) lesz, ami az aktuális paraméterre hivatkozik. Ezzel el tudjuk érni, hogy a függvényen belül megváltoztathassuk a külsö változóinkat.

Lehet konstans referencia szerint is átadni paramétert, melynek esetén szintén nem lesz másolás (hatékony) és azt is garantálja, hogy ő rajta keresztül (vagyis a függvényen belül) nem lesz megváltoztatva a hivatkozott érték.

Példák:
```C++
void triple(int& n)
{
	n *= 3;
}

void print(const int& n)
{
	std::cout << n;
}

int num = 5;
const int cnum = 10;

triple(num);  // ez után num 15 lesz
triple(cnum); // fordítási hiba: int& nem hivatkozhat konstansra, const-ot nem lehet elveszíteni
              // lásd: konstans referencia
print(num);   // int& -> const int& konverzió OK, const-ot lehet kapni
print(cnum);  // OK, konstansra hivatkozhat konstans referencia
```

## Cím szerinti paraméter átadás<a id='ptrparam'></a>

A referencia szerinti átadás mellett egy másik alternatíva, ha a megváltoztatandó változó címét adjuk át paraméterként. (C-ben
ez a megoldás játszik). Ennél a megoldásnál szükség van referálásokra és dereferálásokra. Ha read-only módon akarunk átadni, akkor const pointert adjunk át.

Példák:
```C++
void triple(int *n)
{
	*n *= 3; // mutatott területet írjuk át
}

void print(const int *n)
{
	std::cout << *n;
}

int num = 5;
const int cnum = 10;

triple(&num);  // címet adunk át, ez után num 15 lesz
triple(&cnum); // fordítási hiba: const int* -> int* konverzió nincs, const-ot nem lehet elveszíteni
               // lásd: konstansság és konstans pointer
print(&num);   // int* -> const int* konverzió OK, const-ot lehet kapni
print(&cnum);  // OK, konstansra mutathat konstans pointer
```

## inline kulcsszó<a id='inline'></a>

A függvény deklarációja elé az `inline` kulcsszót kiírva adhatunk egy javaslatot a fordítónak, hogy "inline-olja" a függvényt. Ez annyit jelent, hogy a függvény kódját (blokkot) be fogja másolni a hívás összes helyére.

Előny: nem lesz annyi ugrálás (CALL) az assembly-ben -> kevesebb művelet és kontextus váltás -> gyorsabb.

Hátrány: ha hosszú a függvény törzs és/vagy sok helyen van meghívva, akkor nagy lesz a bináris mérete. (Sőt, ha elég kicsi lenne a bináris, lehet hogy processor cache-be be tudná húzni az egészet, így néha a nem inline-olt a hatékonyabb gyorsaságban is!)

Megjegyzés: Például getter és setter metódusokat érdemes lehet, hiszen azoknak nagyon rövid a törzsük.

Példa:
```C++
inline int getX() { return _x; }
```

Fontos: Ez csak egy hint a fordítónak. E nélkül is lehet, hogy valamit inline-olni fog, vagy ennek megléte esetén is lehet, hogy nem fog inline-olni. A fordító általában elég okosan optimalizál, jobban ki tudja találni, hogy érdemes.

Az inline-olás persze függhet a használt optimalizációs szinttől is (lásd: `-O` kapcsolók)

Tipp: debuggolásnál problémásak lehetnek az inline-olt függvények, hiszen nem fogjuk megkapni a kód (függvény def) eredeti helyét (fájl+sorszám). Ezért debuggoláshoz érdemes lehet az `-fno-inline` kapcsolót használni, hogy garantáltan semmi ne legyen inline-olva.

Megjegyzés: egy másik hatása az `inline`-nak, hogy ha kitesszük egy függvény definíció elé, akkor az a függvény definiálva lehet több fordítási egységben is (feltéve, hogy mindegyikben pontosan egyszer). Ez azért szerencsés, mert így írhatunk `inline` függvény definíciókat header fájlokba, amit több helyre include-olhatunk.

# Operátorok

## Operátor fogalma<a id='operator'></a>

Az operátorok speciális szintaxissal ellátott függvények.

A legtöbb operátornál le van fixálva, hogy hány paramétert kaphat, például az `operator+` kettőt, az `operator!` eggyet.

Az operátorok paramétereit gyakran operandusoknak nevezzük.

Ezeken túl minden igaz rájuk, amik a függvényekre.

## Unáris operátor<a id='unaris'></a>

Egyparaméteres operátorok, például: `!`, `&`, `*`, `++`, `--`, stb.

## Prefix szintaxis<a id='prefix'></a>

Egyes unáris operátorok használják. Az operátor az operandus elé kerül.

Például: `++x`, `--x`

(Ezek megváltoztatják a változó értékét, majd az új értékkel térnek vissza).

## Postfix szintaxis<a id='postfix'></a>

Egyes unáris operátorok használják. Az operátor az operandus után kerül.

Például: `x++`, `x--`

(Ezek megváltoztatják a változó értékét, de még a régivel térnek vissza).

## Bináris operátor<a id='binaris'></a>

Kétparaméteres operátorok, például: `+`, `*`, `/`, `%`, `&&`, `==`, `+=`, stb.

## Infix szintaxis<a id='infix'></a>

Bináris operátorok használják. Az operátor a két operandus közé kerül.

## Ternáris operátor<a id='ternaris'></a>

Egyetlen ternáris operátor: `? :`

Három paramétert vár, használata:
```C++
int x = -30;
std::cout << (x < 0 ? "negativ" : "nemnegativ"); // output: negativ
```

* Első paraméter a kiértékelendő kifejezés, melynek `bool` típusúnak, vagy azzá konvertálhatónak kell lennie.
* Második paraméter: ezzel tér vissza, ha az első paraméter `true`.
* Harmadik paraméter: ezzel tér vissza, ha az első paraméter `false`.

Megjegyzés: A második és a harmadik paraméter típusa tetszőleges, de mindig **ugyanolyan** típusúnak kell lenniük! (nem lehet, hogy egyszer `int`-et, máskor pedig `float`-ot ad vissza egy függvény/operátor, hiszen ez sértené a nyelv statikus típusosságát).

## Függvény-szerű szintaxis<a id='fvszeru'></a>

Vannak olyan operátorok, melyeket függvényekhez hasonló szintaxissal hívhatunk meg, például: `sizeof()`, `typeid()`, stb.

## Precedencia<a id='precedencia'></a>

Két operátor között meghatározza, hogy melynek kell hamarabb lefutnia.
Például:
```C++
int x = 10 + 5 * 3; // 25, mert * erősebb +-nál
```

[Precedencia táblázat](https://en.cppreference.com/w/cpp/language/operator_precedence)

## Asszociativitás<a id='assoc'></a>

Meghatározza az operátorok alap zárójelezését (ha nem írunk ki explicit zárójeleket). Lehet bal- vagy jobbasszociatív.

Például:
* `10 + 3 + 2` esetén a zárójelezés: `(10 + 3) + 2` - balasszociatív
* `int x = y = z` esetén: `int x = (y = z)` - jobbasszociatív

Megjegyzés: A legtöbb operátor balasszociatív, az értékadó operátorok (pl. `=`, `+=`, `-=`, `*=`, `&=`, `|=`, stb.) mind jobbasszociatívak.

## Operátor túlterhelés<a id='operatortulterheles'></a>

Függvényekhez hasonlóan az operátorokat is túl lehet terhelni különböző típusú operandusokra.

Van néhány, melyet nem lehet viszont túlterhelni, például a `sizeof` operátort.

## Bit manipuláló operátorok<a id='bitoperatorok'></a>

Vannak operátorok, melyekkel bitenkénti műveleteket végezhetünk.

Például:
* `&` : bitenkénti ésselés
* `|` : bitenkénti vagyolás
* `^` : xor-olás
* stb.

## Lusta kiértékelés<a id='lustakiertekeles'></a>

A logikai operátorok lusta kiértékelésűek. Például, ha az `&&` operátor első operandusa hamis, a másodikat ki sem értékeli; ha a `||` operátor első operandusa igaz, a másodikat ki sem értékeli.

Hasznos lehet, ha mondjuk le akarjuk tesztelni, hogy egy pointer nem-e null.

Példa:
```C++
Person *p = nullptr;
...
if (p && p->getName() == "John") {
	...
}
```

Ha `p` az null pointer, akkor `false`-ra fog konvertálódni a a feltételben és ekkor a `&&` ki se fogja értékelni a `p->getName()` hívást. Ez azért jó, mert a `p->getName()`, ami a `(*p).getName()`-et jelenti null pointert próbálna dereferálni, ami nem definiált viselkedés. Így az egész if feltétel hamis lesz ha `p` nem mutat semmire, ha meg mutat egy objektumra, akkor megnézi a második feltételt.

Megjegyzés: A példa zárójelezés nélkül is helyes, mert a `==` operátor precedencia szerint erősebb a `&&`-nál.

# Vezérlési szerkezetek

## Szekvencia<a id='szekvencia'></a>

`;`

Egyfajta ún. szekvencia pontot definiál. Garantálja, hogy az előtte álló utasítás hamarabb fog lefutni, mint az utána álló (ezt a sima vessző: `,` nem szokta garantálni).

## Elágazás<a id='elagazas'></a>

`if` - Standard imperatív elágazás:

```C++
if (logikai kifejezés) {
	utasítások
}
else if (logikai kifejezés) {
	utasítások
}
...
else {
	utasítások
}
```

A logikai kifejezés `bool` típusú, vagy olyan típusú lehet, mely implicit azzá tud konvertálódni.

`switch` - Többágú elágazás, mely egy változó értékét teszteli `==` operátorral:

Példa:
```C++
switch (x) {               // x-nek integrális, enumerációs, vagy olyan
case 0: utasítások; break; // típusnak kell lennie, ami konvertálható implicit egy integrális típusra
case 1: utasítások; break;
...
default: utasítások;
}
```

A `break`-ek azért kellenek, mert C-ben és C++-ban "tovább folyna a vezérlés", ha teljesül egy feltétel.

`default` ágat opcionális írni, akkor fut le, ha semelyik előző ág nem volt igaz.

Ha szeretnénk egy `case` ág alá új lokális változót felvenni, akkor ahhoz egy új scope-ot kell nyitni kapcsoszárójelekkel:

```C++
...
case N: { int x; utasítások; break; }
...
```

## Ciklus<a id='ciklus'></a>

Elöl tesztelő ciklus:

```C++
while (logikai kifejezés) {
	utasítások
}
```

Megjegyzés: végtelen ciklus: `while(true)` vagy akár: `while(1)`

Hátul tesztelő ciklus:

```C++
do {
	utasítások
} while (logikai kifejezés);
```

Számlálós ciklus:

```C++
for (...;...;...) {
	...
}
```

Például, gyakori usecase:
```C++
for (int i=0; i<100; ++i) {
	...
}
```

Az első `;` előtti részben inicializálások vannak (a ciklus előtt futnak le egyszer); a középső részben a ciklus feltételét kiértékelő logikai kifejezésnek kell állnia; az utolsó részben pedig az iterációk végén lefuttatandó utasításnak.

A három rész közül bármelyik elhagyható (a középső elhagyásakor az azonosan igaz lesz a feltétel).

Két másik példa több változóval:
```C++
for (int i=0,j=10; i*j<1000; ++i,j*=2) {
	...
}

for (Node *p=llist, int idx=0; p!=nullptr; p=p->next,++idx) {
	...
}
```

Megjegyzés: végtelen ciklus: `for(;;)`

## Ugrások<a id='ugrasok'></a>

`goto` - Ugró utasítás, mellyel a vezérlést átirányíthatjuk kódunk tetszőleges pontjára, ahova címkét (label-t) írtunk.

Példa:
```C++
int i=0;
begin: // ez a címke
std::cout << ++i << " ";
if (i < 5)
	goto begin;
```

Output: 1 2 3 4 5

Megjegyzés: Ha tehetjük, ne használjuk, mert erősen ellenmegy a procedurális programozásnak! Használjunk elágazásokat, ciklusokat és függvényeket helyette! (Ezek persze szintén ugrásokat tesznek, de el van absztraktálva, így olvashatóbb a kód és kevesebb a hibalehetőség).

`break` - Ciklus belsejébe írhatjuk. Meg fogja szakítani a ciklus vezérlését (kiugrik a ciklustörzs utánra).

`continue` - Ciklus belsejébe írhatjuk. A következő iterációra fog ugorni a vezérlés. A `for` ciklus esetén az iteráció végén futtatandó utasítás ekkor is le fog futni az új iteráció megkezdése előtt.

Megjegyzés: a `goto`-val ellentétben ezt a kettőt szokták gyakran használni, hiszen nem lehet velük "akárhova" ugrani és sok esetben igencsak hasznosak.

# Típus szinoníma

## typedef kulcsszó<a id='typedef'></a>

Típus szinonímát definiálhatunk vele. Olyan, mint egy alias név a típusra. Hosszú típusnevek kiírását tudjuk elkerülni vele.

Példa:
```C++
typedef std::map<int, std::string> IMap;
IMap my_map1;
IMap my_map2; // nem kell mindenhova kiírni a hosszú típusnevet.
IMap my_map3;
```

Megjegyzés: Ez C-ben is van.

Megjegyzés: Alias template típusokkal nem működik. Ahhoz a C++11 óta bevezetett `using` kulcsszavas szintaxist használhatjuk:

```C++
template <typename T>
using Dictionary = std::map<std::string, T>;
...
Dictionary<int>         dict_i = {{"Foo", 10}, {"Bar", 42}};
Dictionary<std::string> dict_s = {{"Foo", "first"}, {"Bar", "second"}};
```

# Felsorolási típus

## enum<a id='enum'></a>

Az `enum` kulcsszót használva definiálhatjuk a felsorolási típusainkat. Ezek csoportos aliasként fognak működni szám értékekre és kibővítik a típusrendszert.

Példa:
```C++
enum Color {
	Black = 0x000000, // hexadecimális szám literálok
	White = 0xffffff,
	Red   = 0xff0000,
	Green = 0x00ff00
	...
};
```

## Alapjául szolgáló típus<a id='enumtipus'></a>

Egész számot ábrázoló típusnak kell lennie, melyen elfér az összes enumerációs érték (általában `int`).

## Default értékek felsorolási elemeknek<a id='defaultenumertekek'></a>

Ha nem adunk konkrét értéket a felsorolási elemeknek, akkor azoknak a fordító nullától kezdődően generál értékeket.

Példa:
```C++
enum Gender {
	Male,  // ez 0 lesz
	Female // ez 1 lesz
};
```

# Osztályok - alapok

## Deklarálása, definíciója<a id='classes'></a>

Az objektum-orientált paradigma típus konstrukciói, melyek adattárolás mellett az azokon végzett műveleteket, algoritmusokat is definiálják és enkapszulálják.

Az osztály egy típust definiál. Az ilyen típusú változók definiálását példányosításnak nevezzük, magukat a változókat pedig példányoknak (instance) vagy objektumoknak (object).

Deklarációja:
```C++
class MyClass;
```

Definíciója:
```C++
class MyClass {
	/* tagok és típusok deklarációi és/vagy definíciói */
};
```

## class kulcsszó<a id='class'></a>

Ha a `class` kulcsszóval definiálunk egy osztály típust, akkor annak alapértelmezetten az összes tagja privát láthatóságú lesz (ha nem írunk ki láthatósági módosítót).

## struct kulcsszó<a id='struct'></a>

Ha a `struct` kulcsszóval definiálunk egy osztály típust, akkor annak alapértelmezetten az összes tagja publikus láthatóságú lesz (ha nem írunk ki láthatósági módosítót).

Figyelem: C-ben is létezik ez a kulcsszó, de ott egy sima C-s `struct`-ot definiál, ami sokban különbözik egy C++-os osztálytól (pl. csak adattagjai lehetnek, tagfüggvényei nem)!

## Reprezentáció a memóriában<a id='classmemory'></a>

A adattagok rendre, amilyen sorrendben deklarálva vannak az osztálydefinícióban, fognak szerepelni a példánynak lefoglalt memóriában:

```C++
class MyClass {
	int x;
	int y;
	char c;
};
...
MyClass obj;
```
A memóriában: `obj.x`, `obj.y` és `obj.c` egymás mellett lesznek ("hole"-ok esetleg lehetnek köztük a gépi szóhoz igazítás miatt).

Megjegyzés: Az adattagok összméreteiből ki lehet számolni az osztályunk példányának méretét (ezzel max néhány bájtot tévedhetünk a padding miatt). Ha az osztályunk adattagja is maga egy osztály, akkor annak is ki lehet számolni és így tovább (rekurzív módon), előbb-utóbb biztos, hogy alap típusokhoz jutunk, melyeknek az adott architektúrárán fix a mérete.

Megjegyzés: Ez a memóriakép C-s `struct` esetén is teljesen így működik.

## Adattag<a id='adattag'></a>

Osztályaink törzsében deklarált változókat adattagoknak (member variable) szoktuk nevezni.

## Konstans adattag<a id='konstadattag'></a>

`const` kulcsszóval ellátott adattag, mely sehol nem kaphat új értéket. Kötelező inicializálni őket a konstruktor inicializáló listájában.

## Statikus adattag<a id='staticadattag'></a>

Osztály szintű adattagot jelent, melyet a `static` kulcsszóval kell deklarálni. Ekkor nem fog rendelkezni minden osztályból példányosított objektum ilyen adattaggal, hanem helyette a statikus memóriában lesz elhelyezve ez az adattag, melyet közösen elérnek és használhatnak a példányok (sőt, ha az adattag láthatósága publikus, akkor kívülről is látható és használható lesz, hasonlóképpen, mint egy sima globális változó, csak prefixelni kell az osztály nevével: `MyClass::myStaticMember`).

Példa példány számlálásra:
```C++
class MyClass {
public:
	static int object_count; // ez csak deklaráció!

	MyClass() { ++object_count; }  // konstruktor
	~MyClass() { --object_count; } // destruktor
};

int MyClass::object_count = 0; // erre a definiálásra mindenképp szükség van!

std::cout << MyClass::object_count; // 0
{
	MyClass a; // létrehozunk egy példányt, lefut a default konstruktor
	std::cout << MyClass::object_count; // 1
	MyClass * b = new MyClass; // itt is, mint előbb, csak nem a stack-re, hanem a heap-re kerül
	std::cout << MyClass::object_count; // 2
	if (1) {
		MyClass c;
		std::cout << MyClass::object_count; // 3
	} // megsemmisül c, destruktor lefut
	std::cout << MyClass::object_count; // 2
	delete b; // megsemmisül b, destruktor lefut
} // megsemmisül a, destruktor lefut
std::cout << MyClass::object_count; // 0
```

Megjegyzés: Ezzel a megoldással az a probléma, hogy kívülről bárki át tudja állítani az `object_count`-ot, mondjuk így:
```C++
MyClass::object_count = 100;
```
Hogy lehetne ezt megakadályozni?

Megjegyzés: A példában látható módon - függvény vagy vezérlési szerkezet használata nélkül - tudunk üres blokkot (scope-ot) írni tetszőleges másik blokkon belül.

Megjegyzés: Egy adattag lehet egyszerre konstans és statikus is.

## Tagfüggvény<a id='tagfuggveny'></a>

Osztályaink törzsében deklarált függvényeket tagfüggvényeknek (member function) vagy metódusoknak (method) szokuk nevezni.

A nem-statikus (azaz nem osztály szintű) tagfüggvényeket mindig csak egy objektumon hívhatunk meg.

A tagfüggvények definícióját megírhatjuk a deklarációjukhoz még az osztálytörzsön belül, de akár külön, "később" is megírhatjuk, de ekkor jelezni kell az osztálynév prefixszel, hogy mely osztályhoz tartozó metódusról beszélünk:
```C++
// MyClass.h
class MyClass {
	void myMethod1() {...} // helyben definiáljuk is a tagfüggvényt
	int myMethod2(char); // a tagfüggvényt csak deklaráljuk
	...
};
```

```C++
// MyClass.cpp
#include "MyClass.h"

int MyClass::myMethod2(char ch) {...} // tagfüggvény definíció
...
```

Megjegyzés: A példában látott módon szokás egy fejállományba írni az osztálydefiníciót, melybe a tagfüggvényeknek csak a deklarációját adjuk meg (mint a `myMethod2` esetén), és egy külön forrásfájlba írni a tagfüggvények definícióját (törzsét). A forrásfájlba azonban be kellett, hogy include-oljuk a fejállományt, hogy az osztálydefiníciót "lássa". Ha bele gondolunk: fordításkor csak a forrásfájlt (.cpp) fogjuk lefordítani, de annak az elejére be lesz másolva a header-be írt kód. Ez a módszer azért is előnyös, mert így elég a fejállományt látnia az osztály használójának, a metódusok konkrét implementációja pedig el van különítve, "rejtve", egy külön fájlba, amivel a használónak nem kell foglalkoznia.

## Konstans tagfüggvény<a id='konsttagfuggveny'></a>

Konstans tagfüggvények garantálják, hogy nem változtatják meg a hívó objektum állapotát, azaz egyik adattagjának sem változtathatják meg az értékét. Konstans objektumokon (konstans változók) csak ilyen tagfüggvények hívhatók. Valamint konstans pointer által mutatott, és konstans referencia által hivatkozott objektumon is csak ilyen tagfüggvény hívható (mivel ennek a kettőnek garantálnia kell, hogy nem változtatják meg azt, amire mutatnak).

Egy tagfüggvény konstansságát úgy jelezhetjük, hogy a formális paraméter listája után kiírjuk a `const` kulcsszót a deklarációban és a definíciónál is:

```C++
class MyClass {
	int x; // ez privát, mert class kulcsszó lett használva
public:
	int getX() const { return x; } // getter konstans tagfüggvény
};
```

Megjegyzés: A getter metódusok tipikusan konstans tagfüggvények.

Megjegyzés: Konstruktor és destruktor nem lehet konstans tagfüggvény.

## Statikus tagfüggvény<a id='staticfuggveny'></a>

Osztály szintű tagfüggvényt jelent, melyet a `static` kulcsszóval kell deklarálni. Ekkor a tagfüggvényt nem objektumokon tudjuk
meghívni (nem lesz implicit `this` paramétere). Úgy fog funkcinálni, mint egy egyszerű globális függvény, csak a hívásához prefixelni kell a tartalmazó osztály nevével, pl. `MyClass::myMethod();` Ha privát (vagy védett) a láthatósága, akkor mondjuk nem fogjuk tudni meghívni csak az osztálynak (vagy annak egy gyerekének) másik tagfüggvényének törzsében.

Példa (statikus adattagos példa felokosítva):
```C++
class MyClass {
public:
	MyClass() { ++object_count; }  // konstruktor
	~MyClass() { --object_count; } // destruktor
	static int getObjectCount() { return object_count; } // publikus statikus tagfüggvény.
private:
	static int object_count; // privát statikus adattag
};

int MyClass::object_count = 0; // erre a definiálásra mindenképp szükség van! (ez megengedett)
...
```

Ezt követően úgy tudjuk használni a példányszám lekérdezést, hogy a `MyClass::getObjectCount()` statikus tagfüggvényt hívjuk meg, viszont kívülről nem fogjuk tudni átállítani az `object_count`-ot, hiszen privát adattag (nem látszódik kintről) és direkt nem lett hozzá írva setter sem.

Megtévesztő, de így is meg lehet hívni: `obj.getObjectCount();` ahol `obj` egy `MyClass` példány. De természetesen ekkor sem a példányon fut le a statikus tagfüggvény.

Megjegyzés: Tagfüggvény nem lehet egyszerre statikus és konstans, hiszen a statikus (vagy más néven osztály szintű) tagfüggvényeket nem is objektumokon hívjuk meg (nincs implicit `this` paraméter), így azok nyilván nem változtathatnak semmilyen objektum állapotán.

Megjegyzés: Konstruktor és destruktor nem lehet statikus tagfüggvény.

## this paraméter és const this<a id='this'></a>

Minden nem-statikus tagfüggvénynek van egy implicit `this` nevű paramétere. Ez mindig az osztályra mutató pointer típusú (például: `MyClass` esetén `MyClass *this`). Minden tagfüggvény-hívás esetén annak az objektumnak a címét tárolja, melyen meghívtuk a tagfüggvényt. A tagfüggvények törzsében pedig amikor meghivatkozunk egy nem-statikus tagot, pl. `myMember`, (legyen az akár adattag, akár tagfüggvény), akkor igazából a `this->myMember` lesz meghivatkozva.

Példa:
```C++
class MyClass {
	int _x, _y;
public:
	void f(int n) {...}
	void setXandY(int x, int y) {
		this->_x = x; // helyette elég: _x = x;
		this->_y = y; // helyette elég: _y = y;
		this->f(x);   // helyette elég: f(x);
	}
};
```

Konstans tagfüggvények esetén viszont a `this` egy konstans pointer, azaz: `const MyClass *this` típusú. Láthatjuk, hogy konstans tagfüggvények esetén a `this` pointer konstanssága garantálja, hogy nem kaphat az objektum egyik adattagja sem új értéket. Hiszen a `this->_x = 10;` értékadás nem megengedett (lásd: konstans pointerek).

## Privát láthatóság<a id='private'></a>

A privát láthatóságú adattagok kívülről nem láthatóak (még egy gyerekosztály sem látja, hogy megörökölte), csak az osztályunk tagfüggvényeinek törzsében hivatkozhatóak meg.

A szükséges ún. access modifier: `private:`

Megjegyzés: C++-ban nem kell minden tag elé kiírni, csoportos a módosító hatóköre, ami egészen egy új módosítóig tart.

## Publikus láthatóság<a id='public'></a>

A publikus láthatóságú adattagok kívülről is láthatóak, bárhonnan meg lehet őket hivatkozni.

A szükséges ún. access modifier: `public:`

Megjegyzés: C++-ban nem kell minden tag elé kiírni, csoportos a módosító hatóköre, ami egészen egy új módosítóig tart.

## Konstruktor<a id='konstruktor'></a>

Speciális tagfüggvény, mely az objektum létrehozásakor (más néven példányosításkor) fut le. Inicializálja az objektumnak allokált memóriaterületet. Visszatérési típusa nincsen, void-ot sem szabad kiírni!

Nevének meg kell egyeznie az osztálynévvel.

Explicit nem tudjuk meghívni, tulajdonképpen egy objektum létrehozásával "hívjuk" meg.

Ha mindegyik konstruktor privát vagy védett láthatóságú, akkor az osztályt nem lehet példányosítani.

## Inicializáló lista<a id='initlista'></a>

Csak konstruktorba lehet írni, a paraméterlista és a törzs közé. Itt inicializálhatjuk az adattagokat, konstans adattagokat kötelező is (nem lehet a konstruktor törzsében sem értéket adni nekik)!

Példa:
```C++
class MyClass {
	int _x;
	std::string _str;
public:
	MyClass(int x, const std::string& str) :
		_x(x),
		_str(str) // itt az std::string másoló konstruktora fog lefutni
	{
		...
	}
};
```

Szintén az inicializáló listában tudjuk meghívni szülőosztály paraméteres konstruktorát (lásd: öröklődés).

Fontos: Az adattagok inicializálása **nem** a lista sorrendje szerint fog történni, hanem az osztálytörzsben tett deklarációjuk sorrendjében! Ez fontos lehet pl. ilyen esetben:
```C++
class MyClass {
	int _y;
	int _x;
MyClass() :
	_x(42),
	_y(_x) // <-- ez fut le hamarabb, de itt _x még inicializálatlan!
	{
		...
	}
};
```

## Default konstruktor<a id='defkonstruktor'></a>

A paraméter nélküli konstruktort default konstruktornak nevezzük. Ha nem írunk egyetlen konstruktort sem, akkor a fordító generál nekünk egyet (ekkor minden adattagunkat default konstruálni fog, vagyis az ő default konstruktoraikkal fogja inicializálni őket).

Megjegyzés: A `MyClass::MyClass(int x = 10);` konstruktor deklaráció generálni fog nekünk paraméter nélküli konstruktort is (lásd: függvény túlterhelés default érték esetén), ezért lesz saját magunk által írt default konstruktor.

Fontos: Default konstruálás esetén **ne** írjunk ki üres zárójelet az objektum neve után, mert az függvény deklarációnak számítana!

Példa:
```C++
MyClass obj;     // default konstruálás (nincs üres zárójel)
MyClass obj(42); // paraméteres konstruktor hívás

MyClass obj(); // ez egy olyan függvényt deklarálna, aminek
               // obj a neve, MyClass a visszatérési típusa és nem vár
               // egyetlen paramétert sem!
```

## Implicit konverzió egyparaméteres konstruktorral<a id='konvkonstruktor'></a>

Ha írunk az osztályunknak egy 1 db paramétert váró konstruktort, akkor a paraméter típusa implicit konvertálható lesz az osztályunk típusává. Angol szakirodalomban: converting constructor.

Példa:
```C++
class Rational {
	int szaml;
	int nevezo;
public:
	Rational(int sz, int n) : szaml(sz), nevezo(n) {}
	Rational(int sz) : szaml(sz), nevezo(1) {}
	Rational() : szaml(1), nevezo(1) {}
	...
};

...

Rational x(10, 3); // 10/3 racionális szám
Rational y(8);     // 8/1 racionális szám, azaz 8
Rational z = 12;   // 12/1, itt az egyparaméteres konstruktor fog meghívódni a 12 paraméterrel
```

Továbbá:
```C++
void f(Rational r) {...}

f(42);
```
Lehet ilyet, mert `f` bár `Rational`-t vár, de a `42` `int` típusú, és a `Rational`-nak van olyan egyparaméteres konstruktora, ami `int`-et vár, ezért tud implicit konvertálódni. Ekkor az `f(42)` ekvivalens lesz ezzel: `f(Rational(42))`, itt a `Rational(42)` egy temporális objektum (jobbérték).

## explicit kulcsszó<a id='explicit'></a>

Ha az egyparaméteres konstruktor deklarációja elé kiírjuk az `explicit` kulcsszót, akkor azzal letiltjuk az előbb tárgyalt implicit konverziót.

Nem fog működni sem a `Rational z = 12;`, sem az `f(42);` példa.

Megjegyzés: Az esetek döntő többségében érdemes kiírni, mert nem szeretnénk az implicit konverziót lehetővé tenni. A `Rational` osztály épp egy ellenpélda erre.

Megjegyzés: Azért lehet ilyet:
```C++
std::string str = "hello";
```
mert az `std::string` osztálynak van olyan nem-explicit egyparaméteres konstruktora, ami `const char*`-ot vár paraméterül (`"hello"` típusa `const char[6]`, ami `const char*`-ra tud konvertálódni, lásd: literálok, pointerek és tömbök).

## Konverzió konverziós operátorral<a id='konvoperator'></a>

Az implicit konverziók egyik másik eszköze a konverziós operátor írása.

Példa (racionális példa kibővítése):
```C++
class Rational {
	int szaml;
	int nevezo;
public:
	Rational(int sz = 1, int n = 1) : szaml(sz), nevezo(n) {}
	...
	operator float() { return (float)szaml/(float)nevezo; }
	...
};

void print_float(float f) { std::cout << f << "\n"; }

Rational r(10, 3);
print_float(r); // működni fog, mert van imlpicit konverziós
                // operátor írva a Rational osztályhoz,
		// mely float-tal tér vissza.
```

Megjegyzés: Tetszőleges számú konverziós operátort írhatunk az osztályunkhoz, más-más típusokba való konvertáláshoz.

Megjegyzés: Ha a konverziós operátor elé kiírjuk az `explicit` kulcsszavat, akkor azzal implicit helyett egy explicit konverziós operátort definiálunk, mely esetben szintén lehet konvertálni, de csak ha explicit meghívjuk (kasztolunk), pl. `print_float((float)r);`

## Másoló konstruktor<a id='copykonstruktor'></a>

Azokat a konstruktorokat szoktuk másoló (vagy copy) konstruktornak nevezni, melyek egy másik példányra hivatkozó konstans referenciát várnak egyetlen paraméterül. Feladata, hogy egy másik példány adattagjait felhasználva egy másolatot példányosítson.

Ha nem írunk az osztályunkhoz, akkor a fordító fog generálni egyet (rekurzívan minden adattagnak a copy konstruktora lesz meghívva az inicializáló listában).

Példa:
```C++
class MyClass {
	int x; int y; std::string str;
public:
	MyClass(const MyClass& src) :
		x(src.x),
		y(src.y),
		str(src.str)
	{
		...
	}
};
```

Megjegyzés: Ha egy dinamikus memórát használó osztályunk van, akkor jóeséllyel szükségünk lesz saját magunknak definiálni copy konstruktort és értékadás operátort is, mert nem szeretnénk, hogy csak a dinamikus memóriára mutató pointereink másolódjanak default módon, hanem a teljes mutatott memóriaterületetről (pl. láncolt lista vagy bináris fa esetén) szeretnénk másolatot készíteni.

## Értékadás operátor<a id='ertekadasop'></a>

Hasonlít a másoló konstruktorra, de ez nem konstruktor egy új példány gyártásához, hanem egy már létező példánynak szeretnénk új értéket adni egy másik példány állapotát lemásolva.

Ezt is generál nekünk a fordító, ha mi nem definiálunk explicit (minden adattagnak értékül adja a forrás objektum megfelelő adattagját).

Konvenció: minden értékadás operátor (és társai, pl. `+=`, `*=`, `&=` stb.) térjen vissza a baloldali operandussal referencia szerint. Erre azért van szükség, hogy tudjuk láncolni az értékadásokat, azaz szerepelhessen egyik részkifejezésként egy másikban: `a = b = c;` zárójeleket kiírva: `a = (b = c);`

Szintén fontos: mindig ellenőrizzük le, hogy nem-e próbálunk egy objektumot önmagának értékül adni! Ha ezt nem kezeljük le, akkor nagyon súlyos és nehezen detektálható hibákhoz juthatunk!

Példa:
```C++
MyClass& operator=(const MyClass& rhs)
{
	if (this == &src)     // ha a hívó objektum címe ugyanaz mint a "right hand side" címe
		return *this; // akkor nem csinálok semmit, egyből visszatérek

	x   = src.x;   // átmásolom a másik objektum állapotát
	y   = src.y;
	str = src.str;

	return *this; // a this-t dereferálva megkapom a hívó objektumot,
	              // amiről egy referenciát adok vissza (lásd: visszatérési típus)
}
```

Megjegyzés: dinamikus memóriát kezelő osztályok esetén, a copy constructor-hoz hasonlóan, ezt is magunk kell definiálnunk, hiszen a fordító által generált az csak az adott pointer adattagot másolná le (memória címet), azt nem amire ő mutat! (lásd: shallow vs deep copy)

## Destruktor<a id='destruktor'></a>

Objektumunk megsemmisülésekor először ez a speciális tagfüggvény hívódik meg, ha definiálva van. Még azelőtt hívódik meg mielőtt megkezdődne az adattagok megsemmisítése.

Egyetlen egy lehet belőle.

Visszatérési típusa nincsen, `void`-ot sem szabad kiírni!

Nevének meg kell egyeznie a "~" jellel prefixált osztálynévvel.

Paramétert nem adhatunk neki (fordítási hibát okozna)!

Egy objektum megsemmisítésével "hívjuk" meg (dinamikus memória kezelése esetén a `delete` vagy `delete[]` operátorhívással, más esetekben pedig "magától meghívódik").

Akkor szükséges írnunk destruktort, ha pl. az osztályunk dinamikus memóriát kezel, mert akkor meg kell hívnunk az adattagként szereplő pointeren a `delete`/`delete[]` operátort! Erre azért van szükség, mert magának a pointer adattagnak a kitörlése esetén csak a pointer változó lesz törölve, az nem, amire ő mutat (eml.: nem is feltételezheti a fordító, hogy futási időben az adott pointer mutatni fog-e valamire a heap-en vagy sem...)

Példa:
```C++
Vector::~Vector()
{
	delete[] _bufferPtr;
}
```

Akkor szintén szükséges lehet saját destruktort írni, ha pl. valami fizikai erőforrást, pl. fájl deszkriptort, socket-et, adatbázis tranzakciót (lásd: RAII), kell lezárni, vagy esetleg loggolni szeretnénk valamit az objektum életciklusának végén.

Ha a destruktor privát vagy védett láthatóságú, akkor az osztályt nem lehet példányosítani.

## Rule of Three<a id='ruleofthree'></a>

Ha a másoló konstruktor, értékadás operátor és destruktor közül bármelyiket definiáljuk, akkor a másik kettőt is definiáljuk! Mert az esetek 99.99%-ban ha valamiért definiálni szükséges az egyiket, akkor a másik kettőt is kell!

Lásd: a három fogalomhoz írt dinamikus memória kezelés esetét.

Megjegyzés: modern C++-ban a "rule of five"-nak ugyanez a lényege és célja, csak kiegészül move konstruktorral és move értékadás operátorral (optimalizációs célból), de ezek a tárgy keretein kívül esnek, így őket nem kell ismerni.

## RAII<a id='raii'></a>

RAII = Resource Acquisition Is Initialization

A lényege az, hogy minden olyan erőforrást, amit le kell foglalnunk, majd fel kell szabadítani, egy osztállyal absztraktáljuk el oly módon, hogy az osztály inicializáláskor (konstruktor) lefoglal minden szükséges erőforrást, majd megsemmisüléskor (destructor) felszabadítja azokat. Így az erőforrások használati idejét szorosan összekötjük az objektumunk élettartamával.

Ha az objektum automata tárolású (hívási verembe írt változó), akkor az erőforrás automatiksan fel lesz szabadítva, amikor az objektum kikerül a scope-ból (pl. akkor is ha egy kezeletlen kivétel szakítja meg a scope-ot). Az erőforrás menedzsmenttel így nincs külön dolgunk, mert azt az osztály végzi elabsztraktálva. Ez egy nagyon erős garancia, így programunk sokkal biztonságosabb, valamint jobban skálázható és könnyebben maintain-elhető kódhoz jutunk.

Ilyen osztályok például az STL konténerek (dinamikus memóriát kezelnek helyettünk) vagy az `std::fstream` (fájldeszkriptort kezel).

Részletesebb leírás [itt](https://en.cppreference.com/w/cpp/language/raii).

## friend kulcsszó, barát függvény, barát osztály<a id='friend'></a>

Az osztályunk törzsén belül `friend` kulcsszóval deklarált "idegen" függvények és osztályok láthatják és meghivatkozhatják az osztály privát és védett láthatóságú tagjait is (annak ellenére, hogy ők nem az osztályhoz tartoznak, csak a "barátai").

Példa: Ki szeretnénk tudni íratni a saját `Person` példányunkat a megszokott `<<` operátor használatával. Ehhez az `operator<<`-nak barátfüggvénynek kell lennie, hogy lássa a privát tagokat.
```C++
class Person {
	std::string _name;
	int _age;
public:
	Person(const std::string& n, int a) : _name(n), _age(a) {}

	friend std::ostream& operator<<(std::ostream& out, const Person& person);
};

std::ostream& operator<<(std::ostream& out, const Person& person)
{
	out << "Name: " << person._name << ", " // a barátság miatt láthatja a privát
	    << "Age: " << person._age << "\n";  // _name és _age tagokat
	return out;
}
...
Person p1("Valaki", 24);
Person p2("Másik valaki", 39);

std::cout << p1 << p2 << "\n";

// azért kellett az std::ostream& referenciával visszatérni, hogy
// tudjuk így láncolni, záróleket kiírva: ((std::cout << p1) << p2) << "\n";

// output:
// Name: Valaki1, Age: 24
// Name: Másik valaki, Age: 39
```

Megjegyzés: Ez működne fájlba írással is, mert az `std::ofstream` típus az `std::ostream`-ből származik, ezért simán upcast-olható.

Megjegyzés: Adatok beolvasásához hasonlóan túlterhelhetjük a `>>` operátort is, mellyel pedig az `std::istream` típust használhatjuk (az `std::cin` olyan típusú globális objektum).

## Osztálytörzsben definiált "belső" típus<a id='belsotipus'></a>

Osztály törzsébe új típusdefiníciókat is írhatunk, melyek a következők lehetnek pl. típus szinoníma: `typedef`/`using`, másik osztálydefiníció: `class`/`struct`/`union`, felsorolási típus: `enum`.

Ezek teljesen hagyományos módon fognak típust definiálni, viszont a típusnevek a tartalmazó osztály neve alá fognak tartozni (névprefixileg), tehát prefixálni kell majd őket a külső oszály nevével.

Példa:
```C++
class MyClass {
	...
	class MyInnerClass {
		...
	};
	...
	typedef unsigned long long ULL;
	...
};

MyClass::MyInnerClass obj; // a belső osztály típusnevét így tudom meghivatkozni.
MyClass::ULL nagyszam;
```

Megjegyzés: Hasznos eszköze a típushierarchia megfelelő
modularizálásának és típusnevek enkapszulálásának (objektum-orientáltság).

Megjegyzés: láthatóság is hat rájuk. Egy másik példa:

```C++
class LinkedList {
private:
	struct Node {
		int data;
		Node *next;
	};
	...
public:
	...
}
```


# Osztályok - haladóbb fogalmak

## OOP röviden (motiváció)<a id='oop'></a>

A kódunkban az adatokat (változók) és az azokon végzett műveleteket, algoritmusokat (függvények) egy típusba, ún. osztályba csoportosítjuk. Így magas izoláció érhető el az objektumok között, jobban csoportosíthatók és áttekinthetők a kódban a felelősségek: minden osztály a saját adatát felelős kezelni. (Ennek szöges ellentétei a globális változók és a stand-alone függvények, melyeket a kódban bárhol elérünk/átírhatunk/meghívhatunk).

Az osztályok között persze szükség van valamennyi kommunikációra, melynek számos támogatott módja van: asszociáció (pl. tagfüggvény hívásokkal), aggregáció (tárolt pointer/referencia más osztály objektumára), kompozíció (hasonlóan, csak itt a saját élettartamunkkal összekötött a tartalmazott objektumé), öröklődés (kód újrafelhasználáshoz), stb.

Megjegyzés: Az öröklődési, illetve a tartalmazási relációkkal ún. osztály hierarchiát alakíthatunk ki.

Minden osztálynak van egy "publikus interfésze" - itt ez alatt a public adattagokra és tagfüggvényekre gondolunk - és egy rejtett, privát része. A "publikus interfész" biztosítja a kommunikációs felületet az osztály felhasználójának (ami tisztán OOP kódban szintén osztály lesz).

Célszerű az osztályok között ezt az érintkezési felületet minimumon tartani (más szóval: a kommunikáció keresztmetszetét minimalizálni). Ennek számtalan előnye van (néhol egyik következik a másikból):
* jobban elkülönülnek a kódban felelősségek, kevéssé függnek egymástól
* könnyebben belátható az osztály helyessége
* könnyebben tesztelhető (pl. unit tesztek)
* maintain-elhetőbb (ha később módosítani kell egy osztály kódján, akkor kisebb eséllyel törik el más kód és kisebb eséllyel kell belenyúlni a felhasználási helyekre is) -> időt, energiát és pénzt spórolunk
* robust-abb lesz a kódunk, könnyen refaktorálható és bővíthető
* ha megfelelően alkalmazzuk az öröklődést és az altípusos polimorfizmust (lásd kicsit később), akkor absztrakt funkciókhoz számos megvalósítást írhatunk, amik között szabadon, extra kölcségek nélkül váltogathatunk
* ...

A továbbiakban megnézzük, hogy a C++ milyen nyelvi elemekkel támogatja az említett elvek megvalósítását (a legtöbb eszköz más objektum orientált nyelvekben is megvan, kisebb-nagyobb különbségekkel).

## Getter, setter<a id='gettersetter'></a>

Getter: konstans tagfüggvény, mellyel adattagot tudunk lekérdezni:
```C++
int getX() const { return _x; }
```

Setter: tagfüggvény, mellyel adattagnak tudunk új értéket adni:
```C++
void setX(int x) { _x = x; }
```

Adatelrejtés elve (enkapszuláció): Az osztályaink tagjait írjuk privátra (kívülről ne látszódjanak). Ha mégis szükséges elérni valamely adattagokat, akkor írjunk nekik olvasáshoz gettert, ha pedig írni is akarjuk kintről, akkor settert. A segédmetódusokat, melyeket csak más metódusok használnak, írjuk szintén privátra.

Privát tag + getter-nek számos előnye van public taggal szemben:
* a tényleges reprezentáció nem látszik kívülről -> könnyebben átírható a külvilág "megzavarása" nélkül
* felelősség átvállalás: pl. típus invariáns betarttatását maga az osztály tegye (Pl. `Rational` osztályban a "nevező" adattagba soha ne kerülhessen 0)
* a setter dobhat akár kivételt is (pl. ha egy invariáns sérülne)
* ...

## Öröklődés szemantikája, szülő- és gyerekosztály<a id='oroklodes'></a>

Haszna:
* Kód újrafelhasználás: Ugyanazt ne implementáljuk többször, elég legyen egyszer megírni/review-zni/tesztelni, illetve csak egy helyen módosítani/refaktorálni később ha kell...
* Absztrakció: típusok között "is a" kapcsolat, absztrakt funkciók leírása + megvalósítások (ezeket lásd kicsit később).

Öröklődés esetén a szülöosztály (vagy ősosztály) összes tagja (adattagok és tagfüggvények egyaránt) részei lesznek a gyerekosztálynak (vagy leszármazott osztálynak).

Amik **nem** öröklődnek: konstruktorok, destruktor, értékadás operátorok, baráti kapcsolatok (friendship).

A privát tagok öröklődnek, de a gyerekosztály nem fogja látni őket (nem fog tudni róluk, így nem is hivatkozhatja meg őket). Bár konstruktor és destruktor nem öröklődik de meg lesz hívva objektum default konstruálása esetén a szülő default konstruktora, megsemmisülés esetén pedig a szülő destruktora.

Példa:
```C++
struct Animal {...};
struct Mammal : public Animal {...};
struct Dog : public Mammal {...};

Dog myDog; // default konstruálás esetén a következők fognak
           // lefutni ebben a sorrendben:
           // Animal def ktor, Mammal def ktor, Dog def ktor

           // megsemmisülés idején fordított a sorrend:
           // Dog dtor, Mammal dtor, Animal dtor
```

De mi a helyzet ha a szülőnek és/vagy a gyereknek paraméteres
konstruktorját szeretnénk meghívni (mert pl. csak olyan van neki)?

```C++
struct Animal {
	Animal(int x) {...} // Animal vár egy int-et
};

struct Mammal : public Animal {
	Mammal(int x) : Animal(x) {...} // Mammal vár egy int-et, amivel meghívja Animal ktorját
};

struct Dog : public Mammal {
	Dog(int x) : Mammal(x) {...} // Dog vár egy int-et, amivel meghívja Mammal ktorját
}
```

A példán láthatjuk, hogy a paraméteres szülő ktorokat a gyerek inicializáló listájában hívhatjuk meg.

Megjegyzés: A példákban azért a `struct` kulcsszavat használtam, hogy ne kelljen mindegyik konstruktora elé kiírni a `public:` módosítót.

Megjegyzés: Mindkét példában publikus öröklődés lett használva.

## Protected láthatóság<a id='protected'></a>

A `protected` (vagy védett) láthatóságú tagokat csak maga az osztály és annak leszármazottai látják.

## Publikus öröklődés<a id='publicoroklodes'></a>

A megörökölt tagok max láthatósága publikus lesz. Ekkor minden megörökölt tag láthatósága ugyanaz lesz a gyerekben, mint amilyen a szülőben volt.

Mindenki aki látja a gyerekosztályt és a szülőosztályt, tudni fog az öröklődésről (például menni fog az implicit upcast).

Megjegyzés: Legtöbb esetben ezt az öröklődést használjuk.

## Protected öröklődés<a id='protectedoroklodes'></a>

A megörökölt tagok max láthatósága védett lesz. Vagyis ami publikus volt, az a gyerekben védett lesz.

Csak a gyerek és annak a gyerekei fognak tudni az öröklődésről.

## Privát öröklődés<a id='privateoroklodes'></a>

A megörökölt tagok max láthatósága privát lesz. Azaz: `public` -> `private` és `protected` -> `private`.

Egyedül maga a gyerekosztály tud az öröklődésről.

Megjegyzés: Ha nem írjuk ki az öröklődésnél a láthatóságát, akkor alapértelmezetten privát lesz, pl.
```C++
class Child : Base {...}`
```

## Többszörös öröklődés<a id='tobbszorosoroklodes'></a>

A C++ támogatja a többszörös öröklődést. Ekkor ha például két szülő van, mindkettő összes megfelelő tagja meg lesz örökölve:

```C++
struct Student {
	void study();
	...
};

struct Teacher {
	void teach();
	...
};

struct Demonstrator : public Student, public Teacher {
	...
};
...

Demonstrator d;
d.study();
d.teach(); // mindkét metódus hívható, mert meg lettek örökölve
```

Vigyázat: Ha van ugyanolyan nevű/szignatúrájú tagja mindkét szülőnek, akkor azok duplán lesznek megörökölve és fordítási hiba lesz!

## Gyémánt öröklődés<a id='gyemantoroklodes'></a>

A többszörös öröklődésből adódó probléma. Ha van egy `GrandParent` osztály, amiből öröklődik `Parent1` és `Parent2`, valamint `Parent1` és `Parent2`-ből többszörös öröklődéssel öröklődik `Child`, akkor a `Child` duplán meg fogja kapni a `GrandParent` tagjait (mindkét szülői ágon). Ez persze fordítási hibához vezet.

Példa:
```C++
struct Person {
	std::string name;
	...
};

struct Student : public Person {
	void study();
	...
};

struct Teacher : public Person {
	void teach();
	...
};

struct Demonstrator : public Student, public Teacher {
	...
};
```

Fordítási hiba lesz mert `Demonstrator` az örökbített tagok tranzitivitása miatt két `name` adattaggal fog rendelkezni.

Megjegyzés: ebben a négy osztályos példában tisztán látszik a hiba, de a gyakorlatban sajnos sokszor sokkal bonyolultabb a helyzet. Például a konfliktus előjöhet egy 7 hosszú apai és 10 hosszú anyai ágon át. Arról nem is beszélve, ha nem csak kettő, hanem több osztályból öröklődünk többszörösen...

## Virtuális öröklődés<a id='virtualoroklodes'></a>

A virtuális öröklődéssel tudjuk elkerülni a gyémánt öröklődés problémáját. Ha a közbülső `Parent1` és `Parent2` osztályok virtuálisan öröklődnek a nagyszülő `GrandParent` osztályból, akkor a fordító garantálni fogja, hogy a `Child` csak egyik szülői ágon kapja meg a nagyszülő tagjait.

Példa:
```C++
struct Person {
	std::string name;
	...
};

struct Student : public virtual Person {
	void study();
	...
};

struct Teacher : public virtual Person {
	void teach();
	...
};

struct Demonstrator : public Student, public Teacher {
	...
};
```

OK, mert a közbülső osztályok viruálisan öröklődnek (`virtual` kulcsszóval), ezért a fordító csak az egyik ("anyai" vagy "apai") ágon fogja bemásolni a `name` tagot.

Megjegyzés: ennek azért vannak hátulütői:
* A virtuálisan örökölt szülők konstruktorai nem lesznek meghívva a gyerek osztályban (hiába hívják a közbülső osztályok), hiszen akkor többször is lefutna a nagyszülő konstruktora. Ezért annak meghívását manuálisan kell megtenni a gyerek init listájában.
* Ezért a gyerekosztály jobban fog függni a fölötte álló öröklődési hierarchia szerkezetétől és annak megváltozásától.
* A biztonságos konverziókért `dynamic_cast`-ot kell használni, aminek vannak futási idejű többletköltségei.
* Bonyolult és nagy `vtable`.
* Hiába van virtuális öröklődésünk, a gyakorlatban érdemes kerülni az olyan design-t, amihez ezt kéne használni. Sőt, általában magát az többszörös öröklődést is érdemes kerülni, mert csak több bonyodalomhoz vezethet, mint amennyi haszna van! (Anti-pattern). Nem véletlen van sok objektum orientált nyelv, ami nem is engedi ezt, pl. Java.

## Virtuális metódus<a id='virtualmetodus'></a>

A szülőosztályban definiált tagfüggvényeket felül lehet definiálni (új definíciót adni nekik) gyerekosztályban.

Ha a szülő osztályban használjuk a tagfüggvény deklarációjánál a `virtual` kulcsszót, akkor dinamikus kötést fogunk kapni.

Ez azt jelenti, hogy az olyan pointereken keresztül, melyek statikus típusa `Base*`, de a mutatott objektum egy `Child` típusú, a meghívott virtuális metódus a `Child` gyerekosztály megfelelő definícióját hívja meg. Az ilyen osztályokat polimorf ("többalakú") osztályoknak nevezik. Látható, hogy ez egy futási idejű (dinamikus idejű) mechanizmus.

Példákat lásd: kicsit lejjebb + órai anyagok között.

Megjegyzés: akit érdekel, hogy lehet ez leimplementálva, lásd: `vtable` és `_vptr` adattag...

## Tisztán virtuális metódus<a id='tisztanvirtualmetodus'></a>

Olyan virtuális metódus, melynek nem adunk definíciót.

Példa:
```C++
struct Shape {
	virtual int area() = 0; // nincs definíciója
	...
};

struct Rectangle : public Shape {
	int area() { return _width * _height; } // felüldefiniálja a metódust
	...
};
```

## Absztrakt osztály<a id='abstractosztaly'></a>

Azokat az osztályokat, melyeknek van legalább 1 tisztán virtuális metódusa, absztrakt osztályoknak nevezzük (előző példában a `Shape` ilyen). Absztrakt osztályt nem lehet példányosítani, `incomplete type` errort kapnánk!

## Interfész, implementáció<a id='interfaceimpl'></a>

Olyan absztrakt osztályokat nevezünk interfésznek, melyeknek célja, hogy a tisztán virtuális metódusaival egy felületet biztosítson funkciókhoz.

Megjegyzés: tipikusan azok a jó interfészek, melyekben nincs adattag és az összes metódusa public és tisztán virtuális.

Azokat az osztályokat, melyek interfészből öröklődnek és megvalósítják az összes metódust, implementációnak vagy megvalósításnak szoktuk nevezni.

Az interfész-implementáció kapcsolatokat elsősorban az altípusos polimorfizmussal karöltve fogjuk felhasználni (lásd: kicsit lejjebb).

# Unió típus

## union kulcsszó és unió szemantika<a id='union'></a>

C-ben is van, ott olyan C-s `struct`-ot definiál, melynek az összes mezője osztozik ugyanazon a memóriaterületen.

C++-ban egy olyan osztályt definiál, melynek az összes nem-statikus adattagja osztozik ugyanazon a memória területen, néhány megkötéssel kiegészülve: (ezeket nem fontos tudni)
* nem lehet virtuális tagfüggvénye
* nem lehet sem szülő-, sem gyerekosztály
* nem lehet nem-statikus referencia típusú adattagja
* stb...

Megjegyzés: Van még valamennyi létjogosultsága, de modern C++-ban (C++17-től) már inkább az [std::variant](https://en.cppreference.com/w/cpp/utility/variant)-ot célszerű hasonló dolgokra felhasználni.

# Polimorfizmusok összefoglalása

## Polimorfizmus jelentése<a id='polimorfizmus'></a>

A polimorfizmus szó "többalakúságot" jelent (általában valamilyen típuskonverziót, mely lehet implicit vagy explicit).

Négy fő fajtája van C++-ban.

## Altípusos/futási idejű polimorfizmus, upcast, downcast, statikus és dinamikus típus<a id='altipusospoli'></a>

Két osztály ha öröklődési kapcsolatban áll egymással, akkor a két típus konvertálódhat egymásba. A gyerek típus szülővé konvertálását upcast-nak (felfelé konvertálunk az öröklődési hierarchiában); a szülő típusről gyerekké konvertálást pedig downcast-nak (lefelé konvertálunk az öröklődési hierarchiában) nevezzük. Az upcast történhet implicit módon is, a downcast nem.

Példa:
```C++
class Animal {
	...
};

class Dog : public Animal {
	...
};

void eat(Animal a)
{
	...
}

void bark(Dog d)
{
	...
}

int main()
{
	Animal animal;
	Dog dog;

	eat(animal);  // OK, megfelelő a típus
	bark(animal); // Fordítási hiba, mert a függvény Dog-ot vár és nem Animal-t,
	              // nem lehet implicit downcast-olni

	eat(dog);  // OK, mert implicit megy az upcast szülő típusba
	bark(dog); // OK, megfelelő a típus
}
```

Logikus is a példa:
* enni minden állat tud (így a kutya is)
* ugatni a kutya tud, de más állat nem

Az öröklődést gyakran szokás "is a" kapcsolatnak is nevezni:<br>
Minden kutya egy állat, de nem minden állat egy kutya.

Ha kicsit mélyebben belegondolunk:
Egy `Dog`, mivel öröklődik az `Animal`-ből, rendelkezni fog az `Animal` minden tulajdonságával (adattagok + tagfüggvények), így fog tudni `Animal`-ként viselkedni, sőt még az öröklődés szemantikájából az is következik, hogy a memóriában egy `Dog` objektum pontosan az `Animal` osztályból megörökölt tagokkal fog kezdődni, így nyugodtan vehetjük ezt a `sizeof(Animal)` prefixet és rendben leszünk.\*

Fordított esetben már gondban lennénk: ha egy `Animal`-t próbálnánk meg `Dog`-ként kezelni (lehetnek hiányzó részek, ha `Dog` bármi plusz adattagot vagy tagfüggvényt bevezet), ezért sem megy implicit a downcast!

\*Kivéve ha mégsem: a levágódás (slicing) komoly gondot tud néha okozni ha pl. a nem levágott részen van egy pointer, ami egy levágott részre mutat, akkor az már szemét lesz -> undefined behavior. Ezért is célszerű polimorf osztály példányokat mindig pointer-ként átadni függvényeknek, hiszen akkor nem lesz semmiféle levágódás!

Egy másik példa, ami jól szemlélteti a futási időbeliséget:
```C++
class Shape {
	...
};

class Triangle : public Shape {
	...
};

class Rectangle : public Shape {
	...
};

Shape *sh; // pointer a szülőosztályra, statikus típusa Shape lesz
           // a pointer a kódban azzal van deklarálva

char choice;
std::cout << "What should I create?\n";
std::cin >> choice; // bolvasunk egy karaktert

if (choice == 't')
	sh = new Triangle; // dinamikus (futási) időben dől el -> dinamikus típus Triangle lesz
else if (choice == 'r')
	sh = new Rectangle; // dinamikus (futási) időben dől el -> dinamikus típus Rectangle lesz
else
	sh = nullptr;
...

if (sh)
	delete sh; // felszabadítjuk a dinamikus memória területet, ha lett lefoglalva
	           // emlékeztető: minden new operátornak kell, hogy legyen egy delete párja!
```

Megjegyzés: A C++ nyelvet statikusan típusosnak tekintjük, mert minden változó típusának fordítási (vagy más néven) statikus időben ismertnek kell lennie. Ez a futási idejű polimorfizmus az egyetlen kivétel alóla, viszont a nyelv szemantikája azért ezt erősen kontrollálja (pl. csak akkor fog működni, ha megvan a típusok között az öröklődési kapcsolat, szükségünk lesz pointerekre, dinamikus memóriára, stb.)

\+ A virtuális tagfüggvények felüldefiniálását is a futási idejű polimorfizmus részének tekintjük, hiszen az objektumunk dinamikus típusa fogja meghatározni futási időben, hogy milyen függvény törzs fog lefutni.

## Ad-hoc polimorfizmus (overloading)<a id='adhocpoli'></a>

A függvények és operátorok túlterhelését ad-hoc polimorfizmusnak is nevezzük (ezek is fordítási időben történnek, ezért a fordítási idejű polimorfizmusok egy fajtájának is tekinthetőek).

Lásd: függvény és operátor túlterhelés.

## Parametrikus/fordítási idejű polimorfizmus<a id='parametrikuspoli'></a>

A fordítási idejű polimorfizmus lényege, hogy egy egyszer megírt kódsablonból tudunk generálni különböző konkrét függvényeket/osztályokat (sablon paraméterek például típusnevek is lehetnek). Ezt C++-ban ún. template-ekkel tudjuk megoldani. A sablonparaméterek kiértékeléséből kapott kódgenerálást a fordító végzi fordítási (statikus) időben. Ezért nevezzük parametrikus vagy fordítási idejű (compile time) polimorfizmusnak.

Lásd: Sablonok kicsit később.

## Kasztolások<a id='kasztolasok'></a>

A C++ egy erősen típusos nyelv, sok konverziót csak explicit konvertálással lehet elérni.

Kasztolásnak (coertion polymorphism vagy "kikényszerített" polimorfizmus) nevezzük azt, mikor mi explicit módon konvertálunk egy objektumot másik típusúvá.

Lásd: Kasztolások.

# Kasztolások

## static_cast<a id='staticcast'></a>

Használható upcast és downcast-olásra, implicit kasztok kiírására, felsorolási típus konvertálására, jobbérték referenciákká konvertálásra, stb.

Futási időben már nem végez semmilyen ellenőrzés, hogy sikeres volt-e a konverzió, viszont így nem hordozza a `dynamic_cast` futási idejű költségeit.

Legtöbb esetben ezt a kasztolást szokták használni.

Példa:
```C++
int x = 10, y = 3;

std::cout << x/y; // out: 3, egészt osztottunk egésszel => törtrész elveszett

std::cout << static_cast<float>(x)/y; // out: 3.33333, float a számláló,
                                      // így nevező is promótálva lett azzá, törtrészt is megkaptuk
```

## dynamic\_cast<a id='dynamiccast'></a>

Csak polimorf objektumokra mutató pointerekkel és referenciákkal lehet használni. Tud upcast-ot és downcast-ot is polimorf osztályokon (olyan osztály, melynek van virtuális metódusa). Futási időben ellenőrzéseket végez, hogy sikeres volt-e a konverzió. Pointer konvertálásának sikertelensége esetén egy `nullptr`-t ad vissza; referenciává konvertálás sikertelenségekkor pedig egy null reference kivételt dob. Az előbbit egy `if`-fel, utóbbit egy `try`- `catch` blokkal tudjuk lekezelni.

Példa:
```C++
class Base {...};
class Child : public Base {...}

void f(Child *c) {...}

Base base; // szülő osztályt példányosítjuk
Child *child = dynamic_cast<Child*>(&base); // downcast-olunk szülő objektum címével
if (child) // ellenőrizzük, hogy sikeres volt-e a kasztolás, nem-e nullptr-t adott vissza
	f(child);
```

## reinterpret\_cast<a id='reinterpretcast'></a>

Tetszőleges pointer típust konvertál tetszőleges pointer típusra. Semmilyen ellenőrzést nem tesz sem fordítási, sem pedig futási időben. Szimplán másképpen fogjuk értelmezni a mutatott címen kezdődő bájtokat. Veszélyes, érdemes kerülni a használatát!

Példa:
```C++
class A {...};
class B {...};

A *a = new A;
B *b = reinterpret_cast<B*>(a);
```

Most `b` oda mutat, ahol az `A` típusú objektum van, de ha dereferáljuk, `B`-ként lesz értelmezve. Mivel `A` és `B` típusok között semmilyen kapcsolat nincs (jó eséllyel más-más lehet a méretük is), nem biztonságos `b`-t ezek után dereferálni!

Megjegyzés: nagyon ritkán van rá tényleges szükség. Csak akkor ajánlott használni, ha a programozó teljesen biztos benne, hogy valid a konverzió.

## const\_cast<a id='constcast'></a>

Ezzel a kasztolással tudjuk manipulálni a konstansságát egy mutatott objektumnak. Eltávolítani és hozzáadni is lehet vele konstansságot. Ezzel tudjuk elérni pl. hogy egy eredetileg konstans pointert átadjunk egy nem-konstans pointert váró függvénynek.

Példa:
```C++
void print(char *str) // ez a függvény egy nem-konstans pointert vár
{
	std::cout << str << "\n";
}
...

const char *c = "sample text"; // konstans pointer
print(c);                      // hiba: const char* -> char* konverzió, const nem veszhet el!
print(const_cast<char*>(c));   // a const_cast-tal levesszük a konstansságot, így már OK
```

Figyelem: Ez a példa azért működik, mert a `print()` függvény nem változtatja meg mutatott memóriaterületet. Ha a függvény mégis át próbálná írni, akkor az nem definiált viselkedéshez vezetne!

Ezért ezt a kasztot se használjuk! Ilyen esetben a helyes megoldás, hogy a `print()` függvényt írjuk át, hogy `const char*`-ot várjon.

Megjegyzés: akkor lehet indokolt a használata, ha például:
* Az eredeti változó (memória terület) **nem** `const`, viszont egy pointer/referencia ami arra mutat `const`. Ez esetben biztonságosan leszedhetjük az adott pointerről/referenciáról a `const` qualifier-t
* Egy 3rd-party lib-et használunk, melyet nem akarunk/tudunk módosítani és teljesen biztosak vagyunk benne, hogy nem vezet minket undefined behavior-höz.

Megjegyzés: a `volatile` kulcsszó is módosítható ezzel a cast-tal.

## Legacy kasztolás (C-szerű és függvényszerű szintaxis)<a id='legacycast'></a>

A `static`-/`dynamic`-/`reinterpret`-/`const_cast` kasztoló operátorok mellett használhatjuk a C-ből megszokott kasztolást is. Ennek két egyszerű szintaxisa is van:
```C++
double x = 3.14;
int y = (int)x; // C-szerű, ezt a nyelv a C-ből örökölte (visszafelé kompatibilitás!)
int z = int(x); // függvény-/típus konstruktor-szerű szintaxis
```

Ez a kasztolási módszer még egyszerű primitív típusokhoz megfelelő eszköz lehet, de bonyolultabb - pl. polimorf osztályok konvertálásához - már veszélyesebb megoldás. Képes a négy kasztoló operátor összes konvertálását megtenni, de nem túl egyszerűen definiált, hogy "mikor melyikként fog lefutni". Veszélyes a használata, nem végez pointer konvertálás esetén semmilyen ellenőrzést. Érdemes a négy kasztoló operátor valamelyikét használni, mert akkor egyértelműen tudhatjuk, hogy hogyan fog működni a konvertálás, biztonságosabb.

Megjegyzés: a többi kasztoló operátor "csúnyább", de az olyan kód, melyben sok kasztolgatásra van szükség, eleve gyanús kód. A nevesített kasztok kiírása viszont nem tud olyan jól "elbújni" a kódban. Pl. egy `reinterpret_cast<SomeType*>(obj)` erkölcstelenség sokkal könnyebben szemet szúr, mint egy `(SomeType*)obj` (ami ugyanúgy erkölcstelen). Emellett persze sokkal könnyebben kereshetők is a nevesített kasztok a kódban, mint a C-szerű. (Hogyan lehetne C-szerű kasztra greppelni, ami nem dobna ki egy csomó false pozitívat?)

# Funktorok

## Funktor<a id='funktor'></a>

Funktornak nevezzük az olyan típusú objektumokat, melyekhez lett definiálva `operator()` (gömbölyű zárójel operátor).

Ezeket az objektumokat használhatjuk függvény-szerű szintaxissal, "meghívhatjuk őket", (az `operator()` fog lefutni). Abban többek az egyszerű függvényeknél például, hogy ők állapotot is képesek megőrizni, öröklődhetnek egymásból, stb.

Példa:
```C++
class Prefixer {
	std::string _prefix;
public:
	Prefixer(const std::string& p) : _prefix(p) {}

	void setPrefix(const std::string& p) { _prefix = p; }

	void operator()(std::string& str) { str = _prefix + str; } // ref. szerinti átadás
};

Prefixer prefix_with_king("King "); // objektum példányosítás

std::string name = "Kong";

prefix_with_king(name); // úgy használjuk az objektumot, mint egy függvényt

std::cout << name; // out: King Kong

// később a setPrefix-szel meg is változtathatjuk a használt prefixet...
// tudunk más-más prefixer objektumokat is létrehozni...
```

## Predikátum<a id='predikatum'></a>

Azokat a funktorokat, melyeknek az `operator()` operátora `bool` típussal tér vissza predikátumoknak szoktuk nevezni.

Példa:
```C++
class IsDisivisbleBy {
	int divider;
public:
	IsDisivisbleBy(int d) : divider(d) {}

	bool operator()(int num) { return num % divider == 0; } // maradékképző operátor
};

IsDisivisbleBy isEven(2);
IsDisivisbleBy isDivisibleByThree(3);

isEven(-4);             // true
isEven(13);             // false
isDivisibleByThree(20); // false
isDivisibleByThree(99); // true
```

Megjegyzés: az STL-es adatszerkezetek/algoritmusok gyakran várnak ilyen típusokat sablonparaméter listájukban (lásd később).

# Sablonok

## Generikus programozás<a id='generikusprog'></a>

A lényege, hogy egy általános algoritmus (függvény) vagy adatszerkezet (osztály) szkeletont írhatunk, mely több - paraméterként kapott - típussal is létrehozható. A függvénysablon vagy osztálysablon alapján a fordító (fordítási időben) képes legenerálni a megfelelő sablon behelyettesítést létrehozva a kívánt kódot, melyet utána konvencionálisan lefordít.

## Sablonparaméter lista, template, class, typename kulcsszavak<a id='sablonparamlista'></a>

Osztály sablon vagy függvény sablon írásához elé kell írnunk a `template` kulcsszavat, melyet egy sablonparaméter listának kell követnie. Sablonparaméter lehet egy típusnév vagy a következő típusú változók egyike: integrális típus (pl. char, bool, int, stb.), pointer (objektumra vagy függvényre), balérték referencia vagy tagra mutató pointer.

Példa:
```C++
template <typename T1, typename T2, int I>
```

Megjegyzés: A `typename` kulcsszó helyett `class`-t is írhattunk volna a listába, a kettőnek teljesen ugyanaz a jelentése ebben a kontextusban.

## Default template argumentum<a id='deftemplatearg'></a>

Sablonparaméternek alapértelmezett értéket is írhatunk. Itt is ügyelni kell rá, hogy a default értékekkel ellátott argumentumok a lista jobboldalán álljanak.

Példa:
```C++
template <typename T1, typename T2 = bool, int I = 10>
```

## Függvény sablon<a id='fuggvenysablon'></a>

Függvény sablonokkal elérhetjük, hogy csak egyszer kelljen megírni egy algoritmust, melyet majd számos típussal fogunk tudni használni.

Példa:
```C++
template <typename T>
T max(const T& x, const T& y) {
	return (x < y ? y : x);
}

std::cout << max<int>(11, 23);
// a fordító legenerálja a függvény kódját T helyére int-et helyettesítve

std::cout << max<float>(3.14f, 10.1f);
// itt T=float a helyettesítés

std::cout << max<long long>(39348273498LL, 213213432389234LL);
```

Megjegyzés: Itt akár el is hagyhattuk volna a sablonparaméterek kiírását, mert a fordító ki tudta volna következtetni a parméterek típusaiból, tehát elég lett volna: `max(11, 23)`, `max(3.14f, 10.1f)`,...

Megjegyzés: A kódgenerálás csak akkor fog leforduló kódot eredményezni, ha a `T` típus helyére olyan típust adunk meg a sablonparaméter listában, melyhez van definiálva `operator<`, mivel a függvény törzs itt azt használja.

## Osztály sablon<a id='osztalysablon'></a>

Osztály sablonokkal generikus adatszerkezeteket hozhatunk létre, például olyan konténereket, melyek tetszőleges típusú elemeket tartalmazhatnak.

Példa: Az `std::vector` is egy osztály sablon, használata:
```C++
std::vector<int> vi = { 10, -20, 30 };
std::vector<char> vc = { 'a', 'b', 'c'};
std::vector<std::string> vs = { "hello", "szia", "C++"};
...
```

Lásd: [vector\_template példa](peldak/vector_template).

## Template specializáció<a id='templatespec'></a>

Osztály sablonok és függvény sablonok esetén is meg lehet oldani, hogy egy-egy konkrét esethez (azaz egy-egy konkrét paraméterhez) külön kódot írjunk. Ezt template specializációnak nevezzük.

Példák:
* Template metaprogramozásos példa (lejjebb).
* [specialized\_array.cpp](2021_osz/ora_12/specialized_array.cpp)

Megjegyzés: osztály sablonokhoz ún. parciális template specializációt is lehet írni, mely esetben valamennyi sablonparamétert leszögezünk, a többit paraméternek hagyjuk...

## Template metaprogramozás<a id='templatemetaprog'></a>

A C++-os template-ekkel fordítási idejű programozást lehet elérni, amikor a kívánt számítást elvégeztetjük a fordítóval.

A következő egy egyszerű példa erre:
```C++
template <int i> // az int egy integrális típus, ezért lehet template paraméter int típusú
struct Fact {
	static const int value = i * Fact<i-1>::value; // itt osztály törzsben inicializálni csak static
};                                                     // const adattagokat lehet

template <> // template specializáció, megadjuk egy konkrét "eset" (sablonparaméter) esetén az osztálytörzset
struct Fact<0> {
	static const int value = 1; // ez lesz a rekurzió alapesete
};

std::cout << Fact<4>::value; // 24
std::cout << Fact<10>::value // 3628800, a fordító legenerálja a Fact<10>, Fact<9>,..., Fact<0> osztályokat
```

Megjegyzés: Itt fordítási időben számoltatjuk ki a 4! és a 10! értékeket a fordítóval, futási időben már csak az értékek kiíratása fog megtörténni (ami konstans idejű művelet).

Előny: gyors futási idő; helytelen kód (ami végtelen rekurziót okozna) le se fog fordulni, mivel maga a fordító fog elszállni.

Hátrány: Fordítási idő nagyobb (sok osztályt kell a fordítónak legenerálnia és lefordítania); statikus időben ismertnek kell lennie a paramétereknek, nem függhetnek pl. user input-tól; bonyolult kód, nehezen megfejthető hibaüzenetek, nemigen lehet debuggolni.

Megjegyzés: ez csak egy nagyon dummy példa. Nyilván nem életszerű, hogy faktoriális számolásra valaki ilyet használjon, ugyanakkor rengeteg helyen használnak template metaprogramozást a gyakorlatban: STL, boost,... (akit érdekel a téma, az Interneten rengeteg példát találhat).

# Iterátorok

## Iterátor fogalma<a id='iterator'></a>

Az iterátor típusok célja, hogy egységes módon végig tudjuk haladni tetszőleges (akár nem szekvenciális struktúrájú) adatszerkezetek elemein.

Az STL (Standard Template Library) konténer típusai mind definiálnak saját iterátor típusokat a megfelelő műveletekkel, hogy végig
tudjunk iterálni rajtuk egy általános, konvencionális, sémát követve.

Részletek: https://www.cplusplus.com/reference/iterator/

## Output iterátor<a id='outputiterator'></a>

Olyan iterátor, mellyel csak olvasni tudjuk az elemet, amin éppen rajta áll.

## Input iterátor<a id='inputiterator'></a>

Olyan iterátor, mellyel írni is tudjuk az elemet, amin éppen rajta áll.

## Forward iterátor<a id='forwarditerator'></a>

Olyan iterátor, mellyel tudunk előre lépni az adatszerkezetben a `++` operátort használva.

Példa: Egyirányú láncolt listának van ilyen iterátora.

## Bidirectional iterátor<a id='bidirectionaliterator'></a>

Tud mindent, amit a Forward, emelett: visszafelé is tudunk lépni az adatszerkezetben a `--` operátort használva.

Példa: Kétirányú láncolt listának van ilyen iterátora.

## Random Access iterátor<a id='randomaccessiterator'></a>

Tud mindent, amit a Bidirectional, emelett: garantálja, hogy konstans idő alatt el tudja érni tetszőleges indexű elemet (tud ugrani). Ehhez a `+`, `-`, `+=`, `-=` operátorokat használja. (Illetve az ilyen adatszerkezetek konvencionálisan szoktak `operator[]`-t is definiálni).

Példa: Tömb alapú adatszerkezeteknek lehet ilyen iterátora.

## Konstans iterátor<a id='konstansiterator'></a>

Output iterátort valósít meg. A `*` operátort meghívva rajta konstans referenciát kapunk, ezzel garantálja a read-only-ságot.

## Reverse iterátor<a id='reverseiterator'></a>

Olyan iterátor melynek a megnövelésével, `++`, az adatszerkezetben visszafelé lépünk (fordított az iránya).

## begin, cbegin, rbegin, crbegin metódusok<a id='begin'></a>

Ezeket a metódusokat kell megvalósítania az adatszerkezetnek, hogy a megfelelő típusú iterátorokat használhassuk vele:
* `begin()` - visszatér egy iterátorral, ami az első elemen áll.
* `cbegin()` - visszatér egy konstans iterátorral, ami az első elemen áll.
* `rbegin()` - visszatér egy reverse iterátorral, ami az utolsó elemen áll.
* `crbegin()` - visszatér egy konstans reverse iterátorral, ami az utolsó elemen áll.

## end, cend, rend, crend metódusok<a id='end'></a>

Ezeket a metódusokat kell megvalósítania az adatszerkezetnek, hogy a megfelelő típusú iterátorokat használhassuk vele.
Az adatszerkezet végét egy extremális "utolsó utáni" elemmel jelöljük, ami a gyakorlatban egy olyan iterátor példány, ami már nem valid elemen áll (így onnan ne is próbáljunk `*`-gal elemet kiolvasni).
* `end()` - visszatér az adatszerkezet végén álló iterátorral.
* `cend()` - visszatér az adatszerkezet végén álló konstans iterátorral.
* `rend()` - visszatér az adatszerkezet elején álló reverse iterátorral.
* `crend()` - visszatér az adatszerkezet elején álló konstans reverse iterátorral.

## ++, --, \*, ==, != operátorok használata iterátorokkal<a id='iteratoroperatorok'></a>

A megfelelő iterátor típusoknak meg kell valósítania a nekik megfelelő operátorokat.
* `operator++` - előre lépteti az iterátort az adatszerkezetben.
* `operator--` - hátra lépteti az iterátort az adatszerkezetben.
* `operator*` - lekérdezi az elemet, amin az operandusként szereplő iterátor áll: konstans iterátor esetén egy konstans referenciát ad vissza az adott elemről, sima iterátor esetén sima (írható) referenciát.

Két iterátort össze is kell tudnunk hasonlítani az `operator==` és a `operator!=` operátorokkal (lásd: pl. ciklusos használat).

Minél "fejlettebb típusú" iterátort akarunk megvalósítani, annál több műveletet kell definiálni. Pl. egy Random Access iterátornak kell `<`, `>`, `<=`, `>=` összehasonlító műveletek is sok más mellett...

Lásd: https://www.cplusplus.com/reference/iterator/RandomAccessIterator/

Például innen is látszik, hogy tömb alapú adatszerkezetnek lehet ilyen iterátora, de egy láncolt listásnak lehetetlen.

## Használata<a id='iteratorhasznalat'></a>

```C++
std::set<int> mySet; // halmaz típus, ami int objektumokat fog tárolni

... // feltöltjük a halmazt

typename std::set<int>::const_iterator it = mySet.cbegin();
while (it != mySet.cend()) {
	std::cout << *it << "\n";
	++it;
}
```

Iterálás for ciklussal:
```C++
for (typename std::set<int>::const_iterator it = mySet.cbegin(); it != mySet.cend(); ++it) {
	...
}
```

Megjegyzés: A `typename` kulcsszót nem mindig kötelező kiírni, de azért lehet rá szükség, hogy egyértelműsítsük, hogy egy belső típus nevét akarjuk meghivatkozni és nem egy statikus tagot (lásd: osztály belső típusainak és statikus tagoknak szintaxisa). [Példa](2021_osz/ora_13/typename.cpp)

Fontos: Konstans objektumon csak `const_iterator`-ral tudunk végig iterálni, mert csak azok garantálják a read-only elem elérést, hogy ne sértsük az adatszerkezet konstansságát!

# STL

## Adatszerkezetek<a id='adatszerkezetek'></a>

Szekvenciális konténerek
* [array](https://cplusplus.com/reference/array/array/) : Wrapper osztály statikus tömbhöz, elem lekérdezése konstans idejű, új elemet nem lehet beszúrni.
* [vector](https://cplusplus.com/reference/vector/vector/) : Változtatható méretű tömböt valósít meg, dinamikus tömbbel, elem lekérdezése konstans idejű.
* [deque](https://cplusplus.com/reference/deque/deque/) : Kétvégű sor, olyan mint a vektor, de az elejére is lehet beszúrni, elem lekérdezése konst. idejű.
* [forward\_list](https://cplusplus.com/reference/forward_list/forward_list/) : Egyirányú láncolt lista, legtöbb művelet lineáris idejű.
* [list](https://cplusplus.com/reference/list/list/) : Kétirányú láncolt lista, legtöbb művelet lineáris idejű.

Adapter konténerek
* [stack](https://cplusplus.com/reference/stack/stack/) : Vermet valósít meg, csak a legutoljára hozzáadott elemet lehet lekérdezni és levenni róla (FILO).
* [queue](https://cplusplus.com/reference/queue/queue/) : Sort valósít meg, csak a legrégebben hozzáadott elemet lehet lekérdezni és kivenni belőle (FIFO).
* [priority\_queue](https://cplusplus.com/reference/queue/priority_queue/) : Prioritásos sort valósít meg, a legelső elem mindig a legnagyobb elem.

Asszociatív konténerek (minden érték kulcs szerint összehasonlítható, kulcs szerint rendezettek)
* [set](https://cplusplus.com/reference/set/set/) : Halmazt valósít meg, minden elem egyedi, bináris keresőfa van alatta, legtöbb művelet log(n).
* [multiset](https://cplusplus.com/reference/set/multiset/) : Multiplicitásos halmazt valósít meg.
* [map](https://cplusplus.com/reference/map/map/) : Szótár adatszerkezetet valósít meg, minden elem egyedi, bináris keresőfa van alatta.
* [multimap](https://cplusplus.com/reference/map/multimap/) : Multiplicitásos szótár adatszerkezetet valósít meg.

Rendezetlen asszociatív konténerek (minden érték kulcs szerint összehasonlítható, nincs rendezve)
* [unordered\_set](https://cplusplus.com/reference/unordered_set/unordered_set/) : A set rendezetlen változata.
* [unordered\_multiset](https://cplusplus.com/reference/unordered_set/unordered_multiset/) : A multiset rendezetlen változata.
* [unordered\_map](https://cplusplus.com/reference/unordered_map/unordered_map/) : A map rendezetlen változata.
* [unordered\_multimap](https://cplusplus.com/reference/unordered_map/unordered_multimap/) : A multimap rendezetlen változata.

Részletek: https://www.cplusplus.com/reference/stl/

## Algoritmusok<a id='algoritmusok'></a>

* [find](https://cplusplus.com/reference/algorithm/find/) : Keresést valósít meg, iterátorokkal "-tól -ig"
* [find\_if](https://cplusplus.com/reference/algorithm/find_if/) : Feltételes keresést valósít meg, iterátorokkal "-tól -ig"
* [sort](https://cplusplus.com/reference/algorithm/sort/) : Rendezést valósít meg, iterátorokkal "-tól -ig"
* ...

Összesen több, mint 80 gyakran használt algoritmus helyes és hatékony implementációját tartalmazza!

Teljes lista és részletek: https://www.cplusplus.com/reference/algorithm/

## Egyenlőség<a id='egyenloseg'></a>

Két változót (legyenek azok akár primitív, akár összetett típusok) akkor nevez a szabvány egyenlőnek, ha rajtuk meghívva az `operator==`-t igaz értéket kapunk. Osztályok esetén alapértelmezetten az összes adattagot ezzel hasonlít össze. Ez alapesetben a két változó bájtreprezentációjának bitenkénti egyezését jelenti, de az `operator==` felüldefiniálhatósága miatt ez mást is jelenthet.

Például ha két láncolt listát akkor szeretnénk egyenlőnek nevezni, ha ugyanolyan hosszúak és elemeik rendre egyenlőek, akkor felül kell definiálnunk ezt az operátort. Ez azért szükséges, mert amit a fordító generál nekünk, az a két listacímet (kezdő vagy fejelem címe) - mint adattag értékeket - hasonlítaná össze és mindig hamisat adna két különbőző objektum esetén.

## Ekvivalencia<a id='ekvivalencia'></a>

A standard szerint `a` és `b` változók ekvivalensek, ha igaz rájuk, hogy:
```C++
!(a < b) && !(b < a).
```
Ehhez persze összehasonlíthatónak kell lennie a típusnak az `operator<` által.

Az asszociatív konténerek (pl. `std::set` vagy `std::map`) ezzel az operátorral hasonlítják össze az elemeiket. Ezért ha egy már meglévő elemmel ekvivalenset (nem kell egyenlőnek lenniük!) szeretnénk beszúrni a halmazba, azt ő nem fogja beletenni.

Példa:
```C++
struct Person {
	int id;
	std::string name;
	unsigned int age;
};
```

Ilyen típusú objektumokat szeretnénk egy halmazba tenni úgy, hogy a halmazban minden embernek egyedi azonosítója legyen.

Megoldás #1: túlterheljük az `operator<`-t a típushoz:
```C++
bool operator<(const Person& p1, const Person& p2) {
	return p1.id < p2.id;
}

std::set<Person> s = { /* Person objektumok listája */ };
```

Megoldás #2: átadunk egy összehasonlító funktor típust az `std::set` sablonparaméter listájában:
```C++
struct CmpPerson {
	bool operator()(const Person& p1, const Person& p2)
	{
		return p1.id < p2.id;
	}
}; // ez egy predikátum, lásd: funktorok, predikátumok

std::set<Person, CmpPerson> s = { /* Person objektumok listája */ };
```

Megjegyzés: Ha nem adunk át második sablonparamétert, akkor az default-olni fog az `std::less`-re, ami pedig az `operator<`-t hívja meg. Ezért működik a #1 megoldás is.

# Kivételkezelés

## kivétel<a id='kivetel'></a>

C++-ban kivétel tetszőleges típusú objektum lehet (akár `int` vagy egy pointer típus is). A standard könyvtárban van egy `std::exception` és egy `std::runtime_error` típus (valamint pár leszármazott), melyeket használhatunk, akár származtathatjuk is saját kivétel típusainkat belőle.

## kivétel dobás, throw kulcsszó<a id='throw'></a>

Kivételt a `throw` kulcsszóval dobhatunk. Ekkor terminál a függvényünk, visszatér a vezérlés a hívóhoz (stack unwinding), ahol ha nem kapjuk el (`catch`) a kivételt, akkor mégfeljebb lesz dobva. Ha a hívási verem egyik függvénye sem kapja el a kivételt, akkor azt kezeletlen kivételnek (unhandled exception) nevezzük és a teljes programunk hibakóddal történő terminálásához fog vezetni.

## kivétel elkapás, try blokk, catch ágak<a id='catch'></a>

Kivételek elkapásához `try` blokkot és `catch` ágakat kell írnunk. A `try` kulcsszavat követő blokkba írt kód ha kivételt dob, akkor a megfelelő `catch` ággal tudjuk azt lekezelni a típusától függően.

Példa:
```C++
try {
	...
}
catch(const DivisionByZero& e) {
	std::cerr << "Division by zero!" << std::endl;
}
catch(const MemoryError& e) {
	std::cerr << "Memory error!" << std::endl;
}
catch(...) { // ez bármilyen kivétel típusra illeszkedni fog
	std::cerr << "An unknown exception occured!" << std::endl;
}
```

Ha az egyik ág illeszkedik és lefut, akkor a többi már nem is lesz tesztelve.

Megjegyzés: Ha egy elkapott kivételt tovább szeretnénk dobni (feljebb a hívási veremben), akkor azt a `catch` ágba írt `throw;`-val érhetjük el (rethrowing).

Megjegyzés: Saját kivétel típusainkat érdemes lehet öröklődési hierarchiába szervezni, a `catch(const ParentExcetion& e){...}` el fogja kapni a `Child1Exception`, `Child2Exception`, `Child3Exception` kivételeket is (ha mind publikusan öröklődik a `ParentExcetion`-ből), hiszen az implicit upcast gond nélkül megtörténik (sőt, a várt kivétel akár több szinttel, "generációval", is feljebb lehet, mint a dobott kivétel, nagyszülő osztályra is upcast-olni fog).

Megjegyzés: C++-ban nincsen finally blokk! (Ez egy design decision volt: inkább a RAII elvre hagyatkozzunk, azaz a `try` blokkban élő objektumok pucolják ki maguk után az őáltaluk használt erőforrásokat automatikusan megsemmisüléskor - lefut a destruktoruk akkor is ha exception miatt terminál a függvény - minthogy arra hagyatkozzunk, hogy a programozó odatesz egy megfelelő finally blokkot megfelelő tartalommal...)

# Egyéb

## Zero cost abstraction<a id='zcostabstraction'></a>

A C++ egyik design alapelve, hogy a hatékonyságot megőrizze, így igyekszik a legtöbb feature-t ún. zéró költségű absztrakciókkal megoldani.

* **Absztrakció:** komplexitás elrejtése.
* **Zero cost:** Nincs futási idejű overhead (fordítási idejű megengedett).

Tipikus példái ennek a sablonok. A fordítási komplexitást jelentősen megnövelik, futási időben viszont már nem történik semmiféle "template lookup" vagy hasonló. A generált kód ugyanolyan hatékony, mintha kézi másolás-beillesztéssel duplikáltuk volna le kódunkat különböző típusokra.

Ellenpéldául szolgál az altípusos polimorfizmus, hiszen ott a futási időben eldőlő dinamikus típusok szerint kell különböző virtuális táblákban (vtable) tárolt függvény címekre átkötni a virtuális mutatókat (vptr), illetve a velük kapcsolatos ellenőrzéseket megtenni (lásd: dynamic_cast). Emiatt kevésbé hatékony a nyelv a C-nél? Nem, mert ha ugyanilyen szemantikát szeretnénk elérni, akkor C-ben is szükségünk lenne erre az overhead-re annyi különbséggel, hogy nekünk kéne kézzel megírni ezt a virtuális táblás mechanizmust. Megoldás? Ha nagyon hatékonyság kritikus kódot szükséges írnunk, akkor kerüljük a virtuális függvények és altípusos polimorfizmus használatát.

