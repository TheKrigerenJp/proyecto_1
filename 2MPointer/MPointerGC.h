//
// Created by josepa on 04/09/24.
//

#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include "ListaDoble.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class MPointerGC {
private:
    ListaDoble lista;
    static MPointerGC* instance;
    static std::mutex mutex;
    int autogen = 0;
    bool running = false;
    std::thread threadGC;

    void CheckReferences();
    //Constructor
    MPointerGC();
    //Destructor
    ~MPointerGC();

public:
    MPointerGC(MPointerGC& other) = delete;
    void operator=(const MPointerGC&) = delete;

    //Metodos
    static MPointerGC* getInstance();
    void debug();
    int registerPointer(void* address, TipoDato tipo_dato);
    void incrementRef(int i);
    void cambioAddress(int Cid, void* addressC);
    bool decrementRef(int i);
    void stopGC();
};
#include "MPointerGC.cpp"

#endif //MPOINTERGC_H
