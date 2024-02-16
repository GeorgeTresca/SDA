#include "TestScurt.h"
#include "MD.h"
#include "IteratorMD.h"
#include <assert.h>
#include <vector>
#include<iostream>

void testAll() {
    MD m;
    m.adauga(1, 100);
    m.adauga(2, 200);
    m.adauga(3, 300);
    m.adauga(1, 500);
    m.adauga(2, 600);
    m.adauga(4, 800);

    assert(m.dim() == 6);

    assert(m.sterge(5, 600) == false);
    assert(m.sterge(1, 500) == true);

    assert(m.dim() == 5);

    vector<TValoare> v;
    v=m.cauta(4);
    v=m.cauta(6);
    assert(v.size()==0);

    v=m.cauta(1);
    assert(v.size()==1);

    assert(m.vid() == false);

    IteratorMD im = m.iterator();
    assert(im.valid() == true);
    while (im.valid()) {
        im.element();
        im.urmator();
    }
    assert(im.valid() == false);
    im.prim();
    assert(im.valid() == true);


    //test lab
    MD test=MD();
    test.adauga(1,2);
    test.adauga(1,3);
    test.adauga(2,5);
    test.adauga(3,4);
    MD test2=MD();

    assert(test.adaugaInexistente(test2)==0);
    test2.adauga(1,8);
    test2.adauga(2,6);
    test2.adauga(6,7);
    assert(test.adaugaInexistente(test2)==3);

}

