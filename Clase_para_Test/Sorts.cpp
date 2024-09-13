//
// Created by josepa on 12/09/24.
//
#include "Sorts.h"

template <typename T>
void BS(DLL<T>& list) {
    if (!list.getHead().VeriValiValue()) return;

    bool swapped;
    MPointer<nodeTest<T>> actualnode = MPointer<nodeTest<T>>::createNew();

    do {
        swapped = false;
        actualnode = list.getHead();

        while (actualnode.getPointer()->getNext().VeriValiValue()) {
            if (actualnode.getPointer()->getData() > actualnode.getPointer()->getNext().getPointer()->getData()) {
                swap(actualnode, actualnode.getPointer()->getNext());
                swapped = true;
            }
            actualnode = actualnode.getPointer()->getNext();
        }
    } while (swapped);
}

//QS
template <typename T>
MPointer<nodeTest<T>> partition(MPointer<nodeTest<T>> bajo, MPointer<nodeTest<T>> alto) {
    T tmp = (alto.getData())->getData();
    MPointer<nodeTest<T>> i = (bajo.getData())->getPrev();

    for (MPointer<nodeTest<T>> j = bajo; !j.isSamePointer(alto); j = (j.getData())->getNext()) {
        if ((j.getData())->getData() <= tmp) {
            i = (!i.VeriValiValue()) ? bajo : (i.getData())->getNext();
            swap(i, j);
        }
    }
    i = (!i.VeriValiValue()) ? bajo : (i.getData())->getNext();
    swap(i, alto);
    return i;
}


template <typename T>
void QSRec(MPointer<nodeTest<T>> bajo, MPointer<nodeTest<T>> alto) {
    if (alto.VeriValiValue() && !bajo.isSamePointer(alto) && !bajo.isSamePointer((alto.getData())->getNext())) {
        MPointer<nodeTest<T>> p = partition(bajo, alto);
        QSRec(bajo, (p.getData())->getPrev());
        QSRec((p.getData())->getNext(), alto);
    }
}

template <typename T>
void QS(DLL<T>& list) {
    QSRec(list.getHead(), list.getTail());
}

template <typename T>
void IS (DLL<T>& list) {
    if (!list.getHead()) return;
    MPointer<nodeTest<T>> actualnode = list.getHead()->getNext();
    while (actualnode != nullptr) {
        T tmp = actualnode->getData();
        MPointer<nodeTest<T>> prev = actualnode->getPrev();

        while (prev != nullptr && prev->getData()> tmp) {
            prev ->getNext()->setData(prev->getData());
            prev = prev->getPrev();
        }
        if (actualnode == nullptr) {
            list.getHead()->setData(tmp);
        }else {
            prev->getNext()->setData(tmp);
        }
        actualnode = actualnode->getNext();

    }

}



template <typename T>
void swap (MPointer<nodeTest<T>> node1, MPointer<nodeTest<T>> node2) {
    T tmp = node1.getPointer()->getData();
    node1.getPointer()->setData(node2.getPointer()->getData());
    node2.getPointer()->setData(tmp);
}

