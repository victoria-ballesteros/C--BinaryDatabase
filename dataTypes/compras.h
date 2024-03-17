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
        cout<<""<<endl;
        cout << "ID--------------------: " << compra.id << "\n";
        cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
        cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
        cout <<"____________________________________________________________"<<endl;
        cout<<""<<endl;
      }
      archivo.close();
   }

   void imprimirCompra (Compra compra){
        cout <<"ID--------------: "<< compra.id << endl;
        cout <<"ID_PRODUCTO-----: "<< compra.id_producto << endl;
        cout <<"CANTIDAD--------: "<< compra.cantidad << endl;
        cout <<"ID_FACTURA------: "<< compra.id_factura << endl;
        cout <<"____________________________________________________________"<<endl;
        cout<<""<<endl;
   }

   void registrarCompra (){
        int auxId = 0, generadorId = 0;
        string linea = "";
        Compra modelo;
        ofstream archivo("database/Compra.bin", ios::app | ios::binary);

        do{
            cout<<"Por favor introduzca el ID de la compra (maximo 5 digitos):"<<endl;
            auxId = helper.validarInt(99999);
            modelo = getCompra(auxId);
            if(modelo.id != -1){
            cout<<"Ya existe una compra con el ID especificado"<<endl;
            }

        }while(modelo.id != -1);
            cout<<"Por favor introduzca la informacion solicitada a continuacion:"<<endl;
            modelo.id = auxId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Id del producto: ";
            cin>>modelo.id_producto;
            cout<<"Id de la factura: ";
            cin>>modelo.id_factura;
            cout<<"Cantidad: ";
            cin>>modelo.cantidad;

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
         cout<<"Por favor introduzca el ID de la compra (maximo 5 digitos)"<<endl;
         auxId = helper.validarInt(99999);
         modelo = getCompra(auxId);

         if(modelo.id == -1){
            cout<<"No existe una compra con el ID especificado"<<endl;
         }
      }while(modelo.id == -1);

      do{
         imprimirCompra(modelo);
         cout<<"Seleccione la opcion que desee cambiar:"<<endl;
         cout <<"1. ID del producto asociado" << endl;
         cout <<"2. ID de la factura asociada"<< endl;
         cout <<"3. Cantidad"<< endl;
         cout <<"4. Salir"<< endl;
         cout <<"Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         cout<<""<<endl;

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
        cout<<"Por favor introduzca el ID de la compra (maximo 5 digitos)"<<endl;
        auxId = helper.validarInt(99999);
        modelo = getCompra(auxId);

        if(modelo.id == -1){
            cout<<"No existe una compra con el ID especificado"<<endl;
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

};