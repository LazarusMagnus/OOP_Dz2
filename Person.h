#ifndef _PEARSON_
#define _PEARSON_
#include<iomanip>
#include<string>
#include<list>
#include "Date.h"
using namespace std;
#include "PersonalIdArchive.h"

class Person{
public:
	//pozivnje konstruktora (ne može da se pozove konstruktor kada se inicijalizuje Date date
	Person(string first, string last, Date date, long id) : dateOfBirth(date) {
		firstName = first;
		lastName = last;
		long temp = PersonalIdArchive::nextId();
		try {
			PersonalIdArchive::addRecord(id);
			this->id = id;
		}
		catch (MultiplePersonalIdException& se) {
			cout << se.what() << endl;
			this->id = temp;
		}
	};
	string getLastName() {
		return lastName;
	};
	string getFirstName() {
		return firstName;
	};
	long getPersonalId() {
		return id;
	};
	Date getDateOfBirth() {
		return dateOfBirth;
	};
	friend bool operator<(Person& p1,Person& p2){
		return p1.dateOfBirth > p2.dateOfBirth;};
	friend bool operator>(Person& p1, Person& p2) {
		return p1.dateOfBirth < p2.dateOfBirth;};
	friend bool operator<=(Person& p1, Person& p2) {
		return p1.dateOfBirth >= p2.dateOfBirth;};
	friend bool operator>=(Person& p1, Person& p2) {
		return p1.dateOfBirth <= p2.dateOfBirth;};
	friend bool operator==(Person& p1, Person& p2) {
		return p1.dateOfBirth == p2.dateOfBirth;};
	friend bool operator!=(Person& p1, Person& p2) {
		return p1.dateOfBirth != p2.dateOfBirth;};
	friend int operator-(Person& p1, Person& p2) {
		int t = p1.dateOfBirth - p2.dateOfBirth;
		return t;};
	virtual char gender() = 0;
	friend void print(ostream& os, Person& person) {
		os << setw(9) << setfill('0') << person.id << '\t';
		os << person.lastName << '\t' << person.firstName << '\t';
		os << person.gender() << '\t';
		print(cout, person.dateOfBirth);
	};

private:
	string firstName, lastName;
	long id;
	Date dateOfBirth;
	
};
class Male : public Person {
public:
	Male(string first, string last, Date date, long id) :Person(first, last, date, id) {};
	char gender() override {
		return'M';
	}
private:
	
};
class Female : public Person {
public:
	Female(string first, string last, Date date, long id) :Person(first, last, date, id) {};
	char gender() {
		return'Z';
	}
private:
	
};
/*void print(ostream & os, Person& person)
{
	os << setw(9) << setfill('0') << person.id << '\t';
	os << person.lastName << '\t' << person.firstName << '\t';
	os << person.gender() << '\t';
	print(cout, person.dateOfBirth);
}*/
#endif