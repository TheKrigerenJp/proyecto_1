//
// Created by josepa on 12/09/24.
//

#include <iostream>
#include "../2MPointer/2MPointer.h"
#include "DLL.h"
#include "Sorts.h"

int main() {
    MPointerGC* GC = MPointerGC::getInstance();
    DLL<int> list;

    list.Agrega_head(12);
    list.Agrega_head(5);
    list.Agrega_tail(60);
    list.Agrega_tail(33);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    GC->debug();
    std::cout << "Lista: "<< endl;
    list.printList();

    list.replace(3, 35);
    std::cout << "Después de reemplazar en posición 3: "<< endl;
    list.printList();
    GC->debug();

    list.replace(0, 3);
    std::cout << "Después de reemplazar en posición 0: "<< endl;
    list.printList();
    GC->debug();

    //Para probar los sorts cambiar en la siguiente linea BS por QS O IS
    BS(list);
    std::cout << "Lista después del Sort: "<< endl;
    list.printList();
        GC->debug();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    list.Bora_node(0);
    std::cout << "Después de eliminar en posición 0: "<< endl;
    list.printList();
    GC->debug();
    list.Bora_node(0);
    std::cout << "Después de eliminar en posición 0: "<< endl;
    list.printList();
    GC->debug();
    list.Bora_node(0);
    std::cout << "Después de eliminar en posición 0: "<< endl;
    list.printList();
    GC->debug();
    list.Bora_node(0);
    std::cout << "Después de eliminar en posición 0: "<< endl;
    list.printList();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    GC->debug();
    return 0;
}

