//
// Created by josepa on 11/09/24.
//

#include "2MPointer.h"

template<typename T>
MPointer<T>::MPointer() {
    id = GC->registerPointer(Pointer, TipoDato_deter<T>());

}

template<typename T>
MPointer<T>::MPointer(const MPointer & original) {
    Pointer = original.Pointer;
    id = original.id;
    GC->incrementRef(id);
}

template<typename T>
MPointer<T>::~MPointer() {
    if (GC->decrementRef(id)) {
        Pointer=nullptr;
    }
}

template<typename T>
MPointer<T> MPointer<T>::createNew() {
    MPointer<T> pointer;
    return pointer;
}

template<typename T>
T& MPointer<T>::operator*() {
    return *Pointer;
}

template<typename T>
template<typename U>
MPointer<T> &MPointer<T>::operator=(const U& value) {
    VeriValue = true;
    *Pointer = value;
    return *this;

}

template<typename T>
MPointer<T> &MPointer<T>::operator=(T* puntero) {
    if (Pointer != puntero) {
        VeriValue = true;
        if (Pointer) {
            bool shouldDelete = GC->decrementRef(id);
            deletePointer(shouldDelete);
        }
        Pointer=puntero;
    }
    return *this;
}

template<typename T>
MPointer<T> &MPointer<T>::operator=(const MPointer<T>& puntero) {
    if (this != &puntero) {
        VeriValue = true;
        Pointer = puntero.Pointer;
        GC->incrementRef(puntero.id);
        bool shouldDelete = GC->decrementRef(id);
        id = puntero.id;
    }
    return *this;

}

template<typename T>
void MPointer<T>::deletePointer(bool forceDelete) {
    if (forceDelete) {
        delete Pointer;
        Pointer = nullptr;
    }
}

template<typename T>
bool MPointer<T>::VeriValiValue() const {
    return VeriValue;
}

template<typename T>
bool MPointer<T>::isSamePointer(const MPointer<T> &other) const {
    return this->Pointer == other.Pointer;
}

template<typename T>
T *MPointer<T>::getPointer() {
    return this->Pointer;
}



