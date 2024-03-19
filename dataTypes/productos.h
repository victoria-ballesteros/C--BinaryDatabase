#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "registro.h"

using namespace std;

class productos: public registro {

   public:
   
   void listarProductos(){
      ifstream archivo("database/Producto.bin", ios::binary);
      if (!archivo) {
         cerr << "No se pudo abrir el archivo.\n";
      }
      Producto producto;

      while (archivo.read((char*)&producto, sizeof(Producto))) {
         cout<<""<<'\n';
         cout << "ID--------------------: " << producto.id << "\n";
         cout << "DESCRIPCION-----------: " << producto.description << "\n";
         cout << "STOCK-----------------: " << producto.stock << "\n";
         cout <<"____________________________________________________________"<<'\n';
      }
      archivo.close();
   }

   void imprimirProducto(Producto producto){
      cout <<"ID---------------: "<< producto.id << '\n';
      cout <<"ID proveedor-----:  "<< producto.id_proveedor << '\n';
      cout <<"Stock------------: "<< producto.stock << '\n';
      cout <<"Precio-----------: "<< producto.precio << '\n';
      cout <<"Descripcion------: "<< producto.description << '\n';
      cout <<"Stock minimo-----: "<< producto.stock_min << '\n';
      cout <<"____________________________________________________________"<<'\n';
      cout<<""<<'\n';
   }

   void registrarProducto(){
        int auxId = 0, generadorId = 0;
        string linea = "";
        Producto modelo;
        ofstream archivo("database/Producto.bin", ios::app | ios::binary);

        do{
            cout<<"Por favor introduzca el ID del producto (maximo 5 digitos):"<<'\n';
            auxId = helper.validarInt(99999);
            modelo = getProducto(auxId);
            if(modelo.id != -1){
               cout<<"Ya existe un producto con el ID especificado"<<'\n';
            }

        }while(modelo.id != -1);
            cout<<"Por favor introduzca la informacion solicitada a continuacion:"<<'\n';
            modelo.id = auxId;
            cout<<"ID del proveedor: ";
            cin>>modelo.id_proveedor;
            cout<<"Cantidad en stock: ";
            cin>>modelo.stock;
            cout<<"Precio: ";
            cin>>modelo.precio;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Descripcion: ";
            getline(cin, linea);
            strcpy(modelo.description, linea.c_str());
            cout<<"Cantidad minima de stock necesaria: ";
            cin>>modelo.stock_min;

            if (!archivo) {
                cerr << "No se pudo abrir el archivo para escritura.\n";
            }else{
               archivo.seekp((cantidadRegistro("database/Producto.bin", sizeof(Producto)))*sizeof(Producto));
               cout<<cantidadRegistro("database/Producto.bin", sizeof(Producto));
               archivo.write((char*)&modelo, sizeof(Producto));
               archivo.close();
            }
        }

   void modificarProducto(){
      string linea = "";
      Producto modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Producto.bin", ios::out | ios::in | ios::binary); 
      do{
         cout<<"Por favor introduzca el ID del producto (maximo 5 digitos)"<<'\n';
         auxId = helper.validarInt(99999);
         modelo = getProducto(auxId);

         if(modelo.id == -1){
            cout<<"No existe un producto con el ID especificado"<<'\n';
         }
      }while(modelo.id == -1);

      do{
         imprimirProducto(modelo);
         cout<<"Seleccione la opcion que desee cambiar:"<<'\n';
         cout <<"1. ID proveedor" << '\n';
         cout <<"2. Stock"<< '\n';
         cout <<"3. Precio"<< '\n';
         cout <<"4. Descripcion"<< '\n';
         cout <<"5. Stock minimo"<< '\n';
         cout <<"6. Terminar proceso"<< '\n';
         cout <<"Respuesta: ";
         cin >> cambioPropiedad;
         cout<<""<<'\n';

         if(cambioPropiedad == 1){
            cout<<"ID del proveedor: ";
            cin>> modelo.id_proveedor;
         }else if(cambioPropiedad == 2){
            cout<<"Stock: ";
            cin>> modelo.stock;
         }else if(cambioPropiedad == 3){
            cout<<"Precio: ";
            cin>> modelo.precio;
         }else if(cambioPropiedad == 4){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Descripcion: ";
            getline(cin, linea);
            strcpy(modelo.description, linea.c_str());
         }else if(cambioPropiedad == 5){
            cout<<"Stock minimo: ";
            cin>> modelo.stock_min;
         }

      }while(cambioPropiedad != 6);

      if (!archivo) {
         cerr << "No se pudo abrir el archivo para escritura.\n";
      }else{
         archivo.seekg(auxPosicionProducto * sizeof(Producto));
         archivo.write((char*)&modelo, sizeof(Producto));
         archivo.close();
      }
   }

   void eliminarRegistro(){
    int auxId = 0;
    Producto modelo;
    Producto reemplazo;
    fstream archivoOriginal("database/Producto.bin", ios::out | ios::in | ios::binary);
   
    fstream archivoTemporal("database/ProductoTemp.bin", ios::out);
    archivoTemporal.close();

    archivoTemporal.open("database/ProductoTemp.bin", ios::in | ios::out | ios::binary);

    do{
        cout<<"Por favor introduzca el ID del producto (maximo 5 digitos)"<<'\n';
        auxId = helper.validarInt(99999);
        modelo = getProducto(auxId);

        if(modelo.id == -1){
            cout<<"No existe un producto con el ID especificado"<<'\n';
        }

    }while(modelo.id == -1);

    while (archivoOriginal.read((char*)&reemplazo, sizeof(Producto))) {
        if (reemplazo.id != modelo.id) {
            archivoTemporal.write((char*)&reemplazo, sizeof(Producto));
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    remove("database/Producto.bin");
    rename("database/ProductoTemp.bin", "database/Producto.bin");
}

};