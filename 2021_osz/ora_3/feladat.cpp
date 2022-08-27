#include <iostream>

/*
  Feladat:
  Probaljunk kitalalni olyan eseteket, amikor problemat okoz a kovetkezo
  parameteres makro hasznlata:
*/

#define ABS(X) ((X)<0 ? -1*(X) : (X))

int f() { std::cout << "Hello\n"; return 42; }

int main()
{
	/*
	Eml.:
	ABS(...)
	->
	ABS(...) ((...)<0 ? -1*(...) : (...))
	*/

	int i = 1;
	// ABS(++i);
	// ->
	// ((++i)<0 ? -1*(++i) : (++i))

	std::cout << ABS(++i) << "\n";
	std::cout << i << "\n";
	// output: 3, mert a ++i ketszer lett kiertekelve!

	ABS(f());
	// ->
	// ((f())<0 ? -1*(f()) : (f()))
	// output:
	// Hello
	// Hello
	// hasonloan, f itt ketszer kerul kiertekelesre, ami persze kulonosen
	// veszelyes ha valami "mellekhatast" is eredmenyez (pl. plusz kimenet,
	// globalis valtozo atirasa, stb.)
}

