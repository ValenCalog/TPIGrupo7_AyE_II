#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct fecha{
     int dia,mes,anio; //Inicializamos en 0?
};

struct tecnico{
     int id;
     long int DNI;
     char Nombre[30];
     struct tecnico *sgte;
};

struct cliente{
     int id;
     long int DNI;
     char Nombre[30];
     struct cliente *sgte;
};

struct tarea{
     int id_op,id_tarea,orden;
     float tiempo;
     char descripcion[30];
     struct tarea *sgte;
};

struct materiales{
     int id;
     char descripcion[30];
     float costo_uni,cantidad;
     struct materiales *sgte;
};

struct opcion{
     int id;
     char Nombre[30];
     float costo;
     struct tarea *ini;
     struct materiales *ini;
     struct opcion *sgte;
};

struct pendientes{
     struct tarea *nodo;
     struct fecha fec_fin;
     struct pendientes *sgte;
};

struct trabajos{
     int id_trabajo,id_opcion,may4;
     char direccion[30];
     int id_tecnico, id_cliente;
     struct trabajos *sgte;
};

int main(int argc, char *argv[]){

	return 0;
}
