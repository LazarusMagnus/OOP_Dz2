#ifndef _FAMILYTREE_
#define _FAMILYTREE_
#include"TreeNode.h"
#include<vector>


#include<stack>
class FamilyTree
{
public:
	FamilyTree(string familyname, vector<int> format, vector<Person*> family);
	FamilyTree(const FamilyTree& other);
	FamilyTree(FamilyTree&& other);
	~FamilyTree();
	bool addSibling(Person* person, Person* sibling);
	bool addChild(Person* parent, Person* child);
	TreeNode* lookUp(Person* p);
	TreeNode* lookUpParent(Person* p);
	bool remove(Person* p);
	friend void print(ostream& os, FamilyTree& ft);
	friend int numberOfMarriages(FamilyTree& ft1, FamilyTree& ft2);




private:
	TreeNode* root;
	string familyname;


};
class InvalidVectorSize : public exception
{
public:
	InvalidVectorSize(const char* msg) : exception(msg) { };
private:

};

class InvalidFamilyNameException: public exception
{
public:
	InvalidFamilyNameException(const char* msg) : exception(msg) { };
private:

};
void print(ostream& os, FamilyTree& ft);
int numberOfMarriages(FamilyTree& ft1, FamilyTree& ft2);



#endif // !_FAMILYTHREE_
