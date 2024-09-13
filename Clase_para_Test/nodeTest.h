//
// Created by josepa on 12/09/24.
//

#ifndef NODETEST_H
#define NODETEST_H
#include "../2MPointer/2MPointer.h"

template <typename T>
class nodeTest {

private:
    MPointer<nodeTest> previous;
    MPointer<nodeTest> next;
    T data;

public:
    nodeTest(T value) : data(value), previous(MPointer<nodeTest<T>>::createNew()), next(MPointer<nodeTest<T>>::createNew()) {}

    //Metodos
    MPointer<nodeTest> getPrev() const;
    void setPrev(MPointer<nodeTest> prev);

    MPointer<nodeTest> getNext() const;
    void setNext(MPointer<nodeTest> next);

    T getData() const;
    void setData(T value);
};


#include "nodeTest.cpp"

#endif //NODETEST_H
