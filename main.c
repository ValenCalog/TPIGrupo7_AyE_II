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
    int id_trabajo, id_opcion, opcion, cuatromtrs;
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
     float cHoraMObra; //cortesia de vale. (vale me arruinaste la vida con ese nombre)
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

float OperacionTiempo (int id,struct tarea ** initar);
float OperacionCosto (struct materiales *raiz, int codop,struct materialesop ** inimat);


int BuscarCliente (int codcliente, struct cliente *ini);
int BuscarMayorIdCliente(struct cliente *ini);
int BuscarMayorIdTarea(struct tarea *ini);
int BuscarMayorIdTecnico(struct tecnico *e, struct tecnico *s);
int BuscarMayorIdTrab(struct trabajos *s);
int BuscarMayorIdOpc(struct opcion *ini);
int BuscarTecnico (struct tecnico **nodo, struct tecnico **et, struct tecnico **st);
int ListadoDeOpcionesParaAltaDeTrabajo (struct opcion **iniop, struct materiales **raiz, struct materialesop **inimat, int cuatrometros); //este muestra las opciones y retorna un valor para el alta de trabajo

int GenerarIdMaterial(struct materiales *r);
int InsertarOpcion (struct opcion * nvop,struct opcion * iniop);
int InsertarCliente (struct cliente ** nv,struct cliente ** inicli);

int Menu (int opc);

int Vacia (struct pendientes *tp);
int VerificarId(struct materiales *r, int idRandom);


struct materiales* DescargarArbol (struct materiales *raiz, FILE *p);
struct materiales* InsertarMaterial (struct materiales *mat, struct materiales *raiz);
struct materiales* InsertarNuevoMaterial (struct materiales *r, struct materiales *nodo);
struct tarea* BuscarAnterior (int id_op, struct tarea *initar);


void AltaDeClientes (struct cliente **inicli);
void AltaDeMateriales (struct materiales **r);
void AltaDeOpciones (struct opcion ** iniop);
void AltaDeTrabajos (struct cliente ** inicli,struct opcion ** iniop, struct tecnico **et, struct tecnico **st, struct trabajos **e, struct trabajos **s, struct materialesop **inimat, struct materiales **r);
void AltaDeTecnicos(struct tecnico **e, struct tecnico **s);
void Apilar (struct pendientes **nodo, struct pendientes **tpaux);

void BuscarPrecioMaterial (float *unitario, struct materiales *r, int codmat);

void CargaClientes (FILE *p, struct cliente *cli, struct cliente *antc, struct cliente **inicli);
void CargaMateriales (FILE *p, struct materiales *mat, struct materiales *auxm, struct materiales **raiz);
void CargaMaterialesOpcion (FILE *p, struct materialesop *mato, struct materialesop *antm, struct materialesop **inimat);
void CargaTareas (FILE *p, struct tarea *tar, struct tarea *antt, struct tarea *auxt, struct tarea **initar);
void CargaTecnicos (FILE *p, struct tecnico *tech, struct tecnico **et, struct tecnico **st);
void CargaTrabajos (FILE  *p, struct trabajos *trab, struct trabajos **ent, struct trabajos **sal);
void CargaOpciones (FILE *p, struct opcion *opc, struct opcion *anto, struct opcion **iniopc);
void CargaPendientes (FILE *p, struct pendientes *pend, struct pendientes **tope);
void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **et, struct tecnico **st, struct trabajos **e, struct trabajos **s, struct opcion **iniopc, struct pendientes **tope);

void Desapilar (struct pendientes **nodo, struct pendientes **tp);
void DescargaClientes ( FILE *p, struct cliente *cli, struct cliente *inicli);
void DescargaMaterialesOpcion(FILE *p, struct materialesop *mato, struct materialesop *inimat);
void DescargaTareas (FILE *p, struct tarea *tar, struct tarea *auxt, struct tarea *initar);
void DescargaTecnicos (FILE *p, struct tecnico *tech, struct tecnico *et, struct tecnico *st);
void DescargaTrabajos (FILE *p, struct trabajos *trab, struct trabajos *ent, struct trabajos *sal);
void DescargaOpciones (FILE *p, struct opcion *opc, struct opcion *iniopc);
void DescargaPendientes (FILE *P, struct pendientes *pen, struct pendientes *tope, struct pendientes *tpaux);
void DescargaSupremaDeEstructuras (FILE *p, struct cliente *inicli, struct materiales *raiz, struct materialesop *inimat, struct tarea *initar, struct tecnico *et, struct tecnico *st, struct trabajos *e, struct trabajos *s, struct opcion *iniopc, struct pendientes *tope);
void DesencolarTecnico(struct tecnico **ds, struct tecnico **e, struct tecnico **s);
void DesencolarTrabajos(struct trabajos **ds, struct trabajos **e, struct trabajos **s);

