// Megjegyzes: ez a peldakod szamos ok miatt nincs lefordulo allapotban (hianyoznak dolgok belole)
// Ha valaki szeretne azza hozni, akkor az jo gyakorlo feladat lehet...

// Interfesz (interface)
class IContainer {
public:
	// Tisztan virtualas (absztrakt) metodusok (definicio nelkuliek)
	virtual void addElem(int elem) = 0;
	virtual int getElem(int index) = 0;

	virtual int getsize() = 0;
	virtual void clear() = 0;

	//...

	virtual ~IContainer() {} // kell, hogy a leszarmazott oszalyok sajat dtor-jait
	                         // lehessen dinamikus kotesen keresztul hivni
};
// ^ absztakt osztaly, mert van tisztan virtual metousa -> nem lehet kozvetlen
// peldanyositani, de oroklodni persze lehet belole...

// Megvalositas (implementation) #1
class VectorContainer : public IContainer {
public:
	// Implementalja az absztrakt szulo metodusait (overriding)
	void addElem(int elem) { /*...*/ }
	int getElem(int index) { /*...*/ }

	int getsize() { /*...*/ }
	void clear() { /*...*/ }
private:
	int * _internal_array; // kell a belso adatszerkezethez
};

// Megvalositas (implementation) #2
class LinkedListContainer : public IContainer {
public:
	// hasonloan megvalosit mindent...
	void addElem(int elem) { /*...*/ }
	int getElem(int index) { /*...*/ }

	int getsize() { /*...*/ }
	void clear() { /*...*/ }
private:
	Node * _head; // kell a belso adatszerkezethez
};

int main()
{
	IContainer * container = nullptr;

	// Futasi idoben (mas neven: dinamikus idoben) dol majd el az altipus
	std::cout << "What to create? (v = VectorContainer, l = LinkedListContainer)\n";
	char answer;
	std::cin >> answer;
	if (answer == 'v')
		container = new VectorContainer; // statikus tipus: IContainer, dinamikus tipus: VectorContainer
	else if (answer == 'l')
		container = new LinkedListContainer; // statikus tipus: IContainer, dinamikus tipus: LinkedListContainer
	else
		exit(1); // hiba

	// Hasznalat
	container->addElem(42);
	container->clear();
	//...

	// Mivel az interface-en keresztul hasznaljuk, ezert kesobb barmikor lecserelhetem, hogy
	// masik implementaciot hasznaljon, hiszen csak 1 helyen kell atirnom a kodot es
	// le fog fordulni, mukodni fog (vagy akar a fentebb lathato modon ez futasi idoben
	// is eldolhet/valtozhat...)
	// Lasd: dependency injection

	// Megjegyzes: az interfaszet nem erdekli, hogy az o megvalositasai alatt milyen
	// adatszerkezetek, milyen algoritmusok vannak, hogy hogyan van megvalositva egy-egy funkcio
	// A felhasznaloja elol igy szinten el vannak rejtve az implementacios reszletek,
	// eleg az interface-t megnezni a hasznalathoz -> adatabsztrakcio elve
	// ^ Tulajdonkeppen ez a fo felhasznalasa a futasi ideju polimorfizmusnak

	delete container; // ez ne maradjon le ;)
}

