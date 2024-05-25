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
	int id_trabajo,orden;
	float tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};


float OperacionTiempo (int id);
float OperacionCosto (float tiempo);
float CostoManodeObra(int cod_op);

int buscartecnico();
int buscarcliente(int codcliente);
int Menu (int opc);

struct materiales* InsertarNuevoMaterial (struct materiales *r, struct materiales *nodo);

void AgregarListaEspera (struct trabajos *nuevo_trab);
void AltaDeMateriales (struct materiales *r);
void AltaDeOpciones ();
void AltaDeTrabajos ();
void AltaDeClientes();
void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **initech, struct trabajos **e, struct trabajos **s, struct opcion **iniopc, struct pendientes **tope);
void InsertarOpcion (struct opcion *nueva_op);
void InsertarTrabajo(struct trabajos ** nvt);
void ListadoDeOpciones ();
void ListadoDePendientes ();
void ListadoDeFinalizados ();
void OpcionesMasVendidas ();


int main(int argc, char *argv[]){
	struct cliente *inicli;
	struct materiales *raiz;
	struct materialesop *inimat;
	struct tarea *initar;
	struct tecnico *initech;
	struct trabajos *e,*s;
	struct opcion *iniopc;
	struct pendientes *tope;
	int opc=-1;
	FILE *p;
	
	CargaSupremaDeEstructuras(p, &inicli, &raiz, &inimat, &initar, &initech, &e, &s, &iniopc, &tope);
	
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
				AltaDeMateriales(raiz);
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


float CostoManodeObra(int cod_op){
}

void InsertarTrabajo(struct trabajos ** nvt){
}

void AltaDeClientes(){
}

int buscartecnico(){
}

int buscarcliente(int codcliente){
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
	int op;
	struct trabajos *nuevo_trab;
	nuevo_trab = (struct trabajos *) malloc(sizeof (struct trabajos));
	nuevo_trab->sgte = NULL;
	ListadoDeOpciones();
	
	printf("\n---Ingrese el ID de la opcion a contratar: ");
	scanf("%i",&nuevo_trab->id_opcion);
	
	printf("\n---Ingrese el ID de trabajo: ");
	scanf( "%i",&nuevo_trab->id_trabajo); //Despues se puede implementar el buscaridtrabajo() + 1;
	
	printf("\n---Ingrese la direccion de la instalacion: ");
	gets(nuevo_trab->direccion);
	printf("\nRequiere trabajo en altura?: ");
	scanf("%i",&nuevo_trab->cuatromtrs); //0 no requiere, 1 si requiere trabajo en altura
	
	nuevo_trab->id_tecnico = buscartecnico();
	nuevo_trab->CostoTotal = CostoManodeObra(nuevo_trab->id_opcion) + (CostoManodeObra(nuevo_trab->id_opcion)*nuevo_trab->cuatromtrs*0.20);
	//Por ahora no se esta teniendo en cuenta el costo de los materiales en CostoTotal
	//Si cuatromtrs es 0, no requiere trabajo en altura, por lo cual el resultado del producto sera 0 y no se suma el 20%
	printf("\nIngrese su ID de cliente: ");
	scanf("%i",&nuevo_trab->id_cliente);
	if(buscarcliente(nuevo_trab->id_cliente)==0){ 
		//buscarcliente recorre la lista de clientes en busca del id ingresado, si no lo encuentra devuelve 0
		printf("\nNo se ha encontrado un cliente asociado a la ID ingresada");
		printf("\nDesea darse de alta como cliente?");
		printf("\n1)Si");
		printf("\n2)No");
		printf("\n--> ");
		scanf("%i",&op);
		while(op!=0){
			switch(op){
			case 1:
				AltaDeClientes();
				op=0;
				break;
			case 2:
				printf("\nDisculpe las molestias, vuelva pronto");
				nuevo_trab->id_cliente=0;//Si no esta en la lista de clientes y no quiere estarlo, se cancela la solicitud de trabajo
				op=0;
				break;
			default:
				printf("Ingrese una opcion valida: ");
				printf("\n--> ");
				scanf("%i",&op);
				break;
			}
		}	
	}

	if (nuevo_trab->id_cliente != 0){ //Si no esta en 0 significa que existe en la lista de clientes
		InsertarTrabajo(&nuevo_trab);
	}
}

void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **initech, struct trabajos **ent, struct trabajos **sal, struct opcion **iniopc, struct pendientes **tope){
	struct cliente *cli, *ant;
	struct materiales *mat;
	struct materialesop *mato;
	struct tarea *tar;
	struct tecnico *tech;
	struct trabajos *trab;
	struct opcion *opc;
	struct pendientes *pend;
	int cont=0;
	
	if((p=fopen("clientes.bin","r+b"))==NULL){
		printf("||||||| Error de apertura de archivo Clientes durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			cont++;
			if(cont==1){
				cli=(struct cliente *) malloc(sizeof (struct cliente) );
				fscanf(p, "%ld" ,cli->DNI);
				fscanf(p, "%d" ,cli->id);
				fscanf(p, "%s" ,cli->Nombre);
				(*inicli)=cli;
				(*inicli)->sgte=NULL;
			}else{
				ant->sgte=cli;
				cli=(struct cliente *) malloc(sizeof (struct cliente) );
				fscanf(p, "%ld" ,cli->DNI);
				fscanf(p, "%d" ,cli->id);
				fscanf(p, "%s" ,cli->Nombre);
				ant=cli;
			}
		}
		fclose(p);
	}
}

//------------------------------------------------------------------------------//

/*int main(){
	FILE *archtrabajo;
}

void InsertarTrabajo(struct trabajos ** nv){
	ArmarListaTrab();
}

void ArmarListaTrab(){
	struct trabajos *p=NULL,*E=NULL,*S=NULL;
	if((archtrabajo=fopen("TRABAJOS.bin","r+b")==NULL)){
		printf("Error de apertura de archivo");
	}
		fread(&job,sizeof(job),1,archtrabajo);
		while(!feof(archtrabajo)){
			p=(struct trabajos *)malloc(sizeof(struct trabajos));
			p->id_trabajo = job.id_trabajo;
			p->id_opcion = job.id_opcion;
			//Lo mismo para todos los campos
			p->sgte=NULL;
			encolartrab(&p,&E,&S);
		}
}*/


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
