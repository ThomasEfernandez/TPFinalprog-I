#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#define DIMENSION 100



//structuras
typedef struct
{
    char tipo[25];
    char modelo[20];
    char color[15];
    char talle[2];
    char id[10];
    float precio;
    int cantidad;
} Prendas;
typedef struct
{
    char dni[9];
    char nombre[15];
    float sueldo;
    char puesto[20];
} Empleado;

///prototipado
Prendas CargarPrenda ();
Empleado CargarEmpleado ();

void MostrarEmpleado (Empleado x);
int CargarEmpleadosArreglo (Empleado ArregloEmpleados[DIMENSION], Empleado tempp);
void GuardarSegunPuesto (Empleado ArregloEmpleados[DIMENSION],char puesto[20],int validos);
void PasarEmpleadosArchivos (Empleado ArregloEmpleados[DIMENSION],int validos);
void MostrarSegunPuesto (char puesto[20]);

void EscribirDinero (Pila *A);
float CalcularRecaudado (Pila A);
float VenderXid (char tipo [25], char id[10], int prendasVendidas);
void DevolverPilaCargada (const char *LibroVentas ,Pila *A);
float SumarContenidoPila (Pila A);
void GuardarLoVendido (const char *LibroVentas ,float subtotal);
void ActualizarPrecio (char tipo[25],char id[10],float precioA);

int main()
{
    int accion=0;
    char tipo[25];
    char id[10];
    char puesto[20];
    float sumaRecaudado=0;
    float subtotal=0;
    int CantPrendas=0;
    float precio=0;
    Prendas temp;
    Prendas STOCK [DIMENSION];
    Empleado temporal;
    Empleado ArregloEmpleado[DIMENSION];
    Pila recaudado;
    inicpila (&recaudado);



do {
    menu ();
    fflush (stdin);
    scanf ("%d",&accion);
    switch (accion){
    case 1:
        //cargar prenda
    temp =CargarPrenda ();
    int prendasValidas =CargarPrendasAarreglo (STOCK,temp);
    PasarArregloAarchivo (STOCK,prendasValidas);
    system ("cls");

        break;


    case 2:
        //Cargar empleado
       temporal = CargarEmpleado ();
       int EmpleadosValidos =CargarEmpleadosArreglo (ArregloEmpleado,temporal);
       PasarEmpleadosArchivos (ArregloEmpleado,EmpleadosValidos);

        break;

    case 3:

        system ("cls");
        printf ("Escriba el tipo de la prenda que desea a Actualizar\n");
        printf ("------------------------------------------------------------\n");
        fflush (stdin);
        printf (">>");
        gets (tipo);
        printf ("Escriba el id de la prenda a Actualizar \n");
        printf ("------------------------------------------------------------\n");
        fflush (stdin);
        printf (">>");
        gets (id);

        printf ("Escriba el precio con el cual quiere remplazar el anterior\n");
        printf ("------------------------------------------------------------\n");
        fflush (stdin);
        printf (">>");
        scanf ("%f",&precio);
        printf ("------------------------------------------------------------\n");
        ActualizarPrecio (tipo,id,precio);
        break;



    case 4:
        //Vender prenda

        printf ("Escriba el tipo de la prenda que desea vender \n");
        printf ("-------------------------------------------------\n");
        fflush (stdin);
        printf (">>");
        gets (tipo);
        printf ("Escriba el ID de la prenda que desea vender \n");
        printf ("-------------------------------------------------\n");
        fflush (stdin);
        printf (">>");
        gets (id);

        printf ("Escriba la cantidad que desea vender \n");
        printf ("-------------------------------------------------\n");
        fflush (stdin);
        printf (">>");
        scanf ("%d",&CantPrendas);
        printf ("-------------------------------------------------\n");
        // llamo a la funcion vender por id , le paso los parametros
        subtotal = VenderXid (tipo,id,CantPrendas);
        // muestro lo que debe pagar
        printf ("LO QUE DEBE PAGAR ES: %.2f",subtotal);
        // y lo escribo en el libro de ventas
        GuardarLoVendido ("LibroVentas.txt",subtotal);

        break;

    case 5:
        //Buscar prendas segun su tipo
    system ("cls");
    printf ("escriba la prenda que desea mostrar\n");
    fflush (stdin);
    scanf ("%s",&tipo);
    mostrarSegunPrenda (tipo);


        break;
    case 6:
        //Mostrar Empleado

        system ("cls");
        printf ("  Nombre del local\n");
        printf ("----------------------- \n");
        printf ("escriba el puesto que desea mostrar\n");
        fflush (stdin);
        scanf ("%s",&puesto);
        MostrarSegunPuesto (puesto);


        break;

    case 7:
        //Mostrar total recaudado

    DevolverPilaCargada ("LibroVentas.txt",&recaudado);
    mostrar(&recaudado);
    subtotal = SumarContenidoPila (recaudado);

    printf ("Recaudo diario: %.2f \n",subtotal);

        break;

    }


}while (accion<8);
    return 0;
}

