#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

//  Clases
#include "helpers.h"
#include "dataTypes\dataTypes.h"

using namespace std;

clientes cliente;
compras compra;
facturas factura;
productos producto;
proveedores proveedor;

long key[4] = {11235, 81321, 34558, 0};
int eleccionMenu = 0, keyNumber = 0;

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

int helpers::validarIntSinLimite(){
int numero;
cout << "Respuesta: ";
   while(!(cin >> numero)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada inválida. Por favor, ingresa un número: ";
   }
return numero;
}

 int validarClave() {
   int i= 0, puesto= 0;
   bool flag= false;
   long claveIntroducida = 0;
   
   do{
      claveIntroducida= helper.validarLong();
      for(i = 0; i<4; i++){
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
   case 1:
      cliente.registrarCliente();
      break;
   case 2:
      compra.registrarCompra();
      break;
   case 3:
      factura.registrarFactura();
      break;
   case 4:
      producto.registrarProducto();
      break;
   case 5:
      proveedor.registrarProveedor();
      break;
   default:
      break;
   }
 }

 void modificarRegistro (int eleccionMenu){
   
   switch (eleccionMenu)
   {
   case 1:
      cliente.modificarCliente();
      break;
   case 2:
      compra.modificarCompra();
      break;
   case 3:
      factura.modificarFactura();
      break;
   case 4:
      producto.modificarProducto();
      break;
   case 5:
      proveedor.modificarProveedor();
      break;
   default:
      break;
   }
 }

 void eliminarRegistro (int eleccionMenu){
   
   switch (eleccionMenu)
   {
   case 1:
      cliente.eliminarRegistro();
      break;
   case 2:
      compra.eliminarRegistro();
      break;
   case 3:
      factura.eliminarRegistro();
      break;
   case 4:
      producto.eliminarRegistro();
      break;
   case 5:
      proveedor.eliminarRegistro();
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
   cout<<"4. Seleccionar otro tipo de Registro"<<endl;
   seleccion = helper.validarInt(4);
   return seleccion;
 }
 
 int menu (int clave){
   int eleccionOpcion = 0;
   switch (clave)
   {
   case 0: //  administrador
   
   do{
      system("cls");
      cout<<"Por favor seleccione un registro:"<<endl;
      cout<<"1. Cliente"<<endl;
      cout<<"2. Compra"<<endl;
      cout<<"3. Factura"<<endl;
      cout<<"4. Producto"<<endl;
      cout<<"5. Proveedor"<<endl;
      cout<<"6. Introducir nueva clave de acceso"<<endl;
      eleccionMenu = helper.validarInt(6);

      while(eleccionMenu != 6) {
         if(eleccionMenu == 1){
            system("cls");
            cout<<""<<endl;
            cout<<"CLIENTES REGISTRADOS"<<endl;
            cliente.listarClientes();
            cout<<""<<endl;
         }else if(eleccionMenu == 2){
            system("cls");
            cout<<""<<endl;
            cout<<"COMPRAS REGISTRADOS"<<endl;
            compra.listarCompras();
            cout<<""<<endl;
         }else if(eleccionMenu == 3){
            system("cls");
            cout<<""<<endl;
            cout<<"FACTURAS REGISTRADOS"<<endl;
            factura.listarFacturas();
            cout<<""<<endl;
         }else if(eleccionMenu == 4){
            system("cls");
            cout<<""<<endl;
            cout<<"PRODUCTOS REGISTRADOS"<<endl;
            cliente.listarClientes();
            cout<<""<<endl;
         }else if(eleccionMenu == 5){
            cout<<""<<endl;
            cout<<"PROVEEDORES REGISTRADOS"<<endl;
            proveedor.listarProveedores();
            cout<<""<<endl;
         }

         eleccionOpcion = subMenuAdministrador();

         while(eleccionOpcion != 4){
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
         }

      };
   }while(eleccionMenu != 6);

      break;
   case 1: //  almacén
      break;
   case 2: //  vendedor
      cout<<"APERTURA DE CAJA"<<endl;

      break;
   default:
      break;
   }
 }

  int main (){
      keyNumber= validarClave();
      menu(keyNumber);
      return 0;
 }

