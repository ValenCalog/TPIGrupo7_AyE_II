#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct materiales{ //Arbol de Busqueda Binaria.
     int id;
     char descripcion[30], unimed[10];
     float costo_uni, cantidad;
     struct materiales *izq, *derch;
};

struct trabajos{ //Cola.
     int id_trabajo, id_opcion, cuatromtrs;
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
     float cHoraMObra; //cortesia de vale.
     struct opcion *sgte;
};

struct tecnico{ //Cola.
     int id;
     long int DNI;
     char Nombre[30];
     struct tecnico *sgte;
};

struct pendientes{ //Pila.
	int id_tarea, id_trabajo, orden, completado;
	float tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};

float BuscarPrecioMaterial (int codmat);
float OperacionTiempo (int id,struct tarea ** initar);
float OperacionCosto (int codop,struct materialesop ** inimat);

int BuscarCliente (int codcliente);
int BuscarMayorIdTecnico(struct tecnico *e, struct tecnico *s);
int BuscarTecnico ();
int Menu (int opc);
int Vacia (struct pendientes *tp);

struct materiales* InsertarMaterial (struct materiales *mat, struct materiales *raiz);
struct materiales* InsertarNuevoMaterial (struct materiales *r, struct materiales *nodo);
struct tarea* BuscarAnterior (int id_op, struct tarea *initar);

void AltaDeClientes (struct cliente **inicli);
void AltaDeMateriales (struct materiales **r);
void AltaDeOpciones (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea **initar);
void AltaDeTrabajos (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea ** initar, struct trabajos **sTrab, struct trabajos **eTrab);
void AltaDeTecnicos(struct tecnico **e, struct tecnico **s);
void Apilar (struct pendientes **nodo, struct pendientes **tpaux);
void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **et, struct tecnico **st, struct trabajos **e, struct trabajos **s, struct opcion **iniopc, struct pendientes **tope);
void Desapilar (struct pendientes **nodo, struct pendientes **tp);
void DesencolarTecnico(struct tecnico **ds, struct tecnico **e, struct tecnico **s);
void EncolarTecnico(struct tecnico **nv, struct tecnico **e, struct tecnico **s);
void EncolarTrabajos(struct trabajos **nv, struct trabajos **e, struct trabajos **s);
void InsertarCliente (struct cliente ** nv,struct cliente ** inicli);
void InsertarOpcion (struct opcion ** nvop,struct opcion ** iniop);
void InsertarTrabajo (struct trabajos ** nvt);
void ListadoDeOpciones ();
void ListadoDePendientes (struct pendientes **nodo, struct pendientes **tope);
void OpcionesMasVendidas ();
int buscarMayorIdCliente(struct cliente *ini);
int buscarMayorIdOpc(struct opcion *ini);
int buscarMayorIdTrab(struct trabajos *s);
int buscarMayorIdTarea(struct tarea *ini);
int generarIdMaterial(struct materiales *r);
int verificarId(struct materiales *r, int idRandom);

int main(int argc, char *argv[]){
	struct cliente *inicli;
	struct materiales *raiz;
	struct materialesop *inimat;
	struct tarea *initar;
	struct tecnico *et, *st;
	struct trabajos *e, *s;
	struct opcion *iniopc;
    struct pendientes *nodo, *tope;	
	int opc=-1;
	FILE *p;
	srand(time(NULL));
	CargaSupremaDeEstructuras(p, &inicli, &raiz, &inimat, &initar, &et, &st, &e, &s, &iniopc, &tope);
	
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
				AltaDeTrabajos(&inicli,&inimat,&iniopc,&initar, &e, &s);
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
				AltaDeMateriales(&raiz);
				opc=-1; //NO BORRAR hasta que carguemos la funcion.
				break;
			case 7:
				AltaDeTecnicos(&et, &st);
				opc=-1;
				break;
		}
	}
	return (0);
}

//Floats
float OperacionTiempo (int id, struct tarea **initar){
	float tiempo=0;
	struct tarea *aux=NULL;
	aux = (*initar);
	while(aux!=NULL){
		if(aux->id_op==id){
			tiempo = tiempo + aux->tiempo;
		}
		aux=aux->sgte;
	}
	return (tiempo);
}

float OperacionCosto (int codop,struct materialesop **inimat){
	float costomat=0;
	struct materialesop *aux=NULL;
	aux = (*inimat);
	while(aux!=NULL){
		if(aux->id_opcion=codop){
			//Ira al arbol a buscar el material
			costomat = costomat + (aux->cantidad*BuscarPrecioMaterial(aux->idmat));
		}
		aux=aux->sgte;
	}
	return (costomat);
}

