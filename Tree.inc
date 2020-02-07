#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;
using std::ostream;
using std::cout;
using std::endl;

template<typename A>
ostream& operator<<(ostream& os, Tree<A>& rt){
  os << (&rt)->toString();
  return os;
}
template <typename T>
Tree<T>::Tree(T input){
  data = input;
  kids = NULL;
  sibs = NULL;
  prev = NULL;
}
template <typename T>
Tree<T>::~Tree(){
  if(sibs != NULL){
    delete sibs;
  }
  if(kids != NULL){
    delete kids;
  }
}
template <typename T>
Tree<T>& Tree<T>::operator^(Tree &rt){
  this->addChild(&rt);
  return *this;
}
template <typename T>
bool Tree<T>::operator==(const Tree<T> &root){
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
    else{
      test = false;
    }
  }
  return test;
}
template <typename T>
bool Tree<T>::addChild(T input) {
  Tree<T> * newchild = new Tree<T>(input);
  bool test = addChild(newchild);
  if(test == true){
    return test;
  }
  else{
    delete newchild;
  }
  return test;
}
template <typename T>
bool Tree<T>::addChild(Tree<T> * root){
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
template <typename T>
bool Tree<T>::addSibling(T input){
  Tree<T> * newsibling = new Tree<T>(input);
  if (this->data == input) {
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
template <typename T>
bool Tree<T>::addSibling(Tree<T>* root){
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
template <typename T>
string Tree<T>::toString(){
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