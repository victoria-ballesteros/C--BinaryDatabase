#include <iostream>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include "helpers.h"
#include "dataTypes\dataTypes.h"

clientes cliente;
compras compra;
facturas factura;
productos producto;
proveedores proveedor;

long key[4] = {11235, 81321, 34558, 0};
int eleccionMenu = 0, keyNumber = 0, terminarEjecucion = 0;
random_device rd;
mt19937 gen(rd());

void generarFechaActual(facturas::Factura &factura);
void agregarRegistro(int eleccionMenu);
void modificarRegistro(int eleccionMenu);
void eliminarRegistro(int eleccionMenu);
void mecanismoCaja();
void mecanismoAlmacen();

int subMenuAdministrador();
int generarRandom();
int validarClave();
void menu(int clave);

int main()
{
   do
   {
      keyNumber = validarClave();
      menu(keyNumber);
      system("cls");
      std::cout << "***INDIQUE SI DESEA INTRODUCIR UNA CLAVE DIFERENTE***" << '\n';
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      terminarEjecucion = helper.validarInt(2);
   } while (terminarEjecucion != 2);
   return 0;
}

long helpers::validarLong()
{
   long numero = 0;
   while (!(cin >> numero))
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero: ";
   }
   return numero;
}

int helpers::validarInt(int maximo)
{
   int numero;
   do
   {
      while (!(cin >> numero))
      {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         std::cout << "Entrada invalida. Por favor, ingresa un numero: ";
      }
   } while (numero <= 0 || numero > maximo);
   return numero;
}

int helpers::validarIntSinLimite()
{
   int numero;
   while (!(cin >> numero))
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero: ";
   }
   return numero;
}

float helpers::validarFloat()
{
   float numero = 0.0;
   while (!(std::cin >> numero))
   {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero (punto para la coma flotante): ";
   }
   return numero;
}

void generarFechaActual(facturas::Factura &factura)
{
   time_t time = std::time(0);
   std::tm *now = std::localtime(&time);
   std::strftime(factura.fecha, sizeof(factura.fecha), "%d-%m-%Y", now);
}

int generarRandom()
{
   uniform_int_distribution<> distrib(10, 99);
   int numeroAleatorio = distrib(gen);
   return numeroAleatorio;
}

int validarClave()
{
   int i = 0, puesto = 0;
   bool flag = false;
   long claveIntroducida = 0;

   do
   {
      std::cout << "Introduzca una clave de acceso: ";
      claveIntroducida = helper.validarLong();
      for (i = 0; i < 3; i++)
      {
         if (key[i] == claveIntroducida)
         {
            flag = true;
            puesto = i;
            break;
         }
      }
   } while (flag != true);
   return puesto;
}

void agregarRegistro(int eleccionMenu)
{
   switch (eleccionMenu)
   {
   case 1:
      cliente.registrarCliente();
      break;
   case 2:
      compra.registrarCompra();
      break;
   case 3:
      factura.registrarFactura();
      break;
   case 4:
      producto.registrarProducto();
      break;
   case 5:
      proveedor.registrarProveedor();
      break;
   default:
      break;
   }
}

void modificarRegistro(int eleccionMenu)
{

   switch (eleccionMenu)
   {
   case 1:
      cliente.modificarCliente();
      break;
   case 2:
      compra.modificarCompra();
      break;
   case 3:
      factura.modificarFactura();
      break;
   case 4:
      producto.modificarProducto("database/Producto.bin");
      break;
   case 5:
      proveedor.modificarProveedor();
      break;
   default:
      break;
   }
}

void eliminarRegistro(int eleccionMenu)
{

   switch (eleccionMenu)
   {
   case 1:
      cliente.eliminarRegistro();
      break;
   case 2:
      compra.eliminarRegistro();
      break;
   case 3:
      factura.eliminarRegistro();
      break;
   case 4:
      producto.eliminarRegistro();
      break;
   case 5:
      proveedor.eliminarRegistro();
      break;
   default:
      break;
   }
}

int subMenuAdministrador()
{
   int seleccion = 0;
   std::cout << "Por favor seleccione una opcion:" << '\n';
   std::cout << "1. Agregar Registro" << '\n';
   std::cout << "2. Editar Registro" << '\n';
   std::cout << "3. Eliminar Registro" << '\n';
   std::cout << "4. Seleccionar otro tipo de Registro" << '\n';
   seleccion = helper.validarInt(4);
   return seleccion;
}

