#include <iostream>

// C-ben hasznaltak/hasznaljak az uniokat oroklodes/polimorfizmus implementalasra is:

struct Vehicle {
	enum {
		CAR,
		PLANE,
		SHIP
	} type; // igy el tudom tarolni, hogy milyen fajta jarmu az objektum

	// Common traits
	std::string name;
	int top_speed;

	// Special traits
	union {

		struct {
			int number_of_wheels;
			int horse_power;
		} car_traits;

		struct {
			int wing_lenght;
			int max_altitude;
		} plane_traits;

		struct {
			int anchor_weight;
		} ship_traits;

		//...

	} special_traits;
};

// Igy minden Vehicle objektumban csak "egy fajta" special trait lesz tarolva
// es hasznalva, nem lesz mindenben minden letarolva...

// Masik erdekesseg: figyeljuk meg, hogy a belso enum-nak, union-nak es az abba
// irt 3 struct-nak nem irtam tipusnevet. Ez megengedett: "anonym types"
// Ennek persze vannak limitacioi, nem fogom tudni ezeket a tipusokat meghivatkozni
// Ha ez gondot okozna, akkor ki kell irni hozzajuk egy tipusnevet, pl. struct CarTraits {...

// Egy masik potencialis (hatekonyabb) megoldas ez lenne pl.:
//
// union {
//	CarTraits * car_traits;
//	PlaneTraits * plane_traits;
//	ShipTraits * ship_traits;
// } special_traits;
//
// Igy fixen csak 1 pointer lenne tarolva (csak ~8 byte) es minden objektumnal
// a type-nak megfelelo tipusu objektumra mutato tagot hasznalhatjuk...
//
// ...vagy akar igy is lehetne:
//
// void * special_traits; // <-- ez kesobb mutathat a 3 fajta struct barmelyikere
//
// Kevesbe szep, mert ezzel a megoldassal konnyebben mutathatunk helytelenul
// barmi masra is, pl egy int-re, illetve mindenhol kasztolgatni kene a megfelelo
// pointer tipusra...

// FONTOS: C++-ban erre a usecase-re NE EZT HASZNLAJUK! Van sokkal jobb nyelvi
// elemunk erre: oroklodes
// A kozos tulajdonsagokat beleirjuk egy (akar absztrakt) Vehicle szulo osztajba,
// abbol pedig szarmazhat a 3 gyerekosztaly a sajat plusz adattagjaikkal
// Sokkal biztonsagosabb is, hiszen itt, union eseten semmi nem garantalja, hogy
// a programozo mindig csak a megfelelo union tagot fogja hasznalni minden objektum
// eseten!

int main()
{
	Vehicle car;
	car.type = Vehicle::CAR;
	car.name = "SomeCar";
	car.top_speed = 180;
	car.special_traits.car_traits.number_of_wheels = 4;
	car.special_traits.car_traits.horse_power = 200;

	Vehicle plane;
	plane.type = Vehicle::PLANE;
	plane.name = "SomePlane";
	plane.top_speed = 2000;
	plane.special_traits.plane_traits.wing_lenght = 30;
	plane.special_traits.plane_traits.max_altitude = 7000;

	Vehicle ship;
	ship.type = Vehicle::SHIP;
	ship.name = "SomeShip";
	ship.top_speed = 100;
	ship.special_traits.ship_traits.anchor_weight = 1000;
}

