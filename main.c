#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct tarea{
     int id_op,id_tarea,orden;
     float tiempo;
     char descripcion[30];
     struct tarea *sgte;
};

struct materiales{
     char descripcion[30];
     float costo_uni,cantidad;
     struct materiales *sgte;
};

struct opcion{
     char Nombre[30];
     float costo;
     struct tarea *ini;
     struct materiales *ini;
     struct opcion *sgte;
};

int main(int argc, char *argv[]){

	return 0;
}
