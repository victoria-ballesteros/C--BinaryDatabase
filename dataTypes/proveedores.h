#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "registro.h"

using namespace std;

class proveedores: public registro {

   public:
   
   void listarProveedores (){
      ifstream archivo("database/Proveedor.bin", ios::binary);
      if (!archivo) {
        cerr << "No se pudo abrir el archivo.\n";
      }
      Proveedor proveedor;

      while (archivo.read((char*)&proveedor, sizeof(Proveedor))) {
        cout<<""<<endl;
        cout << "ID--------------------: " << proveedor.id << "\n";
        cout << "NOMBRE----------------: " << proveedor.nombre  << "\n";
        cout << "TELEFONO--------------: " << proveedor.telefono << "\n";
        cout <<"____________________________________________________________"<<endl;
        cout<<""<<endl;
      }
      archivo.close();
   }

   void imprimirProveedor (Proveedor proveedor){
        cout <<"ID--------------: "<< proveedor.id << endl;
        cout <<"NOMBRE----------: " << proveedor.nombre << "\n";
        cout <<"TELEFONO--------: " << proveedor.telefono << "\n";
        cout <<"____________________________________________________________"<<endl;
        cout<<""<<endl;
   }

   void registrarProveedor (){
        int auxId = 0, generadorId = 0;
        string linea = "";
        Proveedor modelo;
        ofstream archivo("database/Proveedor.bin", ios::app | ios::binary);

        do{
            cout<<"Por favor introduzca el ID del proveedor (maximo 5 digitos):"<<endl;
            auxId = helper.validarInt(99999);
            modelo = getProveedor(auxId);
            if(modelo.id != -1){
            cout<<"Ya existe un proveedor con el ID especificado"<<endl;
            }

        }while(modelo.id != -1);
            cout<<"Por favor introduzca la informacion solicitada a continuacion:"<<endl;
            modelo.id = auxId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Nombre: ";
            getline(cin, linea);
            strcpy(modelo.nombre, linea.c_str());
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Telefono: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());

            if (!archivo) {
                cerr << "No se pudo abrir el archivo para escritura.\n";
            }else{
                archivo.write((char*)&modelo, sizeof(Proveedor));
                archivo.close();
            }
        }

   void modificarProveedor (){
      string linea = "";
      Proveedor modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Proveedor.bin", ios::out | ios::in | ios::binary); 
      do{
         cout<<"Por favor introduzca el ID del proveedor (maximo 5 digitos)"<<endl;
         auxId = helper.validarInt(99999);
         modelo = getProveedor(auxId);

         if(modelo.id == -1){
            cout<<"No existe un proveedor con el ID especificado"<<endl;
         }
      }while(modelo.id == -1);

      do{
         imprimirProveedor(modelo);
         cout<<"Seleccione la opcion que desee cambiar:"<<endl;
         cout <<"1. Nombre" << endl;
         cout <<"2. Telefono"<< endl;
         cout <<"3. Salir"<< endl;
         cout <<"Respuesta: ";
         cambioPropiedad = helper.validarInt(3);
         cout<<""<<endl;

         if(cambioPropiedad == 1){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Nombre: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());
         }else if(cambioPropiedad == 2){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Telefono: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());
         }

      }while(cambioPropiedad != 3);

      if (!archivo) {
         cerr << "No se pudo abrir el archivo para escritura.\n";
      }else{
         archivo.seekg(auxPosicionProveedor * sizeof(Proveedor));
         archivo.write((char*)&modelo, sizeof(Proveedor));
         archivo.close();
      }
   }

   void eliminarRegistro (){
        int auxId = 0;
        Proveedor modelo;
        Proveedor reemplazo;
        fstream archivoOriginal("database/Proveedor.bin", ios::out | ios::in | ios::binary);
    
        fstream archivoTemporal("database/ProveedorTemp.bin", ios::out);
        archivoTemporal.close();

        archivoTemporal.open("database/ProveedorTemp.bin", ios::in | ios::out | ios::binary);

        do{
            cout<<"Por favor introduzca el ID del proveedor (maximo 5 digitos)"<<endl;
            auxId = helper.validarInt(99999);
            modelo = getProveedor(auxId);

            if(modelo.id == -1){
                cout<<"No existe un proveedor con el ID especificado"<<endl;
            }

        }while(modelo.id == -1);

        while (archivoOriginal.read((char*)&reemplazo, sizeof(Proveedor))) {
            if (reemplazo.id != modelo.id) {
                archivoTemporal.write((char*)&reemplazo, sizeof(Proveedor));
            }
        }

        archivoOriginal.close();
        archivoTemporal.close();

        remove("database/Proveedor.bin");
        rename("database/ProveedorTemp.bin", "database/Proveedor.bin");
    }

};