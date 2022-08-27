#include <iostream>

/*
  Feladat:
  Vannak globalis valtozoim:
  int a;
  int b;
  int c;
  ...
  int z;
  amiket szeretnek tobb kulonbozo forrasfajlban is elerni es hasznalni
  Hogyan oldhatnam ezt meg?
  + nem szeretnek nagyon sokat gepelni...
  Forrasok: main.cpp, x.cpp, y.cpp
*/

/*
  Megoldas:
  A globals.h-ban deklaralom extern-kent az osszes valtozot, amit minden fajl,
  ami hasznalni szeretne be tud include-olni
  A valtozok definicioit pedig egy dedikalt forditasi egysegbe irom (külön lefordithato),
  hogy PONTOSAN EGY HELYEN legyenek definialva, igy nem sertem az ODR-t!
*/

#include "globals.h"

int main()
{
	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << c << "\n";
}

