#include"PersonalIdArchive.h"
#include"Person.h"
void PersonalIdArchive::addRecord(long id){
	if (nextid == 1 && id == 1)
		nextid++;
	if (containsId(id)) {
		archive.push_back(nextid);
		while (containsId(nextid))
			nextid++;
		throw MultiplePersonalIdException("nije dobar broj");
	}
	else {
		archive.push_back(id);
		archive.sort();
	}
}
bool PersonalIdArchive::containsId(long id) {
	for (auto l : archive) {
		if (id == l)
			return true;
	}
	return false;
}

long PersonalIdArchive::nextid = 1;
list<long> PersonalIdArchive::archive = list<long>{};
