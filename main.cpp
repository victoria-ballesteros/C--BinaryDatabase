#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>

//  Clases
#include "helpers.h"
#include "dataTypes\dataTypes.h"

using namespace std;

clientes cliente;
compras compra;
facturas factura;
productos producto;
proveedores proveedor;

long key[4] = {11235, 81321, 34558, 0};
int eleccionMenu = 0, keyNumber = 0;
random_device rd;
mt19937 gen(rd());

long helpers::validarLong(){
   long numero = 0;
    while(!(cin >> numero)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor, ingresa un número: ";
    }
    return numero;
 }

int helpers::validarInt(int maximo){
int numero;
   do{
   while(!(cin >> numero)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada inválida. Por favor, ingresa un número: ";
   }
   }while(numero <= 0 || numero > maximo);
   return numero;
}   

int helpers::validarIntSinLimite(){
int numero;
   while(!(cin >> numero)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada inválida. Por favor, ingresa un número: ";
   }
return numero;
}

void generarFechaActual(facturas::Factura& factura){
   time_t time = std::time(0); 
   std::tm* now = std::localtime(&time);
   std::strftime(factura.fecha, sizeof(factura.fecha), "%d-%m-%Y", now);
}

int generarRandom(){
   uniform_int_distribution<> distrib(10, 99);
   int numeroAleatorio = distrib(gen);
   return numeroAleatorio;
}
 
int validarClave() {
   int i= 0, puesto= 0;
   bool flag= false;
   long claveIntroducida = 0;
   
   do{
      cout <<"Introduzca una clave de acceso: "<<'\n';
      claveIntroducida= helper.validarLong();
      for(i = 0; i<3; i++){
         if(key[i] == claveIntroducida){
            flag= true;
            puesto= i;
            break;
         }
      }
   }while(flag != true);
   return puesto;
 }
 
void agregarRegistro (int eleccionMenu){
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

void modificarRegistro (int eleccionMenu){
   
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
      producto.modificarProducto();
      break;
   case 5:
      proveedor.modificarProveedor();
      break;
   default:
      break;
   }
 }

void eliminarRegistro (int eleccionMenu){
   
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

int subMenuAdministrador(){
int seleccion = 0;
cout<<"Por favor seleccione una opcion:"<<'\n';
cout<<"1. Agregar Registro"<<'\n';
cout<<"2. Editar Registro"<<'\n';
cout<<"3. Eliminar Registro"<<'\n';
cout<<"4. Seleccionar otro tipo de Registro"<<'\n';
seleccion = helper.validarInt(4);
return seleccion;
}

void mecanismoCaja(){
   long auxId = 0, continuarCompra = 0;
   int id_factura = 0, id_compra = 0;
   bool flagIds = false;
   clientes::Cliente modelo;
   facturas::Factura modeloFactura;
   compras::Compra modeloCompra;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   cout<<"Por favor introduzca el ID del cliente: ";
   auxId = helper.validarLong();
   modelo = cliente.getCliente(auxId);

   if(modelo.id == -1){
      cout<<"Por favor registre al cliente"<<'\n';
      cliente.registroDirecto(auxId);
   }else{
      system("cls");
      cout<<"EL cliente ya existe en la base de datos:"<<'\n';
      cout<<""<<'\n';
      cliente.imprimirCliente(modelo);
   }
   cout<<""<<'\n';
   cout<<"COMPRA:"<<'\n';
   do{
      id_factura = generarRandom();
      modeloFactura = factura.getFactura(id_factura);
      if(modeloFactura.id == -1){
         flagIds = true;
      }
   }while(flagIds == false);
   flagIds = false;
   do{
      do{
         id_compra = generarRandom();
         modeloCompra = compra.getCompra(id_compra);
         if(modeloCompra.id == -1){
            flagIds = true;
         }
      }while(flagIds == false);
      flagIds = false;
      compra.registrarCompraCaja(id_factura, id_compra);
      cout<<"iIndique si hay otro producto por registrar:"<<'\n';
      cout<<"1. Si"<<'\n';
      cout<<"2. No"<<'\n';
      continuarCompra = helper.validarInt(2);
   }while(continuarCompra != 2);
   cout<<""<<'\n';
   cout<<"Procesando factura"<<'\n';
   modeloFactura.id = id_factura;
   modeloFactura.id_cliente = modelo.id;
   generarFechaActual(modeloFactura);
   factura.registrarFacturaDirecta(modeloFactura);
   cout<<""<<'\n';
   factura.imprimirFactura(modeloFactura);
   cout<<"PRODUCTOS FACTURADOS"<<'\n';
   compra.listarComprasUnicas(id_factura);
   cout<<""<<'\n';


}

 int menu (int clave){
   int eleccionOpcion = 0, opcionesCaja = 0;
   switch (clave)
   {
   case 0: //  administrador
   do{
      system("cls");
      cout<<"Por favor seleccione un registro:"<<'\n';
      cout<<"1. Cliente"<<'\n';
      cout<<"2. Compra"<<'\n';
      cout<<"3. Factura"<<'\n';
      cout<<"4. Producto"<<'\n';
      cout<<"5. Proveedor"<<'\n';
      eleccionMenu = helper.validarInt(5);

         if(eleccionMenu == 1){
            system("cls");
            cout<<""<<'\n';
            cout<<"CLIENTES REGISTRADOS"<<'\n';
            cliente.listarClientes();
            cout<<""<<'\n';
         }else if(eleccionMenu == 2){
            system("cls");
            cout<<""<<'\n';
            cout<<"COMPRAS REGISTRADOS"<<'\n';
            compra.listarCompras();
            cout<<""<<'\n';
         }else if(eleccionMenu == 3){
            system("cls");
            cout<<""<<'\n';
            cout<<"FACTURAS REGISTRADOS"<<'\n';
            factura.listarFacturas();
            cout<<""<<'\n';
         }else if(eleccionMenu == 4){
            system("cls");
            cout<<""<<'\n';
            cout<<"PRODUCTOS REGISTRADOS"<<'\n';
            producto.listarProductos();
            cout<<""<<'\n';
         }else if(eleccionMenu == 5){
            system("cls");
            cout<<""<<'\n';
            cout<<"PROVEEDORES REGISTRADOS"<<'\n';
            proveedor.listarProveedores();
            cout<<""<<'\n';
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

   }while (eleccionMenu != 6);
      break;
   case 1: //  almacén
      break;
   case 2: //  vendedor
      cout<<""<<'\n';
      cout<<"APERTURA DE CAJA"<<'\n';
      do{
         mecanismoCaja();
         cout<<"Por favor indique si ya es momento de cerrar caja:"<<'\n';
         cout<<"1. Si"<<'\n';
         cout<<"2. No"<<'\n';
         opcionesCaja = helper.validarInt(2);
      }while(opcionesCaja != 1);
      cout<<"JORNADA FINALIZADA";
      break;
   default:
      break;
   }
 }

  int main (){
      keyNumber= validarClave();
      menu(keyNumber);
      return 0;
 }

