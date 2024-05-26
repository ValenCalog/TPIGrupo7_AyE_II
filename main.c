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


float OperacionTiempo (int id,struct tarea ** initar);
float OperacionCosto(int codop,struct materialesop ** inimat);
float buscarpreciomat(int codmat);

int buscartecnico();
int buscarcliente(int codcliente);
int Menu (int opc);
int vacia(struct pendientes *tp);

struct materiales* InsertarMaterial (struct materiales *mat, struct materiales *raiz);
struct materiales* InsertarNuevoMaterial (struct materiales *r, struct materiales *nodo);

void InsertarCliente(struct cliente ** nv,struct cliente ** inicli);
void AltaDeMateriales (struct materiales *r);
void AltaDeOpciones (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea **initar);
void AltaDeTrabajos (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea ** initar);
void AltaDeClientes(struct cliente **inicli);
void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales *raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **initech, struct trabajos **e, struct trabajos **s, struct opcion **iniopc, struct pendientes **tope);
void InsertarOpcion (struct opcion ** nvop,struct opcion ** iniop);
void InsertarTrabajo(struct trabajos ** nvt);
void ListadoDeOpciones ();
void ListadoDePendientes(struct pendientes **nodo, struct pendientes **tope);
void desapilar(struct pendientes **nodo, struct pendientes **tp);
void apilar(struct pendientes **nodo, struct pendientes **tp);
void OpcionesMasVendidas ();


int main(int argc, char *argv[]){
	struct cliente *inicli;
	struct materiales *raiz;
	struct materialesop *inimat;
	struct tarea *initar;
	struct tecnico *initech;
	struct trabajos *e,*s;
	struct opcion *iniopc;
        struct pendientes *nodo, *tope, *nodoaux, *topeaux;	
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
				AltaDeOpciones(&inicli,&inimat,&iniopc,&initar);
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 3:
				AltaDeTrabajos(&inicli,&inimat,&iniopc,&initar);
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 4:
				ListadoDePendientes(&nodo, &tope);
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 5:
				OpcionesMasVendidas();
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 6:
				AltaDeMateriales(raiz);
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
		}
	}
	return (0);
}

float OperacionTiempo (int id,struct tarea ** initar){
	float tiempo=0;
	struct tarea *aux=NULL;
	aux=initar; //Se puede asignar de esta forma ya que es una variable global
	while(aux!=NULL){
		if(aux->id_op==id){
			tiempo = tiempo + aux->tiempo;
		}
		aux=aux->sgte;
	}
	return tiempo;
}/*struct tarea{ //Lista Doblemente Enlazada.
     int id_op, id_tarea, orden;
     float tiempo;
     char descripcion[30];
     struct tarea *sgte, *ant;
};*/

float OperacionCosto(int codop,struct materialesop ** inimat){
	float costomat=0;
	struct materialesop *aux=NULL;
	aux=inimat;
	while(aux!=NULL){
		if(aux->id_opcion=codop){
			costomat = costomat + (aux->cantidad*buscarpreciomat(aux->idmat));//Ira al arbol a buscar el material
		}
		aux=aux->sgte;
	}
	return costomat;
}

void InsertarOpcion (struct opcion ** nvop,struct opcion ** iniop){
	struct opcion *aux=NULL;
	aux=iniop;
	while(aux->sgte!=NULL){
		aux=aux->sgte;
	}
	aux->sgte=nvop;
}

float buscarpreciomat(int codmat){
}

void InsertarTrabajo(struct trabajos ** nvt){
}

