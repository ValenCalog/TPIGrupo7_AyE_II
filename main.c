#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct fecha{
     int dia,mes,anio; //Inicializamos en 0?
};

struct tecnico{ //cola
     int id;
     long int DNI;
     char Nombre[30];
     struct tecnico *sgte;
};

struct cliente{ //cola
     int id;
     long int DNI;
     char Nombre[30];
     struct cliente *sgte;
};

struct tarea{ //lista doblemente enlazada
     int id_op,id_tarea,orden;
     float tiempo;
     char descripcion[30];
     struct tarea *sgte, *ant;
};

struct materiales{ //arbol de busqueda binaria
     int id;
     char descripcion[30],unimed[10];
     float costo_uni,cantidad;
     struct materiales *izq, *derch;
};

struct materialesop{
	int idaux, cantidad;
	struct materialesop *sgte;
};

struct opcion{ //lista enlazada simple
     int id;
     char Nombre[30];
     float costo, tiempo;
     struct materiales *iniMat;
     struct opcion *sgte;
};

struct pendientes{ //pila
	int id_trabajo,orden;
	float tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};

struct trabajos{ 
     int id_trabajo,id_opcion,cuatromtrs;
     char direccion[30];
     int id_tecnico, id_cliente;
	 struct fecha fc_fin;
     struct trabajos *sgte;
};

int menu (int opc); //menusito
void listado_opc (); //para listar opciones
void alta_opc (); //para dar de alta opciones
void alta_trab (); //para dar de alta trabajos
void listado_trabytar (); //para lisar trabajos pendientes
void listado_finitrab (); //para listar trabajos finalizados
void mopcsvends (); //para listar opciones mas vendidas

int main(int argc, char *argv[]){
	int opc=-1;
	while(opc!=0){
		//system("CLS");
		opc=menu(opc);
		switch(opc){
			case 1:
				listado_opc();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 2:
				alta_opc();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 3:
				alta_trab();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 4:
				listado_trabytar();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 5:
				listado_finitrab();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 6:
				mopcsvends();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
		}
	}
	return (0);
}

int menu (int o){
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

void listado_opc (){
	struct opcion{
     int id;
     char Nombre[30];
     float costo;
     struct tarea *ini;
     struct materiales *iniMat;
     struct opcion *sgte;
};
}

void alta_opc (){
	
}

void alta_trab (){
}

void listado_trabytar (){
}

void listado_finitrab (){
}

void mopcsvends (){
}

void altamateriales(){
    struct materiales *nuevo_mat;
    nuevo_mat= (struct materiales *) malloc(sizeof(struct materiales))
    nuevo_mat->id = buscarmayorid() + 1;//necesitamos saber el id del ultimo material ingresado
    printf("Ingrese la descripcion del material: ");
    gets(nuevo_mat->descripcion);
    printf(Ingrese cual sera la unidad de medida: ");
    gets(nuevo_mat->unimed);
    printf("Ingrese el precio unitario del nuevo material: ");
    scanf("%f",&nuevo_mat->costo_uni);
    insertarnuevomat(nuevo_mat);//insertamos el nodo con el nuevo material al arbol
}

void insertarnuevomat(){
     
}
