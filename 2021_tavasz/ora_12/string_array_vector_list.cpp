#include <iostream>
#include <array>

// Eml.: C++ memoria modellje: - "tarolasi osztalyok"
// - STATIC: lifetime a teljes futas (globalis es static kulcsszavas valtozok)
// - STACK: blokk vegeig el (fv es egyeb kod blokkok lokalis valtozoi) - "auto tarolasi osztaly"
// - HEAP (DYNAMIC MEMORY): new es delete/delete[] hivasok kozott elnek
//

// Az std::string implementacioja valahogy hasonloan nezhet ki:
//
// namespace std {
// class string {
// 	private:
// 		char * _buf;
// 		size_t size;
// 		...
// 	public:
// 		string()...                    // default ktor
// 		string(const string& other)... // copy ktor
// 		string(const char * cstr)...   // char tombbel inicializalo, hogy:
// 		                               // lehessen ilyet string str = "hello";
// 		~string() { delete[] _buf; }
// 		...
// };
// }

int main()
{
// STRING
	// std::string : Egy wrapper osztaly karakter tombokhoz, absztraktalja oket
	//               kenyelmes hasznalat (pl. append metodus), STL kompatibilitas
	//               (iteratorok, algoritmusokhoz...)

	std::string str("hello world!");
	std::string str2 = "hello c++"; // ugyanaz, parameteres konstrualas const char*-bol
	                                // lehet, mert az a ktor-ja nem explicit

	str += "!!!!!!"; // append-eles mukodik az operator+= overload-dal
	                 // (termeszetesen dinamikus memoria ujraallokalast igenyelhet...)

	std::cout << str << "\n";
	std::cout << str2 << "\n";
	std::cout << str.size() << "\n";
	std::cout << str.length() << "\n";

	str.c_str(); // ha el szeretnenk erni az "alatta" levo karakter tombot
	             // pl. egy C-s library hivashoz tuti ez fog kelleni

//------------------------------------------
// ARRAY
	// std::array : Egy wrapper osztaly statikus tombokhoz, kenyelmes a hasznalata,
	//              hiszen vannak metodusai, pl. .size() + STL kompatibilis,
	//              mert vannak iteratorai => konnyen hasznalhato STL-es algoritmusokkal
	//              Tarolt tipust es elemszamot sablonparameterekken varja

	const int size = 42;
	std::array<int, size> a; // OK, size egy ford. ideju konstans

	int size2;
	std::cin >> size2;
	std::array<int, size2> a2; // HIBA, size2 nem ismert ford. idoben =>
	                           // nem szerepelhet template argumentumkent,
	                           // hiszen ford. idoben nem ismert, igy a ford.
	                           // nem tud osztaly kodot generalni belole...


//------------------------------------------
// VECTOR VS LIST
//
// std::vector ---> |___|___|___|___|___|___|___|           <-- tomb van "alatta"
//
// std::list   ---> |___| -> |___|        |___| -> nullptr  <-- lancolt lista
//                             |          ^
//                             V          |
//                            |___| -> |___|
//
// vector pros:
//  - Tomb miatt az elemek szekvencialisan vannak memoriaban => tetszoleges
//    indexu elem konstans ido alatti elerese (eml.: csak ugrani kell
//    N * sizeof(tarolt tipus) bajtot), sot elem beszurasa a vegere is
//    altalaban konstans ideju
//  - Akar az egesz (vagy egy resze) konnyen bemasolhato processor cache-be
//    => sokkal gyorsabb eleres (foleg ha tobbszor akarunk pl. vegigiteralni rajta,
//    hiszen a cache-ben bent is tarthatja tobb idore...)
// vector cons:
//  - Nagy elemszam eseten nehez lehet hosszu egybefuggo memoria szeletet
//    talalni a tombnek, foleg ha eleg toredezett a memoriank (elvileg a
//    kernel probalja toredezettsegmentesiteni...)
//  - Relativ ritkan jon elo, de ha megtelik a tomb kapacitasa, akkor
//    kell ujra allokalni uj tombot es masolgatni => ez mar linearis ideju
//    Illetve belso indexu elem torlese, belso indexre valo beszuras is
//    sok memoria mozgatassal jar (balra vagy jobbra kell "shiftelni" a tobbi elemet)
//
// list pros:
//  - Mivel nincs megkovetelve a szekvencialis "tombos" elrendezes, ezert
//    nem problema magas elemszamnal, ha toredezett a memoria, egy-egy
//    elemet bele tud allokalni egy-egy "lyukba"
//  - Lista kozepere elem beszurasa vagy elem torlese onnan bar ugyanugy
//    linearis ideju, de legalabb elem mozgatasokkal nem jar
// list cons:
//  - Tetszoleges indexu elem elerese/torles/beszuras linearis ideju,
//    hiszen vegig kell lepegetni addig az osszes listaelemen ("next" pointerek)
//  - Minden egyes lepesnel ujra kell olvasni mindig a memoriabol egy
//    cimet, hiszen az egyes tarolt elemek teljesen mas-mas cimeken vannak
//    (CPU <-> RAM kommunikacio a busz rendszeren at egy bottleneck),
//    ez parositva azzal, hogy egy N. elem eleresehez vegig kell lepni N
//    db elemen: nem tul hatekony
//    Nem lehet konnyen CPU cache-be tenni az egeszet