///FUNCIONES
Prendas CargarPrenda (){
Prendas x;

system ("cls");
printf ("  Nombre del local\n");
printf ("----------------------- \n");
printf ("Tipo de la prenda: \n");
fflush (stdin);
printf (">>");
gets (x.tipo);
printf ("Modelo de la prenda: \n");
fflush (stdin);
printf (">>");
gets (x.modelo);

printf ("ID de la prenda: \n");
fflush (stdin);
printf (">>");
gets (x.id);
printf ("Color de la prenda: \n");
fflush (stdin);
gets (x.color);

printf ("Cantidad de la prenda: \n");
fflush (stdin);
printf (">>");
scanf ("%d",&x.cantidad);

printf ("Talle de la prenda: \n");
fflush (stdin);
printf (">>");
gets (x.talle);

printf ("Precio de la prenda: \n");
fflush (stdin);
printf (">>");
scanf ("%f",&x.precio);


return x;
}
void MostrarPrenda (Prendas x){
   printf ("--------------------------\n");
   printf ("ID: %s \n",x.id);
   printf ("Tipo de prenda: %s \n",x.tipo);
   printf ("Modelo: %s \n",x.modelo);
   printf ("Cantidad: %d\n",x.cantidad);
   printf ("Color: %s \n",x.color);
   printf ("Precio: %.2f \n",x.precio);
   printf ("Talle: %s \n",x.talle);
   printf ("--------------------------\n");



}
int CargarPrendasAarreglo (Prendas stock[DIMENSION],Prendas temp){

  int i=0;

        stock[i]=temp;
        i++;


    return i;
}
void GuardarSegunPrendas (Prendas stock[DIMENSION],char tipo[25],int validos){

FILE *buffer =fopen (tipo,"ab");

if (buffer !=NULL)
    {

        for (int i=0; i<validos; i++)
        {
            if (strcmp(stock[i].tipo,tipo)==0)
            {
                fwrite (&stock[i],sizeof(Prendas),1,buffer);

            }
        }
    }
    else
    {
        printf ("error\n");
    }

    fclose (buffer);
}
void PasarArregloAarchivo (Prendas stock[DIMENSION],int validos){


    FILE *buffer = fopen ("STOCK.bin","wb");
    int i=0;


    if (buffer!=NULL)
    {
        for (int i=0; i<validos; i++)
        {
            GuardarSegunPrendas (stock,stock[i].tipo,validos);
        }

    }
    else
    {

        printf ("error \n");

    }
    fclose (buffer);



}
void mostrarSegunPrenda (char tipo[25]){

Prendas temp;
FILE *buffer = fopen (tipo,"rb");


    if (buffer!=NULL){

         while (fread(&temp,sizeof(Prendas),1,buffer)>0)
        {

            MostrarPrenda (temp);

        }


    }



}
void menu (){
printf ("\n Nombre de local\n");
printf ("---------------------\n");
printf ("Cargar  Prendas   [1]\n");
printf ("Cargar  Empleado  [2]\n");
printf ("Actualizar precio [3]\n");
printf ("Vender  Prendas   [4]\n");
printf ("Mostrar Prendas   [5]\n");
printf ("Mostrar Empleado  [6]\n");+
printf ("Mostrar Recaudado [7]\n");
printf ("Salir             [8]\n");
printf ("---------------------\n");


}