void AltaDeClientes(struct cliente **inicli){
	struct cliente *nvcliente=NULL;
	nvcliente = (struct cliente *) malloc(sizeof(struct cliente));
	if(nvcliente!=NULL){
		printf("\nBienvenido a SistemaSeguro S.A!");
		printf("\nA continuacion le pediremos una serie de datos para poder registrarlo como cliente");
		printf("\nDigite su DNI: ");
		scanf("%ld",&nvcliente->DNI);
		printf("\nDigite su nombre completo: ");
		gets(nvcliente->Nombre);
		printf("\nDigite un ID con el que quiera identificarse en el sistema: ");
		scanf("%i",&nvcliente->id);
		nvcliente->sgte=NULL;
		InsertarCliente(&nvcliente,&inicli);
	}else{
		printf("\nError de asignacion de espacio de Memoria");
	}
	/*
	struct cliente{ //Lista Enlazada Simple.
     int id;
     long int DNI;
     char Nombre[30];
     struct cliente *sgte;
};*/
}
void InsertarCliente(struct cliente ** nv,struct cliente ** inicli){
	struct cliente * aux=NULL;
	aux = inicli;
	while(aux->sgte!=NULL){
		aux=aux->sgte;
	}
	aux->sgte=nv;
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

struct materiales* InsertarMaterial (struct materiales *mat, struct materiales *raiz){
	if( raiz == NULL) {
		mat->derch = NULL;
		mat->izq = NULL;
		raiz = mat;
	}else{
		if( mat->id < raiz->id ){
			raiz->izq = InsertarMaterial(mat, raiz);
		}else{
			raiz->derch = InsertarMaterial(mat, raiz);
		}
	}
	return(raiz);
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

void AltaDeOpciones (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea **initar){
	struct opcion *nueva_op;
	nueva_op = (struct opcion *) malloc (sizeof (struct opcion) );
	if(nueva_op == NULL){
		printf( ":( No hay espacio en memoria \n" );
		
	}else{
		printf( "---Digite el ID de la opcion: \n" );
		scanf( "%i", &nueva_op->id );
		
		printf( "---Digite el nombre de la nueva opcion: \n" );
		gets( nueva_op->Nombre );
		
		nueva_op->tiempo = OperacionTiempo ( nueva_op->id,&initar);
		nueva_op->costo = nueva_op->tiempo*100 + OperacionCosto(nueva_op->id,&inimat);
		//100 es el costo de cada hora de trabajo
		nueva_op->sgte = NULL;
		InsertarOpcion (nueva_op,&iniop);
	}
}

void AltaDeTrabajos (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea ** initar){
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
	nuevo_trab->CostoTotal = (OperacionTiempo(nuevo_trab->id_opcion,&inimat)*100) + ((OperacionTiempo(nuevo_trab->id_opcion,&inimat)*100) *nuevo_trab->cuatromtrs*0.20);
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
				AltaDeClientes(&inicli);
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

void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales *raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **initech, struct trabajos **ent, struct trabajos **sal, struct opcion **iniopc, struct pendientes **tope){
	struct cliente *cli=NULL, *antc=NULL;
	struct materiales *mat=NULL;
	struct materialesop *mato=NULL, *antm=NULL;
	struct tarea *tar=NULL, *antt=NULL;
	struct tecnico *tech=NULL;
	struct trabajos *trab=NULL;
	struct opcion *opc=NULL;
	struct pendientes *pend=NULL;
	
	//carga lista simple clientes
	if((p=fopen("clientes.bin","r+b"))==NULL){
		printf("||||||| Error de apertura de archivo Clientes durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			cli=(struct cliente *) malloc(sizeof (struct cliente) );
			if(cli==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%ld" ,cli->DNI);
				fscanf(p, "%d" ,cli->id);
				fscanf(p, "%s" ,cli->Nombre);					
				if(inicli==NULL){
					(*inicli)=cli;
					(*inicli)->sgte=NULL;
				}else{
					antc->sgte=cli;
					antc=cli;
				}
			}
		}
		fclose(p);
	}
	
	//carga arbol materiales
	p=NULL;
	if((p=fopen("materiales.bin","r+b"))==NULL){
		printf("||||||| Error de apertura de archivo Materiales durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			mat=(struct materiales *) malloc(sizeof (struct materiales) );
			if(mat==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%f", mat->cantidad);
				fscanf(p, "%f", mat->costo_uni);
				fscanf(p, "%s", mat->descripcion);
				fscanf(p, "%d", mat->id);
				fscanf(p, "%s", mat->unimed);
				raiz = InsertarMaterial(mat, raiz);
			}
		}
		fclose(p);
	}
	
	//carga lista simple materiales
	p=NULL;
	antm=NULL;
	if((p=fopen("materialesop.bin","r+b"))==NULL){
		printf("||||||| Error de apertura de archivo Materiales por Opcion durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			mato=(struct materialesop *) malloc(sizeof(struct materialesop));
			if(mato==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%d", mato->cantidad);
				fscanf(p, "%d", mato->idmat);
				fscanf(p, "%d", mato->id_opcion);
				if(inicli==NULL){
					(*inimat)=mato;
					(*inimat)->sgte=NULL;
				}else{
					antm->sgte=mato;
					antm=mato;
				}
			}
		}
		fclose(p);
	}
	
	//carga lista doble tareas
	p=NULL;
	if((p=fopen("tareas.bin","r+b"))==NULL){
		printf("||||||| Error de apertura de archivo Tareas durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			tar=(struct tarea *) malloc(sizeof (struct tarea) );
			if(tar==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%s", tar->descripcion);
				fscanf(p, "%d", tar->id_op);
				fscanf(p, "%d", tar->id_tarea);
				fscanf(p, "%d", tar->orden);
				fscanf(p, "%f", tar->tiempo);
				if(initar==NULL){
					(*initar)=tar;
					(*initar)->sgte=NULL;
					(*initar)->ant=NULL;
				}else{
					
				}
			}
		}
		fclose(p);
	}
}

void ListadoDeOpciones (){
}

void ListadoDePendientes (){
}

void ListadoDePendientes (struct pendientes **nodo, struct pendientes **tope){
	int pila;

	pila = vacia(*tope);
  	if (pila == 1) {
        printf("La pila está vacia\n");
   	} else {
      		desapilar(nodo, tope);
        	if ((*nodo)->completado == 1) {
           		printf("La tarea con la descripción %s, ID de trabajo %d, orden %d y con un tiempo de realizacion de %f ya está finalizada.\n",(*nodo)->descripcion, (*nodo)->id_trabajo, (*nodo)->orden, (*nodo)->tiempo);
           		free(*nodo);
      		} else {
       			printf("La tarea con la descripción %s, ID de trabajo %d, orden %d y con un tiempo de realizacion de %f sigue pendiente.\n", (*nodo)->descripcion, (*nodo)->id_trabajo, (*nodo)->orden, (*nodo)->tiempo);
           		apilar(nodo, tope);
       		}
   	}
}

int vacia (struct pendientes *tp){
	int v;
	
	if (tp == NULL){
		v = 1;
	}else {
		v = 0;
	}
	return (v);
}

void desapilar (struct pendientes **nodo, struct pendientes **tp){
	(*nodo) = (*tp);
	(*tp) = (*tp)->sgte;
	(*nodo)->sgte = NULL;
}

void apilar (struct pendientes **nodo, struct pendientes **tp){
	(*nodo)->sgte = (*tp);
	(*tp) = (*nodo);
	(*nodo) = NULL;
}

void OpcionesMasVendidas (){
}
