#include <iostream>

// Masolo konstruktor: egy masik peldany alapotat akarjuk lemasolni egy uj peldanyba

// A fordito altal generalt copy ctor az az osszes adattagon copy ctor-t fog
// hivni. Ez azt vonja maga utan, hogy ha van pointer adattag, akkor annak a
// pointer valtozonak az erteke, azaz a memoria cim lesz atmasolva es NEM AZ
// AMIRE A POINTER MUTAT

class MyClass {
public:
	int size;
	int * dyn_array;

	MyClass(int n, int start, int diff) :
		size(n),
		dyn_array(new int[size]) // gyartunk dinamikus tombot, aminek a cimevel inicializaljuk a pointer-t
	{
		int value = start;
		for (int i=0; i<size; ++i) {
			dyn_array[i] = value;
			value += diff;
		}
	}

	// A ford. ezt generalja: "shallow copy"
	/*
	MyClass(const MyClass& other) :
		dyn_array(other.dyn_array) // pointer erteke lesz masolva, ami a memoria cim
	{}
	*/

	// "deep copy"
	MyClass(const MyClass& other) :
		size(other.size),
		dyn_array(new int[size]) // SAJAT dinamikus tombje lesz...
	{
		for (int i=0; i<size; ++i)
			dyn_array[i] = other.dyn_array[i]; //...amibe atmasoljuk az ertekeket
	}

	// Kell irni dtor-t delete[] hivassal, hiszen magatol csak a dyn_array
	// pointer torlodik, az nem amire mutat
	~MyClass()
	{
		delete[] dyn_array; // shallow copy eseten itt kapnank egy "double free" futasi hibat
	}
};

int main()
{
	MyClass obj(10, 5, 3);

	for (int i=0; i<10; ++i)
		std::cout << obj.dyn_array[i] << "\n";

	MyClass other_obj(obj); // copy konstrualas

	for (int i=0; i<10; ++i)
		std::cout << other_obj.dyn_array[i] << "\n";

	obj.dyn_array[0] = -10; // ha az egyik dyn_array-jet modositom...

	std::cout << other_obj.dyn_array[0] << "\n"; //...a masike nem lesz atirva

	// Lathatjuk, hogy a kezdo cimek is masok
	std::cout << obj.dyn_array << "\n";
	std::cout << other_obj.dyn_array << "\n";
}