Empleado CargarEmpleado (){
Empleado temp;

system ("cls");
printf ("  Nombre del local\n");
printf ("----------------------- \n");
printf ("Escriba el nombre del empleado\n");
fflush (stdin);
printf (">>");
gets (temp.nombre);
printf ("Escriba el DNI del empleado\n");
fflush (stdin);
printf (">>");
gets (temp.dni);
printf ("Escriba el puesto  del empleado\n");
fflush (stdin);
printf (">>");
gets (temp.puesto);
printf ("Escriba el sueldo del empleado\n");
fflush (stdin);
printf (">>");
scanf ("%f",&temp.sueldo);






return temp;
}
void MostrarEmpleado (Empleado x){

printf ("------------------------------\n");
printf ("El nombre es: %s \n",x.nombre);
printf ("El dni es: %s \n",x.dni);
printf ("El puesto es: %s \n",x.puesto);
printf ("El sueldo es: %.2f \n",x.sueldo);
printf ("------------------------------\n");

}
int CargarEmpleadosArreglo (Empleado ArregloEmpleados[DIMENSION], Empleado tempp){

      int i=0;

        ArregloEmpleados[i]=tempp;
        i++;

    return i;
}
void GuardarSegunPuesto (Empleado ArregloEmpleados[DIMENSION],char puesto[20],int validos){
FILE *buffer =fopen (puesto,"ab");

if (buffer !=NULL)
    {

        for (int i=0;i<validos;i++)
        {
            if (strcmp(ArregloEmpleados[i].puesto,puesto)==0)
            {
                fwrite (&ArregloEmpleados[i],sizeof(Empleado),1,buffer);

            }
        }
    }
    else
    {
        printf ("error\n");
    }

    fclose (buffer);


}
void PasarEmpleadosArchivos (Empleado ArregloEmpleados[DIMENSION],int validos){

    FILE *buffer = fopen ("EMPLEADOS.bin","wb");
    int i=0;


    if (buffer!=NULL)
    {
        for (int i=0;i<validos;i++)
        {
            GuardarSegunPuesto (ArregloEmpleados,ArregloEmpleados[i].puesto,validos);
        }

    }
    else
    {

        printf ("error \n");

    }
    fclose (buffer);


}
void MostrarSegunPuesto (char puesto[20]){
Empleado temp;

FILE *buffer = fopen (puesto,"rb");


    if (buffer!=NULL){

         while (fread(&temp,sizeof(Empleado),1,buffer)>0)
        {

            MostrarEmpleado (temp);

        }


    }else{
printf ("error \n");

    }
fclose (buffer);
}
float VenderXid (char tipo [25],char id[10], int prendasVendidas){

Prendas temp;
FILE *buffer = fopen (tipo,"r+b");
int flag=0;
float precioPrenda=0;

    if (buffer!=NULL){

         while (!flag && fread(&temp,sizeof(Prendas),1,buffer)>0)
        {
            if (strcmp(temp.id,id)==0){

                temp.cantidad=temp.cantidad - prendasVendidas;

                fseek(buffer,sizeof(Prendas)*-1,SEEK_CUR);
                fwrite (&temp,sizeof(Prendas),1,buffer);
                flag=1;
                precioPrenda=temp.precio*prendasVendidas;

        }
        }

    }
fclose (buffer);
return precioPrenda;
}

void GuardarLoVendido (const char *LibroVentas ,float subtotal){

    FILE *buffer = fopen (LibroVentas,"a");

    if (buffer!=NULL){

        fwrite (&subtotal,sizeof(float),1,buffer);

    }else {
    printf ("error \n");
    }
fclose (buffer);
}

void DevolverPilaCargada (const char *LibroVentas, Pila *A){
float precioTemp=0;

FILE  *buffer = fopen (LibroVentas,"r");

if (buffer!=NULL){
        while (fread(&precioTemp,sizeof(float),1,buffer)>0){

        apilar (A,precioTemp);

}
}else{

printf ("error  \n");

}

}

float SumarContenidoPila (Pila A){

float ganancia=0;

while (!pilavacia(&A)){


    ganancia = ganancia + desapilar(&A);

}

return ganancia;
}


void ActualizarPrecio (char tipo[25],char id[10],float precioA){
Prendas temp;
int flag=0;
FILE *buffer = fopen (tipo,"r+b");
if (buffer!=NULL){
     while (!flag && fread(&temp,sizeof(Prendas),1,buffer)>0)
        {
            if (strcmp(temp.id,id)==0){

                temp.precio=precioA;

                fseek(buffer,sizeof(Prendas)*-1,SEEK_END);
                fwrite (&temp,sizeof(Prendas),1,buffer);
                flag=1;

        }
        }

}else{
printf ("error\n");

}
fclose (buffer);
}
