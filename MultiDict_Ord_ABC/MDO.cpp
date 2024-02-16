#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	this->rad = nullptr;
	this->rel = r;
	this->nrElements = 0;

	
}

//BC: Theta(1), WC: Theta(inaltime) -> Total : O(inaltime)
void MDO::adauga(TCheie c, TValoare v) {
	

	if (this->rad == nullptr) {
		
		auto* newNode = new ABCNode();
		newNode->info.first = c;
		newNode->info.second = v;
		this->rad = newNode;
		this->nrElements++;
	}
	else {
		ABCNode* currentNode = this->rad;
		ABCNode* previousNode = nullptr;
		//gaseste parintele noului nod
		while (currentNode != nullptr) {
			if (this->rel(c, currentNode->info.first)) {
				//caz stanga
				previousNode = currentNode;
				currentNode = currentNode->stg;
			}
			else {
				//caz dreapta
				previousNode = currentNode;
				currentNode = currentNode->dr;
			}
		}
		//adaug nodul si il conectez la parinte
		auto* newNode = new ABCNode();
		newNode->info.first = c;
		newNode->info.second = v;
		newNode->parinte = previousNode;
		this->nrElements++;
		if (this->rel(c, previousNode->info.first)) {
			//nodul va fi copilul stanga
			previousNode->stg = newNode;
		}
		else {
			//nodul va fi copilul dreapta
			previousNode->dr = newNode;
		}
	}
}

//BC: Theta(1), WC: Theta(nrElements) -> Total : O(nrElements)
vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> matching;
	ABCNode* currentNode = this->rad;
	while (currentNode != nullptr) {
		if (this->rel(c, currentNode->info.first)) {
			// elementele se afla pe stajnga daca exista
			if (c == currentNode->info.first) {
				matching.push_back(currentNode->info.second);
			}
			currentNode = currentNode->stg;
		}
		else {
			// elementele se afla pe dreapta daca exista
			currentNode = currentNode->dr;
		}
	}
	return matching;
}


//BC: Theta(1), WC: Theta(nrElements) -> Total : O(nrElements)
ABCNode* MDO::searchNode(TCheie c, TValoare v) {
	ABCNode* returnNode = nullptr;
	ABCNode* currentNode = this->rad;
	bool ok = false;
	while (currentNode != nullptr && !ok) {
		if (this->rel(c, currentNode->info.first)) {
			// elementul se afla pe stajnga daca exista
			if (c == currentNode->info.first) {
				if (v == currentNode->info.second) {
					returnNode = currentNode;
					ok = true;
				}
			}
			currentNode = currentNode->stg;
		}
		else {
			// elementul se afla pe dreapta daca exista
			currentNode = currentNode->dr;
		}
	}
	return returnNode;
}

//BC: Theta(1), WC: Theta(nrElements + inaltime) -> Total : O(nrElements + inaltime)
bool MDO::sterge(TCheie c, TValoare v) {
	bool removed = false;
	ABCNode* toRemove = this->searchNode(c, v);
	if (toRemove != nullptr) {
		if (toRemove == this->rad) {
			//remove the rad
			this->removerad(toRemove);
		}
		else {
			//remove a node
			this->removeNode(toRemove);
		}
		removed = true;
		this->nrElements--;
	}
	return removed;
}

int MDO::dim() const {
	return this->nrElements;
}

bool MDO::vid() const {
	if (this->nrElements == 0)
		return true;
	return false;
}



	// BC,WC: Theta(nrElements) -> Total : Theta(nrElements)
//pseudocod pentru colecia valorilor
// colectiaValorilor():
// 	values = []
// 	getValori(rad, values)
// returneaza values
// sf subalgoritm
//

//getValori(currentNode, values) :
	// 	daca currentNode != NIL:
	// 		values.adauga(currentNode.info.second)
	// 		getValori(currentNode.stg, values)
	// 		getValori(currentNode.dr, values)
	// sf daca
	// returneaza values
	// sf subalgoritm
vector<TValoare> MDO::colectiaValorilor() const {
	
	vector<TValoare> values;
	this->getValori(this->rad, values);
	return values;
	
	
	
}



vector <TValoare> MDO::getValori(ABCNode* currentNode, vector<TValoare>& values) const {
	if (currentNode != nullptr) {
		values.push_back(currentNode->info.second);
		this->getValori(currentNode->stg, values);
		this->getValori(currentNode->dr, values);
	}
	return values;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}


//Theta(nrElements)
MDO::~MDO() {
	this->deleteSortedMultiMap(this->rad);
}

//Theta(nrElements)
void MDO::deleteSortedMultiMap(ABCNode* currentNode) {
	if (currentNode != nullptr) {
		if (currentNode->stg != nullptr) {
			this->deleteSortedMultiMap(currentNode->stg);
		}
		if (currentNode->dr != nullptr) {
			this->deleteSortedMultiMap(currentNode->dr);
		}
	}
}

//BC: Theta(1), WC: Theta(inalt) -> Total : O(height)
ABCNode* MDO::findMaxstgSide(ABCNode* currentNode) {
	//gaseste max din partea stanga
	ABCNode* node = currentNode->stg;
	bool changed = false;
	while (node->dr != nullptr) {
		node = node->dr;
		changed = true;
	}
	if (changed) {
		node->parinte->dr = nullptr;
	}
	return node;
}


