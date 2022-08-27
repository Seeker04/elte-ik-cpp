#include <iostream>

int main()
{
	const int ct[] = {10, 20, 30}; // const T[] ~ const * T
	ct[1] = 42; // hiba, miert?
	*(ct + 1) = 42; // (ct + 1) is const int*
	                // *(ct + 1) ezert const int-et ad
			// const int nem kaphat uj erteket

	int size;
	std::cin >> size;
	int t[size]; // -pedantic szol, hogy nem standard feature!

	int * dynt = new int[size]; // allokal size * sizeof(int) bajtot
	                            // def ktor-ral letrehoz size db int
				    // objektumot

	for (int i=0; i<size; ++i) {
		dynt[i] = 10*i;
	}
	for (int i=0; i<size; ++i) {
		std::cout << dynt[i]     << "\n";
		std::cout << *(dynt + i) << "\n";
	}


	std::cout << dynt[1] << "\n";

	//------------------------

	int t2[234];

	std::cout << sizeof(t2)/sizeof(*t2) << "\n";

	std::cout << sizeof(dynt)/sizeof(*dynt) << "\n";
	// ford idoben csak ennyit tudunk: int * dynt
	// pointer merete a gepemen 8 => 8/4 = 2

	delete[] dynt; // megsemmisiti a size db int objektumot (dtor)
	               // es deallokalja a size * sizeof(int) bajtot

	//------------------------
	
	struct S {
		int x;     // tfh. most sizeof(int) == 4
		char a, b; // 2*sizeof(char) == 2*1 == 2
	};

	std::cout << "sizeof(S): " << sizeof(S) << "\n";
}

