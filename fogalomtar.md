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

[Kidolgozás a fogalomtárhoz](fogalomtar_kidolgozott.md)

----

# Alapfogalmak
* [Deklaráció](fogalomtar_kidolgozott.md#deklaracio)
* [Definíció](fogalomtar_kidolgozott.md#definicio)
* [Fordítási egység](fogalomtar_kidolgozott.md#forditasiegyseg)
* [One Definition Rule (ODR)](fogalomtar_kidolgozott.md#odr)
* [static kulcsszó (globális változóknál és függvényeknél)](fogalomtar_kidolgozott.md#static)
* [extern kulcsszó](fogalomtar_kidolgozott.md#extern)
* [Típusrendszer](fogalomtar_kidolgozott.md#tipusrendszer)
* [Statikusan típusos nyelv](fogalomtar_kidolgozott.md#statikusantipusos)

# Névterek
* [namespace kulcsszó](fogalomtar_kidolgozott.md#namespace)
* [névterek egymásba ágyazása (A::B::C)](fogalomtar_kidolgozott.md#nevterekegymasba)
* [::x jelentése](fogalomtar_kidolgozott.md#globalisnev)
* [using namespace](fogalomtar_kidolgozott.md#usingnamespace)
* [Névtelen névtér](fogalomtar_kidolgozott.md#nevtelennevter)

# Fordítás, futtatás
* [Forrás fájl (source file)](fogalomtar_kidolgozott.md#forrasfajl)
* [Fejállomány (header file)](fogalomtar_kidolgozott.md#fejallomany)
* [Szabványok](fogalomtar_kidolgozott.md#szabvanyok)
* [Fordító](fogalomtar_kidolgozott.md#fordito)
* [Fordítás parancssorból](fogalomtar_kidolgozott.md#forditasparancssorbol)
* [Fordítási flag-ek](fogalomtar_kidolgozott.md#forditasiflagek)
* [Fordítási hiba (error)](fogalomtar_kidolgozott.md#hiba)
* [Fordítási figyelmeztetés (warning)](fogalomtar_kidolgozott.md#figyelmeztetes)
* [Preprocesszor](fogalomtar_kidolgozott.md#preprocesszor)
* [Preprocesszor direktíva](fogalomtar_kidolgozott.md#preprocesszordirektiva)
* [#include](fogalomtar_kidolgozott.md#include)
* [Include guard](fogalomtar_kidolgozott.md#includeguard)
* [Makró](fogalomtar_kidolgozott.md#makro)
* [Paraméteres makró](fogalomtar_kidolgozott.md#parameteresmakro)
* [Tárgykód](fogalomtar_kidolgozott.md#targykod)
* [Összeszerkesztés (linkelés)](fogalomtar_kidolgozott.md#linkeles)
* [Futtatható bináris](fogalomtar_kidolgozott.md#binaris)
* [main függvény](fogalomtar_kidolgozott.md#main)
* [Parancssori argumentumok](fogalomtar_kidolgozott.md#argumentumok)
* [Hibakód](fogalomtar_kidolgozott.md#hibakod)
* [Futási hiba](fogalomtar_kidolgozott.md#futasihiba)
* [Szegmentációs hiba](fogalomtar_kidolgozott.md#szegmentacioshiba)

# Program viselkedés
* [Nem definiált viselkedés](fogalomtar_kidolgozott.md#undef)
* [Nem specifikált viselkedés](fogalomtar_kidolgozott.md#unspec)
* [Implementáció által definiált viselkedés](fogalomtar_kidolgozott.md#impldef)

# Beépített típusok
* [Karakter típus: char](fogalomtar_kidolgozott.md#char)
* [Egész típusok: short, int, long, long long](fogalomtar_kidolgozott.md#egesztipusok)
* [Lebegőpontos típusok: float, double, long double](fogalomtar_kidolgozott.md#lebegopontostipusok)
* [Logikai típus: bool](fogalomtar_kidolgozott.md#bool)
* [Integrális típus](fogalomtar_kidolgozott.md#integralis)
* [Méret szabályok](fogalomtar_kidolgozott.md#meretszabalyok)
* [Konverziók](fogalomtar_kidolgozott.md#konverziok)

# Változók
* [Deklarálása, definíciója, inicializálása](fogalomtar_kidolgozott.md#valtozo)
* [Globális változó](fogalomtar_kidolgozott.md#globalisvaltozo)
* [Balérték (lvalue)](fogalomtar_kidolgozott.md#lvalue)
* [Jobbérték (rvalue)](fogalomtar_kidolgozott.md#rvalue)
* [Temporális objektum](fogalomtar_kidolgozott.md#temporalis)
* [Literál](fogalomtar_kidolgozott.md#literal)
* [Értékadás](fogalomtar_kidolgozott.md#ertekadas)
* [Konstans](fogalomtar_kidolgozott.md#konstans)
* [Láthatóság](fogalomtar_kidolgozott.md#lathatosag)
* [Láthatóság leárnyékolása](fogalomtar_kidolgozott.md#learnyekolas)
* [Élettartam](fogalomtar_kidolgozott.md#elettartam)

# Mutatók
* [Memória cím](fogalomtar_kidolgozott.md#memoriacim)
* [Pointer típus](fogalomtar_kidolgozott.md#pointer)
* [Referáló operátor: &](fogalomtar_kidolgozott.md#referalas)
* [Dereferáló operátor: \*](fogalomtar_kidolgozott.md#dereferalas)
* [Konstans pointer (\* előtt)](fogalomtar_kidolgozott.md#konstpointer1)
* [Konstans pointer (\* után)](fogalomtar_kidolgozott.md#konstpointer2)
* [void\* pointer](fogalomtar_kidolgozott.md#voidpointer)
* [Null pointer, NULL, nullptr](fogalomtar_kidolgozott.md#null)
* [Pointer konverziója bool-ra](fogalomtar_kidolgozott.md#pointerkonvbool)
* [Függvény mutató](fogalomtar_kidolgozott.md#fvpointer)
* [Pointerre mutató pointer](fogalomtar_kidolgozott.md#p2p)
* [-> operátor](fogalomtar_kidolgozott.md#nyil)
* [Dangling pointer](fogalomtar_kidolgozott.md#danglingpointer)

# Referenciák
* [Deklarálása, definíciója, inicializálása](fogalomtar_kidolgozott.md#ref)
* [Konstans referencia](fogalomtar_kidolgozott.md#konstref)

# Tömbök
* [Fogalma](fogalomtar_kidolgozott.md#tombok)
* [Deklarálása, definíciója, inicializálása](fogalomtar_kidolgozott.md#tombdef)
* [Kapcsolat a mutatókkal (konverzió)](fogalomtar_kidolgozott.md#tombpointer)
* [Konstans tömb](fogalomtar_kidolgozott.md#konsttomb)
* [Pointer aritmetika](fogalomtar_kidolgozott.md#pointeraritmetika)
* [[] operátor szemantikája tömbökre](fogalomtar_kidolgozott.md#tombindex)
* [Statikus tömb](fogalomtar_kidolgozott.md#statikustomb)
* [Dinamikus tömb](fogalomtar_kidolgozott.md#dinamikustomb)
* [Kiindexelés](fogalomtar_kidolgozott.md#kiindexeles)

# Memória
* [Bit](fogalomtar_kidolgozott.md#bit)
* [Bájt](fogalomtar_kidolgozott.md#bajt)
* [Gépi szó](fogalomtar_kidolgozott.md#word)
* [Padding](fogalomtar_kidolgozott.md#padding)
* [Memória szemét](fogalomtar_kidolgozott.md#memoriaszemet)
* [sizeof operátor](fogalomtar_kidolgozott.md#sizeof)
* [Statikus memória (Static memory)](fogalomtar_kidolgozott.md#statikusmem)
* [Dinamikus memória (Heap)](fogalomtar_kidolgozott.md#dinamikusmem)
* [Hívási verem (Call stack)](fogalomtar_kidolgozott.md#hivasiverem)

# Dinamikus memória
* [Memória allokálás, new operátor](fogalomtar_kidolgozott.md#new)
* [Memória deallokálás, delete és delete[] operátorok](fogalomtar_kidolgozott.md#delete)
* [Memória szivárgás](fogalomtar_kidolgozott.md#leak)

# Függvények
* [Deklarálása, definíciója](fogalomtar_kidolgozott.md#fv)
* [Visszatérési típus](fogalomtar_kidolgozott.md#visszateresitipus)
* [void visszatérési típus](fogalomtar_kidolgozott.md#voidvisszateres)
* [Formális paraméter lista](fogalomtar_kidolgozott.md#formparamlista)
* [Aktuális paraméter lista](fogalomtar_kidolgozott.md#aktparamlista)
* [Szignatúra](fogalomtar_kidolgozott.md#szignatura)
* [Függvény prototípus](fogalomtar_kidolgozott.md#prototipus)
* [Függvény túlterhelés](fogalomtar_kidolgozott.md#tulterheles)
* [Paraméter default értéke](fogalomtar_kidolgozott.md#defparam)
* [Lokális változó](fogalomtar_kidolgozott.md#lokalisvaltozo)
* [Statikus lokális változó](fogalomtar_kidolgozott.md#fvstatikus)
* [Rekurzió](fogalomtar_kidolgozott.md#rekurzio)
* [Érték szerinti paraméter átadás](fogalomtar_kidolgozott.md#ertekparam)
* [Referencia szerinti paraméter átadás](fogalomtar_kidolgozott.md#refparam)
* [Cím szerinti paraméter átadás](fogalomtar_kidolgozott.md#ptrparam)
* [inline kulcsszó](fogalomtar_kidolgozott.md#inline)

# Operátorok
* [Operátor fogalma](fogalomtar_kidolgozott.md#operator)
* [Unáris operátor](fogalomtar_kidolgozott.md#unaris)
* [Prefix szintaxis](fogalomtar_kidolgozott.md#prefix)
* [Postfix szintaxis](fogalomtar_kidolgozott.md#postfix)
* [Bináris operátor](fogalomtar_kidolgozott.md#binaris)
* [Infix szintaxis](fogalomtar_kidolgozott.md#infix)
* [Ternáris operátor](fogalomtar_kidolgozott.md#ternaris)
* [Függvény-szerű szintaxis](fogalomtar_kidolgozott.md#fvszeru)
* [Precedencia](fogalomtar_kidolgozott.md#precedencia)
* [Asszociativitás](fogalomtar_kidolgozott.md#assoc)
* [Operátor túlterhelés](fogalomtar_kidolgozott.md#operatortulterheles)
* [Bit manipuláló operátorok](fogalomtar_kidolgozott.md#bitoperatorok)
* [Lusta kiértékelés](fogalomtar_kidolgozott.md#lustakiertekeles)

# Vezérlési szerkezetek
* [Szekvencia](fogalomtar_kidolgozott.md#szekvencia)
* [Elágazás](fogalomtar_kidolgozott.md#elagazas)
* [Ciklus](fogalomtar_kidolgozott.md#ciklus)
* [Ugrások](fogalomtar_kidolgozott.md#ugrasok)

# Típus szinoníma
* [typedef kulcsszó](fogalomtar_kidolgozott.md#typedef)

# Felsorolási típus
* [enum](fogalomtar_kidolgozott.md#enum)
* [Alapjául szolgáló típus](fogalomtar_kidolgozott.md#enumtipus)
* [Default értékek felsorolási elemeknek](fogalomtar_kidolgozott.md#defaultenumertekek)

# Osztályok - alapok
* [Deklarálása, definíciója](fogalomtar_kidolgozott.md#classes)
* [class kulcsszó](fogalomtar_kidolgozott.md#class)
* [struct kulcsszó](fogalomtar_kidolgozott.md#struct)
* [Reprezentáció a memóriában](fogalomtar_kidolgozott.md#classmemory)
* [Adattag](fogalomtar_kidolgozott.md#adattag)
* [Konstans adattag](fogalomtar_kidolgozott.md#konstadattag)
* [Statikus adattag](fogalomtar_kidolgozott.md#staticadattag)
* [Tagfüggvény](fogalomtar_kidolgozott.md#tagfuggveny)
* [Konstans tagfüggvény](fogalomtar_kidolgozott.md#konsttagfuggveny)
* [Statikus tagfüggvény](fogalomtar_kidolgozott.md#staticfuggveny)
* [this paraméter és const this](fogalomtar_kidolgozott.md#this)
* [Privát láthatóság](fogalomtar_kidolgozott.md#private)
* [Publikus láthatóság](fogalomtar_kidolgozott.md#public)
* [Konstruktor](fogalomtar_kidolgozott.md#konstruktor)
* [Inicializáló lista](fogalomtar_kidolgozott.md#initlista)
* [Default konstruktor](fogalomtar_kidolgozott.md#defkonstruktor)
* [Implicit konverzió egyparaméteres ktor-ral](fogalomtar_kidolgozott.md#konvkonstruktor)
* [explicit kulcsszó](fogalomtar_kidolgozott.md#explicit)
* [Konverzió konverziós operátorral](fogalomtar_kidolgozott.md#konvoperator)
* [Másoló konstruktor](fogalomtar_kidolgozott.md#copykonstruktor)
* [Értékadás operátor](fogalomtar_kidolgozott.md#ertekadasop)
* [Destruktor](fogalomtar_kidolgozott.md#destruktor)
* [Rule of Three](fogalomtar_kidolgozott.md#ruleofthree)
* [RAII](fogalomtar_kidolgozott.md#raii)
* [friend kulcsszó, barát függvény, barát osztály](fogalomtar_kidolgozott.md#friend)
* [Osztálytörzsben definiált "belső" típus](fogalomtar_kidolgozott.md#belsotipus)

# Osztályok - haladóbb fogalmak
* [OOP röviden (motiváció)](fogalomtar_kidolgozott.md#oop)
* [Getter, setter](fogalomtar_kidolgozott.md#gettersetter)
* [Öröklődés szemantikája, szülő- és gyerekosztály](fogalomtar_kidolgozott.md#oroklodes)
* [Protected láthatóság](fogalomtar_kidolgozott.md#protected)
* [Publikus öröklődés](fogalomtar_kidolgozott.md#publicoroklodes)
* [Protected öröklődés](fogalomtar_kidolgozott.md#protectedoroklodes)
* [Privát öröklődés](fogalomtar_kidolgozott.md#privateoroklodes)
* [Többszörös öröklődés](fogalomtar_kidolgozott.md#tobbszorosoroklodes)
* [Gyémánt öröklődés](fogalomtar_kidolgozott.md#gyemantoroklodes)
* [Virtuális öröklődés](fogalomtar_kidolgozott.md#virtualoroklodes)
* [Virtuális metódus](fogalomtar_kidolgozott.md#virtualmetodus)
* [Tisztán virtuális metódus](fogalomtar_kidolgozott.md#tisztanvirtualmetodus)
* [Absztrakt osztály](fogalomtar_kidolgozott.md#abstractosztaly)
* [Interfész, implementáció](fogalomtar_kidolgozott.md#interfaceimpl)

# Unió típus
* [union kulcsszó és unió szemantika](fogalomtar_kidolgozott.md#union)

# Polimorfizmusok összefoglalása
* [Polimorfizmus jelentése](fogalomtar_kidolgozott.md#polimorfizmus)
* [Altípusos/futási idejű polimorfizmus, upcast, downcast, statikus és dinamikus típus](fogalomtar_kidolgozott.md#altipusospoli)
* [Parametrikus/fordítási idejű polimorfizmus](fogalomtar_kidolgozott.md#adhocpoli)
* [Ad-hoc polimorfizmus (overloading)](fogalomtar_kidolgozott.md#parametrikuspoli)
* [Kasztolások](fogalomtar_kidolgozott.md#kasztolasok)

# Kasztolások
* [static\_cast](fogalomtar_kidolgozott.md#staticcast)
* [dynamic\_cast](fogalomtar_kidolgozott.md#dynamiccast)
* [reinterpret\_cast](fogalomtar_kidolgozott.md#reinterpretcast)
* [const\_cast](fogalomtar_kidolgozott.md#constcast)
* [Legacy kasztolás (C-szerű és függvényszerű szintaxis)](fogalomtar_kidolgozott.md#legacycast)

# Funktorok
* [Funktor](fogalomtar_kidolgozott.md#funktor)
* [Predikátum](fogalomtar_kidolgozott.md#predikatum)

# Sablonok
* [Generikus programozás](fogalomtar_kidolgozott.md#generikusprog)
* [Sablonparaméter lista, template, class, typename kulcsszavak](fogalomtar_kidolgozott.md#sablonparamlista)
* [Default template argumentum](fogalomtar_kidolgozott.md#deftemplatearg)
* [Függvény sablon](fogalomtar_kidolgozott.md#fuggvenysablon)
* [Osztály sablon](fogalomtar_kidolgozott.md#osztalysablon)
* [Template specializáció](fogalomtar_kidolgozott.md#templatespec)
* [Template metaprogramozás](fogalomtar_kidolgozott.md#templatemetaprog)

# Iterátorok
* [Iterátor fogalma](fogalomtar_kidolgozott.md#iterator)
* [Output iterátor](fogalomtar_kidolgozott.md#outputiterator)
* [Input iterátor](fogalomtar_kidolgozott.md#inputiterator)
* [Forward iterátor](fogalomtar_kidolgozott.md#forwarditerator)
* [Bidirectional iterátor](fogalomtar_kidolgozott.md#bidirectionaliterator)
* [Random Access iterátor](fogalomtar_kidolgozott.md#randomaccessiterator)
* [Konstans iterátor](fogalomtar_kidolgozott.md#konstansiterator)
* [Reverse iterátor](fogalomtar_kidolgozott.md#reverseiterator)
* [begin, cbegin, rbegin, crbegin metódusok](fogalomtar_kidolgozott.md#begin)
* [end, cend, rend, crend metódusok](fogalomtar_kidolgozott.md#end)
* [++, -- és * operátorok használata iterátorokkal](fogalomtar_kidolgozott.md#iteratoroperatorok)
* [Használata](fogalomtar_kidolgozott.md#iteratorhasznalat)

# STL
* [Adatszerkezetek](fogalomtar_kidolgozott.md#adatszerkezetek)
  - Szekvenciális konténerek
    + [array](https://cplusplus.com/reference/array/array/)
    + [vector](https://cplusplus.com/reference/vector/vector/)
    + [deque](https://cplusplus.com/reference/deque/deque/)
    + [forward\_list](https://cplusplus.com/reference/forward_list/forward_list/)
    + [list](https://cplusplus.com/reference/list/list/)
  - Adapter konténerek
    + [stack](https://cplusplus.com/reference/stack/stack/)
    + [queue](https://cplusplus.com/reference/queue/queue/)
    + [priority\_queue](https://cplusplus.com/reference/queue/priority_queue/)
  - Asszociatív konténerek
    + [set](https://cplusplus.com/reference/set/set/)
    + [multiset](https://cplusplus.com/reference/set/multiset/)
    + [map](https://cplusplus.com/reference/map/map/)
    + [multimap](https://cplusplus.com/reference/map/multimap/)
  - Rendezetlen asszociatív konténerek
    + [unordered\_set](https://cplusplus.com/reference/unordered_set/unordered_set/)
    + [unordered\_multiset](https://cplusplus.com/reference/unordered_set/unordered_multiset/)
    + [unordered\_map](https://cplusplus.com/reference/unordered_map/unordered_map/)
    + [unordered\_multimap](https://cplusplus.com/reference/unordered_map/unordered_multimap/)

* [Algoritmusok](fogalomtar_kidolgozott.md#algoritmusok)
    + [find](https://cplusplus.com/reference/algorithm/find/)
    + [find\_if](https://cplusplus.com/reference/algorithm/find_if/)
    + [sort](https://cplusplus.com/reference/algorithm/sort/)
  - ...

* [Egyenlőség](fogalomtar_kidolgozott.md#egyenloseg)
* [Ekvivalencia](fogalomtar_kidolgozott.md#ekvivalencia)

# Kivételkezelés
* [kivétel](fogalomtar_kidolgozott.md#kivetel)
* [kivétel dobás, throw kulcsszó](fogalomtar_kidolgozott.md#throw)
* [kivétel elkapás, try blokk, catch ágak](fogalomtar_kidolgozott.md#catch)

