//
// Created by josepa on 12/09/24.
//

#include "nodeTest.h"

//Nodo anterior
template<typename T>
MPointer<nodeTest<T> > nodeTest<T>::getPrev() const {
    return previous;
}
template<typename T>
void nodeTest<T>::setPrev(MPointer<nodeTest> prev) {
    previous = prev;
}

//Nodo siguiente
template<typename T>
MPointer<nodeTest<T> > nodeTest<T>::getNext() const {
    return next;
}
template<typename T>
void nodeTest<T>::setNext(MPointer<nodeTest> nxt) {
    next = nxt;
}

//Dato
template<typename T>
T nodeTest<T>::getData() const {
    return data;
}
template<typename T>
void nodeTest<T>::setData(T value) {
    data = value;
}


