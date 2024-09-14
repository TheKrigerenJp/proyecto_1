//
// Created by josepa on 04/09/24.
//
#include "MPointerGC.h"
#include <iostream>
#include <mutex>

MPointerGC* MPointerGC::instance = nullptr;
std::mutex MPointerGC::mutex;

//Constructor
MPointerGC::MPointerGC() {
    threadGC = std::thread(&MPointerGC::CheckReferences, this);
}

//Destructor
MPointerGC::~MPointerGC() {
    stopGC();
    if (threadGC.joinable()) {
        threadGC.join();
    }
    debug();
}

MPointerGC *MPointerGC::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new MPointerGC();
    }
    return instance;
}

void MPointerGC::cambioAddress(int Cid, void* addressC) {
    lista.cambioAddress(Cid, addressC);
}


void MPointerGC::CheckReferences() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> lock(mutex);

        for (int i = 0; i<lista.getSize(); ++i) {
            int ID = lista.getIDAt(i);
            if (lista.getRefCount(ID)<=0) {
                lista.deleteNode(ID);
                std::cout << "GC: nodo con ID" << ID << "Falta de referencias, por lo que se elimina" << std::endl;

            }
        }
    }

}

void MPointerGC::debug() {
    lista.display();
}

void MPointerGC::stopGC() {
    running = false;
}

int MPointerGC::registerPointer(void *address, TipoDato tipo_dato) {
    this->autogen++;
    int ID = this->autogen;
    this->lista.createMpointer(ID, address, tipo_dato);
    return ID;
}

void MPointerGC::incrementRef(int i) {
    lista.incrementRef(i);
}

bool MPointerGC::decrementRef(int i) {
    int ref = lista.decrementRef(i);
    return (ref==0);
}








