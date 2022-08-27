#include <iostream>

//class A {};
//class B {};

void print (char * str) // ez a függvény egy nem-konstans pointert vár
{
	std::cout << str << std::endl;
}

int main()
{
	//int x = 42;
	//float f = static_cast<float>(x);

	//int y = static_cast<int>(f);

	//std::cout << f << "\n";

	//A * a = new A;
	//B * b = a; ford. hiba
	//B * b = reinterpret_cast<B*>(a);

	const char * c = "sample text"; // konstans pointer
	//print(c); // ford. hiba
	print(const_cast<char *>(c));   // a const_cast-tal levesszük a konstansságot

	print((char *)c);   // a const_cast-tal levesszük a konstansságot

	//int x;
	//...
	//const int * p = &x;
	//...
	//const_cast<int*>(p)
}

