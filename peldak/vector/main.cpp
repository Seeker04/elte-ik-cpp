/*
 *  Pelda egy egyszeru, tomb-alapu, dinamikus kontener tipus implementaciojara
 *  az std::vector mintajara.
 *  Bemutatja az osztaly irast, dinamikus memoria kezelest, operator irast es
 *  tulterhelest, konstanssag fogalmat, kivetelkezelest, az adatabsztrakcio es
 *  az adatelrejtes elvet.
 *
 *  Forditas: g++ main.cpp vector.cpp
 *  Futtatas: ./a.out (Linux)
 *            a.exe   (Windows)
 */

#include <iostream> // standard output kezeleshez

#include "vector.h" // targykod generalasi lepesben deklaraltnak kell lennie a Vector tipusnak,
                    // ezert kell bemasolni a vector.h tartalmat, a definicioja eleg, ha linkeleskor van meg

void printVector(const Vector& vector) // parameter atadas: hatekony, ha nem keszitunk lokalis masolatot => referencia hasznalata
                                       // es itt csak olvasni akarjuk, ezert const referencia => garantaltan nem modositja a fv
{
	for (int i=0; i<vector.getSize(); ++i)
		std::cout << vector[i] << " "; // ehhez kell a const int& operator(int index) const tulterhelt fv prototipus,
		                               // mert const referencian csak const metodus hivhato
	std::cout << std::endl;
}

int main()
{
	Vector v; // peldanyositas default konstruktorral
	std::cout << v.getSize() << std::endl; // meret lekerdezese

	v.add(20); // elemek hozzaadasa
	v.add(42);
	v.add(7);
	v.add(100);

	v.pop(42); // elem torlese

	v[2] = 9; // elem megvaltoztatasa (a [] operator nem-konstans referenciaval visszateresenek kihasznalasa)

	printVector(v);

	int array[] = {200, 150, 23, 44, 90};
	Vector w(array, 5); // tombbol masolo konstruktor hasznalata (meretet is at kell adni!)

	printVector(w);

	Vector vc(v); // masolo konstruktor hasznalata

	printVector(vc);

	try {
		std::cout << v[8] << std::endl; // kiindexeles kezelese kivetellel
	}
	catch (const Vector::OutOfBoundsException& e) {
		std::cerr << "Error: An out of bounds exception was caught!" << std::endl; // standard error stream-re irjuk a hibat
	}

	Vector x = v = w; // ertekadas operator hasznalata

	printVector(w);
	printVector(v);
	printVector(x);
}

