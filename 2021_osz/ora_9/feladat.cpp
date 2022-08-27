#include <iostream>

class Matrix {
private:
	int _n, _m;
	int **_t;
public:
	Matrix(int n, int m) :
		_n(n),
		_m(m)
	{
		_t = new int*[n];
		for (int i=0; i<n; ++i)
			_t[i] = new int[m];

		// Csak a latvanyossagert...
		for (int i=0; i<n; ++i)
			for (int j=0; j<m; ++j)
				_t[i][j] = 42;
	}

	// Feladat: ertekadas operator-t megirni
	Matrix& operator=(const Matrix& other)
	{
		if (this == &other) // nem-e onmaganak akarok ertekul adni
			return *this;

		// Regi tomboket torolni kell!
		for (int i=0; i<_n; ++i)
			delete[] _t[i];
		delete[] _t;

		_n = other._n;
		_m = other._m;

		// Uj sajat tombok
		_t = new int*[_n];
		for (int i=0; i<_n; ++i)
			_t[i] = new int[_m];

		// Atmasolas
		for (int i=0; i<_n; ++i)
			for (int j=0; j<_m; ++j)
				_t[i][j] = other._t[i][j];

		return *this;
	}

	// Hf: copy constructor-t is kell irni!

	~Matrix()
	{
		for (int i=0; i<_n; ++i)
			delete[] _t[i];
		delete[] _t;
	}

};

int main()
{
	Matrix A(10, 20);

	Matrix B(5, 10);

	A = B;

	// Ilyesmi is mukodjon:
	// A = (B = C);
	// f(B = C);
	// azaz az operator=-nek vissza kell ternie a baloldali objektummal!
}

