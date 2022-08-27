#ifndef HEADER2__H // <-- ez mindig legyen egyedi szimbolum!
#define HEADER2__H

#include "header.h" // az #include preprocessor direktiva tranzitiv, tehat ha
                    // valami include-olja ezt a header-t, abba benne lesz "header.h" tartalma is

void out()
{
	std::cout << z << "\n";
}

#endif // HEADER2__H