float BuscarPrecioMaterial (int codmat){
}

//Ints
int BuscarCliente(int codcliente){
}

int BuscarTecnico(){
}

int BuscarMayorIdTecnico(struct tecnico *e, struct tecnico *s){
	int maxId = s->id;
	while(s!=NULL){
		if(s->id > maxId){
			maxId = s->id;
		}
		s = s->sgte;
	}
	return maxId;
}

int Menu (int o){
	int contgency=0;
	while( (o!=0) && (o!=1) && (o!=2) && (o!=3) && (o!=4) && (o!=5) && (o!=6) ){
		if(contgency>=1){
			printf( "El valor que ingreso no es valido, vuelva a ingresar una opcion. \n" );
			fflush(stdin);
			scanf( "%d", &o );
		}else{
			printf( "-------------------Bienvenido al menu :D-------------------\n---Ingrese 1 para listar opciones.\n---Ingrese 2 para dar de alta un opcion.\n---Ingrese 3 para dar de alta un trabajo.\n---Ingrese 4 para listar trabajos y tareas pendientes.\n---Ingrese 5 para listar los trabajos finalizados.\n---Ingrese 6 para listar las opciones mas vendidas.\n---Ingrese 7 para dar de alta un tecnico." );
			fflush(stdin);
			scanf( "%d", &o );
			contgency++;
		}
	}
	return (o);
}

int Vacia (struct pendientes *tp){
	int v;
	
	if (tp == NULL){
		v = 1;
	}else {
		v = 0;
	}
	return (v);
}

//Structs
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

struct tarea* BuscarAnterior (int dato, struct tarea *rc){
	struct tarea *ant=NULL;
	while( rc != NULL){
		if( rc->id_op > dato){
			rc = NULL;
		}else{
			ant = rc;
			rc = rc->sgte;
		}
	}
	return (ant);
}

