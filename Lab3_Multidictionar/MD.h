#pragma once
#include<vector>
#include<utility>

using namespace std;
#define NULL_TVALOARE (-50000)
typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class Nod;

typedef Nod* pointer_nod;

class Nod{
    friend class MD;
private:
    TElem dict;
    pointer_nod adress_urmator;

public:

    //constructor
    Nod(TElem el, pointer_nod p);

    TElem element();

    pointer_nod urmator();


};

class MD
{
    friend class IteratorMD;

private:
    /* aici e reprezentarea */
    pointer_nod prim;
    int n;

public:
    // constructorul implicit al MultiDictionarului
    MD();

    // adauga o pereche (cheie, valoare) in MD
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    [[nodiscard]]vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MD
    int dim() const;

    //verifica daca MultiDictionarul e vid
    bool vid() const;

    int adaugaInexistente(MD &md);

    // se returneaza iterator pe MD
    IteratorMD iterator() const;

    // destructorul MultiDictionarului
    ~MD();



};


