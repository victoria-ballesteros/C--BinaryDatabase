#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

//  Clases
#include "helpers.h"
#include "productos.h"

 using namespace std;
 productos producto; 

 long key[3] = {11235, 81321, 34558};

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

 int validarClave() {
   int i= 0, puesto= 0;
   bool flag= false;
   long claveIntroducida = 0;

   do{
      claveIntroducida= helper.validarLong();
      for(i = 0; i<3; i++){
         if(key[i] == claveIntroducida){
            flag= true;
            puesto= i;
            break;
         }
      }
   }while(flag != true);
   return puesto;
 }
 
 void agregarRegistro (int eleccionMenu){
   switch (eleccionMenu)
   {
   case 4:
      producto.registrarProducto();
      break;
   default:
      break;
   }
 }

 void modificarRegistro (int eleccionMenu){
   
   switch (eleccionMenu)
   {
   case 4:
      producto.modificarProducto();
      break;
   
   default:
      break;
   }
 }

 void eliminarRegistro (int eleccionMenu){
   
   switch (eleccionMenu)
   {
   case 4:
      producto.eliminarRegistro();
      break;
   
   default:
      break;
   }
 }

 int subMenuAdministrador(){
   int seleccion = 0;
   cout<<"Por favor seleccione una opcion:"<<endl;
   cout<<"1. Agregar Registro"<<endl;
   cout<<"2. Editar Registro"<<endl;
   cout<<"3. Eliminar Registro"<<endl;
   seleccion = helper.validarInt(3);
   return seleccion;
 }
 
 int menu (int clave){
   int eleccionMenu = 0, eleccionOpcion = 0;
   switch (clave)
   {
   case 0: //  administrador
      cout<<"Por favor seleccione un registro:"<<endl;
      cout<<"1. Cliente"<<endl;
      cout<<"2. Compra"<<endl;
      cout<<"3. Factura"<<endl;
      cout<<"4. Producto"<<endl;
      cout<<"5. Proveedor"<<endl;
      eleccionMenu = helper.validarInt(5);
      switch (eleccionMenu)
      {
      case 1: //  cliente

         break;
      case 2: //  compra
         
         break;
      case 3: //  factura
         
         break;
      case 4: //  producto
         cout<<""<<endl;
         cout<<"PRODUCTOS REGISTRADOS"<<endl;
         producto.listarProductos();
         eleccionOpcion = subMenuAdministrador();
         switch (eleccionOpcion)
         {
         case 1:
            agregarRegistro(eleccionMenu);
            break;
         
         case 2:
            modificarRegistro(eleccionMenu);
            break;

         case 3:
            eliminarRegistro(eleccionMenu);
            break;

         default:
            break;
         }
         
         break;
      case 5: //  proveedor
         
         break;

      default:
         break;
      }
      break;
   case 1: //  almacén
      break;
   case 2: //  vendedor
      break;
   default:
      break;
   }
 }

  int main (){
   int keyNumber = 0;
   keyNumber= validarClave();
   menu(keyNumber);
   return 0;
 }