//BC: Theta(1), WC: Theta(inalt) -> Total : O(height)
void MDO::removerad(ABCNode* toRemove) {
	if (toRemove->dr != nullptr && toRemove->stg != nullptr) {
		//sterge radacina cu 2 copii
		ABCNode* replacementNode = this->findMaxstgSide(toRemove);
		if (replacementNode == toRemove->stg) {
			//inlocuitorul este copilul stang
			replacementNode->dr = toRemove->dr;
			replacementNode->dr->parinte = replacementNode;
			replacementNode->parinte = nullptr;
			ABCNode* radToDelete = toRemove;
			this->rad = replacementNode;
			delete radToDelete;
		}
		else {
			// inlocuitorul nu este copilul stang
			replacementNode->dr = toRemove->dr;
			replacementNode->dr->parinte = replacementNode;
			replacementNode->parinte = nullptr;
			replacementNode->stg = toRemove->stg;
			replacementNode->stg->parinte = replacementNode;
			ABCNode* radToDelete = toRemove;
			this->rad = replacementNode;
			delete radToDelete;
		}
	}
	else if (toRemove->dr == nullptr && toRemove->stg == nullptr) {
		//sterge radacina fara copii(frunza)
		ABCNode* radToDelete = toRemove;
		this->rad = nullptr;
		delete radToDelete;
	}
	else {
		//sterge radacina cu un copil
		if (toRemove->dr != nullptr) {
			//rada are un copil pe dreapta
			ABCNode* newrad = toRemove->dr;
			ABCNode* radToDelete = toRemove;
			newrad->parinte = nullptr;
			this->rad = newrad;
			delete radToDelete;
		}
		else {
			//rad are un copil pe stanga
			ABCNode* newrad = toRemove->stg;
			ABCNode* radToDelete = toRemove;
			newrad->parinte = nullptr;
			this->rad = newrad;
			delete radToDelete;
		}
	}
}


//BC: Theta(1), WC: Theta(inalt) -> Total complexity: O(inalt)
void MDO::removeNode(ABCNode* toRemove) {
	if (toRemove->dr != nullptr && toRemove->stg != nullptr) {
		//sterg un nod cu 2 copii
		ABCNode* replacementNode = this->findMaxstgSide(toRemove);
		if (replacementNode == toRemove->stg) {
			//inlocuitorul este copilul stang
			replacementNode->dr = toRemove->dr;
			replacementNode->dr->parinte = replacementNode;
			replacementNode->parinte = toRemove->parinte;
			if (replacementNode->parinte->stg == toRemove) {
				// inlocuitorul va inlocui copilul stang al parintelui
				replacementNode->parinte->stg = replacementNode;
			}
			else {
				// inlocuitorul va inlocui copilul drept al parintelui
				replacementNode->parinte->dr = replacementNode;
			}
			ABCNode* nodeToDelete = toRemove;
			toRemove = replacementNode;
			delete nodeToDelete;
		}
		else {
			// inlocuitorul nu este copilul stang
			replacementNode->dr = toRemove->dr;
			replacementNode->dr->parinte = replacementNode;
			replacementNode->parinte = toRemove->parinte;
			if (replacementNode->parinte->stg == toRemove) {
				//	inlocuitorul va inlocui copilul stang al parintelui
				replacementNode->parinte->stg = replacementNode;
			}
			else {
				// inlocuitorul va inlocui copilul drept al parintelui
				replacementNode->parinte->dr = replacementNode;
			}
			replacementNode->stg = toRemove->stg;
			replacementNode->stg->parinte = replacementNode;
			ABCNode* nodeToDelete = toRemove;
			toRemove = replacementNode;
			delete nodeToDelete;
		}
	}
	else if (toRemove->dr == nullptr && toRemove->stg == nullptr) {
		//sterge un nod fara copii(frunza)
		if (toRemove->parinte->stg == toRemove) {
			// nodul este copilul stang al parintelui
			toRemove->parinte->stg = nullptr;
			delete toRemove;
		}
		else if (toRemove->parinte->dr == toRemove) {
			// nodul este copilul drept al parintelui	
			toRemove->parinte->dr = nullptr;
			delete toRemove;
		}
	}
	else {
		//sterge un nod cu un copil
		if (toRemove->parinte->stg == toRemove) {
			// nodul este copilul stang al parintelui
			if (toRemove->stg != nullptr) {
				// dacă nodul are copil stâng, trebuie să îl legăm la parintele parintelui
				toRemove->parinte->stg = toRemove->stg;
				toRemove->stg->parinte = toRemove->parinte;
			}
			else {
				// daca nodul are copil drept, trebuie sa il legam la parintele parintelui
				toRemove->parinte->stg = toRemove->dr;
				toRemove->dr->parinte = toRemove->parinte;
			}
			delete toRemove;
		}
		else {
			// nodul este copilul drept al parintelui
			if (toRemove->stg != nullptr) {
				// dacă nodul are copil stâng, trebuie să îl legăm la parintele parintelui
				toRemove->parinte->dr = toRemove->stg;
				toRemove->stg->parinte = toRemove->parinte;
			}
			else {
				// daca nodul are copil drept, trebuie sa il legam la parintele parintelui
				toRemove->parinte->dr = toRemove->dr;
				toRemove->dr->parinte = toRemove->parinte;
			}
			delete toRemove;
		}
	}
}


void MDO::replaceInOrderRecursive(ABCNode* startNode, Transformer t) {
	if (startNode != nullptr) {
		this->replaceInOrderRecursive(startNode->stg, t);
		TValoare value = t(startNode->info.first, startNode->info.second);
		startNode->info.second = value;
		this->replaceInOrderRecursive(startNode->dr, t);
	}
}
//Theta(n)

void MDO::replaceAll(Transformer  t) {
	ABCNode* startNode = this->rad;
	this->replaceInOrderRecursive(startNode, t);
}
//Theta(n)