#include "helpers.h"

long helpers::validarLong(){
   long numero = 0;
   cout << "Por favor, ingrese una clave de acceso: ";
    while(!(cin >> numero)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor, ingresa un número: ";
    }
    return numero;
 }

 int helpers::validarInt(int maximo){
   int numero;
    cout << "Respuesta: ";
    do{
      while(!(cin >> numero)) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Entrada inválida. Por favor, ingresa un número: ";
      }
    }while(numero <= 0 || numero > maximo);
    return numero;
 }