//Voids
void AltaDeClientes(struct cliente **inicli){
	struct cliente *nvcliente=NULL;
	nvcliente = (struct cliente *) malloc(sizeof(struct cliente));
	if( nvcliente != NULL ){
		printf( "\nBienvenido a SistemaSeguro S.A!" );
		printf( "\nA continuacion le pediremos una serie de datos para poder registrarlo como cliente." );
		printf( "\nDigite su DNI: " );
		fflush(stdin);
		scanf( "%ld", &nvcliente->DNI );
		printf( "\nDigite su nombre completo: " );
		fflush(stdin);
		gets( nvcliente->Nombre );
		if(*inicli == NULL){
			nvcliente->id = 1;
		}else{
			nvcliente->id = buscarMayorIdCliente(*inicli) +1;
		}
		nvcliente->sgte=NULL;
		//inicli no hace falta que pases por referencia porque ya llego a la funcion de esa manera.
		InsertarCliente ( &nvcliente, inicli );
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

int buscarMayorIdCliente(struct cliente *ini){
	int maxId = ini->id;
	while(ini!=NULL){
		if(ini->id > maxId){
			maxId = ini->id;
		}
		ini = ini->sgte;
	}
	return maxId;
}

void AltaDeMateriales (struct materiales **raiz){
    struct materiales *nuevo_mat;

    nuevo_mat = (struct materiales *) malloc (sizeof (struct materiales) );
    if( nuevo_mat == NULL ){
       printf( ":( No hay espacio en la memoria \n" );
    }else{
    		nuevo_mat->id = generarIdMaterial(*raiz);
		printf( "---Ingrese la descripcion del material: \n" );
	    	fflush(stdin);
		gets( nuevo_mat->descripcion );
		
		printf( "---Ingrese cual sera la unidad de medida: \n" );
	    	fflush(stdin);
		gets( nuevo_mat->unimed );
		
		printf( "---Ingrese el precio unitario del nuevo material: \n" );
	    	fflush(stdin);
		scanf( "%f", &nuevo_mat->costo_uni );
		*raiz = InsertarNuevoMaterial (*raiz, nuevo_mat);
		//Insertamos el nodo, con el nuevo material, al arbol.
	}
}

int generarIdMaterial(struct materiales *r){
	int min = 10, max = 40000, idRandomizado, idEncontrado = 0;
	do{
		idRandomizado = rand() % (max - min + 1) + min;
    	idEncontrado = verificarId(r, idRandomizado);		
	}while(idEncontrado == 1);
   return idRandomizado;
}

int verificarId(struct materiales *r, int idRandom){
	int band = 0;
	if(r!=NULL){
		if(r->id == idRandom){
			band = 1;
		}else{
			if(idRandom > r->id){
				band = verificarId(r->derch, idRandom);
			}else{
				band = verificarId(r->izq, idRandom);
			}
		}
	}
	return band;
}

void AltaDeOpciones (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea **initar){
	struct opcion *nueva_op;
	nueva_op = (struct opcion *) malloc (sizeof (struct opcion) );
	if(nueva_op == NULL){
		printf( ":( No hay espacio en memoria \n" );
		
	}else{
		if(*iniop != NULL){
			nueva_op->id = 1;
		}else{
			nueva_op->id = buscarMayorIdOpc(*iniop) + 1;
		}
		
		printf( "---Digite el nombre de la nueva opcion: \n" );
		fflush(stdin);
		gets( nueva_op->Nombre );
		
		printf("---Digite el costo por hora de la mano de obra: \n");
		scanf("%2.f", &nueva_op->cHoraMObra);
		//lo puse como comentario apra que no de problemas en la compilacion porque ya no hay costo y tiempo en opciones.
		//nueva_op->tiempo = OperacionTiempo ( nueva_op->id, initar );
		//nueva_op->costo = nueva_op->tiempo*100 + OperacionCosto ( nueva_op->id, inimat );
		//100 es el costo de cada hora de trabajo
		nueva_op->sgte = NULL;
		//iniop no hace falta que pases por referencia porque ya llego a la funcion de esa manera.
		//Por el prototipo, nueva_op debe pasar por referencia, faltaba el & y se lo puse pero no se si erra un error o a propósito.
		InsertarOpcion (&nueva_op, iniop);
	}
}

int buscarMayorIdOpc(struct opcion *ini){
	int idMax = ini->id;
	ini = ini->sgte;
	while(ini!=NULL){
		if(ini->id > idMax){
			idMax = ini->id;
		}
		ini = ini->sgte;
	}
	return idMax;
}

void AltaDeTrabajos (struct cliente ** inicli,struct materialesop ** inimat,struct opcion ** iniop,struct tarea ** initar, struct trabajos **sTrab, struct trabajos **eTrab){
	int op;
	struct trabajos *nuevo_trab;
	nuevo_trab = (struct trabajos *) malloc(sizeof (struct trabajos));
	nuevo_trab->sgte = NULL;
	ListadoDeOpciones();
	
	printf( "\n---Ingrese el ID de la opcion a contratar: " );
	fflush(stdin);
	scanf( "%i", &nuevo_trab->id_opcion );
	
	/*printf( "\n---Ingrese el ID de trabajo: " );
	fflush(stdin);
	scanf( "%i", &nuevo_trab->id_trabajo ); //Despues se puede implementar el buscaridtrabajo() + 1;*/
	if(*sTrab!=NULL){
		nuevo_trab->id_trabajo = 1;
	}else{
		nuevo_trab->id_trabajo = buscarMayorIdTrab(*sTrab) + 1;
	}
	
	printf( "\n---Ingrese la direccion de la instalacion: " );
	fflush(stdin);
	gets( nuevo_trab->direccion );
	printf( "\nRequiere trabajo en altura?: " );
	fflush(stdin);
	scanf( "%i", &nuevo_trab->cuatromtrs ); //0 no requiere, 1 si requiere trabajo en altura
	
	nuevo_trab->id_tecnico = BuscarTecnico();
	
	//lo puse como comentario apra que no de problemas en la compilacion porque ya no hay costo y tiempo en opciones.
	//nuevo_trab->CostoTotal = (OperacionTiempo(nuevo_trab->id_opcion, inimat)*100) + ((OperacionTiempo(nuevo_trab->id_opcion, inimat)*100) *nuevo_trab->cuatromtrs*0.20);
	
	//Por ahora no se esta teniendo en cuenta el costo de los materiales en CostoTotal
	//Si cuatromtrs es 0, no requiere trabajo en altura, por lo cual el resultado del producto sera 0 y no se suma el 20%
	
	printf("\nIngrese su ID de cliente: ");
	fflush(stdin);
	scanf("%i",&nuevo_trab->id_cliente);
	if(BuscarCliente(nuevo_trab->id_cliente)==0){ 
		//BuscarCliente recorre la lista de clientes en busca del id ingresado, si no lo encuentra devuelve 0
		printf("\nNo se ha encontrado un cliente asociado a la ID ingresada");
		printf("\nDesea darse de alta como cliente?");
		printf("\n1)Si");
		printf("\n2)No");
		printf("\n--> ");
		fflush(stdin);
		scanf("%i",&op);
		while(op!=0){
			switch(op){
			case 1:
				//inicli no hace falta que pases por referencia porque ya llego a la funcion de esa manera.
				AltaDeClientes(inicli);
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

int buscarMayorIdTrab(struct trabajos *s){
	int maxId = s->id_trabajo;
	while(s!=NULL){
		if(s->id_trabajo > maxId){
			maxId = s->id_trabajo;
		}
		s = s->sgte;
	}
	return maxId;
}

void AltaDeTecnicos(struct tecnico **e, struct tecnico **s){
	struct tecnico *nv;
	nv = (struct tecnico*) malloc(sizeof(struct tecnico));
	if(nv!=NULL){
		if(*e == NULL){
			nv->id = 1;
		}else{
			nv->id = BuscarMayorIdTecnico(*e, *s) +1;	
		}
		printf("\nDNI: ");
		scanf("%d", &nv->DNI);
		printf("\nNombre: ");
		scanf("%29s", nv->Nombre);
		nv->sgte = NULL;
		EncolarTecnico(&nv, e, s);
	}
}

void Apilar (struct pendientes **nodo, struct pendientes **tpaux){
	(*nodo)->sgte = (*tpaux);
	(*tpaux) = (*nodo);
	(*nodo) = NULL;
}

void EncolarTecnico(struct tecnico **nv, struct tecnico **e, struct tecnico **s){
	if((*e) == NULL){
		*s = *nv;
	}else{
		(*e)->sgte = *nv;
	}
	*e=*nv;
	*nv = NULL;
}

void EncolarTrabajos(struct trabajos **nv, struct trabajos **e, struct trabajos **s){
	if((*e) == NULL){
		*s = *nv;
	}else{
		(*e)->sgte = *nv;
	}
	*e=*nv;
	*nv = NULL;
}

void DesencolarTecnico(struct tecnico **ds, struct tecnico **e, struct tecnico **s){
	(*ds) = (*s);
	(*s)=(*s)->sgte;
	if (*s == NULL){
		(*e) = NULL;	
	} 
}

void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **et, struct tecnico **st, struct trabajos **ent, struct trabajos **sal, struct opcion **iniopc, struct pendientes **tope){
	struct cliente *cli=NULL, *antc=NULL;
	struct materiales *mat=NULL, *auxm=NULL;
	struct materialesop *mato=NULL, *antm=NULL;
	struct tarea *tar=NULL, *antt=NULL, *auxt=NULL;
	struct tecnico *tech=NULL;
	struct trabajos *trab=NULL;
	struct opcion *opc=NULL, *anto=NULL;
	struct pendientes *pend=NULL;
	//carga lista simple clientes
	if((p=fopen("clientes.txt","r"))==NULL){
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
	if((p=fopen("materiales.txt","r"))==NULL){
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
				auxm = (*raiz);
				auxm = InsertarMaterial(mat, auxm);
				(*raiz) = auxm;
			}
			free (mat);
		}
		fclose(p);
	}
	//carga lista simple materiales
	p=NULL;
	antm=NULL;
	if((p=fopen("materialesop.txt","r"))==NULL){
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
			free (mato);
		}
		fclose(p);
	}
	//carga lista doble tareas
	p=NULL;
	if((p=fopen("tareas.txt", "r"))==NULL){
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
				antt = BuscarAnterior (tar->id_op, (*initar));
				if( initar == NULL ){
					(*initar) = tar;
					(*initar)->sgte = NULL;
					(*initar)->ant = NULL;
				}else{
					if( antt == NULL ){
						tar->sgte = (*initar);
						(*initar)->ant = tar;
						(*initar) = tar;
					}else{
						auxt = antt->sgte;
						tar->ant = antt;
						antt->sgte = tar;
						if( auxt != NULL ){
							tar->sgte = auxt;
							auxt->ant = tar;
						}
					}
				}
				free (tar);
			}
		}
		fclose(p);
	}
	//carga cola tecnicos
	p=NULL;
	if((p=fopen("tecnicos.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Tecnicos durante la carga |||||||\n");
	}else{
		while(feof(p)){
			tech=(struct tecnico *) malloc(sizeof (struct tecnico) );
			if(tech==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%ld", tech->DNI);
				fscanf(p, "%d", tech->id);
				fscanf(p, "%s", tech->Nombre);
				EncolarTecnico(&tech, &(*et), &(*st));
				free(tech);
			}
		}
		fclose(p);
	}
	//carga cola trabajos
	p=NULL;
	if((p=fopen("trabajos.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Trabajos durante la carga |||||||\n");
	}else{
		while(feof(p)){
			trab=(struct trabajos *) malloc(sizeof (struct trabajos) );
			if(trab==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%d", trab->cuatromtrs);
				fscanf(p, "%s", trab->direccion);
				fscanf(p, "%d", trab->fc_fin);
				fscanf(p, "%d", trab->id_cliente);
				fscanf(p, "%d", trab->id_opcion);
				fscanf(p, "%d", trab->id_tecnico);
				fscanf(p, "%d", trab->id_trabajo);
				EncolarTrabajos(&trab, &(*ent), &(*sal));
				free(trab);
			}
		}
		fclose(p);
	}
	//carga lista simple opciones
	p=NULL;
	if((p=fopen("opciones.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Opciones durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			opc=(struct opcion *) malloc(sizeof(struct opcion));
			if(opc==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%d", opc->id);
				fscanf(p, "%f", opc->cHoraMObra);
				fscanf(p, "%s", opc->Nombre);
				if(iniopc==NULL){
					(*iniopc)=opc;
					(*iniopc)->sgte=NULL;
				}else{
					anto->sgte=opc;
					anto=opc;
				}
			}
			free (opc);
		}
		fclose(p);
	}
	//carga de pila pendientes
	p=NULL;
	if((p=fopen("pendientes.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Pendientes durante la carga |||||||\n");
	}else{
		while(!feof(p)){
			pend=(struct pendientes *) malloc(sizeof(struct pendientes));
			if(pend==NULL){
				printf("-------No hay espacio de memoria-------\n");
			}else{
				fscanf(p, "%d", pend->completado);
				fscanf(p, "%s", pend->descripcion);
				fscanf(p, "%d", pend->id_tarea);
				fscanf(p, "%d", pend->id_trabajo);
				fscanf(p, "%d", pend->orden);
				fscanf(p, "%f", pend->tiempo);
				Apilar (&pend, tope);
			}
		}
		free (pend);
	}
	fclose(p);
}

void Desapilar (struct pendientes **nodo, struct pendientes **tp){
	(*nodo) = (*tp);
	(*tp) = (*tp)->sgte;
	(*nodo)->sgte = NULL;
}

void InsertarCliente(struct cliente ** nv,struct cliente ** inicli){
	struct cliente *aux=NULL;
	aux = (*inicli);
	while( aux->sgte != NULL ){
		aux = aux->sgte;
	}
	aux->sgte = (*nv);
}

void InsertarOpcion (struct opcion **nvop,struct opcion **iniop){
	struct opcion *aux=NULL;
	aux = (*iniop);
	while(aux->sgte!=NULL){
		aux=aux->sgte;
	}
	aux->sgte = (*nvop);
}

void InsertarTrabajo(struct trabajos ** nvt){
}

void ListadoDeOpciones (){
}

void ListadoDePendientes (struct pendientes **nodo, struct pendientes **tope){
	int pila;
	struct pendientes *topeaux=NULL;
	/*struct pendientes{ //Pila.
	int id_tarea, id_trabajo, orden, completado;
	float tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};*/

	pila = Vacia(*tope);
  	if (pila == 1) {
        printf("La pila está Vacia\n");
   	} else {
  		Desapilar(nodo, tope);
    	if ((*nodo)->completado == 1) {
    		printf("La tarea %d del trabajo con ID %d, con orden %d y descripcion %s ya está terminada.\n", (*nodo)->id_tarea, (*nodo)->id_trabajo, (*nodo)->orden, (*nodo)->descripcion);
			free(*nodo);
  		} else {
   			printf("La tarea %d del trabajo con ID %d, con orden %d y descripcion %s aun no está terminada.\n", (*nodo)->id_tarea, (*nodo)->id_trabajo, (*nodo)->orden, (*nodo)->descripcion);	
			Apilar(nodo, &topeaux);
   		}
   	}
}

void OpcionesMasVendidas (){
}
