// 2. pluszminusz

#include <iostream>

struct Date {
	int year;
	int month;
	int day;
};

class Person {

public:

	Person(const Date& date, const std::string& name = "John Doe") :
		_name(name),
		_dateOfBirth(date){}

	// getters
	std::string getName() const { return _name; }
	Date getDateOfBirth() const { return _dateOfBirth; }

	// setters
	void setName(const std::string& name) { _name = name; }
	void setDateOfBirth(const Date& date) { _dateOfBirth = date; }

private:

	std::string _name;
	Date _dateOfBirth;

};

int main()
{
	Date d1 {1980, 10, 13};
	Date d2 {2003, 11, 19};

	const Person p1(d1, "Paul");
	      Person p2(d2);

	std::cout << p1.getName() << ", " << p2.getName() << std::endl; // Paul, John Doe

	Date d = p1.getDateOfBirth();
	std::cout << d.year << "." << d.month << "." << d.day << std::endl; // 1980.10.13

	p2.setName("Will");
	p2.setDateOfBirth({1995, 12, 24});
	std::cout << p2.getName() << std::endl; // Will
	std::cout << p2.getDateOfBirth().year << std::endl; // 1995
}

