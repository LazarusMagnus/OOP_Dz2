#include"FamilyTree.h"
#include<string>
#include"MarriagesArchive.h"

FamilyTree::FamilyTree(string familyname, vector<int> format, vector<Person*> family){
	//brojaci :brcvorova(mesto u family), i(mesto u format), j(iterator za format[i])
	int brcvora = 1, i = 0, j = 0;
	TreeNode* node;
	try {
		if (format.size() != family.size())
			throw InvalidVectorSize("vektor se ne poklapa sa duz porodice");
		for (auto ite : family) {
			if (ite->getLastName() != familyname)
				throw InvalidFamilyNameException("ne prezivaju se isto");
		}
	}
	catch (exception &se) {
		cout << se.what() << endl;
		return;
	}
		this->familyname = familyname;
		root = new TreeNode(family[0]);
		for (auto it : family) {
			node = this->lookUp(it);
			if (node != nullptr) {
				while (j < format[i]) {
					try {
						node->addChild(family[brcvora]);
					}
					catch (exception &se) {}
					brcvora++;
					j++;
				}
			}
			i++;
			j = 0;
			if (brcvora == family.size())
				break;
		}	
	
}

FamilyTree::FamilyTree(const FamilyTree & other)
{
	stack<TreeNode*> s;
	TreeNode* tren = nullptr, *tnovi = nullptr;;
	this->root = new TreeNode(other.root->getPersonInfo());
	this->familyname= other.familyname;
	s.push(other.root);
	while (!s.empty()) {
		tren = s.top();
		
		s.pop();
		if (tren == nullptr)
			continue;

		tnovi = this->lookUp(tren->getPersonInfo());
		
		if (tren->getOldestChildNode() != nullptr) {
			tnovi->addChild(tren->getOldestChildNode()->getPersonInfo());
		}
		if (tren->getYoungerSiblingNode() != nullptr) {
			tnovi->addSibling(tren->getYoungerSiblingNode()->getPersonInfo());
		}

		s.push(tren->getYoungerSiblingNode());
		s.push(tren->getOldestChildNode());
	}
}

FamilyTree::FamilyTree(FamilyTree && other){
	this->familyname = other.familyname;
	this->root = other.root;
	other.root = nullptr;
}

FamilyTree::~FamilyTree(){
	remove(root->getPersonInfo());
}

bool FamilyTree::addSibling(Person * person, Person * sibling){
	TreeNode* p = lookUp(person);
	if (p==nullptr)
		return false;
	try {
		p->addSibling(sibling);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool FamilyTree::addChild(Person * parent, Person * child){
	TreeNode* p = lookUp(parent);
	if (p == nullptr)
		return false;
	//zbog povratne vrednosti mora da se baca dupli izuzetak
	try {
		p->addChild(child);
	}
	catch (...) {
		return false;
	}
	return true;
}

TreeNode * FamilyTree::lookUp(Person * p){
	stack<TreeNode*> stek;
	TreeNode* tren = nullptr;
	stek.push(root);
	//pre-order
	while (!stek.empty()) {
		tren = stek.top();
		stek.pop();
		if (tren == nullptr)
			continue;
		if (tren->getPersonInfo() == p)
			return tren;
		stek.push(tren->getYoungerSiblingNode());
		stek.push(tren->getOldestChildNode());
	}
	return nullptr;
}

TreeNode * FamilyTree::lookUpParent(Person * p){
	stack<TreeNode*> stek;
	TreeNode* tren = nullptr;
	stek.push(root);
	while (!stek.empty()) {
		tren = stek.top();
		stek.pop();
		if (tren == nullptr)
			continue;
		//ako nadje dete
		if (tren->getChildNode(p) != nullptr)
			return tren;
		stek.push(tren->getYoungerSiblingNode());
		stek.push(tren->getOldestChildNode());
		
	}
	return nullptr;
}

bool FamilyTree::remove(Person * p){
	int br = 0;
	stack<TreeNode*> stek;

	TreeNode* tren = nullptr,*per=lookUp(p),*parrent;
	if (per == nullptr)
		return false;
	stek.push(per->getOldestChildNode());
	while (!stek.empty()) {
		tren = stek.top();
		stek.pop();
		if (tren == nullptr) {
			continue;
		}
		stek.push(tren->getYoungerSiblingNode());
		stek.push(tren->getOldestChildNode());
		//sredjuje problem najstarijeg deteta
		if (tren->getOlderSiblingNode() == nullptr) {
			parrent = this->lookUpParent(tren->getPersonInfo());
			if(parrent!=nullptr)
				parrent->setOldestChildNode(tren->getYoungerSiblingNode());
		}
		delete tren;
	}
	//sredjuje problem najstarijeg deteta(prevezuje mladje dete da bude najstarije)
	if (per->getOlderSiblingNode() == nullptr) {
		parrent = this->lookUpParent(per->getPersonInfo());
		if (parrent != nullptr)
			parrent->setOldestChildNode(per->getYoungerSiblingNode());
	}
	delete per;
	return true;
}

int numberOfMarriages(FamilyTree & ft1, FamilyTree & ft2){
	int br = 0;
	stack<TreeNode*> stek;
	TreeNode* tren = nullptr;
	stek.push(ft1.root);
	while (!stek.empty()) {
		tren = stek.top();
		stek.pop();
		if (tren == nullptr) {
			continue;
		}
		if (ft2.lookUp(MarriagesArchive::getSpouse(tren->getPersonInfo())) != nullptr)
			br++;
		stek.push(tren->getYoungerSiblingNode());
		stek.push(tren->getOldestChildNode());
	}
	return br;
}

void print(ostream & os, FamilyTree & ft){
	stack<TreeNode*> stek;
	TreeNode* tren = nullptr;
	stek.push(ft.root);
	while (!stek.empty()) {
		tren = stek.top();
		stek.pop();
		if (tren == nullptr) {
			continue;
		}
		//broj clanova u steku odredjuje generaciju
		for (int i = 0; i < stek.size(); i++)
			os << "\t";
		print(os,*(tren->getPersonInfo()));
		os << endl;

		stek.push(tren->getYoungerSiblingNode());
		stek.push(tren->getOldestChildNode());
	}
}
