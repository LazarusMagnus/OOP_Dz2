#ifndef _ARCHIVE_
#define _ARCHIVE_

#include<list>
#include "Date.h"
using namespace std;

class PersonalIdArchive
{
public:
	static void addRecord(long id);
	static long nextId() {
		return nextid;
	};
	static list<long> getRecords() {
		return archive;
	};
	static bool containsId(long id);

	PersonalIdArchive() = delete;

private:
	static list<long> archive;
	static long nextid;
};

class MultiplePersonalIdException :public exception
{
public:
	MultiplePersonalIdException(const char* msg) : exception(msg) {};

private:

};

#endif // !_ARCHIVE_
