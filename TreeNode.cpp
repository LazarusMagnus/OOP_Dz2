#include "TreeNode.h"
#include<stack>

TreeNode::TreeNode(Person * p){
	youngerSibling = nullptr;
	olderSibling = nullptr;
	oldestChild = nullptr;
	personInfo = p;
}

TreeNode::~TreeNode(){
	//u sredini
	if (youngerSibling != nullptr && olderSibling != nullptr) {
		this->youngerSibling->olderSibling = this->olderSibling;
		this->olderSibling->youngerSibling = this->youngerSibling;
	}
	//na poc
	if (olderSibling == nullptr && youngerSibling != nullptr) {
		this->youngerSibling->olderSibling = nullptr;
	}
	//na kraju
	if (olderSibling != nullptr && youngerSibling == nullptr) {
		this->olderSibling->youngerSibling = nullptr;
	}
	youngerSibling = nullptr;
	olderSibling = nullptr;
	oldestChild = nullptr;
	personInfo = nullptr;
}

void TreeNode::addChild(Person * child){
	TreeNode* node = new TreeNode(child);
	try {
		int t = (*(this->getPersonInfo()) - *(child));
		if ((*(this->getPersonInfo()) - *(child)) < 18)
			throw UnderageParentException("otac mladji od deteta");
		if (this->oldestChild == nullptr)
			this->oldestChild = node;
		else {
			this->oldestChild->addSibling(child);
		}
	}
	catch(UnderageParentException se){
		cout << se.what() << endl;
		throw;
	}

}

void TreeNode::addSibling(Person * sibling){
	TreeNode* novi = new TreeNode(sibling);
	Person* temp;
	TreeNode* pret = this->getOldestSiblingNode();
	TreeNode* sled = pret->youngerSibling;
	try {
		if (*sibling > *(pret->getPersonInfo())) {
			if (*(sibling)-*(pret->getPersonInfo()) < 1)
				throw InvalidSiblingAgeException("razlika u god manja od 1");			
			if (sled != nullptr) {
				pret->youngerSibling = novi;
				sled->olderSibling = novi;
				novi->youngerSibling = sled;
				novi->olderSibling = pret;


				temp = novi->personInfo;
				novi->personInfo = pret->personInfo;
				pret->personInfo = temp;

				novi->oldestChild = pret->oldestChild;
				pret->oldestChild = nullptr;
			}
			else {
				pret->youngerSibling = novi;
				novi->olderSibling = pret;

				temp = novi->personInfo;
				novi->personInfo = pret->personInfo;
				pret->personInfo = temp;
			}
		}
		else {
			if(sled!=nullptr)
				while (*(sibling) < *(sled->getPersonInfo())) {
				pret = sled;
				sled = sled->youngerSibling;
				if (sled == nullptr)
					break;
				}
			if (sled == nullptr) {
				if (*(pret->getPersonInfo()) - *(sibling) < 1)
					throw InvalidSiblingAgeException("razlika u god manja od 1");
				pret->youngerSibling = novi;
				novi->olderSibling = pret;
			}
			else {
				if (*(pret->getPersonInfo()) - *(sibling) < 1 || *(sibling) - *(sled->getPersonInfo()) < 1)
					throw InvalidSiblingAgeException("razlika u god manja od 1");
				novi->youngerSibling = sled;
				novi->olderSibling = pret;
				pret->youngerSibling = novi;
				sled->olderSibling = novi;
			}
		}
	}
	catch (exception se) {
		cout << se.what() << endl;
	}

}

int TreeNode::numberOfSiblings(){
	int n = 0;
	TreeNode* temp = this->getOldestSiblingNode();
	if (temp == nullptr)
		return 0;
	while (temp != nullptr) {
		temp = temp->youngerSibling;
		n++;
	}
	return n;
}

int TreeNode::numberOfChildren()
{ 
	int br = 0;
	if (oldestChild == nullptr) {
		return 0;
	}
	else{
		br = oldestChild->numberOfSiblings() + 1;
	}
	return br;
}

Person * TreeNode::getPersonInfo()
{
	return personInfo;
}

TreeNode * TreeNode::getOlderSiblingNode(){

	return olderSibling;
}

TreeNode * TreeNode::getYoungerSiblingNode()
{
	return youngerSibling;
}

TreeNode * TreeNode::getOldestChildNode()
{
	return oldestChild;
}

TreeNode * TreeNode::getOldestSiblingNode(){
	TreeNode* temp = this;
	while (temp->olderSibling != nullptr){
		temp = temp->olderSibling;
	}
	return temp;
}

TreeNode * TreeNode::getYoungestSiblingNode(){
	TreeNode* temp = this;
	while (temp->youngerSibling != nullptr) {
		temp = temp->youngerSibling;
	}
	return temp;
}

TreeNode * TreeNode::getChildNode(Person * child){
	TreeNode *temp = this->getOldestChildNode();
	if (temp == nullptr)
		return nullptr;
	while (temp != nullptr) {
		if (temp->personInfo->getPersonalId() == child->getPersonalId())
			return temp;
		temp = temp->youngerSibling;
	}
	return nullptr;
}

TreeNode * TreeNode::getSiblingNode(Person * sibling){
	TreeNode* temp = this;
	while (temp != nullptr) {
		if (temp->personInfo->getPersonalId() == sibling->getPersonalId())
			return temp;
		temp = temp->youngerSibling;
	}
	temp = this;
	while (temp != nullptr) {
		if (temp->personInfo->getPersonalId() == sibling->getPersonalId())
			return temp;
		temp = temp->olderSibling;
	}

	return nullptr;
}

void TreeNode::setOldestChildNode(TreeNode * tn){
	this->oldestChild = tn;
}


