#include <iostream>

union ChNumUnion {
	char ch;
	int num;
};

// Ez is egy osztalyt definial
// A fo kulonbseg az, hogy a ch es a num adattagok osztozni fognak egy kozos
// memoria teruleten => az ossz unio meret a legnagyobb adattag meretevel egyezik
// (esetleg + padding meg lehet a vegen)
//
// |--------|--------|--------|--------|  (Tfh. most sizeof(int) == 4)
//  ^                          ^
//  num                        ch
//
// 
// - Mivel a char csak 1 byte-os, ezert az azon keresztuli atiras az ossz 4 byte-bol
//   csak az also 1-et (legkisebb helyiertek) fogja modositani => num is valtozik
// - Ha a num adatagot modositjuk, akkor az jo esellyel azokon a biteken (legkisebb byte)
//   is modosit, melyeken a ch van => ch is modosul
// - Ha a num-nak 0..255 kozotti erteket adunk, akkor azzal elerhetjuk, hogy
//   csak a legkisebb helyierteku byte-ot (amit a ch is hasznal) modositsuk

int main()
{
	ChNumUnion cnu;

	std::cout << cnu.ch  << "\n";
	std::cout << cnu.num << "\n";

	std::cout << "-------------\n";

	cnu.ch = 'a';
	std::cout << cnu.ch  << "\n";
	std::cout << cnu.num << "\n"; // 97 <-- ez valoban az 'a' betu ASCII kodja

	cnu.num = 80;
	std::cout << cnu.ch  << "\n"; // 'P' <-- ez valoban a 80-as ASCII kodhoz tartozo karakter
	std::cout << cnu.num << "\n";
}

