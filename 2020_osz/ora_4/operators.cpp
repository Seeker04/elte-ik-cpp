#include <iostream>

// Emlekezteto: az operatorok specialis szintaxisu fuggvenyek (fix szimbolum +
// parameterek szama is fix a legtobb esetben, pl. operator+ pontosan 2 paramot kaphat)
// A "kinezetuket" leszamitva teljesen ekvivalensek a fuggvenyekkel:
// parameterek === operandusok + egyeb fogalmak (stack, lokalis valtozok,
// visszateresi ertek, tulterheles, stb.) megegyeznek

struct Point {
	int x, y;
};

// Operator tulterheles (overloading)
bool operator==(Point p1, Point p2) // 2 param -> binaris operator (infix szintaxis)
{
	return p1.x == p2.x && p1.y == p2.y; // itt a precedencia szabalyok fontosak: == erosebb &&-nel
	                                     // standard eloirja, de persze zarojelekkel lehetunk explicitek
}

int main()
{
	Point p = {10, 20}; // igy is OK: Point p {10, 20};
	Point q = {10, 20};
	// Megjegyzes: azert lehet igy kapcsoszarojeles listaval inicializalni, mert
	// az osztaly osszes tagja public (lasd: struct kulcsszo lett hasznlava)

	if (p == q) // hasznalat, ha kitoroljuk az operator==-nek a bool(Point,Point) prototipusat -> ford. hiba lenne
		std::cout << "igen\n";
	else
		std::cout << "nem\n";

}

