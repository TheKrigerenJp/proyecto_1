//
// Created by josepa on 04/09/24.
//

#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
using namespace std;

enum class TipoDato {
    UNKNOWN, INT, DOUBLE, FLOAT
};

struct node {
    int info;
    void* address = nullptr;
    int i = 0;
    node* next = nullptr;
    TipoDato dato;

    //Constructor
    node(int info = 0, void* address = nullptr, int i = 0, node* next=nullptr, TipoDato dato = TipoDato::INT)
        : info(info), address(address), i(i), next(next), dato(dato) {}

};

class ListaDoble {
private:
    node* head;
    int size;

public:
    //constructor
    ListaDoble(): head(nullptr), size(0) {}

    //destructor
    ~ListaDoble() = default;

    //Metodos
    void createMpointer(int id, void* address, TipoDato tipo_dato); //Crea el puntero
    void incrementRef(int identifier); //Incrementa el i
    int decrementRef(int identifier); //Decrementa el i
    void deleteNode(int identifier); //Borra el nodo
    void display();
    void cambioAddress(int Cid, void* addressC);
    int getSize() const;               // Retorna el número de nodos en la lista
    int getIDAt(int index) const;      // Retorna el ID del nodo en el índice especificado
    int getRefCount(int id) const;     // Retorna el conteo de referencias para un nodo con un ID especificado
};
#include "ListaDoble.cpp"
#endif //LISTADOBLE_H
