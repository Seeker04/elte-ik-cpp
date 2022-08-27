#include <iostream>

void f()
{
	exit(10); // ezzel lehet fuggvenybol terminalni a programot
}

int main(int argc, char *const argv[])
{
	//f();

	std::cout << "Arg count:" << argc << "\n";

	std::cout << "Args:\n";
	for (int i=0; i<argc; ++i) {
		std::cout << argv[i] << "\n";
	}

	// Megj.: argv[0] maganak a programnak a neve, olyan formaban (utvonallal),
	// ahogy a szulo processz elinditja (pl. ahogy a commandline-on futtatom

	if (argc == 1) {
		return 1; // konvencio: hiba jelzese hibakoddal
	}

	return 0; // konvencio: sikeres futas

	// Megj.: maradjunk 0-255 ertekeknel, mert POSIX (es valoszinuleg legtobb
	// mas rendszeren is) a szulo folyamat csak az also 1 bajtjat fogja nezni
}

