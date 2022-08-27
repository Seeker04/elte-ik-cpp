#include <iostream>

void f() { throw 10; } // kivetel lehet tetszoleges tipusu objektum, pl. int

void g() { f(); } // itt nem kezelem le, ezert tovabb lesz dobva a stack-en

void h()
{
	try {
		g();
	} catch(int e) { // az e tipusa illeszkedik a dobott kivetel tipusara
		std::cerr << "Error\n"; // detektaltam, tetszoleges modon lekezelem
	}
}

int main()
{
	h();
}

/* Hivasi verem (stack memory):

   |      |
   |  f   | <- innen dobom
   |  g   |
   |  h   | <- itt kezelem le
   | main |
   |------|
*/

