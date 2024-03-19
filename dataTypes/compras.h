#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "registro.h"

using namespace std;

class compras: public registro {

   public:
   
   void listarCompras (){
      ifstream archivo("database/Compra.bin", ios::binary);
      if (!archivo) {
         cerr << "No se pudo abrir el archivo.\n";
      }
      Compra compra;

      while (archivo.read((char*)&compra, sizeof(Compra))) {
        cout<<""<<'\n';
        cout << "ID--------------------: " << compra.id << "\n";
        cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
        cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
        cout <<"____________________________________________________________"<<'\n';
        cout<<""<<'\n';
      }
      archivo.close();
   }

   void imprimirCompra (Compra compra){
        cout <<"ID--------------: "<< compra.id << '\n';
        cout <<"ID_PRODUCTO-----: "<< compra.id_producto << '\n';
        cout <<"CANTIDAD--------: "<< compra.cantidad << '\n';
        cout <<"ID_FACTURA------: "<< compra.id_factura << '\n';
        cout <<"____________________________________________________________"<<'\n';
        cout<<""<<'\n';
   }

   void registrarCompra (){
        int auxId = 0, generadorId = 0;
        string linea = "";
        Compra modelo;
        ofstream archivo("database/Compra.bin", ios::app | ios::binary);

        do{
            cout<<"Por favor introduzca el ID de la compra (maximo 5 digitos):"<<'\n';
            auxId = helper.validarInt(99999);
            modelo = getCompra(auxId);
            if(modelo.id != -1){
            cout<<"Ya existe una compra con el ID especificado"<<'\n';
            }

        }while(modelo.id != -1);
            cout<<"Por favor introduzca la informacion solicitada a continuacion:"<<'\n';
            modelo.id = auxId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Id del producto: ";
            modelo.id_producto = helper.validarIntSinLimite();
            cout<<"Id de la factura: ";
            modelo.id_factura = helper.validarIntSinLimite();
            cout<<"Cantidad: ";
            modelo.cantidad = helper.validarIntSinLimite();

            if (!archivo) {
                cerr << "No se pudo abrir el archivo para escritura.\n";
            }else{
                archivo.write((char*)&modelo, sizeof(Compra));
                archivo.close();
            }
        }

   void modificarCompra (){
      string linea = "";
      Compra modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Compra.bin", ios::out | ios::in | ios::binary); 
      do{
         cout<<"Por favor introduzca el ID de la compra (maximo 5 digitos)"<<'\n';
         auxId = helper.validarInt(99999);
         modelo = getCompra(auxId);

         if(modelo.id == -1){
            cout<<"No existe una compra con el ID especificado"<<'\n';
         }
      }while(modelo.id == -1);

      do{
         imprimirCompra(modelo);
         cout<<"Seleccione la opcion que desee cambiar:"<<'\n';
         cout <<"1. ID del producto asociado" << '\n';
         cout <<"2. ID de la factura asociada"<< '\n';
         cout <<"3. Cantidad"<< '\n';
         cout <<"4. Salir"<< '\n';
         cout <<"Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         cout<<""<<'\n';

         if(cambioPropiedad == 1){
            cout<<"Id del producto asociado: ";
            cin>>modelo.id_producto;
         }else if(cambioPropiedad == 2){
            cout<<"Id de la factura asociada: ";
            cin>>modelo.id_factura;
         }else if(cambioPropiedad == 3){
            cout<<"Cantidad: ";
            cin>>modelo.cantidad;
         }

      }while(cambioPropiedad != 4);

      if (!archivo) {
         cerr << "No se pudo abrir el archivo para escritura.\n";
      }else{
         archivo.seekg(auxPosicionCompra * sizeof(Compra));
         archivo.write((char*)&modelo, sizeof(Compra));
         archivo.close();
      }
   }

   void eliminarRegistro (){
    int auxId = 0;
    Compra modelo;
    Compra reemplazo;
    fstream archivoOriginal("database/Compra.bin", ios::out | ios::in | ios::binary);
   
    fstream archivoTemporal("database/CompraTemp.bin", ios::out);
    archivoTemporal.close();

    archivoTemporal.open("database/CompraTemp.bin", ios::in | ios::out | ios::binary);

    do{
        cout<<"Por favor introduzca el ID de la compra (maximo 5 digitos)"<<'\n';
        auxId = helper.validarInt(99999);
        modelo = getCompra(auxId);

        if(modelo.id == -1){
            cout<<"No existe una compra con el ID especificado"<<'\n';
        }

    }while(modelo.id == -1);

    while (archivoOriginal.read((char*)&reemplazo, sizeof(Compra))) {
        if (reemplazo.id != modelo.id) {
            archivoTemporal.write((char*)&reemplazo, sizeof(Compra));
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    remove("database/Compra.bin");
    rename("database/CompraTemp.bin", "database/Compra.bin");
}

   void registrarCompraCaja(int id_factura, int id_compra){
      Compra modelo;
      ofstream archivo("database/Compra.bin", ios::app | ios::binary);
      modelo.id = id_compra;
      modelo.id_factura = id_factura;
      int id_producto_aux = 0, cantidad_producto_aux = 0, confirmarCompra = 0;
      Producto modeloProducto;
      do{
         cout<<"Por favor introduzca el Id del producto: ";
         id_producto_aux = helper.validarIntSinLimite();
         modeloProducto = getProducto(id_producto_aux);
         if(modeloProducto.id == -1){
            cout<<"El producto indicado no existe en la base de datos"<<'\n';
         }
         if(modeloProducto.stock_min > modeloProducto.stock){
            cout<<"Producto no disponible para venta"<<'\n';
         }
      }while(modeloProducto.id == -1 || modeloProducto.stock_min > modeloProducto.stock);
      do{
         system("cls");
         cout<<"Cantidad del producto a facturar: ";
         cantidad_producto_aux = helper.validarIntSinLimite();
         
         if(modeloProducto.stock < cantidad_producto_aux){
            cout<<"No hay suficiente producto en existencia"<<'\n';
         }
      }while(modeloProducto.stock < cantidad_producto_aux);
      cout<<"Por favor confirme la compra (Una vez confirmada se ejecutarán cambios irreversibles en la base de datos)"<<'\n';
      cout<<"1. Si"<<'\n';
      cout<<"2. No"<<'\n';
      confirmarCompra = helper.validarInt(2);
      if(confirmarCompra == 1){
         if (!archivo) {
            cerr << "No se pudo abrir el archivo para escritura.\n";
         }else{
            modelo.id = id_compra;
            modelo.cantidad = cantidad_producto_aux;
            modelo.id_factura = id_factura;
            modelo.id_producto = id_producto_aux;
            modificarCantidadProducto(modeloProducto.id, cantidad_producto_aux);
            archivo.write((char*)&modelo, sizeof(Compra));
            archivo.close();
         }
      }else{
         cout<<"Compra cancelada"<<'\n';
      }
   }  

   void listarComprasUnicas(int id_factura){
      ifstream archivo("database/Compra.bin", ios::binary);
      if (!archivo) {
         cerr << "No se pudo abrir el archivo.\n";
         return;
      }
      Compra compra;
      while (archivo.read((char*)&compra, sizeof(Compra))) {
         if (!archivo) {
               cerr << "Error al leer del archivo.\n";
               break;
         }
         if(compra.id_factura == id_factura){
               cout<<""<<'\n';
               cout << "ID--------------------: " << compra.id << "\n";
               cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
               cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
               cout <<"____________________________________________________________"<<'\n';
               cout<<""<<'\n';
         }
      }
      archivo.close();
}

};