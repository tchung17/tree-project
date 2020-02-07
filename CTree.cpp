#include "CTree.h"
#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;
using std::ostream;
using std::cout;

ostream& operator<<(ostream& os, CTree& rt){
  os << (&rt)->toString();
  return os;
}
CTree::CTree(char ch){
  data = ch;
  kids = NULL;
  sibs = NULL;
  prev = NULL;
}
CTree::~CTree(){
  if(sibs != NULL){
    delete sibs;
  }
  if(kids != NULL){
    delete kids;
  }
}
CTree& CTree::operator^(CTree &rt){
  this->addChild(&rt);
  return *this;
}
bool CTree::operator==(const CTree &root){
  bool test = (root.data == this->data);
  if(this->sibs && root.sibs && root.data == this->data){
    if(*(this->sibs) == *(root.sibs)){
      test = true;
    }
    else {
      test = false;
    }
  }
  if(this->kids && root.kids && root.data == this->data){
    if(*(this->kids) == *(root.kids)){
      test = true;
    }
    else {
      test = false;
    }
  }
  return test;
}
bool CTree::addChild(char ch) {
  CTree * newchild = new CTree(ch);
  bool test = addChild(newchild);
  if(test == true){
    return test;
  }
  else{
    delete newchild;
  }
  return test;
}
bool CTree::addChild(CTree * root){
  if (root->prev != NULL || root->sibs != NULL) {
    return 0;
  }  
  if (this->kids == NULL) {
    this->kids = root;
    root->prev = this;
    root->sibs = NULL;
    return 1;
  }
  if (this->kids->data == root->data) {
    return 0;
  }
  if (root->data < this->kids->data) {
    root->prev = this;
    root->sibs = this->kids;
    this->kids->prev = root;
    this->kids = root;
    return 1;
  }
  return this->kids->addSibling(root); //thiskiddata <rootdata
}
bool CTree::addSibling(char ch){
  CTree * newsibling = new CTree(ch);
  if(this->data == ch) {
    delete newsibling;
    return false;
  }
  bool test = addSibling(newsibling);
  if(test == true){
    return test;
  }
  else {
    delete newsibling;
  }
  return test;
}
bool CTree::addSibling(CTree* root){
  bool thisthenroot = (this->data < root->data);
  if(this->prev == NULL || root->prev != NULL || root->sibs != NULL || root->data == this->data){
    return 0;
  }
  if(this->sibs == NULL && thisthenroot){
    root->prev = this;
    root->sibs = this->sibs;
    this->sibs = root;
    return 1;
  }
  if(this->sibs != NULL && thisthenroot){
    return this->sibs->addSibling(root);
  }
  if(!thisthenroot){
    root->prev = this->prev;
    root->sibs = this;
    this->prev->sibs = root;
    this->prev = root;
    return 1;
  }
  return 0;
}
string CTree::toString(){
  stringstream output;
  output << data << "\n";
  if(kids != NULL){
    output << kids->toString();
  }
  if(sibs != NULL){
    output << sibs->toString();
  }
  return output.str();;
}
