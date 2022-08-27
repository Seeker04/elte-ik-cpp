#include <iostream>

int main()
{
	std::cout << sizeof(bool) << "\n"; // 1

	// legalabb 1 byte-nak lennie kell, hiaba fer el 1 bit-en is az informacio
	// bit-et nem lehet megcimezni, csak bajtot (pl. ha bool tipusu valtozo
	// memoria cimet le akarom kerni pointerhez), ill. a memoriabol processor
	// register-be bajtot/bajtokat lehet masolni, biteket nem (az atmasolt
	// bajt bitjein persze lehet allitani es utana azt RAM-ba visszairni...)
}

