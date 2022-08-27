#include <iostream>

class C {
public:
	int x = 10;
	int y = 20;
private:
	int z = 30;
};

int main()
{
	//int * p = "hello"; // ez ford. hiba lenne, mert "hello" tipusa const char[] === const char*
	                     // es const char* pointer nem tipushelyes int* pointerrel
	char p[] = "hello";
	std::cout << p << "\n"; // az operator<<(std::ostream&, const char*) operator tulterheles
	                        // ugy van implementalva, hogy a '\0' karakterig kiir mindent
	                        // eml.: a ford. a karakter tomb literal vegere teszi a '\0'-t

	std::cout << "hello" + 1 << "\n"; // pointer aritmetika, a tombot (ami a kezdo cim) eltoljuk 1-gyel

	std::cout << *("hello" + 1) << "\n"; // ha a pointer eltolasa utan kiolvassuk (dereferaljuk),
	                                     // akkor const char* -> const char-t kapunk, igy csak
	                                     // a masodik (1-gyel toltuk el a kezdo cimet) karaktert irja ki

	std::cout << "hello"[1] << "\n"; // ez teljesen ekvivalens az elobbivel, csak szebb a szintaxis

	std::cout << (1 + "hello") + 2 << "\n"; // osszeadas kommutativ, ill. eltolt cimet is eltolhatunk...

	//---------------------------------------------------------------------

	std::cout << "sizeof(int): " << sizeof(int)  << "\n";
	std::cout << "sizeof(long): " << sizeof(long) << "\n";

	C c; // objektum peldanyositas, memoriaban rendre lesznek az adattagok: x, y, z

	std::cout <<      *( (int*)&c + 2) << "\n"; // lekerem a cimet, amire int*-kent tekintek es ugy tolom el 2-vel
	                                            // => 2*sizeof(int)-et ugrottam, majd kiolvasok egy int-et (mert int*) => z
	std::cout <<      *((long*)&c + 1) << "\n"; // hasonlo, most long-kent tekintek a cimre es 1-gyel tolom el, mert 1 long
	                                            // az 8 bajt a rendszeremen, tehat ugyanoda jutok mint a 2 int-nyi eltolassal
	                                            // miert latok szemetet? a vegso kifejezes long*, ezert 8 bajtot olvasok ki,
	                                            // ami a z mellett a c objektum utani 4 bajtot is tartalmazza :S
	std::cout << (int)*((long*)&c + 1) << "\n"; // igy mar jo, mert az eltolt cimre meg dereferalas elott int*-kent tekintek
	                                            // a kasztolas miatt, ezert int-et olvasok ki => 4 bajt => pontosan z erteke

	*((int*)&c + 2) *= 4; // nem csak olvasni, de meg atirni is at tudom a privat adattagot ilyen hackelessel
	                      // de ilyeneket azert ne nagyon csinaljunk, ha nincs ra nyomos okunk!
	std::cout << *((int*)&c + 2) << "\n"; // tenyleg 120 lett a z terulete

	// c
	// |----|----|----|----|------
	//   x    y    z
	//  ^         ^
	// &c        (int*)&c + 2
	//(int*)&c  (long*)&c + 1

}

