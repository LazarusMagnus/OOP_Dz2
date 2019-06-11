#include "Date.h"
#include<iomanip>
Date::Date(int day, int month, int year) {
	try {
		if (month < 1 || month>12)
			throw InvalidDateException("greska u mesecu");
		switch (month)
		{
		case 1:case 3:case 5:case 7:
		case 8:case 10:case 12:
			if (day < 1 || day>31)
				throw InvalidDateException("greska u danu");
			break;
		case 4:case 6:case 9:case 11:
			if (day < 1 || day>30)
				throw InvalidDateException("greska u danu");
			break;
		case 2:
			if (year % 4 != 0) {
				if (day < 1 || day>28)
					throw InvalidDateException("greska u danu");
			}
			else
			{
				if (day < 1 || day>29)
					throw InvalidDateException("greska u danu");
			}
		}

	}
	catch (InvalidDateException& se) {
		day = 1;
		month = 1;
		year = 1900;
		cout << se.what() << endl;
	}
	this->day=day;
	this->month = month;
	this->year = year;
}
void print(ostream & os, Date & date){
	os<<setw(2)<<setfill('0')<< date.day <<'.' << date.month << '.'<<setw(4)<< date.year << endl;
}
bool operator==(Date& d1, Date& d2) {
	if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)
		return true;
	else
		return false;
}
bool operator>(Date& d1, Date& d2) {
	if (d1.year > d2.year)
		return true;
	if (d1.year == d2.year) {
		if (d1.month > d2.month)
			return true;
		if (d1.month == d2.month)
			if (d1.day > d2.day)
				return true;
	}
	return false;
}
bool operator<(Date& d1, Date& d2) {
	if (d1 > d2 || d1 == d2)
		return false;
	else
		return true;
}
bool operator<=(Date& d1, Date& d2) {
	if (d1 > d2)
		return false;
	else
		return true;
}
bool operator>=(Date& d1, Date& d2) {
	if (d1 < d2)
		return false;
	else
		return true;
}
bool operator!=(Date& d1, Date& d2) {
	return !(d1 == d2);
}

int operator-(Date& d1, Date& d2){
	int m, d = 0, t;
	t = d2.year - d1.year;
	m = d2.month - d1.month;
	d = d2.day - d1.day;

	if (m > -6 && m < 6) {
		return t;
	}
	else {
		if ((m == 6 && d < 0) || (m == -6 && d > 0)) return t;
		if ((m < -6) || (m == -6 && d < 0)) return --t;
		t++;
	}
	return t;
}
