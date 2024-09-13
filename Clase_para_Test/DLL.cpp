//
// Created by josepa on 12/09/24.
//

#include "DLL.h"
#include <iostream>

template<typename T>
DLL<T>::DLL() : largo(0) {}

template<typename T>
DLL<T>::~DLL() {
    while (largo>0) {
        MPointer<nodeTest<T>> tmp = head;
        head = head.getPointer()->getNext();
        tmp.deletePointer(true);
        largo--;
    }
    tail = MPointer<nodeTest<T>>::createNew();
    MPointerGC* GC = MPointerGC::getInstance();
    head.deletePointer(true);
    tail.deletePointer(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    GC->debug();
}

//GETS
template<typename T>
MPointer<nodeTest<T>> DLL<T>::getHead() const {
    return head;
}
template<typename T>
MPointer<nodeTest<T> > DLL<T>::getTail() const {
    return tail;
}
template<typename T>
int DLL<T>::getLargo() const {
    return largo;
}

//Agrega..
template<typename T>
void DLL<T>::Agrega_head(T value) {
    MPointer<nodeTest<T>> newHead = MPointer<nodeTest<T>>::createNew();
    newHead = new nodeTest<T>(value);
    if (!head.VeriValiValue()) {
        head = tail = newHead;
    }else {
        newHead.getPointer()->setNext(head);
        head.getPointer()->setPrev(newHead);
        head = newHead;
    }
    largo++;
}
template<typename T>
void DLL<T>::Agrega_tail(T value) {
    MPointer<nodeTest<T>> newTail = MPointer<nodeTest<T>>::createNew();
    newTail = new nodeTest<T>(value);
    if (!tail.VeriValiValue()) {
        head = tail = newTail;
    }else {
        tail.getPointer()->setNext(newTail);
        newTail.getPointer()->setPrev(tail);
        tail = newTail;
    }
    largo++;
}

//Borrar
template<typename T>
void DLL<T>::Bora_node(int pos) { //Era Borra_node pero tambien me dio gracia el "Bora", lo dejaré
    if (pos < 0 || pos >= largo) {
        std::cerr << "Error" << std::endl;
        return;
    }
    if (largo == 1 && pos == 0) {
        head.deletePointer(true);
        head = MPointer<nodeTest<T>>::createNew();
        tail = MPointer<nodeTest<T>>::createNew();
        largo--;
        return;
    }

    MPointer<nodeTest<T>> actualnode = MPointer<nodeTest<T>>::createNew();
    int i;

    if (pos < largo/2) {
        actualnode = head;
        i = 0;
        while (i<pos) {
            actualnode = (actualnode.getPointer())->getNext();
            i++;
        }
    } else {
        actualnode = tail;
        i = largo-1;
        while (i>pos) {
            actualnode = (actualnode.getPointer())->getPrev();
            i--;
        }
    }

    if (actualnode.VeriValiValue()) {
        if (actualnode.isSamePointer(head)) {
            head = (head.getPointer())->getNext();
            if (head.VeriValiValue()) {
                (head.getPointer())->setPrev(MPointer<nodeTest<T>>::createNew());
            }
        } else if (actualnode.isSamePointer(tail)) {
            tail = (tail.getPointer())->getPrev();
            if (tail.VeriValiValue()) {
                (tail.getPointer())->setNext(MPointer<nodeTest<T>>::createNew());
            }
        } else {
            MPointer<nodeTest<T>> tmp = (actualnode.getPointer())->getPrev();
            (tmp.getPointer())->setNext((actualnode.getPointer())->getNext());
            tmp = (actualnode.getPointer())->getNext();
            (tmp.getPointer())->setPrev((actualnode.getPointer())->getPrev());
        }

        actualnode.deletePointer(true);
        largo--;

    } else {
        std::cerr << "Error al eliminar posición" << std::endl;
    }


}

//Remplazar
template<typename T>
void DLL<T>::replace(int pos, T newvalue) {
    if (pos<0 || pos>=largo) {
        std::cerr << "Error" << std::endl;
        return;
    }

    MPointer<nodeTest<T>> actualnode = MPointer<nodeTest<T>>::createNew();
    int i;

    if (pos< largo/2) {
        actualnode = head;
        i = 0;
        while (i < pos) {
            actualnode = (actualnode.getPointer())->getNext();
            i++;
        }
    } else {
        actualnode = tail;
        i = largo-1;
        while (i > pos) {
            actualnode = (actualnode.getPointer())->getPrev();
            i--;
        }
    }

    if (actualnode.VeriValiValue()) {
        (actualnode.getPointer())->setData(newvalue);
    } else {
        std::cerr << "Error al reemplazar posición" << std::endl;
    }
}

//Printeo
template<typename T>
void DLL<T>::printList() {
    if(largo>0) {
        MPointer<nodeTest<T>> actualnode = MPointer<nodeTest<T>>::createNew();
        actualnode = head;
        while (!actualnode.isSamePointer((tail.getPointer())->getNext())) {
            std::cout << (actualnode.getPointer())->getData() << std::endl;
            actualnode = (actualnode.getPointer())->getNext();
        }
        std::cout << std::endl;
    }
}











