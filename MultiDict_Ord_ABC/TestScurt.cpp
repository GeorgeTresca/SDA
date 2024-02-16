#include <assert.h>

#include "MDO.h"
#include "IteratorMDO.h"

#include <exception>
#include <vector>

using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll() {
    MDO dictOrd = MDO(relatie1);
    assert(dictOrd.dim() == 0);
    assert(dictOrd.vid());
    dictOrd.adauga(1, 2);
    dictOrd.adauga(1, 3);
    assert(dictOrd.dim() == 2);
    assert(!dictOrd.vid());
    vector<TValoare> v = dictOrd.cauta(1);
    assert(v.size() == 2);
    v = dictOrd.cauta(3);
    assert(v.size() == 0);
    IteratorMDO it = dictOrd.iterator();
    it.prim();
    while (it.valid()) {
        TElem e = it.element();
        it.urmator();
    }
    assert(dictOrd.sterge(1, 2) == true);
    assert(dictOrd.sterge(1, 3) == true);
    assert(dictOrd.sterge(2, 1) == false);
    assert(dictOrd.vid());



    //test colectia valorilor
    MDO dictOrd2 = MDO(relatie1);
    dictOrd2.adauga(1, 2);
    dictOrd2.adauga(1, 3);
    dictOrd2.adauga(2, 4);
    dictOrd2.adauga(3, 5);
    dictOrd2.adauga(3, 6);

    assert(dictOrd2.dim() == 5);
    assert(!dictOrd2.vid());
    assert(dictOrd2.colectiaValorilor().size() == 5);
    assert(dictOrd2.colectiaValorilor()[0] == 2);
    assert(dictOrd2.colectiaValorilor()[1] == 3);
    assert(dictOrd2.colectiaValorilor()[2] == 4);
    assert(dictOrd2.colectiaValorilor()[3] == 5);
    assert(dictOrd2.colectiaValorilor()[4] == 6);
    



}

