//
// Created by josepa on 12/09/24.
//

#ifndef DLL_H
#define DLL_H
#include "nodeTest.h"

template <typename T>
class DLL {
private:
    MPointer<nodeTest<T>> head = MPointer<nodeTest<T>>::createNew();
    MPointer<nodeTest<T>> tail = MPointer<nodeTest<T>>::createNew();
    int largo;

public:
    //Constructor y destructor
    DLL();
    ~DLL();

    MPointer<nodeTest<T>> getHead() const;
    MPointer<nodeTest<T>> getTail() const;
    int getLargo() const;

    void Agrega_head(T value);
    void Agrega_tail(T value);
    void Bora_node(int pos);
    void replace(int pos, T newvalue);
    void printList();

};

#include "DLL.cpp"
#endif //DLL_H
