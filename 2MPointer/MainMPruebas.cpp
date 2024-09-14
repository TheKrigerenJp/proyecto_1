//
// Created by josepa on 11/09/24.
//

#include <thread>
#include <chrono>
#include <iostream>
#include "2MPointer.h"

int main() {

  //Pruebas
  MPointerGC* gc = MPointerGC::getInstance();

  MPointer<int> prueba1 = MPointer<int>::createNew();
  *prueba1 = 2;
  gc->debug();


  MPointer<int> prueba2 = MPointer<int>::createNew();
  *prueba2 = 88;
  gc->debug();


  MPointer<int> prueba3 = prueba2;
  gc->debug();


  prueba1 = prueba3;
  gc->debug();


  MPointer<double> prueba_pri1 = MPointer<double>::createNew();
  *prueba_pri1 = 4.231;
  gc->debug();


  *prueba2 = 150;
  *prueba_pri1 = 5.333;
  gc->debug();


  for (int i = 0; i < 10; i++) {
    MPointer<int> temp = MPointer<int>::createNew();
    *temp = i * 10;
  }
  gc->debug();



  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  gc->debug();
  return 0;



}

