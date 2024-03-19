#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "registro.h"

using namespace std;

class facturas: public registro {

   public:
   
   void listarFacturas (){
      ifstream archivo("database/Factura.bin", ios::binary);
      if (!archivo) {
         cerr << "No se pudo abrir el archivo.\n";
      }
      Factura factura;

      while (archivo.read((char*)&factura, sizeof(Factura))) {
        cout<<""<<'\n';
        cout << "ID--------------------: " << factura.id << "\n";
        cout << "FECHA-----------------: " << factura.fecha << "\n";
        cout << "CLIENTE---------------: " << factura.id_cliente << "\n";
        cout <<"____________________________________________________________"<<'\n';
        cout<<""<<'\n';
      }
      archivo.close();
   }

   void imprimirFactura (Factura factura){
        cout <<"ID--------------: "<< factura.id << '\n';
        cout <<"FECHA-----------: " << factura.fecha << "\n";
        cout <<"CLIENTE---------: " << factura.id_cliente << "\n";
        cout <<"____________________________________________________________"<<'\n';
        cout<<""<<'\n';
   }

   void registrarFactura (){
        int auxId = 0, generadorId = 0;
        string linea = "";
        Factura modelo;
        ofstream archivo("database/Factura.bin", ios::app | ios::binary);

        do{
            cout<<"Por favor introduzca el ID de la factura (maximo 5 digitos):"<<'\n';
            auxId = helper.validarInt(99999);
            modelo = getFactura(auxId);
            if(modelo.id != -1){
            cout<<"Ya existe una factura con el ID especificado"<<'\n';
            }

        }while(modelo.id != -1);
            cout<<"Por favor introduzca la informacion solicitada a continuacion:"<<'\n';
            modelo.id = auxId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Id del cliente: ";
            cin>>modelo.id_cliente;
            cout<<"Fecha: ";
            cin>>modelo.fecha;

            if (!archivo) {
                cerr << "No se pudo abrir el archivo para escritura.\n";
            }else{
                archivo.write((char*)&modelo, sizeof(Factura));
                archivo.close();
            }
        }

   void modificarFactura (){
      string linea = "";
      Factura modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Factura.bin", ios::out | ios::in | ios::binary); 
      do{
         cout<<"Por favor introduzca el ID de la factura (maximo 5 digitos)"<<'\n';
         auxId = helper.validarInt(99999);
         modelo = getFactura(auxId);

         if(modelo.id == -1){
            cout<<"No existe una factura con el ID especificado"<<'\n';
         }
      }while(modelo.id == -1);

      do{
         imprimirFactura(modelo);
         cout<<"Seleccione la opcion que desee cambiar:"<<'\n';
         cout <<"1. ID del cliente asociado" << '\n';
         cout <<"2. Fecha"<< '\n';
         cout <<"3. Salir"<< '\n';
         cout <<"Respuesta: ";
         cambioPropiedad = helper.validarInt(3);
         cout<<""<<'\n';

         if(cambioPropiedad == 1){
            cout<<"Id del cliente asociado: ";
            cin>>modelo.id_cliente;
         }else if(cambioPropiedad == 2){
            cout<<"Fecha: ";
            cin>>modelo.fecha;
         }

      }while(cambioPropiedad != 3);

      if (!archivo) {
         cerr << "No se pudo abrir el archivo para escritura.\n";
      }else{
         archivo.seekg(auxPosicionFactura * sizeof(Factura));
         archivo.write((char*)&modelo, sizeof(Factura));
         archivo.close();
      }
   }

   void eliminarRegistro (){
        int auxId = 0;
        Factura modelo;
        Factura reemplazo;
        fstream archivoOriginal("database/Factura.bin", ios::out | ios::in | ios::binary);
    
        fstream archivoTemporal("database/FacturaTemp.bin", ios::out);
        archivoTemporal.close();

        archivoTemporal.open("database/FacturaTemp.bin", ios::in | ios::out | ios::binary);

        do{
            cout<<"Por favor introduzca el ID de la factura (maximo 5 digitos)"<<'\n';
            auxId = helper.validarInt(99999);
            modelo = getFactura(auxId);

            if(modelo.id == -1){
                cout<<"No existe una factura con el ID especificado"<<'\n';
            }

        }while(modelo.id == -1);

        while (archivoOriginal.read((char*)&reemplazo, sizeof(Factura))) {
            if (reemplazo.id != modelo.id) {
                archivoTemporal.write((char*)&reemplazo, sizeof(Factura));
            }
        }

        archivoOriginal.close();
        archivoTemporal.close();

        remove("database/Factura.bin");
        rename("database/FacturaTemp.bin", "database/Factura.bin");
    }

   void registrarFacturaDirecta(Factura factura){
      ofstream archivo("database/Factura.bin", ios::app | ios::binary);
      if (!archivo) {
                cerr << "No se pudo abrir el archivo para escritura.\n";
            }else{
                archivo.write((char*)&factura, sizeof(Factura));
                archivo.close();
            }
      }
};