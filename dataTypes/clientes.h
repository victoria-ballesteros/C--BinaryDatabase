#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class clientes : public registro
{

public:
   void listarClientes()
   {
      ifstream archivo("database/Cliente.bin", ios::binary);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Cliente cliente;
      while (archivo.read((char *)&cliente, sizeof(Cliente)))
      {
         std::cout << ""
                   << "\n";
         std::cout << "ID--------------------: " << cliente.id << "\n";
         std::cout << "NOMBRE----------------: " << cliente.nombre << "\n";
         std::cout << "__________________________________________________"
                   << "\n";
      }
      archivo.close();
   }

   void imprimirCliente(Cliente cliente)
   {
      std::cout << "ID--------------: " << cliente.id << "\n";
      std::cout << "Nombre----------: " << cliente.nombre << "\n";
      std::cout << "Direccion-------: " << cliente.direccion << "\n";
      std::cout << "Telefono--------: " << cliente.telefono << "\n";
      std::cout << "____________________________________________________________"
                << "\n";
      std::cout << "\n";
   }

   void registrarCliente()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Cliente modelo;
      ofstream archivo("database/Cliente.bin", ios::app | ios::binary);
      std::cout << "Por favor introduzca el ID del cliente: "
                  << "\n";
      auxId = helper.validarIntSinLimite();
      modelo = getCliente(auxId);
      if (modelo.id != -1)
      {
         std::cout << "Ya existe un cliente con el ID especificado"
                     << "\n";
         system("pause");
         return;
      }
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Nombre: ";
      getline(cin, linea);
      strcpy(modelo.nombre, linea.c_str());
      std::cout << "Direccion: ";
      getline(cin, linea);
      strcpy(modelo.direccion, linea.c_str());
      std::cout << "Telefono: ";
      getline(cin, linea);
      strcpy(modelo.telefono, linea.c_str());

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }

   void modificarCliente()
   {
      string linea = "";
      Cliente modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Cliente.bin", ios::out | ios::in | ios::binary);
      std::cout << "Por favor introduzca el ID del cliente"
                  << "\n";
      auxId = helper.validarIntSinLimite();
      modelo = getCliente(auxId);

      if (modelo.id == -1)
      {
         std::cout << "No existe un cliente con el ID especificado"
                     << "\n";
         system("pause");
      }
      do
      {
         imprimirCliente(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:"
                   << "\n";
         std::cout << "1. Nombre"
                   << "\n";
         std::cout << "2. Direccion"
                   << "\n";
         std::cout << "3. Telefono"
                   << "\n";
         std::cout << "4. Salir"
                   << "\n";
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         std::cout << ""
                   << "\n";

         if (cambioPropiedad == 1)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Nombre: ";
            getline(cin, linea);
            strcpy(modelo.nombre, linea.c_str());
         }
         else if (cambioPropiedad == 2)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Direccion: ";
            getline(cin, linea);
            strcpy(modelo.direccion, linea.c_str());
         }
         else if (cambioPropiedad == 3)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Telefono: ";
            getline(cin, linea);
            strcpy(modelo.direccion, linea.c_str());
         }

      } while (cambioPropiedad != 4);

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
      }
      else
      {
         archivo.seekg(auxPosicionCliente * sizeof(Cliente));
         archivo.write((char *)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }

   void eliminarRegistro()
   {
      int auxId = 0;
      Cliente modelo;
      Cliente reemplazo;
      fstream archivoOriginal("database/Cliente.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/ClienteTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/ClienteTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "Por favor introduzca el ID del Cliente:"
                  << "\n";
      auxId = helper.validarInt(99999);
      modelo = getCliente(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe un cliente con el ID especificado"
                     << "\n";
         system("pause");
         return;
      }
      if (archivoOriginal.fail())
      {
         cerr << "No se pudo abrir el archivo original.\n";
         system("pause");
         return;
      }
      if (archivoTemporal.fail())
      {
         cerr << "No se pudo abrir el archivo temporal.\n";
         system("pause");
         return;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Cliente)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Cliente));
         }
      }

      archivoOriginal.close();
      archivoTemporal.close();

      remove("database/Cliente.bin");
      rename("database/ClienteTemp.bin", "database/Cliente.bin");
   }

   void registroDirecto(int _id)
   {
      string linea = "";
      Cliente modelo;
      ofstream archivo("database/Cliente.bin", ios::app | ios::binary);
      modelo.id = _id;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Nombre: ";
      getline(cin, linea);
      strcpy(modelo.nombre, linea.c_str());
      std::cout << "Direccion: ";
      getline(cin, linea);
      strcpy(modelo.direccion, linea.c_str());
      std::cout << "Telefono: ";
      getline(cin, linea);
      strcpy(modelo.telefono, linea.c_str());

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }
};