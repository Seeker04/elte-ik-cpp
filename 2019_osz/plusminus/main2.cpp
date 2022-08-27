#include <iostream>

void customPrint(const char * str)
{
	for (const char * p = str; *p!='\0'; ++p) {
		if (*p == ';')
			std::cout << "\n";
		else
			std::cout << *p;
	}
}

void customPrint2(const char * str)
{
	for (int i=0; str[i]!='\0'; ++i) {
		if (str[i] == ';')
			std::cout << "\n";
		else
			std::cout << str[i];
	}
}

int main()
{
	int nums[4] = { 10, -5, 20, -10 };
	const char text[] = "almafa";

	/* 1. */ std::cout << 1[nums] << std::endl;
	/* 2. */ std::cout << *text   << std::endl;
	/* 3. */ std::cout << *(nums-1000) << std::endl;
	/* 4. */ char * p = text; std::cout << p[2] << std::endl;
	/* 5. */ const int * pi = nums+3; std::cout << *(pi+1) << std::endl;

	/* +1 Írjunk függvényt, ami kap egy karakter tömböt és kiírja stdout-ra
	 *    az elemeit úgy, hogy minden a szövegben található pontosvessző
	 *    helyett újsorjelet ír ki */
	customPrint("ez;egy pontos vesszőkkel;széttagolt;szöveg;mint egy .csv fájl\n");
	customPrint2("ez;egy pontos vesszőkkel;széttagolt;szöveg;mint egy .csv fájl\n");
}

