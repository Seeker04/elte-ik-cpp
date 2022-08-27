
int a = 42;
int b = 128;
int c = -5;
//...
int z;

// Ebben a forditasi egysegben definialom a globalis valtozoim
// Ezt leforditva kapom a globals.o-t, amit majd bele kell linkelnem a binarisba,
// hogy ne kapjak undefined reference hibakat a linker-tol

