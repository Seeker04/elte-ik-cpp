/*
 *  Pelda egy egyszeru, tomb-alapu, dinamikus kontener tipus implementaciojara
 *  az std::vector mintajara.
 *  Bemutatja az osztaly irast, dinamikus memoria kezelest, operator irast es
 *  tulterhelest, konstanssag fogalmat, kivetelkezelest, az adatabsztrakcio es
 *  az adatelrejtes elvet, valamint a sablonok hasznalatat
 *
 *  Forditas: g++ main.cpp
 *  Futtatas: ./a.out (Linux)
 *            a.exe   (Windows)
 */

#include <iostream> // standard output kezeleshez

#include "vector.h" // targykod generalasi lepesben deklaraltnak kell lennie a Vector tipusnak,
                    // ezert kell bemasolni a "vector.h" tartalmat, valamint mivel a Vector egy sablon osztaly,
                    // teljesen definialtnak kell lennie, ezert a "vector.tpp" tartalma is kell (metodus definiciok),
                    // de az be van include-olva a "vector.h" vegere, igy ez az egy include mindent bemasol

template <typename T> // sablon fuggveny tudja csak a sablon osztalyt hasznalni
void printVector(const Vector<T>& vector) // parameter atadas: hatekony, ha nem keszitunk lokalis masolatot => referencia hasznalata
                                          // es itt csak olvasni akarjuk, ezert const referencia => garantaltan nem modositja a fv
{
	std::cout << "{";
	for (int i=0; i<vector.getSize(); ++i)
		std::cout << vector[i] << (i<vector.getSize()-1 ? ", " : ""); // ehhez kell a const T& operator(int index) const tulterhelt fv prototipus,
	std::cout << "}" << std::endl;                                        // mert const referencian csak const metodus hivhato
}

int main()
{
	Vector<int> v; // peldanyositas default konstruktorral es int a sablon parameter => a fordito legeneralja a Vector<int>
	               // tipus kodjat ugy, hogy a sablon osztalyban T helyere int-et helyettesit
	std::cout << v.getSize() << std::endl; // meret lekerdezese

	v.add(20); // elemek hozzaadasa (int-ek)
	v.add(42);
	v.add(7);
	v.add(100);

	v.pop(42); // elem torlese

	v[2] = 9; // elem megvaltoztatasa (a [] operator nem-konstans referenciaval visszateresenek kihasznalasa)

	printVector<int>(v);

	int array[] = {200, 150, 23, 44, 90};
	Vector<int> w(array, 5); // tombbol masolo konstruktor hasznalata (meretet is at kell adni!)

	printVector<int>(w);

	Vector<int> vc(v); // masolo konstruktor hasznalata

	printVector(vc); // akar el is hagyhatjuk a printVector mogul az <int>-et, mert a ford itt egyertelmuen ki tudja kovetkeztetni vc tipusabol

	try {
		std::cout << v[8] << std::endl; // kiindexeles kezelese kivetellel
	}
	catch (const Vector<int>::OutOfBoundsException& e) {
		std::cerr << "Error: An out of bounds exception was caught!" << std::endl; // standard error stream-re irjuk a hibat
	}

	Vector<int> x = v = w; // ertekadas operator hasznalata

	std::cout << "w vector: " << w << std::endl; // a friend fuggveny hasznalata
	std::cout << "v vector: " << v << std::endl; // az std::ostream& (referencia) visszateres miatt lehet lancolni
	std::cout << "x vector: " << x << std::endl; // fajlba is tudnank irni, mert az std::ofstream az std::ostream-bol szarmazik

	Vector<std::string> strVect; // masik tipus hasznalata => a fordito egy masik osztaly kodot is legeneral
	                              // most T helyere std::string kerul, ez az osztaly igy egy masik tipus lesz

	strVect.add("Almafa");
	strVect.add("Asd");
	strVect.add("Random string");

	std::cout << strVect << ", and its size: " << strVect.getSize() << std::endl; // minden metodus es funkcionalitas ugyanugy mukodik
}

