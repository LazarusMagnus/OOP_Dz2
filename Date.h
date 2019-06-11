#ifndef _DATE_
#define _DATE_

#include <iostream>
#include <exception>
using namespace std;


class Date
{
public:
	Date(int day, int month, int year);
	~Date() = default;
	friend void print(ostream& os, Date& date);
	friend bool operator==(Date& d1, Date& d2);
	friend bool operator<(Date& d1, Date& d2);
	friend bool operator>(Date& d1, Date& d2);
	friend bool operator<=(Date& d1, Date& d2);
	friend bool operator>=(Date& d1, Date& d2);
	friend bool operator!=(Date& d1, Date& d2);
	friend int operator-(Date& d1, Date& d2);

private:
	int day, month, year;
};


class InvalidDateException: public exception
{
public:
	InvalidDateException(const char* msg) : exception(msg) { };

private:

};
void print(ostream & os, Date & date);


#endif // !_DATE_