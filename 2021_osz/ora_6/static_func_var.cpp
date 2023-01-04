#include <iostream>

void f()
{
	static int call_count = 0; // ez csak egyszer fut le

	// call_count elettartama (lifetime): globalis (statikus tarteruletre lett irva), azaz tuleli a fv hivasokat,
	// mas szoval: minden fv hivas ugyanazt a valtozot hasznlja ahelyett, hogy ujat gyartana
	// DE a lathatosaga (scope) tovabbra is erre az f() fv-re van korlatozva

	std::cout << "I was called " << ++call_count << " times\n";
}

int main(int argc, char *const argv[])
{
	f(); // output: I was called 1 times
	f(); // output: I was called 2 times
	f(); // output: I was called 3 times
	f(); // output: I was called 4 times
}

// Ebben van egy fel fokkal eletszerubb pelda is erre:
// https://github.com/Seeker04/elte-ik-cpp/blob/master/2020_osz/ora_4/static.cpp

