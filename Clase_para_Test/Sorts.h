//
// Created by josepa on 12/09/24.
//

#ifndef SORTS_H
#define SORTS_H
#include "DLL.h"

//Sorts

//Bubble
template <typename T>
void BS(DLL<T>& list);

//Quick
//Partir en dos la lista
template <typename T>
MPointer<nodeTest<T>> partition(MPointer<nodeTest<T>> bajo, MPointer<nodeTest<T>> alto);
//Algoritmo que ve como hacer la particion
template <typename T>
void QSRec(MPointer<nodeTest<T>> bajo, MPointer<nodeTest<T>> alto);
//El quick como tal
template <typename T>
void QS(DLL<T>& list);

//Insertion
template <typename T>
void IS(DLL<T>& list);

//Swaps
template <typename T>
void swap(MPointer<nodeTest<T>> node1, MPointer<nodeTest<T>> node2);

#include "Sorts.cpp"
#endif //SORTS_H
