#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
    /* de adaugat */
    curent = _md.prim;
}

TElem IteratorMD::element() const{
    /* de adaugat */
    if(valid())
        return pair<TCheie,TValoare>(curent->element().first,curent->element().second);
    throw std ::exception();
    //return pair <TCheie, TValoare>  (-1, -1);
}

bool IteratorMD::valid() const {
    /* de adaugat */
    return curent != nullptr;
}

void IteratorMD::urmator() {
    /* de adaugat */
    if(!valid())
        throw std ::exception();
    curent = curent->urmator();
}

void IteratorMD::prim() {
    /* de adaugat */
    curent  = md.prim;
}


