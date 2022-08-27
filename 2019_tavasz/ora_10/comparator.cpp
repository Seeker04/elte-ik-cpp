#include <iostream>
#include <set>

struct Person {
	int id;
	std::string name;
	int age;
};

// megoldas #1:
struct PersonCmp { // ez egy predikatum (mert bool-t ad vissza az operator()-je)
	bool operator()(const Person& p1, const Person& p2) { return p1.id < p2.id; }
};

// megoldas #2:
// bool operator<(const Person& p1, const Person& p2) { return p1.id < p2.id; }
// megjegyzes: ha a Person adattagjai rejtettek lennenek es nem lennenek getter-ek hozzajuk, akkor friend-elni kene ezt a fv-t

int main()
{
	std::set<Person, PersonCmp> s = { // a komparator predikatum osztalyt, mint tipus, sablon parameterkent adjuk at
		{ 4210, "Emma", 32 },     // e szerint lesz rendezve a halmaz es egyedi kulcskent funkcional
		{ 1024, "John", 29 },
		{ 1024, "Will", 57 }
	};

	for (auto person : s) // hack, kesobbi anyag...
		std::cout << person.name << " "; // John Emma
		                                 // Will nem szerepel, mert id szerint egyedi rendezes van, igy be se lett szurva
		                                 // John van elol, mert neki kisebb az id-je

	// John es Will ekvivalensek, mert !(j < w) && !(j < w) igaz rajuk
	// viszont nem egyenloek, mert j == w nem igaz (ha nem definialjuk felul az operator==-t, alapertelmezetten adattagonkent hasonlitodnak ossze)

	// a masodik template parameternek van default erteke: std::less (alapertelmezetten az operator<-t hivja meg), ezert
	// azt is csinalhattuk volna, hogy az operator<-t definialjuk felul a Person tipushoz (megoldas #2)
	// es akkor nem kell masodik template parametert megadni: std::set<Person> s = { ... };
}

