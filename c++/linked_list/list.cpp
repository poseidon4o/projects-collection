#include <iostream>
#include <cstdlib>
using namespace std;

class node
{
private:
	int val;
	node *next;
	node *prev;
public:
	node(int = 0);
	int getVal() const;
	void setVal(int);
	int at() const;
	void setNext(node*);
	void setPrev(node*);
	node* getPrev();
	node* getNext();
};

node* node::getNext() {
	return this->next;
}

node* node::getPrev() {
	return (this->prev);
}

void node::setVal(int n) {
	this->val = n;
}

int node::getVal() const {
	return this->val;
}

int node::at() const{
	return this->getVal();
}

void node::setNext(node *next) {
	this->next = next;
}

void node::setPrev(node *prev) {
    this->prev = prev;
}

node::node (int n) {
	this->next = NULL;
	this->prev = NULL;
	this->val = n;
}


class List
{
public:
	List(int n = 0);
	int val() const;
	int getLen() const;
	int len() const;
	List& val(int);
	List& getNext();
	List& getPrev();
	List& reset();
	List* operator->();
	List& push(int);
	int pop();
private:
	int length;
	node *first;
	node *last;
	node *current;
};

List::List(int n) {
	if( n > 0 ) {
		for (int c = 0; c < n; ++c) {
			if( c == 0 ){
				this->first = this->current = new node();
			} else {
				node *p = new node();
				this->current->setNext(p);
				p->setPrev(this->current);
				this->current = p;
				if( c == n-1 )
					this->last = this->current;
					this->current->setNext(this->first);
					this->first->setPrev(this->current);
			}
		}
		this->length = n;
	}
}

List* List::operator->(){
	return this;
}

int List::getLen() const {
	return this->length;
}

int List::len() const {
	return this->getLen();
}

List& List::reset() {
	this->current = this->first;
	return *this;
}

int List::val() const {
	return this->current->getVal();
}

List& List::val(int n) {
	this->current->setVal(n);
	return *this;
}

List& List::getPrev() {
	if( this->current->getPrev() != NULL )
		this->current = this->current->getPrev();
	return *this;
}

List& List::getNext() {
	if( this->current->getNext() != NULL )
		this->current = this->current->getNext();
	return *this;
}

List& List::push(int n){
	node *p = new node(n);
	this->first->setPrev(p);
	this->last->setNext(p);
	this->last = p;
	this->length++;
	this->current = this->last;
	return *this;
}

int List::pop() {
	this->current->getPrev()->setNext(this->current->getNext());
	this->current->getNext()->setPrev(this->current->getPrev());
	int ret = this->current->getVal();
	node *cur = this->current->getPrev();
	delete[] this->current;
	this->current = cur;
	return ret;
}

int main() {
    List p(10);

	for(int c = 0; c < p.len(); c++)
		p.val(c).getNext();

	p.reset();

	p.pop();
	p.reset();


	for(int c = 0; c < p.len(); c++, p.getNext())
		cout << p.val() << " | ";

	return 0;
}
