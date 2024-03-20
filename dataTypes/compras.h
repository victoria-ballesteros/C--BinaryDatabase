#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class compras : public registro
{

public:
   void listarCompras()
   {
      ifstream archivo("database/Compra.bin", ios::binary);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Compra compra;
      while (archivo.read((char *)&compra, sizeof(Compra)))
      {
         std::cout << "" << '\n';
         std::cout << "ID--------------------: " << compra.id << "\n";
         std::cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
         std::cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
         std::cout << "____________________________________________________" << '\n';
         std::cout << "" << '\n';
      }
      archivo.close();
   }

   void imprimirCompra(Compra compra)
   {
      std::cout << "ID--------------: " << compra.id << '\n';
      std::cout << "ID_PRODUCTO-----: " << compra.id_producto << '\n';
      std::cout << "CANTIDAD--------: " << compra.cantidad << '\n';
      std::cout << "ID_FACTURA------: " << compra.id_factura << '\n';
      std::cout << "______________________________________________ " << '\n';
      std::cout << '\n';
   }

   void registrarCompra()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Compra modelo;
      ofstream archivo("database/Compra.bin", ios::app | ios::binary);
      std::cout << "Por favor introduzca el ID de la compra:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getCompra(auxId);
      if (modelo.id != -1)
      {
         std::cout << "Ya existe una compra con el ID especificado" << '\n';
         system("pause");
         return;
      }
      std::cout << "Por favor introduzca la informacion solicitada a continuacion:" << '\n';
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Id del producto: ";
      modelo.id_producto = helper.validarIntSinLimite();
      std::cout << "Id de la factura: ";
      modelo.id_factura = helper.validarIntSinLimite();
      std::cout << "Cantidad: ";
      modelo.cantidad = helper.validarIntSinLimite();
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Compra));
         archivo.close();
      }
   }

   void modificarCompra()
   {
      string linea = "";
      Compra modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Compra.bin", ios::out | ios::in | ios::binary);
      std::cout << "Por favor introduzca el ID de la compra:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getCompra(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe una compra con el ID especificado" << '\n';
         system("pause");
         return;
      }
      do
      {
         imprimirCompra(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:" << '\n';
         std::cout << "1. ID del producto asociado" << '\n';
         std::cout << "2. ID de la factura asociada" << '\n';
         std::cout << "3. Cantidad" << '\n';
         std::cout << "4. Salir" << '\n';
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         std::cout << '\n';
         if (cambioPropiedad == 1)
         {
            std::cout << "Id del producto asociado: ";
            modelo.id_producto = helper.validarIntSinLimite();
         }
         else if (cambioPropiedad == 2)
         {
            std::cout << "Id de la factura asociada: ";
            modelo.id_factura = helper.validarIntSinLimite();
         }
         else if (cambioPropiedad == 3)
         {
            std::cout << "Cantidad: ";
            modelo.cantidad = helper.validarIntSinLimite();
         }
      } while (cambioPropiedad != 4);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekg(auxPosicionCompra * sizeof(Compra));
         archivo.write((char *)&modelo, sizeof(Compra));
         archivo.close();
      }
   }

   void eliminarRegistro()
   {
      int auxId = 0;
      Compra modelo;
      Compra reemplazo;
      fstream archivoOriginal("database/Compra.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/CompraTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/CompraTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "Por favor introduzca el ID de la compra: " << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getCompra(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe una compra con el ID especificado" << '\n';
         system("pause");
         return;
      }
      if (archivoOriginal.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      if (archivoTemporal.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Compra)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Compra));
         }
      }
      archivoOriginal.close();
      archivoTemporal.close();
      remove("database/Compra.bin");
      rename("database/CompraTemp.bin", "database/Compra.bin");
   }

   void registrarCompraCaja(int id_factura, int id_compra)
   {
      Compra modelo;
      ofstream archivo("database/Compra.bin", ios::app | ios::binary);
      modelo.id = id_compra;
      modelo.id_factura = id_factura;
      int id_producto_aux = 0, cantidad_producto_aux = 0, confirmarCompra = 0;
      Producto modeloProducto;
      do
      {
         std::cout << "Por favor introduzca el Id del producto: ";
         id_producto_aux = helper.validarIntSinLimite();
         modeloProducto = getProducto(id_producto_aux);
         if (modeloProducto.id == -1)
         {
            std::cout << "El producto indicado no existe en la base de datos" << '\n';
            system("pause");
         }
         if (modeloProducto.stock_min > modeloProducto.stock)
         {
            std::cout << "Producto no disponible para la venta por escasez de inventario." << '\n';
            system("pause");
         }
      } while (modeloProducto.id == -1 || modeloProducto.stock_min > modeloProducto.stock);
      do
      {
         std::cout << "Cantidad del producto a facturar: ";
         cantidad_producto_aux = helper.validarIntSinLimite();

         if (modeloProducto.stock < cantidad_producto_aux)
         {
            std::cout << "No hay suficiente producto en existencia" << '\n';
            system("pause");
         }
      } while (modeloProducto.stock < cantidad_producto_aux);
      std::cout << "Por favor confirme la compra (Una vez confirmada se ejecutarán cambios irreversibles en la base de datos)" << '\n';
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      confirmarCompra = helper.validarInt(2);
      if (confirmarCompra == 1)
      {
         if (archivo.fail())
         {
            cerr << "No se pudo abrir el archivo.\n";
            system("pause");
            return;
         }
         else
         {
            modelo.id = id_compra;
            modelo.cantidad = cantidad_producto_aux;
            modelo.id_factura = id_factura;
            modelo.id_producto = id_producto_aux;
            modificarCantidadProducto(modeloProducto.id, cantidad_producto_aux);
            archivo.write((char *)&modelo, sizeof(Compra));
            archivo.close();
         }
      }
      else
      {
         std::cout << "Compra cancelada" << '\n';
         system("pause");
      }
   }

   void listarComprasUnicas(int id_factura)
   {
      ifstream archivo("database/Compra.bin", ios::binary);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Compra compra;
      while (archivo.read((char *)&compra, sizeof(Compra)))
      {
         if (archivo.fail())
         {
            cerr << "Error al leer del archivo.\n";
            system("pause");
            return;
         }
         if (compra.id_factura == id_factura)
         {
            std::cout << "" << '\n';
            std::cout << "ID--------------------: " << compra.id << "\n";
            std::cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
            std::cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
            std::cout << "____________________________________________________________" << '\n';
            std::cout << '\n';
         }
      }
      archivo.close();
   }
};