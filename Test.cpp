#include "Date.h"
#include "Person.h"
#include"MarriagesArchive.h"
#include"PersonalIdArchive.h"
#include"TreeNode.h"
#include"FamilyTree.h"
#define STUDENT_TEST 1
using namespace std;
// Ako je definisan makro PROF_TEST deklarisace se funkcija test, cija implementacija ce biti
//data u drugom.cpp fajlu
#ifdef PROF_TEST
void test();

#elif STUDENT_TEST
void test() {
	Person* baki = new Male("Baki", "Flipovski", Date(26, 4, 1900), 2);
	Person* laki = new Male("Laki", "Flipovski", Date(26, 4, 1990), 3);
	Person* laki1 = new Male("Laki1", "Flipovski", Date(16, 4, 1999), 3);
	Person* laki2 = new Male("Laki2", "Flipovski", Date(12, 4, 2018), 50);
	Person* laki3 = new Male("Laki3", "Flipovski", Date(6, 4, 2040), 50);
	Person* maki = new Female("Maki", "Flipovski", Date(26, 4, 2060), 1);
	Person* naki = new Male("Narko", "Flipovski", Date(26, 4, 2080), 1);
	MarriagesArchive::marry(baki, maki);
	Person* p1 = MarriagesArchive::getSpouse(baki);
	//MarriagesArchive::divorce(baki);
	p1 = MarriagesArchive::getSpouse(baki);
	TreeNode* p = new TreeNode(baki);
	vector <int> form = { 2,2,1,1,0,0,0 };
	vector<Person*> fam = { baki,laki,laki1,laki2,laki3,maki,naki };
	FamilyTree * stablo = new FamilyTree("Flipovski", form, fam);
	print(cout, *stablo);
	bool t = stablo->remove(laki);
	cout << endl;
	print(cout, *stablo);
	FamilyTree T = *stablo;
	cout << endl;
	//print(cout, T);
	cout << endl;


	Person* gaus = new Male("Gauss", "Mladenovski", Date(26, 4, 1900), 2);
	Person* Darko = new Male("Darko", "Mladenovski", Date(26, 4, 1990), 2);
	Person* Darko1 = new Male("Darko1", "Mladenovski", Date(26, 4, 2010), 2);
	Person* Darko2 = new Male("Darko2", "Mladenovski", Date(26, 4, 2030), 2);
	Person* Darko3 = new Male("Darko3", "Mladenovski", Date(26, 4, 2050), 2);
	Person* kati = new Female("Katarina", "Mladenovski", Date(26, 4, 2070), 2);
	vector <int> form2 = { 2,1,1,1,0,0 };
	vector<Person*> fam2 = { gaus,Darko,Darko1,Darko2,Darko3,kati };
	MarriagesArchive::marry(maki, Darko);
	MarriagesArchive::marry(kati, baki);
	FamilyTree * ft2 = new FamilyTree("Mladenovski", form2, fam2);
	int br = numberOfMarriages(*stablo, *ft2);
	cout << "br brak:" << br << endl;
	MarriagesArchive::divorce(kati);
	br = numberOfMarriages(*stablo, *ft2);
	cout << "br brak:" << br << endl;
	print(cout, *ft2);
	ft2->remove(Darko);
	print(cout, *ft2);

	system("pause");
}
#endif
// main funkcija poziva metodu test() ukoliko je definisan makar jedan od makroa
int main() {
#if defined(PROF_TEST) || defined(STUDENT_TEST)
	test();
#endif
	return 0;
}

