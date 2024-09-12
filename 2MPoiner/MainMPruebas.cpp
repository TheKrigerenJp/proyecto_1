//
// Created by josepa on 11/09/24.
//

#include <thread>
#include <chrono>
#include <iostream>
#include "2MPointer.h"


int main() {

  MPointerGC* gc = MPointerGC::getInstance();


  // Prueba 1: Crear y asignar valores a MPointer<int>
  MPointer<int> prueba1 = MPointer<int>::createNew();
  *prueba1 = 2;
  gc->debug();  // Verificar estado después de la creación y asignación

  // Prueba 2: Crear otro MPointer<int> y asignar su valor
  MPointer<int> prueba2 = MPointer<int>::createNew();
  *prueba2 = 88;
  gc->debug();

  // Prueba 3: Copia de punteros y comprobación de referencias
  MPointer<int> prueba3 = prueba2;
  gc->debug();  // Debe mostrar que mp3 apunta a la misma dirección que mp1

  // Prueba 4: Reasignación de puntero
  prueba1 = prueba3;  // mp3 ahora debería apuntar a la misma dirección que mp2
  gc->debug();  // Verificar cambios en las referencias

  // Prueba 5: Manejo de punteros con diferentes tipos primitivos
  MPointer<double> prueba_pri1 = MPointer<double>::createNew();
  *prueba_pri1 = 4.231;
  gc->debug();

  // Prueba 6: Desreferenciar y modificar valores
  *prueba1 = 40;  // Cambiar valor al que apunta mp1
  *prueba2 = 150;  // Cambiar valor al que apunta mp2
  *prueba_pri1 = 5.333;
  gc->debug();  // Verificar cambios en valores


  // Prueba 8: Crear y eliminar múltiples punteros rápidamente
  for (int i = 0; i < 10; i++) {
    MPointer<int> temp = MPointer<int>::createNew();
    *temp = i * 10;
  }
  gc->debug();  // Verificar la correcta liberación de todos los punteros

  // Prueba 9: Reasignación en un bucle y eliminación de referencias anteriores
  MPointer<double> prueba_pri2 = MPointer<double>::createNew();
  for (int i = 0; i < 5; i++) {
    *prueba_pri2 = i * 0.5;
    gc->debug();
  }
  gc->debug();  // Verificar que solo queda una referencia

  // Simulación de tiempo de espera para verificar la salida de la consola
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  gc->debug();
  return 0;



}

