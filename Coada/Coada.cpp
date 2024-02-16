
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;


Coada::Coada() {
    capacity=1000;
    elements=(TElem *)malloc(sizeof(TElem)*capacity) ;
    front=1;
    back=1;
    lenght=0;


}


void Coada::adauga(TElem elem) {
    if ((front == 1 && back == capacity) || (front == back + 1))
        if (lenght == capacity) {
            int newCapacitate = capacity * 2;
            TElem *aux_elems;
            aux_elems = (TElem *) malloc(sizeof(TElem) * newCapacitate);
            if (front == 1 && back == capacity) {
                for (int i = 1; i < capacity; i++) {
                    aux_elems[i] = elements[i];
                }
                free(elements);
                elements = aux_elems;
                capacity = newCapacitate;
            }

            else if (front == back + 1) {

                int j = 1;
                for (int i = front; i <=capacity; i++) {
                    aux_elems[j] = elements[i];
                    j++;
                }
                for (int i = 1; i < back; i++) {
                    aux_elems[j] = elements[i];
                    j++;
                }
                free(elements);
                elements = aux_elems;
                capacity = newCapacitate;
            }
        }
            elements[back]=elem;
        if(back==capacity){
            back=1;
        }
        else back=back+1;
}
//arunca exceptie daca coada e vida
TElem Coada::element() const {
	if(vida()== false){
        return elements[front];
    }
    else{
        throw std::exception();
    }
	return -1;
}

TElem Coada::sterge() {
	/* de adaugat */
	return -1;
}

bool Coada::vida() const {
	if(front==back)
	    return true;
    return false;
}


Coada::~Coada() {
	free(elements);
}

