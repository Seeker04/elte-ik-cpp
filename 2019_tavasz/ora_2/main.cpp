#include <iostream>

void print(const char * str)
{
	while (*str) {
		std::cout << *str << " ";
		++str;
	}
}

int main(int argc, char *const argv[])
{
//	int x;
//	x = 42;
//	42 = x;
//	const int y;
//	const int y = 20;
//	y = 30;

	int x = 13;
	int y = 200;

	int * p = &x;
	//std::cout << *p << std::endl;
	p = &y;
	//std::cout << *p << std::endl;
	//float* c = &x;

	struct S {
		int x = 5, y, z;
		char c;
	};

	S s;
	S * r = &s;

//	std::cout << r->c << std::endl;

//	p = *r;
//	p = r->x;
	p = &((*r).x);
	//std::cout << *p << std::endl;

	int const * const q = &x;
	//q = &y;

	int t[4] = { 12, 3, 0, 7 };
	int * v = t;

	//for (int i=0; i<10; ++i)
		//std::cout << *(v++) << std::endl;

	std::cout << *((t+1)-1) << std::endl;

	int * e = new int(130);
	std::cout << *e << std::endl;
	delete e;

	print("Hello!");
}

