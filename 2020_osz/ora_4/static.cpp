#include <iostream>
#include <map>

void f()
{
	static int call_count = 0; // nem a hivasi verembe (stack),
	                           // hanem a statikus memoriaba lesz irva (mint a globalis valtozok)
	                           // -> elettartam a teljes futas, de lathatosag csak ez a fv

	++call_count;
	std::cout << "I was called " << call_count << " times\n";
}

// Faktorialis fv implementacio iterativ modszerrel
int factorial(int n)
{
	static std::map<int, int> cache; // ilyesmire is jo lehet: szamitas igenyes fv-t
	                                 // ugyanarra az ertekre nem szamolunk ujra
	// (persze a factorial nem tul eletszeru pelda erre, de demonstraciora jo...)

	// ezek majd kesobb lesznek az anyagban (lasd: iteratorok, algoritmusok, std::pair,...)
	auto find_result = cache.find(n);
	if (find_result != cache.end())
		return find_result->second; // ha benne van a cache-ben, visszaadom azt

	int result = 1;
	for (int i=2; i<=n; ++i)
		result *= i;

	cache[n] = result; // elmentem az eredmenyt visszateres elott, pl. 10 -> 3628800
	return result;
}
// E helyett persze lehetett volna a cache egy sima globalis valtozo is, de az
// sokkal csunyabb megoldas, hiszen akkor barhonnan latszodna (polluting the global namespace)
// es barki tudna azt modositani (mellekhatasos kod!) -> csunya es nem biztonsagos
// Igy viszont erre a factorial fv-re van lekorlatozva a lathatosaga, igy nem problemas
// (Illetve mas-mas fuggvenyeknek lehet sajat "cache" nevu valtozoja nevutkozes nelkul)

int main()
{
	f(); // 1
	f(); // 2
	f(); // 3
	f(); // 4

	std::cout << factorial(10) << "\n";
}
