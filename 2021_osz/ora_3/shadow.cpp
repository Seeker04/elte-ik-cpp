#include <iostream>

int main()
{
	int x = 5;                                                      /* L */
                                                                        /* L */
	if (1) {                                                        /* L */
		int x = 10;
		std::cout << x; // output: 10
	} // ebben az elagazas blokkban a kulso x nem latszodik
                                                                        /* L */
	std::cout << x << "\n";                                         /* L */
	return 0;                                                       /* L */
}

// A kulso x valtozo lathatosagat az if blokk belso x-sze elfedi (shadowing),
// ezert csak az L betuvel megjelolt sorokra korlatozodik a lathatosaga
//
// Viszont a kulso x elettartama az a teljes main fv futasa lesz
// (ertelem szeruen az if blokk futasa alatt is el a memoriaban a kulso x)

