#include <sys/stat.h>

// for directory creation on Windows platform
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#endif

//...

void make_testdir()
{
	int error = 0;
#if defined(_WIN32) || defined(_WIN64)
	error = _mkdir("testdir");
#else
	error = mkdir("testdir", S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
#endif
}

// g++ -E make_testdir.cpp
// Ezzel a paranccsal meg tudjuk nezni, hogy milyen elofeldolgozott kodot fog
// adni a preprocesszor (ezt adja tovabb a C++ nyelvi forditonak)
//
// - Ha Windows-on forditjuk a kodot, akkor a <direct.h> tartalma is benne lesz,
//   illetve az _mkdir-es sor kerul bele
// - Mas OS (pl. Linux) eseten az mkdir-es sor kerul bele