void mecanismoCaja()
{
   long auxId = 0, continuarCompra = 0;
   int id_factura = 0, id_compra = 0;
   bool flagIds = false;
   clientes::Cliente modelo;
   facturas::Factura modeloFactura;
   compras::Compra modeloCompra;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   std::cout << "Por favor introduzca el ID del cliente: ";
   auxId = helper.validarLong();
   modelo = cliente.getCliente(auxId);

   if (modelo.id == -1)
   {
      std::cout << "Por favor registre al cliente" << '\n';
      cliente.registroDirecto(auxId);
   }
   else
   {
      system("cls");
      std::cout << "EL cliente ya existe en la base de datos:" << '\n';
      std::cout << "" << '\n';
      cliente.imprimirCliente(modelo);
   }
   std::cout << "" << '\n';
   std::cout << "COMPRA:" << '\n';
   do
   {
      id_factura = generarRandom();
      modeloFactura = factura.getFactura(id_factura);
      if (modeloFactura.id == -1)
      {
         flagIds = true;
      }
   } while (flagIds == false);
   flagIds = false;
   do
   {
      do
      {
         id_compra = generarRandom();
         modeloCompra = compra.getCompra(id_compra);
         if (modeloCompra.id == -1)
         {
            flagIds = true;
         }
      } while (flagIds == false);
      flagIds = false;
      compra.registrarCompraCaja(id_factura, id_compra);
      std::cout << "iIndique si hay otro producto por registrar:" << '\n';
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      continuarCompra = helper.validarInt(2);
   } while (continuarCompra != 2);
   std::cout << "" << '\n';
   std::cout << "Procesando factura" << '\n';
   modeloFactura.id = id_factura;
   modeloFactura.id_cliente = modelo.id;
   generarFechaActual(modeloFactura);
   factura.registrarFacturaDirecta(modeloFactura);
   std::cout << "" << '\n';
   factura.imprimirFactura(modeloFactura);
   std::cout << "PRODUCTOS FACTURADOS" << '\n';
   compra.listarComprasUnicas(id_factura);
   std::cout << "" << '\n';
}

void mecanismoAlmacen()
{
   string dir = "";
   int aux_id = 0, finJornada = 0;
   productos::Producto modelo;
   do
   {
      std::cout << "Por favor introduzca el nombre del archivo de texto con el cual va a trabajar: ";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      getline(cin, dir);
      if (dir == "Producto" || dir == "ProductoTemp")
      {
         std::cout << "Su archivo no puede tener el nombre indicado" << '\n';
      }
   } while (dir == "Producto" || dir == "ProductoTemp");
   producto.escribirNuevoArchivo(dir);
   std::cout << "__________________________________" << '\n';
   producto.listarProductos("database/" + dir + ".bin");
   do
   {
      do
      {
         std::cout << "Por favor indique el ID del producto que desea modificar: ";
         aux_id = helper.validarIntSinLimite();
         modelo = producto.getProducto(aux_id);
         if (modelo.id == -1)
         {
            std::cout << "El ID indicado no corresponde a ningun producto" << '\n';
         }
      } while (modelo.id == -1);
      producto.modificacionesAlmacen(dir, aux_id);
      std::cout << "Fin de jornada?:" << '\n';
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      finJornada = helper.validarInt(2);
   } while (finJornada == 2);
   std::cout << "Su archivo será aprobado o desechado por un administrador" << '\n';
}

void menu(int clave)
{
   int eleccionOpcion = 0, opcionesCaja = 0;
   switch (clave)
   {
   case 0: //  administrador
      do
      {
         system("cls");
         std::cout << "Por favor seleccione un registro:" << '\n';
         std::cout << "1. Cliente" << '\n';
         std::cout << "2. Compra" << '\n';
         std::cout << "3. Factura" << '\n';
         std::cout << "4. Producto" << '\n';
         std::cout << "5. Proveedor" << '\n';
         std::cout << "6. Volver" << '\n';
         eleccionMenu = helper.validarInt(6);
         if (eleccionMenu == 1)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "CLIENTES REGISTRADOS" << '\n';
            cliente.listarClientes();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 2)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "COMPRAS REGISTRADOS" << '\n';
            compra.listarCompras();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 3)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "FACTURAS REGISTRADOS" << '\n';
            factura.listarFacturas();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 4)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "PRODUCTOS REGISTRADOS" << '\n';
            producto.listarProductos("database/Producto.bin");
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 5)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "PROVEEDORES REGISTRADOS" << '\n';
            proveedor.listarProveedores();
            std::cout << "" << '\n';
         }else if (eleccionMenu == 6){
            return;
         }

         eleccionOpcion = subMenuAdministrador();

         switch (eleccionOpcion)
         {
         case 1:
            agregarRegistro(eleccionMenu);
            break;

         case 2:
            modificarRegistro(eleccionMenu);
            break;

         case 3:
            eliminarRegistro(eleccionMenu);
            break;
         default:
            break;
         }

      } while (eleccionMenu != 6);
      break;
   case 1: //  almacén
      std::cout << "" << '\n';
      std::cout << "APERTURA DE ALMACEN" << '\n';
      std::cout << "" << '\n';
      mecanismoAlmacen();

      break;
   case 2: //  vendedor
      std::cout << "" << '\n';
      std::cout << "APERTURA DE CAJA" << '\n';
      std::cout << "" << '\n';
      do
      {
         mecanismoCaja();
         std::cout << "Por favor indique si ya es momento de cerrar caja:" << '\n';
         std::cout << "1. Si" << '\n';
         std::cout << "2. No" << '\n';
         opcionesCaja = helper.validarInt(2);
      } while (opcionesCaja != 1);
      std::cout << "JORNADA FINALIZADA";
      break;
   default:
      break;
   }
}
