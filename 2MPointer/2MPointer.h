//
// Created by josepa on 11/09/24.
//

#ifndef INC_2MPOINTER_H
#define INC_2MPOINTER_H

#include "MPointerGC.h"
#include  <type_traits>
using  namespace  std;

template<typename  T>
TipoDato TipoDato_deter() {
    if (std::is_same_v<T, int>) return TipoDato::INT;
    if (std::is_same_v<T, float>) return TipoDato::FLOAT;
    if (std::is_same_v<T, double>) return TipoDato::DOUBLE;
    return TipoDato::UNKNOWN; //Si no esta definido
}

template<typename T>
class MPointer {
    MPointerGC* GC = MPointerGC::getInstance();
private:
    int id;
    bool VeriValue = false;
    T* Pointer=nullptr;
    MPointer(); //Constructor privado como pidio el profe

public:
    //Destructor
    ~MPointer();
    MPointer(const MPointer& original);
    static MPointer<T> createNew();

    //Aca adelante ire poniendo las sobrecargas de operadores
    T& operator*();

    template <typename U>
    MPointer<T>& operator=(const U& value);

    MPointer<T>& operator=(T* ptr);
    MPointer<T>& operator=(const MPointer<T>& pointer);

    //Metodos
    bool VeriValiValue() const; //me dio mucha risa poner el nombre asi jaja; lo dejaré
    void deletePointer(bool forceDelete);
    bool isSamePointer(const MPointer<T>& other) const;
    T* getPointer();



};
#include "2MPointer.cpp"
#endif //INC_2MPOINTER_H
