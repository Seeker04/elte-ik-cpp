#include <iostream>

// Feladat: szeretnenk egy fv-t, ami egy matrixot fog nekunk legyartani int elemekkel
// Parameterul megadjuk a sorok (n) es az oszlopok szamat (m), ezek persze lehet,
// hogy csak futasi (dinamikus) idoben fognak kiderulni, pl. user input-bol/fajlbol
// => csak dinamikus tombokkel tudjuk megoldani (std::vector hasznalata eseten is
// ez a helyzet, mert az lenyegeben egy osztaly, ami egy dinamikus tombot wrap-pol,
// azt hasznal adattagkent)
// Harmadik parameterul egy elemeknek adando default erteket is varjon a fv

// Otlet: agyazzunk egymasba tomboket, tehat legyen egy dinamikus tomboket tartalmazo
// dinamikus tomb. A "kulso tomb" elemei a sorok es az egyes "belso tombok" az oszlop
// elemeket tartalmazzak
// De mik is a tombok valojaban? Pointerek. Kezdo elem cime, amit el tudunk tolni
// pointer aritmetikaval + nyilvan fontos a meretet tudni, hogy ne toljuk el
// tul sokkal a cimet
// belso tombok: int[]   === int*
// kulso tomb  : int[][] === int*[] === int** <-- pointerre mutato pointer, ezzel terunk vissza

int** createMatrix(int, int, int); // (forward) deklaracio

int main()
{
	int **mtx = createMatrix(3, 5, 42); // hasznalhatom, ezen a ponton ismert a tipusa

	// Hasznalat:
	std::cout << mtx[1][2] << std::endl;

	// teljesen ekvivalens ezzel:
	std::cout << *(*(mtx + 1) + 2) << std::endl; // eltolasok (az indexszel) es dereferalasok

	//     mtx           ~ int**
	//     mtx + 1       ~ int** eltolt cim 1-gyel
	//   *(mtx + 1)      ~ int*  kiolvasom az ott tarolt cimet
	//   *(mtx + 1) + 2  ~ int* eltolt cim 2-vel
	// *(*(mtx + 1) + 2) ~ int

	// Memory layout:
	// 
	// mtx
	//  |
	//  v      _________
	// |.|--->|_|_|_|_|_|
	// |.|--\    _________
	// |.|   \_>|_|_|X|_|_|
	//  \_    _________
	//    \_>|_|_|_|_|_|
	//
	//
	// X jeloli az mtx[1][2] elemet

	// Ne legyen memory leak!
	for (int i=0; i<3; ++i)
		delete[] mtx[i];
	delete[] mtx;
	// Eloszor az altomboket kell torolnom, mivel azokat csak a kulso tombben
	// tarolt cimeken keresztul erem el
	// Miutan az osszes pointer altat mutatott tomb tarterulete deallokalva lett,
	// torolhetem a kulso tombot is (amiben ekkor mar csak ezek a hasztalanna valt cimek vannak)
	// Miert valtak hasztalanna? delete[] utan mar nem biztonsagos (undefined behavior) onnan olvasni!
}

// n : sorok szama
// m : oszlopok szama
// defVal : alapertelmezett ertek minden elemnek
// retval : pointerre mutato pointer, ami a "kulso tomb" elso elemere mutat
int** createMatrix(int n, int m, int defVal) // definicio
{
	int **mtx = new int*[n]; // kulso pointer tomb a heap-en, int** === int*[]

	for (int i=0; i<n; ++i)
	{
		mtx[i] = new int[m]; // a kulso tomb osszes eleme egy int tomb a heap-en, mtx[i] === *(mtx + i)
		for (int j=0; j<m; ++j)
		{
			mtx[i][j] = defVal; // feltoltes, mtx[i][j] === *(*(mtx + i) + j)
		}
	}
	return mtx;
}

// Erdekesseg: tobb dimenzios statikus tombot lehet igy inicializalni:
int mtx2[4][3] = {
	{10, 20, 30},
	{10, 20, 30},
	{10, 20, 30},
	{10, 20, 30}
};
// Hasznalata ugyanaz, csak itt nem a heap-en lesz es itt ford.
// idoben ismertnek kell lennie a mereteknek (4, 3), lasd: statikus tombok

// Itt tenyleg fontos, hogy az osszes sorban pontosan ugyanannyi (pl. 3) elem legyen
// Dinamikus tombokkel valojaban lehetne eltero sorhosszakat is krealni:
//
//  _    _________
// | |->|_________|
// | |->|__|_
// | |->|____|_______
// | |->|____________|
// | |->|_|__
// |_|->|____|
//
// Oszlopok szama eltero
// new int[9]
// new int[2]
// new int[4]
// ...

