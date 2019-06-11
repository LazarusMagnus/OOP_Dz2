#include"MarriagesArchive.h"

vector<Brak> MarriagesArchive::brakovi = vector<Brak>{};

void MarriagesArchive::marry(Person * p1, Person * p2){
	Brak b;
	try {
		if (p1->gender() == p2->gender()) {
			throw SameGenderMarriageException("isti pol");
		}
		if (p1->getLastName() == p2->getLastName()) {
			throw SameLastNameMarriageException("incest");
		}
		for (auto it = brakovi.begin(); it != brakovi.end(); it++) {
			if ((p1->getPersonalId() == it->m->getPersonalId()) || (p2->getPersonalId() == it->m->getPersonalId()))
				throw AlreadyMarriedException("muz je ozenjen");
			if ((p1->getPersonalId() == it->z->getPersonalId()) || (p2->getPersonalId() == it->z->getPersonalId()))
				throw AlreadyMarriedException("zena je udata");
		}
		if (p1->gender() == 'M') {
			b.m = p1;
			b.z = p2;
			brakovi.push_back(b);
		}
		else {
			b.m = p2;
			b.z = p1;
			brakovi.push_back(b);
		}
	}
	catch(exception& se){
		cout << se.what() << endl;
	}
}

void MarriagesArchive::divorce(Person * p){
	bool isInList=false;
	for (auto it = brakovi.begin(); it != brakovi.end(); it++) {
		if (it->m->getPersonalId() == p->getPersonalId() || it->z->getPersonalId() == p->getPersonalId()) {
			isInList = true;
			brakovi.erase(it);
			break;
			}
	}
	try {
		if (!isInList)
			throw NotMarriedException("nije vencan");
	}
	catch (exception se) {
		cout << se.what();
	}
}

Person * MarriagesArchive::getSpouse(Person * p){
	if (p->gender()=='M'){
		for (auto it = brakovi.begin(); it != brakovi.end(); ++it) {
			if (it->m->getPersonalId() == p->getPersonalId())
				return it->z;
		}
	}
	else {
		for (auto it = brakovi.begin(); it != brakovi.end(); ++it) {
			if (it->z->getPersonalId() == p->getPersonalId())
				return it->m;
		}
	}
	return nullptr;
}

Person * MarriagesArchive::getSpouse(long id){
	for (auto it = brakovi.begin(); it != brakovi.end(); ++it) {
		if (it->m->getPersonalId() == id)
			return it->z;
		if (it->z->getPersonalId() == id)
			return it->m;
	}
	return nullptr;
}

vector<Person*> MarriagesArchive::getMarriedMen(){
	vector<Person*> niz;
	for (auto it = brakovi.begin(); it != brakovi.end(); ++it)
		niz.push_back(it->m);
	return niz;
}

vector<Person*> MarriagesArchive::getMarriedWomen(){
	vector<Person*> niz;
	for (auto it = brakovi.begin(); it != brakovi.end(); ++it)
		niz.push_back(it->z);
	return niz;
}
