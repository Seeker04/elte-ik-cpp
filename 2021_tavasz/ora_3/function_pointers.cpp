#include <iostream>

// Fv tipusokat a visszateresi tipus es a formalis parameter lista hatarozza meg
// Pl. ezek mas-mas fv tipusok:
//   void(int,int)
//   bool(const char *)
//   long&()

void doubleInt(int& i)  { i*= 2; } // referencia az aktualis paramra -> at tudja irni
void invertSign(int& i) { i*=-1; }

//void foreach(int *t, int size, void (*p)(int&)) <--- t[] helyett *t is ok, ugyanaz
void foreach(int t[], int size, void (*p)(int&)) // var egy int tombot, a meretet es egy
{                                                // fv pointert, ami int referenciat var
	for (int i=0; i<size; ++i)               // es nem ter vissza semmivel
		p(t[i]);  // meghivja a p altal mutatott fv-t a t[i]-vel (ref szerint adja at)
	// (ki lehetet volna irni a dereferalast: *p(t[i]), de fv pointernel nem kell
}

int main()
{
	// FUGGVENY POINTEREK

	int array[4] = { 10, -5, 42, 3 };

	foreach(array, 4, &doubleInt); // atadom a tombot (pointer-t),
	                               // a meretet (mennyivel szabad max eltolni,
	                               // es a fuggveny cimet (tipushelyes, mert void(int&))

	std::cout << array[0] << "\n";
	std::cout << array[1] << "\n";
	std::cout << array[2] << "\n";
	std::cout << array[3] << "\n";

	foreach(array, 4, invertSign); // a referalo & operatort fv elol el is lehet hagyni

	std::cout << array[0] << "\n";
	std::cout << array[1] << "\n";
	std::cout << array[2] << "\n";
	std::cout << array[3] << "\n";

}

