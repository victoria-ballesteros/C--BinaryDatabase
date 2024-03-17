#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "registro.h"

using namespace std;

class clientes: public registro {

   public:
   
   void listarClientes (){
      ifstream archivo("database/Cliente.bin", ios::binary);
      if (!archivo) {
         cerr << "No se pudo abrir el archivo.\n";
      }
      Cliente cliente;

      while (archivo.read((char*)&cliente, sizeof(Cliente))) {
         cout<<""<<endl;
         cout << "ID--------------------: " << cliente.id << "\n";
         cout << "NOMBRE----------------: " << cliente.nombre << "\n";
         cout <<"____________________________________________________________"<<endl;
      }
      archivo.close();
   }

   void imprimirCliente (Cliente cliente){
        cout <<"ID--------------: "<< cliente.id << endl;
        cout <<"Nombre----------: "<< cliente.nombre << endl;
        cout <<"Direccion-------: "<< cliente.direccion << endl;
        cout <<"Telefono--------: "<< cliente.telefono << endl;
        cout <<"____________________________________________________________"<<endl;
        cout<<""<<endl;
   }

   void registrarCliente (){
        int auxId = 0, generadorId = 0;
        string linea = "";
        Cliente modelo;
        ofstream archivo("database/Cliente.bin", ios::app | ios::binary);

        do{
            cout<<"Por favor introduzca el ID del cliente:"<<endl;
            auxId = helper.validarIntSinLimite();
            modelo = getCliente(auxId);
            if(modelo.id != -1){
            cout<<"Ya existe un cliente con el ID especificado"<<endl;
            }

        }while(modelo.id != -1);
            modelo.id = auxId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nombre: ";
            getline(cin, linea);
            strcpy(modelo.nombre, linea.c_str());
            cout << "Direccion: ";
            getline(cin, linea);
            strcpy(modelo.direccion, linea.c_str());
            cout << "Telefono: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());

            if (!archivo) {
                cerr << "No se pudo abrir el archivo para escritura.\n";
            }else{
                archivo.write((char*)&modelo, sizeof(Cliente));
                archivo.close();
            }
        }

   void modificarCliente (){
      string linea = "";
      Cliente modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Cliente.bin", ios::out | ios::in | ios::binary); 
      do{
         cout<<"Por favor introduzca el ID del cliente (maximo 5 digitos)"<<endl;
         auxId = helper.validarInt(99999);
         modelo = getCliente(auxId);

         if(modelo.id == -1){
            cout<<"No existe un cliente con el ID especificado"<<endl;
         }
      }while(modelo.id == -1);

      do{
         imprimirCliente(modelo);
         cout<<"Seleccione la opcion que desee cambiar:"<<endl;
         cout <<"1. Nombre" << endl;
         cout <<"2. Direccion"<< endl;
         cout <<"3. Telefono"<< endl;
         cout <<"4. Salir"<< endl;
         cout <<"Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         cout<<""<<endl;

         if(cambioPropiedad == 1){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Nombre: ";
            getline(cin, linea);
            strcpy(modelo.nombre, linea.c_str());
         }else if(cambioPropiedad == 2){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Direccion: ";
            getline(cin, linea);
            strcpy(modelo.direccion, linea.c_str());
         }else if(cambioPropiedad == 3){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Telefono: ";
            getline(cin, linea);
            strcpy(modelo.direccion, linea.c_str());
         }

      }while(cambioPropiedad != 4);

      if (!archivo) {
         cerr << "No se pudo abrir el archivo para escritura.\n";
      }else{
         archivo.seekg(auxPosicionCliente * sizeof(Cliente));
         archivo.write((char*)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }

   void eliminarRegistro (){
    int auxId = 0;
    Cliente modelo;
    Cliente reemplazo;
    fstream archivoOriginal("database/Cliente.bin", ios::out | ios::in | ios::binary);
   
    fstream archivoTemporal("database/ClienteTemp.bin", ios::out);
    archivoTemporal.close();

    archivoTemporal.open("database/ClienteTemp.bin", ios::in | ios::out | ios::binary);

    do{
        cout<<"Por favor introduzca el ID del Cliente (maximo 5 digitos)"<<endl;
        auxId = helper.validarInt(99999);
        modelo = getCliente(auxId);

        if(modelo.id == -1){
            cout<<"No existe un cliente con el ID especificado"<<endl;
        }

    }while(modelo.id == -1);

    while (archivoOriginal.read((char*)&reemplazo, sizeof(Cliente))) {
        if (reemplazo.id != modelo.id) {
            archivoTemporal.write((char*)&reemplazo, sizeof(Cliente));
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    remove("database/Cliente.bin");
    rename("database/ClienteTemp.bin", "database/Cliente.bin");
}

};