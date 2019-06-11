#ifndef _TREENODE_
#define _TREENODE_
#include"Person.h"
#include<string>
class TreeNode{

public:
	TreeNode(Person *p);
	~TreeNode();
	void addChild(Person* child);
	void addSibling(Person* sibling);
	int numberOfSiblings();
	int numberOfChildren();
	Person* getPersonInfo();
	TreeNode* getOlderSiblingNode();
	TreeNode* getYoungerSiblingNode();
	TreeNode* getOldestChildNode();
	TreeNode* getOldestSiblingNode(); 
	TreeNode* getYoungestSiblingNode();
	TreeNode* getChildNode(Person* child);
	TreeNode* getSiblingNode(Person* sibling);
	void setOldestChildNode(TreeNode* tn);
	

private:
	TreeNode* olderSibling;
	TreeNode *youngerSibling;
	TreeNode* oldestChild;
	Person* personInfo;
	
};
class UnderageParentException: public exception{
public:
	UnderageParentException(const char* msg) : exception(msg) { };
	
};

class InvalidSiblingAgeException : public exception {
public:
	InvalidSiblingAgeException(const char* msg) : exception(msg) { };
};





#endif