void EncolarTecnico(struct tecnico **nv, struct tecnico **e, struct tecnico **s);
void EncolarTrabajos(struct trabajos **nv, struct trabajos **e, struct trabajos **s);

void ListadoDePendientes (struct pendientes **nodo, struct pendientes **tope);
void ListadoDeOpciones (struct opcion **iniop); //este solo muestra las opciones que hay

void OpcionesMasVendidas ();

int main(int argc, char *argv[]){
	struct cliente *inicli=NULL;
	struct materiales *raiz=NULL;
	struct materialesop *inimat=NULL;
	struct tarea *initar=NULL;
	struct tecnico *et=NULL, *st=NULL;
	struct trabajos *e=NULL, *s=NULL;
	struct opcion *iniopc=NULL;
    struct pendientes *nodo=NULL, *tope=NULL;	
	int opc=-1;
	FILE *p=NULL;
	
	srand(time(NULL));
	CargaSupremaDeEstructuras(p, &inicli, &raiz, &inimat, &initar, &et, &st, &e, &s, &iniopc, &tope);
	
	while(opc!=0){
		//system("CLS");
		opc = Menu(opc);
		switch(opc){
			case 1:
				ListadoDeOpciones(&iniopc);
				opc=-1;
				break;
			case 2:
				AltaDeOpciones(&iniopc);
				opc=-1;
				break;
			case 3:
				AltaDeTrabajos(&inicli, &iniopc, &et, &st, &e, &s, &inimat, &raiz); //et y st para técnico, e y s para trabajo
				opc=-1;
				break;
			case 4:
				ListadoDePendientes(&nodo, &tope);
				opc=-1;
				break;
			case 5:
				OpcionesMasVendidas();
				opc=-1; 
				break;
			case 6:
				AltaDeMateriales(&raiz);
				opc=-1;
				break;
			case 7:
				AltaDeTecnicos(&et, &st);
				opc=-1;
				break;
		}
	}
	DescargaSupremaDeEstructuras(p, inicli, raiz, inimat, initar, et, st, e, s, iniopc, tope);
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

float OperacionCosto (struct materiales *raiz, int codop, struct materialesop **inimat){
	float costomat=0, auxc=0;
	struct materialesop *aux=NULL;
	aux = (*inimat);
	while(aux!=NULL){
		if(aux->id_opcion=codop){
			BuscarPrecioMaterial(&auxc, raiz, aux->idmat);
			if(auxc==0){
				printf("--- El material no se encontro en en arbol ---\n");
			}else{
				costomat = costomat + (aux->cantidad * auxc);			
			}
		}
		aux=aux->sgte;
	}
	return (costomat);
}

//ints
int BuscarCliente (int id, struct cliente *ini){
	int encontroid=0;
	
	while (ini != NULL){
		if (ini->id == id){
			encontroid = 1;
		} else {
			ini = ini->sgte;
		}
	}
	return (encontroid);	
}

int BuscarMayorIdCliente (struct cliente *ini){
	int maxId = ini->id;
	while(ini!=NULL){
		if(ini->id > maxId){
			maxId = ini->id;
		}
		ini = ini->sgte;
	}
	return maxId;
}

int BuscarMayorIdOpc (struct opcion *ini){
	int idMax = ini->id;
	ini = ini->sgte;
	while(ini!=NULL){
		if(ini->id > idMax){
			idMax = ini->id;
		}
		ini = ini->sgte;
	}
	return (idMax);
}

int BuscarMayorIdTrab (struct trabajos *s){
	int maxId = s->id_trabajo;
	while(s!=NULL){
		if(s->id_trabajo > maxId){
			maxId = s->id_trabajo;
		}
		s = s->sgte;
	}
	return maxId;
}

int BuscarTecnico (struct tecnico **nodo, struct tecnico **e, struct tecnico **s){
	int cont = 0;
	while (cont == 0){
		DesencolarTecnico (nodo, e, s);
		cont = cont + 1;
		printf ("Su tecnico sera: %s.\n", (*nodo)->Nombre);
		return ((*nodo)->id);
		EncolarTecnico (nodo, e, s);
	}
}

int BuscarMayorIdTecnico (struct tecnico *e, struct tecnico *s){
	int maxId = s->id;
	while (s != NULL){
		if (s->id > maxId){
			maxId = s->id;
		}
		s = s->sgte;
	}
	return (maxId);
}

int GenerarIdMaterial (struct materiales *r){
	int min = 10, max = 40000, idRandomizado, idEncontrado = 0;
	do{
		idRandomizado = rand() % (max - min + 1) + min;
		idEncontrado = VerificarId (r, idRandomizado);		
	}while (idEncontrado == 1);
	
	return (idRandomizado);
}

int Menu (int o){
	int contgency = 0;
	while ((o!=0) && (o!=1) && (o!=2) && (o!=3) && (o!=4) && (o!=5) && (o!=6) && (o!=7)){
		if (contgency >= 1){
			printf ("El valor que ingreso no es valido, vuelva a ingresar una opcion. \n" );
			fflush (stdin);
			scanf ("%d", &o );
		}else{
			printf ("-------------------Bienvenido al menu :D-------------------\n---Ingrese 1 para listar opciones.\n---Ingrese 2 para dar de alta un opcion.\n---Ingrese 3 para dar de alta un trabajo.\n---Ingrese 4 para listar trabajos y tareas pendientes.\n---Ingrese 5 para ver las opciones mas vendidas.\n---Ingrese 6 para dar de alta un material.\n---Ingrese 7 para dar de alta un tecnico.\n" );
			fflush (stdin);
			scanf ("%d", &o);
			contgency++;
		}
	}
	return (o);
}

int Vacia (struct pendientes *tp){
	int v;
	
	if ( tp == NULL ){
		v = 1;
	}else {
		v = 0;
	}
	return ( v );
}

int VerificarId (struct materiales *r, int idRandom){
	int band = 0;
	if( r != NULL ){
		if( r->id == idRandom ){
			band = 1;
		}else{
			if( idRandom > r->id ){
				band = VerificarId( r->derch, idRandom );
			}else{
				band = VerificarId( r->izq, idRandom );
			}
		}
	}
	return ( band );
}

//Structs
struct materiales* DescargarArbol (struct materiales *raiz, FILE *p){
	if(raiz!=NULL){
		raiz->izq = DescargarArbol (raiz->izq, p);
		if((p=fopen("materiales.txt", "a+"))==NULL){
			printf("||||||| Error de apertura de archivo Materiales durante la carga |||||||\n");
		}else{
			fprintf(p, "%f", raiz->cantidad);
			fprintf(p, "%f", raiz->costo_uni);
			fprintf(p, "%s", raiz->descripcion);
			fprintf(p, "%d", raiz->id);
			fprintf(p, "%s", raiz->unimed);
			fclose(p);
		}
		raiz->derch = DescargarArbol(raiz->derch, p);
	}
	return (raiz);
}

struct materiales* InsertarMaterial (struct materiales *mat, struct materiales *raiz){
	if (raiz == NULL) {
		raiz = mat;
	}else{
		if (mat->id < raiz->id){
			raiz->izq = InsertarMaterial (mat, raiz->izq);
		}else{
			raiz->derch = InsertarMaterial (mat, raiz->derch);
		}
	}
	return (raiz);
}

struct materiales* InsertarNuevoMaterial (struct materiales *raiz, struct materiales *nodo){
	if (raiz == NULL){
		raiz = nodo;
	}else{
		if (raiz->id == nodo->id){
			printf ("\n --- Ya esta en la lista, se sumara el nuevo stock al deposito --- \n");
			raiz->cantidad = raiz->cantidad + nodo->cantidad;
		}else{
			if (nodo->id < raiz->id){
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
	while (rc!=NULL){
		if (rc->id_op > dato){
			rc=NULL;
		}else{
			ant=rc;
			rc=rc->sgte;
		}
	}
	return (ant);
}

//Voids
void AltaDeClientes (struct cliente **inicli){
	struct cliente *nvcliente = NULL;
	
	nvcliente = ( struct cliente * ) malloc( sizeof( struct cliente ) );
	
	if( nvcliente != NULL ){
		printf( "\n¡Bienvenido a SistemaSeguro S.A!" );
		printf( "\nA continuacion le pediremos una serie de datos para poder registrarlo como cliente." );
		printf( "\n---Digite su DNI: " );
		scanf( "%ld", &nvcliente->DNI );
		fflush(stdin);
		printf( "\n---Digite su nombre completo: " );
		fflush(stdin);
		gets( nvcliente->Nombre );
		
		if( *inicli == NULL ){
			nvcliente->id = 1;
		}else{
			nvcliente->id = BuscarMayorIdCliente( *inicli ) +1;
		}
		nvcliente->sgte = NULL;
		inicli = InsertarCliente( &nvcliente, inicli );
	}else{
		printf( "\n|||||| Error de asignacion de espacio de Memoria ||||||" );
	}
}

void AltaDeMateriales (struct materiales **raiz){
    struct materiales *nuevo_mat;

    nuevo_mat = (struct materiales *) malloc (sizeof (struct materiales) );
    
    if( nuevo_mat == NULL ){
       printf( ":( No hay espacio en la memoria \n" );
    }else{
    	nuevo_mat->id = GenerarIdMaterial( (*raiz) );
    	
		printf( "\n---Ingrese la descripcion del material: " );
		fflush(stdin);
		gets( nuevo_mat->descripcion );
		
		printf( "\n---Ingrese cual sera la unidad de medida: " );
		fflush(stdin);
		gets( nuevo_mat->unimed );
		
		printf( "\n---Ingrese el precio unitario del nuevo material: " );
		fflush(stdin);
		scanf( "%f", &nuevo_mat->costo_uni );
		
		printf( "\n---Ingrese la cantidad a almacenar del nuevo material: ");
		fflush(stdin);
		scanf( "%f", &nuevo_mat->cantidad );
		
		(*raiz) = InsertarNuevoMaterial ( (*raiz), nuevo_mat );
	}
}

void AltaDeOpciones (struct opcion ** iniop){
	struct opcion *nueva_op;
	nueva_op = (struct opcion *) malloc (sizeof (struct opcion) );
	
	if (nueva_op == NULL){
		printf( ":( No hay espacio en memoria \n" );
	}else{
		if ((*iniop) == NULL){
			nueva_op->id = 1;
		}else{
			nueva_op->id = BuscarMayorIdOpc((*iniop)) + 1;
		}
		fflush(stdin);
		
		printf( "---Digite el nombre de la nueva opcion: \n" );
		gets( nueva_op->Nombre );
		fflush(stdin);
		printf("---Digite el costo  de la mano de obra: \n");
		scanf("%f", &nueva_op->cHoraMObra);
		fflush(stdin);
		nueva_op->sgte = NULL;
		(*iniop) = InsertarOpcion (nueva_op, (*iniop));
	}
}

void AltaDeTrabajos (struct cliente **_inicli, struct opcion **_iniop, struct tecnico **eTec, struct tecnico **sTec, struct trabajos **eTra, struct trabajos **sTra, struct materialesop **_inimat, struct materiales **raiz){
    struct tecnico *nodoaux = NULL; 
    struct trabajos *nuevo_trab;
    int op;
    
    system("cls");
    nuevo_trab = (struct trabajos *) malloc(sizeof (struct trabajos));
    if (nuevo_trab == NULL){
    	printf ("No hay memoria.\n");
	}else{
		nuevo_trab->sgte = NULL;
		printf ("\n--- Ponga 1 si el trabajo debe realizarse a una altura mayor a 4 metros, de lo contrario 0: " );
    	scanf ("%i", &nuevo_trab->cuatromtrs); 
    	fflush (stdin);
    	
    	while ((nuevo_trab->cuatromtrs > 1) || (nuevo_trab->cuatromtrs < 0)){
    		printf ("\n |||| Opción inválida |||| \n--- Ponga 1 o 0: ");
    		scanf ("%i", &nuevo_trab->cuatromtrs);
    		fflush (stdin);
		}
		
    	op = ListadoDeOpcionesParaAltaDeTrabajo (_iniop, raiz, _inimat, nuevo_trab->cuatromtrs); 
    	nuevo_trab->opcion = op;
    	nuevo_trab->id_opcion = op; //el id de la opcion es el mismo que el nro de opcion
    	printf ("\n---Ingrese la direccion de la instalacion: " );
    	fflush(stdin);
    	gets (nuevo_trab->direccion);
		nuevo_trab->id_tecnico = BuscarTecnico(&nodoaux, eTec, sTec);
		fflush(stdin);
   		printf ("\nIngrese su ID de cliente: ");
   		fflush (stdin);
   		scanf ("%i",&nuevo_trab->id_cliente); 
		if (BuscarCliente (nuevo_trab->id_cliente, (*_inicli))==0){
            printf ("\n--- No se ha encontrado un cliente asociado a la ID ingresada---");
            printf ("\n ¿Desea darse de alta como cliente? ");
            printf ("\n 1)Si");
            printf ("\n 2)No");
            printf ("\n --> ");
            scanf ("%i",&op);
            fflush (stdin);
			while (op!=0){
                switch (op){
	                case 1:
	            	    AltaDeClientes(_inicli);
	            	    if (nuevo_trab->id_cliente != 0){
        					nuevo_trab->id_trabajo = BuscarMayorIdTrab((*sTra)) + 1;
           					 EncolarTrabajos(&nuevo_trab, eTra, sTra);
           					 printf("Trabajo agregado exitosamente.\n");
        				}
	                    op=0;
	                    break;
	                case 2:
	                    printf("\nDisculpe las molestias, vuelva pronto");
	                    nuevo_trab->id_cliente=0;
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
	}    
}

void AltaDeTecnicos (struct tecnico **e, struct tecnico **s){
	struct tecnico *nv;
	nv = (struct tecnico*) malloc (sizeof (struct tecnico));
	if (nv!=NULL){
		if (*e == NULL){
			nv->id = 1;
		}else{
			nv->id = BuscarMayorIdTecnico(*e, *s) +1;	
		}
		printf ("\nDNI: ");
		scanf ("%d", &nv->DNI);
		printf ("\nNombre: ");
		scanf ("%s", &nv->Nombre);
		nv->sgte = NULL;
		EncolarTecnico (&nv, e, s);
	}
}

void Apilar (struct pendientes **nodo, struct pendientes **tpaux){
	(*nodo)->sgte = (*tpaux);
	(*tpaux) = (*nodo);
	(*nodo) = NULL;
}

void BuscarPrecioMaterial (float *unit, struct materiales *raiz, int codmat){
	if(raiz==NULL){
		*unit = 0;
	}else{
		if(*unit == 0){
			if(codmat == raiz->id){
				*unit = raiz->costo_uni;
			}else{
				if(codmat < raiz->id){
					BuscarPrecioMaterial (&(*unit), raiz->izq, codmat);
				}else{
					BuscarPrecioMaterial (&(*unit), raiz->derch, codmat);
				}
			}
		}
	}
}

void CargaClientes (FILE *p, struct cliente *cli, struct cliente *antc, struct cliente **inicli){
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
					(*inicli) = cli;
					(*inicli)->sgte=NULL;
				}else{
					antc->sgte=cli;
					antc=cli;
				}
			}
		}
		fclose(p);
	}
}

void CargaMateriales (FILE *p, struct materiales *mat, struct materiales *auxm, struct materiales **raiz){
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
}

void CargaMaterialesOpcion (FILE *p, struct materialesop *mato, struct materialesop *antm, struct materialesop **inimat){
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
				if(inimat==NULL){
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
}

void CargaTareas (FILE *p, struct tarea *tar, struct tarea *antt, struct tarea *auxt, struct tarea **initar){
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
}

void CargaTecnicos (FILE *p, struct tecnico *tech, struct tecnico **et, struct tecnico **st){
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
}

void CargaTrabajos (FILE  *p, struct trabajos *trab, struct trabajos **ent, struct trabajos **sal){
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
}

void CargaOpciones (FILE *p, struct opcion *opc, struct opcion *anto, struct opcion **iniopc){
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
}

void CargaPendientes (FILE *p, struct pendientes *pend, struct pendientes **tope){
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
		fclose(p);
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
	
	CargaClientes (p, cli, antc, inicli);
	CargaMateriales (p, mat, auxm, raiz);
	CargaMaterialesOpcion (p, mato, antm, inimat);
	CargaTareas (p, tar, antt, auxt, initar);
	CargaTecnicos (p, tech, et, st);
	CargaTrabajos (p, trab, ent, sal);
	CargaOpciones (p, opc, anto, iniopc);
	CargaPendientes (p, pend, tope);
}

void Desapilar (struct pendientes **nodo, struct pendientes **tp){
	(*nodo) = (*tp);
	(*tp) = (*tp)->sgte;
	(*nodo)->sgte = NULL;
}

void DescargaClientes( FILE *p, struct cliente *cli, struct cliente *inicli){
	if((p=fopen("clientes.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Clientes durante la carga |||||||\n");
	}else{
		while(inicli != NULL){
			fscanf(p, "%ld" ,cli->DNI);
			fscanf(p, "%d" ,cli->id);
			fscanf(p, "%s" ,cli->Nombre);
			inicli = inicli->sgte;
		}
		fclose(p);
	}
}

void DescargaMaterialesOpcion(FILE *p, struct materialesop *mato, struct materialesop *inimat){
	p=NULL;
	if((p=fopen("materialesop.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Materiales por Opcion durante la carga |||||||\n");
	}else{
		while(inimat != NULL){
			fprintf(p, "%d", mato->cantidad);
			fprintf(p, "%d", mato->idmat);
			fprintf(p, "%d", mato->id_opcion);
			inimat = inimat->sgte;
		}
		fclose(p);
	}
}

void DescargaTareas (FILE *p, struct tarea *tar, struct tarea *auxt, struct tarea *initar){
	p=NULL;
	if((p=fopen("tareas.txt","w"))==NULL){
		printf("||||||| Error de apertura de archivo Tareas durante la carga |||||||\n");
	}else{
		tar=initar->ant;
		auxt=initar;
		while(initar != tar){
			fprintf(p, "%s", tar->descripcion);
			fprintf(p, "%d", tar->id_op);
			fprintf(p, "%d", tar->id_tarea);
			fprintf(p, "%d", tar->orden);
			fprintf(p, "%f", tar->tiempo);
			if(tar!=auxt){
				tar=auxt;
			}
			initar=initar->sgte;
		}
		fclose(p);
	}
}

void DescargaTecnicos (FILE *p, struct tecnico *tech, struct tecnico *et, struct tecnico *st){
	p=NULL;
	if((p=fopen("tecnicos.txt","w"))==NULL){
		printf("||||||| Error de apertura de archivo Tecnicos durante la carga |||||||\n");
	}else{
		while(st!=NULL){
			DesencolarTecnico (&tech, &et, &st);
			fprintf(p, "%ld\n", tech->DNI);
			fprintf(p, "%d\n", tech->id);
			fprintf(p, "%s\n", tech->Nombre);
			EncolarTecnico (&tech, &et, &st);
		}
		fclose(p);
	}
}

void DescargaTrabajos (FILE *p, struct trabajos *trab, struct trabajos *ent, struct trabajos *sal){
	p=NULL;
	if((p=fopen("trabajos.txt","w"))==NULL){
		printf("||||||| Error de apertura de archivo Trabajos durante la carga |||||||\n");
	}else{
		while(sal!=NULL){
			DesencolarTrabajos (&trab, &ent, &sal);
			fscanf(p, "%d\n", trab->cuatromtrs);
			fprintf(p, "%s\n", trab->direccion);
			fprintf(p, "%d\n", trab->fc_fin);
			fprintf(p, "%d\n", trab->id_cliente);
			fprintf(p, "%d\n", trab->id_opcion);
			fprintf(p, "%d\n", trab->id_tecnico);
			fprintf(p, "%d\n", trab->id_trabajo);
			EncolarTrabajos (&trab, &ent, &sal);
		}
		fclose(p);
	}
}

void DescargaOpciones (FILE *p, struct opcion *opc, struct opcion *iniopc){
	p=NULL;
	if((p=fopen("opciones.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Opciones durante la carga |||||||\n");
	}else{
		while(iniopc != NULL){
			fprintf(p, "%d\n", opc->id);
			fprintf(p, "%f\n", opc->cHoraMObra);
			fprintf(p, "%s\n", opc->Nombre);
			iniopc = iniopc->sgte;
		}
		fclose(p);
	}
}

void DescargaPendientes (FILE *p, struct pendientes *pend, struct pendientes *tope, struct pendientes *tpaux){
	p=NULL;
	if((p=fopen("pendientes.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Pendientes durante la carga |||||||\n");
	}else{
		while(tope != NULL){
			Desapilar (&pend, &tope);
			fprintf(p, "%d\n", pend->completado);
			fprintf(p, "%s\n", pend->descripcion);
			fprintf(p, "%d\n", pend->id_tarea);
			fprintf(p, "%d\n", pend->id_trabajo);
			fprintf(p, "%d\n", pend->orden);
			fprintf(p, "%f\n", pend->tiempo);
			Apilar (&pend, &tpaux);	
		}
		fclose(p);
	}
}

void DescargaSupremaDeEstructuras (FILE *p, struct cliente *inicli, struct materiales *raiz, struct materialesop *inimat, struct tarea *initar, struct tecnico *et, struct tecnico *st, struct trabajos *ent, struct trabajos *sal, struct opcion *iniopc, struct pendientes *tope){
	struct cliente *cli=NULL;
	struct materialesop *mato=NULL;
	struct tarea *tar=NULL, *auxt=NULL;
	struct tecnico *tech=NULL;
	struct trabajos *trab=NULL;
	struct opcion *opc=NULL;
	struct pendientes *pend=NULL, *tpaux=NULL;
	
	DescargaClientes (p, cli, inicli);
	raiz = DescargarArbol (raiz, p);
	DescargaMaterialesOpcion(p, mato, inimat);
	DescargaTareas (p, tar, auxt, initar);
	DescargaTecnicos (p, tech, et, st);
	DescargaTrabajos (p, trab, ent, sal);
	DescargaOpciones (p, opc, iniopc);
	DescargaPendientes (p, pend, tope, tpaux);
}

void DesencolarTecnico (struct tecnico **ds, struct tecnico **e, struct tecnico **s){
	(*ds) = (*s);
	(*s)=(*s)->sgte;
	if (*s == NULL){
		(*e) = NULL;	
	} 
}

void DesencolarTrabajos (struct trabajos **ds, struct trabajos **e, struct trabajos **s){
	(*ds) = (*s);
	(*s)=(*s)->sgte;
	if (*s == NULL){
		(*e) = NULL;	
	} 
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

int InsertarCliente(struct cliente ** nv,struct cliente ** inicli){
	struct cliente *aux=NULL;
	aux = (*inicli);
	if (aux != NULL) {
		aux->sgte = InsertarCliente (nv, aux->sgte);
	} else {
		aux = nv;
	}
	return (aux);
}

int InsertarOpcion (struct opcion *nvop, struct opcion *iniop){
	
	if (iniop != NULL){
		iniop->sgte = InsertarOpcion(nvop, iniop->sgte);
	} else{
		iniop = nvop;
		printf("Opcion agregada correctamente.\n");
	}
	return (iniop);
}

void ListadoDeOpciones (struct opcion **iniopcion) {
    int cont = 0;
    struct opcion *aux = (*iniopcion);  
    
    printf("Las opciones disponibles son: \n");
    while (aux != NULL) {
        cont = cont + 1;
        printf("--------------------------\n");
        printf("Opción %d: %s. \n", cont, aux->Nombre);
        printf("Precio de mano de obra: %.2f . \n", aux->cHoraMObra);  
        printf("ID de la opcion: %d. \n", aux->id);
        printf("--------------------------\n");
        aux = aux->sgte; 
    }
}
int ListadoDeOpcionesParaAltaDeTrabajo (struct opcion **iniopcion, struct materiales **raiz, struct materialesop **inimat, int _cuatrometros){
	int o, cont=0;
	float total=0, auxc=0;
	struct opcion *aux = (*iniopcion);
	
	printf("Las opciones disponibles son: \n");
	while (aux != NULL){
		cont = cont + 1;
		printf("--------------------------\n");
		printf("Opción %d: %s. \n", cont, aux->Nombre);
		printf("ID de la opcion: %d. \n", aux->id);
		auxc=OperacionCosto ((*raiz), aux->id, inimat);
		total = aux->cHoraMObra + auxc;
		
		if (_cuatrometros == 1){
			printf("El precio de mano de obra es: %.2f, pero con el costo de los materiales y del trabajo en altura queda en: %.2f \n", aux->cHoraMObra, ((20 * total)/100) + total);
		} else {
			printf("El precio de mano de obra es: %.2f, pero con el costo de materiales queda en: %.2f .\n", aux->cHoraMObra, total);
		}
		printf("--------------------------\n");
		total = 0; //se reincia el total para que no vaya acumulando a lo largo del recorrido
		aux = aux->sgte;
	}
	printf("Elija la opcion que desee: \n");
	fflush(stdin);
	scanf("%d", &o);
	while ((o < 0) || (o > cont)){
		printf("Opcion invalida. Elija una opcion correcta: \n");
		fflush(stdin);
		scanf("%d", &o);
	}
	return(o);
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
