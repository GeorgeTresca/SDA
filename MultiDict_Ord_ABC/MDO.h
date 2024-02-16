#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
#include <vector>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TCheie, TValoare>(-111111, -111111);


struct ABCNode {
	TElem info;
	ABCNode* parinte;
	ABCNode* stg;
	ABCNode* dr;
};



class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);
typedef TValoare(*Transformer)(TCheie, TValoare);
class MDO {
	friend class IteratorMDO;
private:
	
	ABCNode* rad;
	Relatie rel;
	int nrElements;
	


	
public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;


	ABCNode* searchNode(TCheie c, TValoare v);

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// returneaza un vector cu toate valorile din MultidicționarOrdonat
	vector<TValoare> colectiaValorilor() const;

	vector<TValoare> getValori(ABCNode* currentNode, vector<TValoare>& values) const;


	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;



	// destructorul 	
	~MDO();

	void deleteSortedMultiMap(ABCNode* currentNode);

	ABCNode* findMaxstgSide(ABCNode* currentNode);

	void removerad(ABCNode* toRemove);

	void removeNode(ABCNode* toRemove);

	void replaceInOrderRecursive(ABCNode* startNode, Transformer t);

	//replaces the value of every key, with the result given by a function invoked on the pair.
	void replaceAll(Transformer  t);

};

