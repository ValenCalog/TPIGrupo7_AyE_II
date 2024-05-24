#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fecha{
     int dia,mes,anio;
};

struct materiales{ //Arbol de Busqueda Binaria.
     int id;
     char descripcion[30],unimed[10];
     float costo_uni,cantidad;
     struct materiales *izq, *derch;
};

struct trabajos{ //Cola.
     int id_trabajo,id_opcion,cuatromtrs;
     char direccion[30];
     int id_tecnico, id_cliente;
	 struct fecha fc_fin;
     struct trabajos *sgte;
};

struct tarea{ //Lista Doblemente Enlazada.
     int id_op,id_tarea,orden;
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
	int idmat, cantidad,id_opcion;
	struct materialesop *sgte;
};

struct opcion{ //Lista Enlazada Simple.
     int id;
     char Nombre[30];
     float costo, tiempo;
     struct opcion *sgte;
};

struct tecnico{ //Lista Enlazada Simple.
     int id;
     long int DNI;
     char Nombre[30];
     struct tecnico *sgte;
};

struct pendientes{ //Pila
	int id_trabajo,orden;
	float tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};

float OperacionTiempo (int id);
float OperacionCosto (float tiempo);
int Menu (int opc);
struct materiales* InsertarNuevoMaterial (struct materiales *r, struct materiales *nodo);
void AltaDeMateriales (struct materiales *r);
void AltaDeOpciones ();
void AltaDeTrabajos ();
void InsertarOpcion (struct opcion *nueva_op);
void ListadoDeOpciones ();
void ListadoDePendientes ();
void ListadoDeFinalizados ();
void OpcionesMasVendidas ();

int main(int argc, char *argv[]){
	struct materiales *r;
	int opc=-1;
	
	while(opc!=0){
		//system("CLS");
		opc = Menu(opc);
		switch(opc){
			case 1:
				ListadoDeOpciones();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 2:
				AltaDeOpciones();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 3:
				AltaDeTrabajos();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 4:
				ListadoDePendientes();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 5:
				ListadoDeFinalizados();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 6:
				OpcionesMasVendidas();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 7:
				AltaDeMateriales(r);
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
		}
	}
	return (0);
}

float OperacionTiempo (int id){
}

float OperacionCosto (float tiempo){
}

int Menu (int o){
	int contgency=0;
	while( (o!=0) && (o!=1) && (o!=2) && (o!=3) && (o!=4) && (o!=5) && (o!=6) ){
		if(contgency>=1){
			printf( "El valor que ingreso no es valido, vuelva a ingresar una opcion. \n" );
			scanf( "%d", &o );
			fflush(stdin);
		}else{
			printf( "-------------------Bienvenido al menu :D-------------------\n---Ingrese 1 para listar opciones.\n---Ingrese 2 para dar de alta un opcion.\n---Ingrese 3 para dar de alta un trabajo.\n---Ingrese 4 para listar trabajos y tareas pendientes.\n---Ingrese 5 para listar los trabajos finalizados.\n---Ingrese 6 para listar las opciones mas vendidas.\n" );
			scanf( "%d", &o );
			fflush(stdin);
			contgency++;
		}
	}
	return (o);
}

struct materiales* InsertarNuevoMaterial (struct materiales *raiz, struct materiales *nodo){
	if( raiz == NULL ){
		raiz = nodo;
	}else{
		if( raiz == nodo ){
			printf( "Ya esta en la lista. \n" );
		}else{
			if( nodo < raiz ){
				raiz->izq = InsertarNuevoMaterial (raiz->izq, nodo);
			}else{
				raiz->derch = InsertarNuevoMaterial (raiz->derch, nodo);
			}
		}
	}
	return (raiz);
}

void AltaDeMateriales (struct materiales *raiz){
    struct materiales *nuevo_mat;

    nuevo_mat = (struct materiales *) malloc (sizeof (struct materiales) );
    if( nuevo_mat == NULL ){
       printf( ":( No hay espacio en la memoria \n" );
    }else{
    	printf( "---Ingrese el ID de material: \n" );
		scanf( "%i", &nuevo_mat->id );
		
		printf( "---Ingrese la descripcion del material: \n" );
		gets( nuevo_mat->descripcion );
		
		printf( "---Ingrese cual sera la unidad de medida: \n" );
		gets( nuevo_mat->unimed );
		
		printf( "---Ingrese el precio unitario del nuevo material: \n" );
		scanf( "%f", &nuevo_mat->costo_uni );
		
		raiz = InsertarNuevoMaterial (raiz, nuevo_mat);
		//Insertamos el nodo, con el nuevo material, al arbol.
	}
}

void AltaDeOpciones (){
	struct opcion *nueva_op;
	nueva_op = (struct opcion *) malloc (sizeof (struct opcion) );
	if(nueva_op == NULL){
		printf( ":( No hay espacio en memoria \n" );
		
	}else{
		printf( "---Digite el ID de la opcion: \n" );
		scanf( "%i", &nueva_op->id );
		
		printf( "---Digite el nombre de la nueva opcion: \n" );
		gets( nueva_op->Nombre );
		
		nueva_op->tiempo = OperacionTiempo ( nueva_op->id );
		nueva_op->costo = OperacionCosto ( nueva_op->tiempo );
		nueva_op->sgte = NULL;
		InsertarOpcion (nueva_op);
	}
}

void AltaDeTrabajos (){
}

void InsertarOpcion (struct opcion *nueva_op){
}

void ListadoDeOpciones (){
}

void ListadoDePendientes (){
}

void ListadoDeFinalizados (){
}

void OpcionesMasVendidas (){
}
