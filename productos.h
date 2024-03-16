#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "helpers.h"

using namespace std;

helpers helper;

class productos{

   public:

   struct Producto
 {
   int id = -1;
   int id_proveedor = -1;
   int stock = -1;
   float precio = -1;
   char description[45] = "";
   int stock_min = -1;

   Producto(){
      int id = -1;
      int id_proveedor = -1;
      int stock = -1;
      float precio = -1;
      char description[45] = "";
      int stock_min = -1;
   }
 };
 
   int cantidadProducto(){
   ifstream archivo("database/Producto.txt", ios::binary | ios::ate);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo.\n";
        archivo.close();
        return 1;
    }
    streamsize size = archivo.tellg();
    archivo.close();
    int cantidadDeRegistros = size / sizeof(Producto);
    archivo.close();
    return cantidadDeRegistros;
 }

   Producto getProducto(int _id){
      fstream e("database/Producto.txt", ios::out | ios::in | ios::binary);
      int i = 0;
      productos::Producto auxiliar;
      if(e.is_open()){
         int cant = cantidadProducto();
         for (i = 0; i < cant; i++){
            e.seekg(i * sizeof(productos::Producto));
            e.read((char*)&auxiliar, sizeof(productos::Producto));
            if(auxiliar.id == _id){
               return auxiliar;
            }
         }
         auxiliar = productos::Producto();
         return auxiliar;
      }
   }

   void imprimirProductos(){
      ifstream archivo("database/Producto.txt", ios::binary);
      if (!archivo) {
         cerr << "No se pudo abrir el archivo.\n";
      }
      Producto producto;

      while (archivo.read((char*)&producto, sizeof(productos::Producto))) {
         cout << "ID del producto: " << producto.id << "\n";
         cout << "DESCRIPCION del producto: " << producto.description << "\n";
      }
      archivo.close();
   }

   void registrarProducto(){
      int auxId = 0, generadorId = 0;
      string linea = "";
      productos::Producto modelo;
      ofstream archivo("database/Producto.txt", ios::binary);
      do{
         cout<<"Por favor introduzca el ID del producto (maximo 5 digitos)"<<endl;
         auxId = helper.validarInt(99999);
         modelo = getProducto(auxId);

         if(modelo.id != -1){
            cout<<"Ya existe un producto con el ID especificado"<<endl;
         }

      }while(modelo.id != -1);
         cout<<"Por favor introduzca la informacion solicitada a continuacion:"<<endl;
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
            std::cerr << "No se pudo abrir el archivo para escritura.\n";
         }else{
            archivo.write((char*)&modelo, sizeof(productos::Producto));
            archivo.close();
         }
   }

   void modificarProducto(){
      
   }

};