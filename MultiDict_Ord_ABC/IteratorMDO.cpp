#include "IteratorMDO.h"
#include "MDO.h"


//Theta(nrNodes)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	ABCNode* startNode = d.rad;
	this->current = 0;
	this->inOrderRecursive(startNode);
}

void IteratorMDO::prim() {
	this->current = 0;
}

void IteratorMDO::urmator() {
	if (!valid()) {
		throw std::exception();
	}
	this->current++;
}

bool IteratorMDO::valid() const {
	if (this->current >= this->stack.getNrElements()) {
		return false;
	}
	return true;
}

//Theta(1)
TElem IteratorMDO::element() const {
	if (!valid()) {
		throw std::exception();
	}
	return this->stack[this->current];
}

//Theta(nrNodes)
void IteratorMDO::inOrderRecursive(ABCNode* startNode) {
	if (startNode != nullptr) {
		this->inOrderRecursive(startNode->stg);
		this->stack.push(startNode);
		this->inOrderRecursive(startNode->dr);
	}
}

//Theta(1)
Stack::Stack() : nrElements{ 0 }, capacity{ 10 } {
	this->elements = new ABCNode * [capacity];
}

int Stack::getNrElements() const {
	return this->nrElements;
}

int Stack::getCapacity() const {
	return this->capacity;
}


//Theta(1) amortizat
void Stack::push(ABCNode* element) {
	if (this->nrElements == this->capacity) {
		this->resize();
	}
	this->elements[this->nrElements] = element;
	this->nrElements++;
}

//Theta(nrElements)
void Stack::resize() {
	auto** newElements = new ABCNode * [this->capacity * 2];
	int index;
	for (index = 0; index < this->nrElements; ++index) {
		newElements[index] = this->elements[index];
	}
	this->capacity = this->capacity * 2;
	delete[] this->elements;
	this->elements = newElements;
}


ABCNode* Stack::pop() {
	this->nrElements--;
	return this->elements[this->nrElements];
}
//Theta(1)

TElem Stack::operator[](int position) const {
	return this->elements[position]->info;
}
//Theta(1)


Stack::~Stack() {
	delete[] this->elements;
}


