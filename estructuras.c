#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct materiales{ //Arbol de Busqueda Binaria.
     int id;
     char descripcion[30],unimed[10];
     float costo_uni,cantidad;
     struct materiales *izq, *derch;
};

struct trabajos{ //Cola.
     int id_trabajo, id_opcion, cuatromtrs;
     float CostoTotal;
     char direccion[30];
     int id_tecnico, id_cliente, fc_fin[3];
     struct trabajos *sgte;
};

struct tarea{ //Lista Doblemente Enlazada.
     int id_op, id_tarea, orden;
     float tiempo;
     char descripcion[30];
     struct tarea *sgte, *ant;
};

struct cliente{ //Lista Enlazada Simple.
     int id;
     long int DNI;
     char Nombre[30];
     struct cliente *sgte;
};

struct materialesop{ //Lista Enlazada Simple.
	int idmat, cantidad, id_opcion;
	struct materialesop *sgte;
};

struct opcion{ //Lista Enlazada Simple.
     int id;
     char Nombre[30];
     float costo, tiempo;
     struct opcion *sgte;
};

struct tecnico{ //Lista Enlazada Simple. La cambiamos a cola(?
     int id;
     long int DNI;
     char Nombre[30];
     struct tecnico *sgte;
};

struct pendientes{ //Pila
	int id_trabajo, orden, completado;
	float tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};

