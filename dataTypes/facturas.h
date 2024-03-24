#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class facturas : public registro
{

public:
   void listarFacturas()
   {
      std::fstream archivo("database/Factura.bin", std::ios::binary | std::ios::in | std::ios::out);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Factura factura;
      while (archivo.read((char *)&factura, sizeof(Factura)))
      {
         std::cout << "" << '\n';
         std::cout << "ID--------------------: " << factura.id << "\n";
         std::cout << "FECHA-----------------: " << factura.fecha << "\n";
         std::cout << "CLIENTE---------------: " << factura.id_cliente << "\n";
         std::cout << "____________________________________________________________" << '\n';
         std::cout << '\n';
      }
      archivo.close();
   }

   void imprimirFactura(Factura factura)
   {
      std::cout << "ID--------------: " << factura.id << '\n';
      std::cout << "FECHA-----------: " << factura.fecha << "\n";
      std::cout << "CLIENTE---------: " << factura.id_cliente << "\n";
      std::cout << "____________________________________________________________" << '\n';
      std::cout << '\n';
   }

   void registrarFactura()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Factura modelo;
      ofstream archivo("database/Factura.bin", ios::app | ios::binary);
      std::cout << "Por favor introduzca el ID de la factura:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getFactura(auxId);
      if (modelo.id != -1)
      {
         std::cout << "Ya existe una factura con el ID especificado" << '\n';
         system("pause");
         return;
      }
      std::cout << "Por favor introduzca la informacion solicitada a continuacion:" << '\n';
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Id del cliente: ";
      modelo.id_cliente = helper.validarIntSinLimite();

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Factura));
         archivo.close();
      }
   }

   void modificarFactura()
   {
      string linea = "";
      Factura modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      int aux_id_cliente = 0;
      Cliente modeloCliente;
      fstream archivo("database/Factura.bin", ios::out | ios::in | ios::binary);
      std::cout << "Por favor introduzca el ID de la factura:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getFactura(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe una factura con el ID especificado" << '\n';
         system("pause");
         return;
      }
      do
      {
         imprimirFactura(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:" << '\n';
         std::cout << "1. ID del cliente asociado" << '\n';
         std::cout << "2. Fecha" << '\n';
         std::cout << "3. Salir" << '\n';
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(3);
         std::cout << "" << '\n';

         if (cambioPropiedad == 1)
         {
            std::cout << "Id del cliente asociado: ";
            aux_id_cliente = helper.validarIntSinLimite();
            modeloCliente = getCliente(aux_id_cliente);
            if (modeloCliente.id == -1){
               std::cout << "El cliente indicado no existe en la base de datos, por favor, registrelo." <<'\n';
            }else{
               modelo.id_cliente = aux_id_cliente;
            }
         }
         else if (cambioPropiedad == 2)
         {
            /*std::cout << "Fecha: ";
            cin >> modelo.fecha;*/
         }
      } while (cambioPropiedad != 3);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekg(auxPosicionFactura * sizeof(Factura));
         archivo.write((char *)&modelo, sizeof(Factura));
         archivo.close();
      }
   }

   int eliminarRegistro()
   {
      int auxId = 0;
      Factura modelo;
      Factura reemplazo;
      Compra modeloCompra;
      fstream archivoOriginal("database/Factura.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/FacturaTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/FacturaTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "Por favor introduzca el ID de la factura:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getFactura(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe una factura con el ID especificado" << '\n';
         system("pause");
         return -1;
      }
      if (archivoOriginal.fail())
      {
         cout << "No se pudo abrir el archivo original." << '\n';
         system("pause");
         return -1;
      }
      if (archivoTemporal.fail())
      {
         cout << "No se pudo abrir el archivo temporal." << '\n';
         system("pause");
         return -1;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Factura)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Factura));
         }
      }

      
      archivoOriginal.close();
      archivoTemporal.close();
      remove("database/Factura.bin");
      rename("database/FacturaTemp.bin", "database/Factura.bin");
      return auxId;
   }

   void registrarFacturaDirecta(Factura factura)
   {
      ofstream archivo("database/Factura.bin", ios::app | ios::binary);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&factura, sizeof(Factura));
         archivo.close();
      }
   }
};