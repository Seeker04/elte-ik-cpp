#include <iostream>

int get_double(int x) { return 2 * x; }
int get_triple(int x) { return 3 * x; }

void transformed_output(int * t, int size, int (*f)(int))
{
	for (int i=0; i<size; ++i)
		std::cout << f(t[i]) << std::endl; // f dereferálása elhagyható, de ki is lehet írni: (*f)(t[i])
}

int main(int argc, char *const argv[])
{
// 1. * helye
	int x = 42;
	int * p1 = &x;
	int ** p2 = &p1;
	std::cout << **p2 << std::endl;

// 2. null pointer
	p1 = nullptr; // vagy NULL vagy 0 C-ben és C++11 elott
	//std::cout << *p1 << std::endl; //segfault
	if (p1) // null pointer false-ra konvertálódik, különben true-ra
		std::cout << "reached" << std::endl;

// 3. void*
	char c = 'k';
	void * v = &c; // lehet const void * is
	//std::cout << *v << std::endl; // HIBA: nem dereferálható, nem ismert a mutatott típus és a méret sem
	std::cout << *(char*)v << std::endl; // k, C-s kasztolás
	v = &x;
	std::cout << *(int*)v << std::endl; // 42

// 4. function pointer
	int numbers[4] = { 2, 3, 4, 5 };
	transformed_output(numbers, 4, &get_double);
	transformed_output(numbers, 4, get_double); // referálás is elhagyható

	int (*func_ptr)(int) = get_triple;
	transformed_output(numbers, 4, func_ptr);

// 5. dinamikus memória

	// változók
	int * p = new int(30);
	float * f;
	f = new float;
	std::cout << *f << std::endl;
	delete p; // FONTOS!
	delete f;

	// tömb
	int n;
	std::cout << "Meret: "; std::cin >> n;
	int * tomb = new int[n];
	for (int i=0; i<n; ++i)
		tomb[i] = 42;
	delete[] tomb; // FONTOS!

	// NxM-es mátrix (HEAP)
	int N, M;
	std::cout << "N: "; std::cin >> N;
	std::cout << "M: "; std::cin >> M;
	int ** mtx = new int*[N];
	for (int i=0; i<N; ++i)
		mtx[i] = new int[M];
	mtx[2][3] = 13;
	std::cout << *(*(mtx+2)+3) << std::endl;
	for (int i=0; i<N; ++i)
		delete[] mtx[i];
	delete[] mtx; // FONTOS!

// 6. referencia (álnév)
	int y = 42;
	int& z = y; // kötelező inicializálni, nincs olyan, hogy null reference
	z = 20; // módosítható rajta keresztül
	std::cout << y << std::endl; // álnévként viselkedik
	const int& cref = z; // konstans referencia
	std::cout << cref << std::endl; // olvasható (jobbérték)
	//cref = 30; // const referencián keresztül nem módosulhat (read-only lvalue)

	// veszély
	int * ptr = new int(20);
	int& ref = *ptr;
	delete ptr;
	std::cout << ref << std::endl; // undefined (memória szemét vagy segfault)
	std::cout << *ptr << std::endl; // hasonlóan, ezért érdemes delete után ptr = nullptr értékadás

// 7. függvény paraméter átadás

}

