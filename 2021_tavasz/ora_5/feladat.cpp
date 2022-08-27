/*
 * Feladat:
 *
 * Irjunk egy create_array fuggvenyt, mellyel int tomboket tudunk
 * legyartani
 * 3 int parametert kapjon:
 *   - tomb elemszama
 *   - kezdo elem erteke
 *   - differencia (minden elem ennyivel legyen tobb/kevesebb az elozonel)
 * A fuggveny hozzon letre egy megfelelo meretu tombot es toltse fel
 * az ertekeit, majd terjen vissza ezzel a tombbel!
 *
 */

#include <iostream>

int* create_array(int size, int start, int difference){
    int* ret = new int[size]; // dinamikus tomb kell, hiszen futasi idoben dolhet el a size erteke

    ret[0] = start;

    for(int i = 1; i < size; ++i)
    {
        ret[i] = ret[i - 1] + difference;
    }

    return ret; // visszaadjuk a tomb kezdoelemenek a cimet (elso int elso bajtjanak a cime)
}

int main()
{
	int * test = create_array(5, 10, 2); // ramutatunk a visszaadott cimre

	for (int i=0; i<5; ++i)
		std::cout << test[i] << "\n"; // eml.: test[i] ekvivalens ezzel: *(test+i)

	delete[] test; // ezt ne felejtsuk le ;)
	               // hiszen a dinamikusan allokalt memoriat fel kell szabaditani
	               // a test egy dinamikus tombre mutat, ezert a tombos delete operatort kell hasznalni
}

