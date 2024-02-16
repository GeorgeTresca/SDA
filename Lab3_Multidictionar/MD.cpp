#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;

//theta(1)
//creeaza md
MD::MD() {
    /* de adaugat */
    prim=nullptr;
    this->n=0;
}

//theta(1)
//adaugare element
void MD::adauga(TCheie c, TValoare v) {
    TValoare val = NULL_TVALOARE;
    //vector<TValoare> rez = cauta(c);

    TElem d;
    d.first = c;
    d.second = v;
    pointer_nod n = new Nod(d, nullptr);
    n->adress_urmator = prim;
    prim = n;
    //pointer_nod p = prim;
    this->n+=1;



}

//best case theta(1)
//worst case theta(n)
//average case O(n)
//stergere element din md
bool MD::sterge(TCheie c, TValoare v) {
    /* de adaugat */
    TValoare rez;
    if(this->prim == nullptr)
        return false;
    rez = NULL_TVALOARE;
    bool ok=false;
    pointer_nod p = this->prim;
    pointer_nod penultim = new Nod(p->dict, nullptr);
    while(p != nullptr)
    {
        if(p->dict.first == c && p->dict.second==v)
        {
            penultim->adress_urmator = p->adress_urmator;
            rez = p->dict.second;
            break;
        }
        penultim = p;
        p = p->urmator();
    }
    if(p == prim)
        prim = p->adress_urmator;

    if(rez != NULL_TVALOARE)
    {   ok=true;
        delete p;
        delete penultim;
        this->n-=1;
    }
    return ok;

}

//theta(n)
//cauta pentru o anumita cheie toate elementele din md si returneaza un vector
vector<TValoare> MD::cauta(TCheie c) const {
/* de adaugat */
vector<TValoare> v;
    pointer_nod p = prim;
    while(p!= nullptr)
    {
        cout<<p->dict.first<<" "<<p->dict.second<<endl;
        if(p->dict.first == c)
            v.push_back(p->dict.second);
        p = p->urmator();
    }

    return v;
}

//theta(1)
//returneaza dimensiunea md
int MD::dim() const {

    return n;
}

//theta(1)
//returneaza daca md este vid
bool MD::vid() const {
    return prim==nullptr;

}
//best case theta(m), m lungime md parametru
//worst case theta(m*n)
//overall case O(m*n)

/*adauga Inexistente(MD M,MD &md){
pointernod<-md.prim
 vector<TValoare> v
 cat timp p!= NILL
    val<-p.v
    daca cauta(md,p.element().first==0
        adauga(M,p.c,p.v)
        nr<-nr+1
    altfel daca cauta(md,p.element().first!=0
        ok<-1
        v=cauta(M,p.c)
        pentru i=0,cauta(M,p.c)
            daca v[i]==val
                ok<-0
        daca ok==1
            adauga(M,p.c,p.v)
            nr<-nr+1
     p<=p.urmator

 returneaza nr
*/
int MD::adaugaInexistente(MD &md){
    pointer_nod p=md.prim;


    int nr=0;
    vector<TValoare> v;

    while(p!=nullptr){

        int val=p->element().second;
        if(cauta(p->element().first).size()==0){
            adauga(p->element().first,p->element().second);
            nr++;
        }
        else if(cauta(p->element().first).size()!=0){
            int ok=1;
            v=cauta(p->element().first);
            for(int i=0;i<=cauta(p->element().first).size();i++){
                if(v[i]==val) ok=0;
            }

            if(ok==1){
            adauga(p->element().first,p->element().second);
            nr++;}
        }

        p=p->urmator();
    }
    return nr;

}

IteratorMD MD::iterator() const {
    return IteratorMD(*this);
}


MD::~MD() {
    /* de adaugat */
    pointer_nod p  = this->prim;
    while(p!= nullptr)
    {
        pointer_nod dealoc = p;
        p = p->urmator();
        delete  dealoc;
    }
}

Nod::Nod(TElem el, pointer_nod p) {
    dict = el;
    adress_urmator =p;
}


TElem Nod::element() {
    return dict;
}

pointer_nod Nod::urmator() {
    return adress_urmator;
}
