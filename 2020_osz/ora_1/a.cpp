#include <iostream>

int a = 42; // globalis valtozo, elerheto es hasznalhato mas ford. egysegbol is
            // de ahhoz, hogy az a masik ford. egyseg leforduljon, elotte
            // deklaralnia kell (extern-nel) <- miert? tipusnak ismertnek kell lennie
            // pl. a statikus tipusossag miatti tipus ellenorzesek miatt + kodgeneralashoz is

static void f(); // csak ez a forditasi egyseg hasznalhatja

namespace Y { struct Asd {int x, y;}; } // tipusnak is adhatok nevprefixet
// namespace blokkba lehet mas-mas helyeken beleirni, lasd: main.cpp-ben is van bele irva Y-ba
// masik pelda: az std:: nevterbe is sok dolog van, amik nem egyetlen ford egysegben vannak definialva

namespace {
	int x;
	int y;
	int z;
	bool f(char);
	enum Valami { A = 12 };
}

static int priv = 10; // csak ez a forditasi egyseg hasznalhatja

void hello() { std::cout << "hello\n" << priv << "\n"; }

