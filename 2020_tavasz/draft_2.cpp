#include <iostream>

struct SizeTester {
	int x;  // 4
	int y;  // 4
	char c; // 1
//      3 byte padding <-- implementacio altal definialt viselkedes
}; // 9? -> 12

class Person {

public:
	Person(int id, int age, std::string name) :
		m_id(id),
		m_age(age),
		m_name(name)
	{
	}

	Person(int id = 100) : // overloading -> lesz default ktor === param nelkuli ktor
		m_id(id),
		m_age(20),
		m_name("default-name")
	{
	}

	//Person() : m_id(200) {} // overloading, mi a gond ezzel?

	//        const Person * this, implicit parameter, hivo objektum cimet tarolja
	int getId()  const { return this->m_id; }
	int getAge() const { return m_age;      } // el lehet hagyni a "this->"-ot, ugyanaz a szemantika
	//           ^ konstans metodus: e miatt const pointer lesz a this

	// -> operator emlekezteto:
	// this->m_age === *(this).m_age

	//          Person * this, implicit parameter
	void setAge(int age) { this->m_age = age; } // === { *(this).m_age = age; }

	// Emlekezteto: (konstanssag nem veszhet el!), & operatornal hasonloan csak forditva
	// *:       Person* ->       Person
	// *: const Person* -> const Person

private:
	const int m_id; // inicializalni kell, uj erteket NEM kaphat!
	int m_age;
	std::string m_name;

};

struct Test2 {
	int x;
	int y;
	Person p;

	Test2() :
		p(1289, 10, "asdasd")
	{}
};

/* Pointer emlekezteto
void f(int * p) { *p = 42; }

int a,
const int ca;

f(&a);
f(&ca); // 1. & : const int  -> const int*          (itt: &a)
        // 2. * : const int* -> const int           (fv torzsben: *p)
        // 3. const int-nek nem adhatunk uj erteket (fv torzsben: *p = 42)

        // Valojaban mar az 1-nel elakad, mert az f int*-ot var es
        // const int* nem tud int*-ra konvertalodni, nem veszhet el a const!
*/

struct MyClass {

	int x;
	float f;

private:
	static int objCount; // nem az egyes peldanyok tarhelyen, hanem a static tarteruleten lesz
	                     // (mint a globalis valtozok), nem az objektumokhoz, hanem az osztalyhoz tartozik
	                     // de privat, ezert nem erhetjuk el kivulrol, csak ennek az osztalynak metodusaibol!

public:

	static int getObjCount() { return objCount; } // nem peldanyokon lehet meghivni (nincs implicit this param),
	                                              // hanem osztaly szintu fuggveny (hivhato mert public, de osztalynev-prefix kell)

	MyClass() : x(42), f(3.14f) {
		++objCount;
	}

	~MyClass() {
		--objCount;
	}
};

int MyClass::objCount = 0; // definialjuk (ill. inicializaljuk), mert a 81. sorban csak deklaracio van

void f()
{
	MyClass obj1; // |----|----|
	//                x    f

	//MyClass::objCount = 1000;

	std::cout << MyClass::getObjCount() << "\n";

	MyClass obj2;
	std::cout << MyClass::getObjCount() << "\n";

	if (true) {
		MyClass obj3;
		std::cout << MyClass::getObjCount() << "\n";
	}

	std::cout << obj1.getObjCount() << "\n"; // igy is meg lehet hivatkozni (kicsit megteveszto, mert ugy nez ki,
	                                         // mintha az obj1 peldanyhoz tartozna az objCount)
}

int main()
{
	std::cout << "sizeof(int): " << sizeof(int) << "\n";

	SizeTester t { 10, 20, 'a' };

	std::cout << "sizeof(SizeTester): " << sizeof(SizeTester) << "\n";
	std::cout << "sizeof(t): " << sizeof(t) << "\n";

	std::cout << t.y << "\n";

//--------------------------------------

	const Person cp;
	std::cout << cp.getAge() << "\n"; // mukodik const Person-on, miert?
	//cp.setAge(40); // error! miert?

	Person p1(12312, 10, "valaki");
	Person p2(2234);
	Person p3; // def ktor hivas
	Person p4(); // <-- ez egy fuggveny deklaracio! mint pl. ez: int f();
	             // (olyan fv, ami Person objektummal ter vissza es nem var egy parametert sem)

	std::cout << p3.getAge() << "\n";
	//std::cout << p4.getAge() << "\n"; // error! miert?

	std::cout << p1.getId() << "\n";

	p2.setAge(30);

	std::cout << p2.getAge() << "\n";

	//Test2 t2;
//--------------------------------------

	std::cout << MyClass::getObjCount() << "\n";
	f();
	std::cout << MyClass::getObjCount() << "\n";
}

