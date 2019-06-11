#ifndef _MAIGE_H_
#define _MAIGE_H_
#include"Person.h"
#include <vector>
struct Brak
{
	Person* m;
	Person* z;
};

class  MarriagesArchive
{
public:
	static void marry(Person* p1, Person* p2);
	static void divorce(Person* p);
	static Person* getSpouse(Person* p);
	static Person* getSpouse(long id);
	static vector<Person*> getMarriedMen();
	static vector<Person*> getMarriedWomen();
	

private:
	MarriagesArchive();
	static vector<Brak> brakovi;

};

class SameLastNameMarriageException:public exception{
public:
	SameLastNameMarriageException(const char* msg) : exception(msg) { };
};

class AlreadyMarriedException:public exception{
public:
	AlreadyMarriedException(const char* msg) : exception(msg) { };
};

class SameGenderMarriageException :public exception{
public:
	SameGenderMarriageException(const char* msg) : exception(msg) { };
};

class NotMarriedException:public exception{
public:
	NotMarriedException(const char* msg) : exception(msg) { };
};

#endif // !_MAIGE_H_

