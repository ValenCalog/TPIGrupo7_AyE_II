#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct opcionesfav{
	int id_op,ventas;
	struct opcionesfav *sgte;
};

struct fecha{
	int dia, mes, anio;
};

struct materiales{ //Arbol de Busqueda Binaria.
     int id;
     char descripcion[30], unimed[10];
     double costo_uni, cantidad;
     struct materiales *izq, *derch;
};

struct trabajos{ //Cola.
    int id_trabajo, id_opcion, opcion, cuatromtrs;
    char direccion[30];
    int id_tecnico, id_cliente;
	struct fecha fc_fin;
    struct trabajos *sgte;
};

struct tarea{ //Lista Doblemente Enlazada.
     int id_op, id_tarea, orden;
     double tiempo;
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
     double cHoraMObra; //cortesia de vale. (vale me arruinaste la vida con ese nombre)
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
	double tiempo;
    char descripcion[30];
    struct pendientes *sgte;
};

double OperacionTiempo (int id,struct tarea * initar);
double OperacionCosto (struct materiales *raiz, int codop, struct materialesop **inimat);

int BuscarCliente (int codcliente, struct cliente *ini);
int BuscarIdMaterialesOP (struct materiales *r, int id, int band);
int BuscarMayorIdCliente(struct cliente *ini);
int BuscarMayorIdTarea(struct tarea *ini);
int BuscarMayorIdTecnico(struct tecnico *e, struct tecnico *s);
int BuscarMayorIdTrab(struct trabajos **nodo, struct trabajos **e, struct trabajos **s);
int BuscarMayorIdOpc(struct opcion *ini);
int BuscarTecnico (struct tecnico **nodo, struct tecnico **et, struct tecnico **st);
int BuscarIDTecnico (int id, struct tecnico **nodo, struct tecnico **et, struct tecnico **st);
int ColaVacia (struct trabajos *s);
int ColaTecVacia(struct tecnico *s);
int GenerarIdMaterial(struct materiales *r);
int ListadoDeOpcionesParaAltaDeTrabajo (struct opcion **iniopcion, struct materiales **raiz, struct materialesop **inimat, int _cuatrometros, struct tarea *initar_);//este muestra las opciones y retorna un valor para el alta de trabajo
int Menu (int opc);
int Vacia (struct pendientes *tp);
int VerificarId(struct materiales *r, int idRandom);

char* BuscarNombreCliente(int id, struct cliente *inicli);
char* BuscarNombreOpcion(int id, struct opcion *iniop);

struct cliente* InsertarCliente (struct cliente *nv,struct cliente *inicli);
struct materiales* DescargarArbol (struct materiales *raiz, FILE *p);
struct materiales* InsertarMaterial (struct materiales *mat, struct materiales *raiz);
struct materiales* InsertarNuevoMaterial (struct materiales *r, struct materiales *nodo);
struct materialesop * InsertarMaterialesOp(struct materialesop *nv,struct materialesop *inimat);
struct tarea* BuscarAnterior (int id_op, struct tarea *initar);
struct opcion* InsertarOpcion (struct opcion * nvop,struct opcion *iniop);
struct opcionesfav * buscaropanterior(struct opcionesfav *auxL,struct opcionesfav *rc);
struct trabajos * DesencolarParaBuscarMayorID (struct trabajos *nv, struct trabajos *e, struct trabajos *s);

void AltaDeClientes (struct cliente **inicli);
void AltaDeMateriales (struct materiales **r);
void AltaDeMaterialesOP (struct materiales *raiz, struct materialesop **inimat, int id);
void AltaDeOpciones (struct opcion ** iniop, struct tarea **initar, struct materiales *raiz, struct materialesop **inimat);
void AltaDeTareas (struct tarea **initar, int id);
void AltaDeTrabajos (struct cliente **_inicli, struct opcion **_iniop, struct tecnico **eTec, struct tecnico **sTec, struct trabajos **eTra, struct trabajos **sTra, struct materialesop **_inimat, struct materiales **raiz, struct tarea *_initar, struct pendientes **topePend);
void AltaDeTecnicos(struct tecnico **e, struct tecnico **s);
void Apilar (struct pendientes **nodo, struct pendientes **tpaux);
void BuscarPrecioMaterial (double *unitario, struct materiales *r, int codmat);
void CargaClientes (FILE *p, struct cliente *cli, struct cliente *antc, struct cliente **inicli);
void CargaMateriales (FILE *p, struct materiales *mat, struct materiales *auxm, struct materiales **raiz);
void CargaTareas (FILE *p, struct tarea *tar, struct tarea *antt, struct tarea *auxt, struct tarea **initar);
void CargaTecnicos (FILE *p, struct tecnico **tech, struct tecnico **et, struct tecnico **st);
void CargaTrabajos (FILE  *p, struct trabajos **trab, struct trabajos **ent, struct trabajos **sal);
void CargaOpciones (FILE *p, struct opcion *opc, struct opcion *anto, struct opcion **iniopc);
void CargaMaterialesOpcion (FILE *p, struct materialesop *mato, struct materialesop *antm, struct materialesop **inimat);
void CargaPendientes (FILE *p, struct pendientes **pend, struct pendientes **tope);
void CargaSupremaDeEstructuras (FILE *p, struct cliente **inicli, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar, struct tecnico **et, struct tecnico **st, struct trabajos **e, struct trabajos **s, struct opcion **iniopc, struct pendientes **tope);
void completarlista(struct opcionesfav**Inicio, struct opcion *ini_opciones);
void Desapilar (struct pendientes **nodo, struct pendientes **tp);
void DescargaClientes ( FILE *p, struct cliente *cli, struct cliente *inicli);
void DescargaTareas (FILE *p, struct tarea *tar, struct tarea *auxt, struct tarea *initar);
void DescargaTecnicos (FILE *p, struct tecnico **tech, struct tecnico **et, struct tecnico **st);
void DescargaTrabajos (FILE *p, struct trabajos *trab, struct trabajos *ent, struct trabajos *sal);
void DescargaOpciones (FILE *p, struct opcion *opc, struct opcion *iniopc);
void DescargaMaterialesOpcion(FILE *p, struct materialesop *mato, struct materialesop *inimat);
void DescargaPendientes (FILE *p, struct pendientes **pend, struct pendientes **tope);
void DescargaSupremaDeEstructuras (FILE *p, struct cliente *inicli, struct materiales *raiz, struct materialesop *inimat, struct tarea *initar, struct tecnico **et, struct tecnico **st, struct trabajos *ent, struct trabajos *sal, struct opcion *iniopc, struct pendientes **tope);
void DesencolarTecnico(struct tecnico **ds, struct tecnico **e, struct tecnico **s);
void DesencolarTrabajos(struct trabajos **ds, struct trabajos **e, struct trabajos **s);
void EncolarTecnico(struct tecnico **nv, struct tecnico **e, struct tecnico **s);
void EncolarTrabajos(struct trabajos **nv, struct trabajos **e, struct trabajos **s);
void insertaropcionordenada(struct opcionesfav **auxL,struct opcionesfav **Lord);
void insertaropfav(struct opcionesfav **nv, struct opcionesfav **ini);
void ListadoPendientes(int id_trabajo,struct pendientes **tope);
void ListadoDeOpciones (struct opcion **iniop, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar); //este solo muestra las opciones que hay
void ListadoDeTrabajosDeTecnicos (struct trabajos **entrada, struct trabajos **salida, struct tecnico **et, struct tecnico **st, struct opcion **iniopc, struct cliente **inicli);
void recorrerIRD(struct materiales *r);
void OpcionesMasVendidas(struct trabajos *entrada,struct trabajos *salida,struct opcion *iniopc);
void copiarTareasPendientes(struct tarea *iniTar, struct pendientes **tpPend, int idTrab, int idOp);
//Consigna 5
void trabajosentre(struct trabajos *entrada,struct trabajos *salida,struct opcion *iniopc,struct materiales *raiz,struct materialesop *inimat,struct tarea *initar);
double BuscarPrecioManodeObra(float id,struct opcion *ini);

int main(int argc, char *argv[]){
	struct cliente *inicli=NULL;
	struct materiales *raiz=NULL;
	struct materialesop *inimat=NULL;
	struct tarea *initar=NULL;
	struct tecnico *et=NULL, *st=NULL;
	struct trabajos *nd=NULL, *e=NULL, *s=NULL;
	struct opcion *iniopc=NULL;
    struct pendientes *nodo=NULL, *tope=NULL;	
	int opc=-1,id_trabajo;
	FILE *p=NULL;
	
	srand(time(NULL));
	CargaSupremaDeEstructuras(p, &inicli, &raiz, &inimat, &initar, &et, &st, &e, &s, &iniopc, &tope);
	
	while(opc!=0){
		//system("CLS");
		opc = Menu(opc);
		switch(opc){
			case 0:
				printf("---Saliendo de Programa---\n Adios!\n");
				opc=0;
				break;
			case 1:
				printf("HUHA/n");
				ListadoDeOpciones(&iniopc, &raiz, &inimat, &initar);
				opc=-1;
				break;
			case 2:
				AltaDeOpciones(&iniopc, &initar, raiz, &inimat);
				opc=-1;
				break;
			case 3:
				AltaDeTrabajos (&inicli, &iniopc, &et, &st, &e, &s, &inimat, &raiz, initar, &tope);
				opc=-1;
				break;
			case 4:
				printf("Digite el ID de trabajo a consultar: ");
				scanf("%i",&id_trabajo);
				fflush(stdin);
				ListadoPendientes(id_trabajo,&tope);
				opc=-1;
				break;
			case 5:
				OpcionesMasVendidas(e,s,iniopc);
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
			case 8:
				AltaDeClientes(&inicli);
				opc=-1;
				break;
			case 9:
				if(raiz!=NULL){
					printf("\nMATERIALES: ");
					recorrerIRD(raiz);
					printf("\n");
				}else{
					printf("\nNo hay materiales cargados en el stock de la empresa");
				}
				opc=-1;
				break;
			case 10:
				ListadoDeTrabajosDeTecnicos (&e, &s, &et, &st, &iniopc, &inicli);
				opc=-1;
				break;
			case 11:
				trabajosentre(e,s,iniopc,raiz,inimat,initar);
				break;
			case 12:
				OpcionesMasVendidas(e,s,iniopc);
				break;
		}
	}
	DescargaSupremaDeEstructuras(p, inicli, raiz, inimat, initar, &et, &st, e, s, iniopc, &tope);
	return (0);
}

//Char
char* BuscarNombreCliente(int id, struct cliente *l) {
    while (l != NULL) {
        if (id == l->id) {
            return l->Nombre;
        }
        l = l->sgte;
    }
    return NULL; // Devuelve NULL si no se encuentra el ID
}

char* BuscarNombreOpcion(int id, struct opcion *r) {
    while (r != NULL) {
        if (id == r->id) {
            return r->Nombre;
        }
        r = r->sgte;
    }
    return NULL; // Devuelve NULL si no se encuentra el ID
}

//Double
double OperacionTiempo (int id, struct tarea *initar){
	double tiempo=0;
	struct tarea *aux=NULL;
	aux = initar;
	while(initar!=NULL){
		printf("\nHOLAAAA ENTRAAAAAAMOS EN TIEMPO");
		if(initar->id_op==id){
			tiempo = tiempo + initar->tiempo;
		}
		initar=initar->sgte;
	}
	return (tiempo);
}

double OperacionCosto (struct materiales *raiz, int codop, struct materialesop **inimat){
	double costomat=0, auxc=0;
	struct materialesop *aux=NULL;
	aux = (*inimat);
	while(aux!=NULL){
		if(aux->id_opcion=codop){
			printf("\nHOLAAAA ENTRAMOS GENTE");
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
	
	while ((ini != NULL) && (encontroid == 0)){
		if (ini->id == id){
			encontroid = 1;
		} else {
			ini = ini->sgte;
		}	
	}
	printf("salio del while\n");
	return (encontroid);	
}

int BuscarIdMaterialesOP (struct materiales *r, int id, int band){
	if (r == NULL){
		printf("\n |||| No hay materiales disponibles ||||");
		return (band);
	}else{
		if (r->id == id){
			printf("\n Se encontro el material en el almacen :) ");
			band=1;
			return (band);
		}else{
			if (id < r->id){
				band = BuscarIdMaterialesOP (r->izq, id, band);
			}else{
				band = BuscarIdMaterialesOP (r->derch, id, band);
			}
		}
	}
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

int BuscarMayorIdTarea (struct tarea *ini){
	int idMax = ini->id_tarea;
	ini = ini->sgte;
	while(ini!=NULL){
		if(ini->id_tarea > idMax){
			idMax = ini->id_tarea;
		}
		ini = ini->sgte;
	}
	return (idMax);
}

int BuscarMayorIdTrab (struct trabajos **nodo, struct trabajos **e, struct trabajos **s){
	int mayor=0;
	struct trabajos *eAux = NULL, *sAux= NULL;
	
	if (ColaVacia(*s) == 1){
		printf("\nhola? la cola esta vaciaaaaaa");
		return mayor;
	} else {
		while (!ColaVacia(*s)){
			printf("\nHOLAAA GENTE ESTAMOS ACA DENTRO");
			DesencolarTrabajos(nodo, e, s);
			printf("\nCONTENIDO DE nodo: %d", (*nodo)->id_trabajo);
			if ((*nodo)->id_trabajo > mayor){
				mayor = (*nodo)->id_trabajo;
			}
			EncolarTrabajos(nodo, &eAux, &sAux);
		}
		
		while(!ColaVacia(sAux)){
			DesencolarTrabajos(nodo, &eAux, &sAux);
			EncolarTrabajos(nodo, e, s);
		}
	}
	printf("\nCONTENIDO DE MAYOR: %d", mayor);
	return(mayor);
}

int BuscarIDTecnico(int id, struct tecnico **aux, struct tecnico **e, struct tecnico **s){
	int band = 0;
	
	while ((!ColaTecVacia(*s)) && (band == 0)){ //hacer funcion
		DesencolarTecnico(aux, e, s);
		if (id == (*aux)->id){
			band = 1;
			EncolarTecnico(aux, e, s);
		} else {
			EncolarTecnico(aux, e, s);
		}
	}
	return (band);
}

int BuscarTecnico (struct tecnico **nodo, struct tecnico **e, struct tecnico **s){
	int cont = 0, id = 0;
	while (cont == 0){
		DesencolarTecnico (nodo, e, s);
		cont = cont + 1;
		printf ("Su tecnico sera: %s.\n", (*nodo)->Nombre);
		id = (*nodo)->id;
		EncolarTecnico (nodo, e, s); //puse el return abajo y cambie la forma ya qu eno enviaba el id del nodo
	}
	return id;
}

int BuscarMayorIdTecnico (struct tecnico *e, struct tecnico *s){
	int maxId = s->id;
	s = s->sgte;
	while (s != NULL){
		if (s->id > maxId){
			maxId = s->id;
		}
		s = s->sgte;
	}
	return (maxId);
}

int ColaVacia (struct trabajos *s){
	int band;
	
	if ( s == NULL ){
		band = 1;
	}else {
		band = 0;
	}
	return (band);
}

int ColaTecVacia(struct tecnico *sal){
	
	int band;
		
		if ( sal == NULL ){
			band = 1;
		}else {
			band = 0;
		}
		return (band);	
}

int GenerarIdMaterial (struct materiales *r){
	int min = 10, max = 40000, idRandomizado, idEncontrado = 0;
	do{
		idRandomizado = rand() % (max - min + 1) + min;
		idEncontrado = VerificarId (r, idRandomizado);		
	}while (idEncontrado == 1);
	
	return (idRandomizado);
}

int ListadoDeOpcionesParaAltaDeTrabajo (struct opcion **iniopcion, struct materiales **raiz, struct materialesop **inimat, int _cuatrometros, struct tarea *initar_){
	int o, cont=0;
	double auxtiempo=0, auxcosto=0, total=0;
	struct opcion *aux = (*iniopcion);
	
	printf("Las opciones disponibles son: \n");
	while (aux != NULL){
		cont = cont + 1;
		printf("\n--------------------------\n");
		printf("Opcion %d: %s. \n", cont, aux->Nombre);
		printf("ID de la opcion: %d. \n", aux->id);
		auxcosto = OperacionCosto ((*raiz), aux->id, inimat);
		auxtiempo = OperacionTiempo(aux->id, initar_);		
		if (_cuatrometros == 0){
			printf("El precio de mano de obra es: %.2f.\n", aux->cHoraMObra);
			printf("El precio de los materiales es: %.2f. \n", auxcosto);
			printf("El tiempo total de las tareas es de: %.2f.\n", auxtiempo);
			printf("---> El precio total de la opcion es: %.2f", auxcosto + aux->cHoraMObra);
		} else {
			printf("El precio de mano de obra es: %.2f.\n", aux->cHoraMObra);
			printf("El precio de los materiales es: %.2f. \n", auxcosto);
			printf("El tiempo total de las tareas es de: %.2f.\n", auxtiempo);
			printf("Se agregara un 20 porciento extra por la mano de obra en altura mayor a 4 metros.\n");
			total = auxcosto + aux->cHoraMObra;
			total = ((total * 20)/100) + total;
			printf("---> El precio total de la opcion es: %.2f", total);
		}
		printf("\n--------------------------\n");
		auxcosto=0;
		auxtiempo=0;
		total = 0;       //se reincia todo para que no se vayan acumulando a lo largo del recorrido
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
int Menu (int o){
	int contgency = 0;
	while ((o!=0) && (o!=1) && (o!=2) && (o!=3) && (o!=4) && (o!=5) && (o!=6) && (o!=7) && (o!=8) && (o!=9) && (o!=10) && (o!=11) && (o!=12)){
		if (contgency >= 1){
			printf ("El valor que ingreso no es valido, vuelva a ingresar una opcion. \n" );
			fflush (stdin);
			scanf ("%d", &o );
		}else{
			printf ("-------------------Bienvenido al menu :D-------------------\n---Ingrese 0 para salir.\n---Ingrese 1 para listar opciones.\n---Ingrese 2 para dar de alta un opcion.\n---Ingrese 3 para dar de alta un trabajo.\n---Ingrese 4 para listar las tareas pendietes de un trabajo.\n---Ingrese 5 para ver las opciones mas vendidas.\n---Ingrese 6 para dar de alta un material.\n---Ingrese 7 para dar de alta un tecnico.\n---Ingrese 8 para dar de alta un cliente.\n---Ingrese 9 para listar materiales.\n---Ingrese 10 para listar trabajos de un tecnico.\n---Ingrese 11 para consultar los trabajos finalizados entre 2 fechas.\n---Ingrese 12 consultar sobre las 4 opciones mas vendidas entre 2 fechas.\n" );
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
struct cliente * InsertarCliente(struct cliente *nv,struct cliente *inicli){
	printf ("LLEGO A CLIENTES \n");
	if (inicli != NULL) {
		printf ("ingreso clientes distinto a null A CLIENTES \n");
		inicli->sgte = InsertarCliente (nv, inicli->sgte);
	} else {
		printf ("ingleso a clientes else CLIENTES \n");
		inicli = nv;
		inicli->sgte=NULL;
	}
	printf ("salio de fc \n");
	return (inicli);
}

struct materiales* DescargarArbol (struct materiales *raiz, FILE *p){
	if(raiz!=NULL){
		printf("\nholaaa");
		raiz->izq = DescargarArbol (raiz->izq, p);
		if((p=fopen("materiales.txt", "a+"))==NULL){
			printf("||||||| Error de apertura de archivo Materiales durante la carga |||||||\n");
		}else{
			printf("probandoooo");
			printf("\nraiz->cantidad: %f", raiz->cantidad);
			fprintf(p, "%d;", raiz->id);
			fprintf(p, "%s;", raiz->descripcion);
			fprintf(p, "%s;", raiz->unimed);
			fprintf(p, "%f;", raiz->cantidad);
			fprintf(p, "%f\n", raiz->costo_uni);
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

struct materialesop * InsertarMaterialesOp(struct materialesop *nv,struct materialesop *inimat){
	if (inimat != NULL) {
		inimat->sgte = InsertarMaterialesOp (nv, inimat->sgte);
	} else {
		inimat = nv;
	}
	return (inimat);
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

struct trabajos * DesencolarParaBuscarMayorID (struct trabajos *n, struct trabajos *e, struct trabajos *s){
	n = s;
	s = s->sgte;
	n->sgte = NULL;
	if (s == NULL){
		e = NULL;
	}
	return n;
}

struct opcion * InsertarOpcion (struct opcion *nvop, struct opcion *iniop) {
    struct opcion *aux = iniop;
    struct opcion *prev = NULL;

    printf("LLEGO A opcion\n");

    // Caso especial: la lista est? vac?
    if (iniop == NULL) {
        printf("ingleso a clientes else opcion\n");
        iniop = nvop;
        iniop->sgte = NULL;
    } else {
        // Recorrer la lista hasta encontrar el ?ltimo elemento
        while (aux != NULL) {
            prev = aux;
            aux = aux->sgte;
        }
        // Insertar el nuevo nodo al final de la lista
        prev->sgte = nvop;
        nvop->sgte = NULL;
    }

    printf("salio de fc\n");
    getchar(); // No recomendado en algunos entornos, considera usar getchar() o printf("Press any key...\n"); getchar();
    return iniop;
}

struct opcionesfav * buscaropanterior(struct opcionesfav *auxL,struct opcionesfav *rc){
	struct opcionesfav *Ant=NULL;
	while(rc!=NULL){
		if(rc->ventas<auxL->ventas){
			rc=NULL;
		}else{
			Ant=rc;
			rc=rc->sgte;
		}
	}
	return(Ant);
}

//Voids
void AltaDeClientes (struct cliente **inicli){
	struct cliente *nvcliente = NULL;
	
	nvcliente = ( struct cliente * ) malloc( sizeof( struct cliente ) );
	
	if( nvcliente != NULL ){
		printf( "\nï¿½Bienvenido a SistemaSeguro S.A!" );
		printf( "\nA continuacion le pediremos una serie de datos para poder registrarlo como cliente." );
		printf( "\n---Digite su DNI: " );
		scanf( "%ld", &nvcliente->DNI );
		fflush(stdin);
		printf( "\n---Digite su nombre completo: " );
		fflush(stdin);
		gets( nvcliente->Nombre );
		
		if( *inicli == NULL ){
			printf("Entra al if\n");
			nvcliente->id = 1;
		}else{
			printf("Entra al else \n");
			nvcliente->id = BuscarMayorIdCliente( *inicli ) +1;
		}
		printf("Su ID de cliente es: %d \n", nvcliente->id);
		nvcliente->sgte = NULL;
		(*inicli) = InsertarCliente( nvcliente,(*inicli) );
		printf("Cliente agregado exitosamente. \n");
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
		scanf( "%lf", &nuevo_mat->costo_uni );
		
		printf( "\n---Ingrese la cantidad a almacenar del nuevo material: ");
		fflush(stdin);
		scanf( "%lf", &nuevo_mat->cantidad );
		nuevo_mat->derch = NULL;
		nuevo_mat->izq = NULL;
		(*raiz) = InsertarNuevoMaterial ( (*raiz), nuevo_mat );
		printf("Material agregado exitosamente.\n");
	}
}

void AltaDeMaterialesOP (struct materiales *raiz, struct materialesop **inimat, int id){
	struct materialesop *newmat=NULL;
	int idaux=0, band=0, opc=1;
	newmat = (struct materialesop *) malloc (sizeof (struct materialesop));
	if(newmat == NULL){
		printf( ":( No hay espacio en memoria \n" );
	}else{
		printf("--- Ingrese (1) para cargar un material o (0) para terminar: ");
		fflush(stdin);
		scanf("%d", &opc);
		while(opc!=0){
			printf("\n--- Ingrese el id de material: ");
			fflush(stdin);
			scanf("%d", &idaux);
			band = BuscarIdMaterialesOP (raiz, idaux, band);
			if(band==0){
				printf("\n|||| El material no se encuentra en el almacen ||||");
			}else{
				newmat->idmat=idaux;
				newmat->id_opcion=id;
				printf("\n--- Ingrese la cantidad del material a utilizar: ");
				fflush(stdin);
				scanf("%d", &newmat->cantidad);
				newmat->sgte=NULL;
				(*inimat) = InsertarMaterialesOp (newmat, (*inimat));
			}
			printf("--- Ingrese (1) para cargar un material o (0) para terminar: ");
			fflush(stdin);
			scanf("%d", &opc);
		}
	}
}

void AltaDeOpciones (struct opcion ** iniop, struct tarea **initar, struct materiales *raiz, struct materialesop **inimat){
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
		printf("El id de la opcion es: %d \n", nueva_op->id);
		
		printf( "---Digite el nombre de la nueva opcion: \n" );
		gets( nueva_op->Nombre );
		fflush(stdin);
		printf("---Digite el costo  de la mano de obra: \n");
		scanf("%lf", &nueva_op->cHoraMObra);
		fflush(stdin);
		nueva_op->sgte = NULL;
		(*iniop) = InsertarOpcion (nueva_op, (*iniop));
		AltaDeTareas (&(*initar), nueva_op->id);
		AltaDeMaterialesOP (raiz, &(*inimat), nueva_op->id);
		printf("\nHolaa");
		printf("Opcion agregada exitosamente.\n");
	}
}

void AltaDeTareas (struct tarea **initar, int id){
	struct tarea *newtar=NULL, *antt=NULL , *auxt=NULL;
	int band=0, opc=1;
	printf("--- Ingrese (1) para cargar una tarea o (0) para terminar: ");
		fflush(stdin);
		scanf("%d", &opc);
		while(opc!=0){
			newtar = (struct tarea *) malloc (sizeof (struct tarea));
			if(newtar!=NULL){
				newtar->id_op=id;
				if ((*initar) == NULL){
					newtar->id_tarea = 1;
				}else{
					newtar->id_tarea = BuscarMayorIdTarea ((*initar)) + 1;
				}
				printf("\n--- Ingrese el orden: ");
				fflush(stdin);
				scanf("%d", &newtar->orden);
				printf("\n--- Ingrese el tiempo estimado: ");
				fflush(stdin);
				scanf("%lf", &newtar->tiempo);
				printf("\n--- Ingrese una descripcion: ");
				fflush(stdin);
				gets(newtar->descripcion);
				newtar->ant=NULL;
				newtar->sgte=NULL;
				        antt = BuscarAnterior (newtar->id_op, (*initar));
						if( *initar == NULL ){
							(*initar) = newtar;
							(*initar)->sgte = NULL;
							(*initar)->ant = NULL;
						}else{
							if( antt == NULL ){
								(*initar) = newtar;
							}else{
								auxt = antt->sgte;
								newtar->ant = antt;
								antt->sgte = newtar;
								if( auxt != NULL ){
									newtar->sgte = auxt;
									auxt->ant = newtar;
								}
							}
						}
				printf("\nINITAR: %d", (*initar)->id_tarea);
				printf("\nTareacargada: id tarea: %d\n", newtar->id_tarea);
			}else{
				//
			}
			printf("--- Ingrese (1) para cargar una tarea o (0) para terminar: ");
			fflush(stdin);
			scanf("%d", &opc);
			fflush(stdin);
		}
}

void AltaDeTrabajos (struct cliente **_inicli, struct opcion **_iniop, struct tecnico **eTec, struct tecnico **sTec, struct trabajos **eTra, struct trabajos **sTra, struct materialesop **_inimat, struct materiales **raiz, struct tarea *_initar, struct pendientes **topePend){
    struct tecnico *nodoaux = NULL; 
    struct trabajos *nuevo_trab=NULL, *aux=NULL, *eaux= (*eTra), *saux=(*sTra);
    int op, ops, cli;
    
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
    		printf ("\n |||| Opci?n inv?lida |||| \n--- Ponga 1 o 0: ");
    		scanf ("%i", &nuevo_trab->cuatromtrs); 
    		fflush (stdin);
		}
		
    	op = ListadoDeOpcionesParaAltaDeTrabajo (_iniop, raiz, _inimat, nuevo_trab->cuatromtrs, _initar); 
    	nuevo_trab->id_opcion = op; //el id de la opcion es el mismo que el nro de opcion
    	if(sTra != NULL){
    		nuevo_trab->id_trabajo = BuscarMayorIdTrab (&aux, &eaux, &saux) + 1; //va a buscar el mayor id
		}else{
			nuevo_trab->id_trabajo = 1;
		}
		printf("El ID de trabajo es: %d \n", nuevo_trab->id_trabajo);
    
		nuevo_trab->fc_fin.anio = 0;
		nuevo_trab->fc_fin.dia = 0;
		nuevo_trab->fc_fin.mes = 0;
    	printf ("\n---Ingrese la direccion de la instalacion: \n" );
    	fflush(stdin);
    	gets (nuevo_trab->direccion);
		nuevo_trab->id_tecnico = BuscarTecnico(&nodoaux, eTec, sTec);
		fflush(stdin);
   		printf ("\nIngrese su ID de cliente: ");
   		fflush (stdin);
   		scanf ("%d",&nuevo_trab->id_cliente); 
   		fflush (stdin);
   		cli = BuscarCliente(nuevo_trab->id_cliente, (*_inicli));
		if (cli == 0){
            printf ("\n--- No se ha encontrado un cliente asociado a la ID ingresada---");
            printf ("\n ¿Desea darse de alta como cliente? ");
            printf ("\n 1) Si");
            printf ("\n 2) No");
            printf ("\n --> ");
            scanf ("%i",&ops);
            fflush (stdin);
			while (ops !=0){
                switch (ops){
	                case 1:
	            	    AltaDeClientes(_inicli);
	            	    if (nuevo_trab->id_cliente != 0){
           					EncolarTrabajos(&nuevo_trab, eTra, sTra);
           				    printf("Trabajo agregado exitosamente.\n");
        				}
        				ops=0;
	                    break;
	                case 2:
	                    printf("\nDisculpe las molestias, vuelva pronto \n");
	                    ops=0;
	                    break;
	                default:
	                    printf("Ingrese una opcion valida: ");
	                    printf("\n--> ");
	                    scanf("%i",&ops);
	                    break;
				}
            }        
        }else{
        	copiarTareasPendientes(_initar, topePend, nuevo_trab->id_trabajo, nuevo_trab->id_opcion);
        	EncolarTrabajos(&nuevo_trab, eTra, sTra);
           	printf("Trabajo agregado exitosamente.\n");	
		}
	}    
}

void copiarTareasPendientes(struct tarea *iniTar, struct pendientes **tpPend, int idTrab, int idOp){
	struct pendientes *auxPend = NULL;
	int band = 0;
	while((iniTar!= NULL) && (band ==0)){
		if(iniTar->id_op == idOp){
			auxPend = (struct pendientes*) malloc(sizeof(struct pendientes));
			if(auxPend != NULL){
				auxPend->id_trabajo = idTrab;
				auxPend->id_tarea = iniTar->id_tarea;
				auxPend->completado = 0;
				strcpy(auxPend->descripcion, iniTar->descripcion);
				auxPend->tiempo = iniTar->tiempo;
				auxPend->orden = iniTar->orden;
				auxPend->sgte = NULL;
				Apilar(&auxPend,tpPend);
			}else{
				band = 0;
			}
		}
		iniTar = iniTar->sgte;
	}
}

void AltaDeTecnicos (struct tecnico **e, struct tecnico **s){
	struct tecnico *nv;
	printf("\nHolaaaaaaaa");
	nv = (struct tecnico*) malloc (sizeof (struct tecnico));
	if (nv!=NULL){
		if (*e == NULL){
			printf("\nHola");
			nv->id = 1;
		}else{
			printf("\nOuYeA");
			nv->id = BuscarMayorIdTecnico(*e, *s) +1;	
			printf("\nEstot aca");
		}
		printf ("\nDNI: ");
		scanf ("%d", &nv->DNI);
		printf ("\nNombre: ");
		scanf ("%s", &nv->Nombre);
		nv->sgte = NULL;
		EncolarTecnico (&nv, e, s);
		printf("Tecnico agregado exitosamente.\n");
	}else{
		printf("\nNo hay espacio de memoria para nuevos tecnicos");
	}
}

void Apilar (struct pendientes **nodo, struct pendientes **tpaux){
	(*nodo)->sgte = (*tpaux);
	(*tpaux) = (*nodo);
	(*nodo) = NULL;
}

void BuscarPrecioMaterial (double *unit, struct materiales *raiz, int codmat){
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
	int cont=0, band = 0;
	if((p=fopen("clientes.txt","r"))==NULL){
		printf("||||||| Error de apertura de archivo Clientes durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                cli = (struct cliente *) malloc(sizeof(struct cliente));
                if (cli == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                	
                	if (a != NULL) {
                        cli->id=atoi(a);
                    }
                    printf("id: %d \n", cli->id);
                    
                	a = strtok(NULL, d);
                    if (a != NULL) {
                        strcpy(cli->Nombre,a);
                    }
                    printf("nomb %s\n", cli->Nombre);
                	
                	a = strtok(NULL, d);
                	if(a!=NULL){
                		cli->DNI=atol(a);	
					}
					printf("dni: %ld \n", cli->DNI);
                    
                	cli->sgte = NULL;
                    (*inicli) = InsertarCliente (cli, (*inicli));
                    a = strtok(NULL, d); 
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        fclose(p);
    }
}

void CargaMateriales (FILE *p, struct materiales *mat, struct materiales *auxm, struct materiales **raiz){
	int cont=0, band = 0;
	p=NULL;
	if((p=fopen("materiales.txt","r"))==NULL){
		printf("||||||| Error de apertura de archivo Materiales durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                mat = (struct materiales *) malloc(sizeof(struct materiales));
                if (mat == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
					
					
					/*
					fprintf(p, "%d;", raiz->id);
					fprintf(p, "%s;", raiz->descripcion);
					fprintf(p, "%s;", raiz->unimed);
					fprintf(p, "%f;", raiz->cantidad); mat->cantidad=atof(a);
					fprintf(p, "%f;\n", raiz->costo_uni); mat->costo_uni=atof(a);
					*/
					
                    if(a != NULL){
                    	mat->id=atoi(a);	
					}
					a = strtok(NULL, d);
					if(a != NULL){
						strcpy(mat->descripcion,a);
					}
					a = strtok(NULL, d);
					if( a != NULL){
						strcpy(mat->unimed,a);
					}
					a = strtok(NULL, d);
					if(a != NULL){
						mat->cantidad=atof(a);
					}
					a= strtok(NULL, d);
					if(a != NULL){
						mat->costo_uni=atof(a);
					}
					
					mat->izq = NULL;
					mat->derch = NULL;
					(*raiz) = InsertarMaterial(mat, (*raiz));
					
					a= strtok(NULL, d);
                    
                }
                
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        printf("\nllgeue aca arriba del fclose");
        fclose(p);
	}
}

void CargaMaterialesOpcion (FILE *p, struct materialesop *mato, struct materialesop *antm, struct materialesop **inimat){
	int band=0;
	p=NULL;
	antm=NULL;
	if((p=fopen("materialesop.txt","r"))==NULL){
		printf("||||||| Error de apertura de archivo Materiales por Opcion durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                mato = (struct materialesop *) malloc(sizeof(struct materialesop));
                if (mato == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                	if(a!=NULL){
                		mato->idmat=atoi(a);
					}
                   
                    a = strtok(NULL, d);
                    
                    if (a != NULL) {
                        mato->id_opcion=atoi(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                       mato->cantidad=atoi(a);
                    }
					mato->sgte = NULL;
                    (*inimat) = InsertarMaterialesOp (mato, *inimat);
                    a = strtok(NULL, d);
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        fclose(p);
	}
}

void CargaTareas (FILE *p, struct tarea *tar, struct tarea *antt, struct tarea *auxt, struct tarea **initar){
	int band=0;
	p=NULL;
	if((p=fopen("tareas.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Tareas durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                tar = (struct tarea *) malloc(sizeof(struct tarea));
                if (tar == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                    //ORDEN: id tarea, id opcion, descripcion, orden, tiempo
                    if(a != NULL){
                    	tar->id_tarea=atoi(a);
					}
					a = strtok(NULL, d);
					if(a != NULL){
						tar->id_op=atoi(a);
					}
					a = strtok(NULL, d);
					if(a != NULL){
						strcpy(tar->descripcion,a);
					}
					a = strtok(NULL, d);
					if(a != NULL){
						tar->orden=atoi(a);
					}
					a = strtok(NULL, d);
					if(a != NULL){
						tar->tiempo=atof(a);
					}
					
					printf("\nPROBANDO TAREA");
					printf("\nid_tarea: %d", tar->id_tarea);
					printf("\nid_opc: %d", tar->id_op);
					
					tar->ant = NULL;
					tar->sgte = NULL;
					
					//Esto despues reemplazamos por una funcion de insertar
					antt = BuscarAnterior (tar->id_op, (*initar));
					if( initar == NULL ){
						(*initar) = tar;
						(*initar)->sgte = NULL;
						(*initar)->ant = NULL;
					}else{
						if( antt == NULL ){
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
					
					a = strtok(NULL, d);
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        fclose(p);
    }
}

void CargaTecnicos (FILE *p, struct tecnico **tech, struct tecnico **et, struct tecnico **st){
	int band=0;
	p=NULL;
	if((p=fopen("tecnicos.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Tecnicos durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                *tech = (struct tecnico *) malloc(sizeof(struct tecnico));
                if (*tech == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                	//id nombre dni
                	if(a!=NULL){
                		(*tech)->id = atoi(a);
					}
					
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        strcpy((*tech)->Nombre, a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        (*tech)->DNI=atol(a);
                    }
                    (*tech)->sgte = NULL;
					printf("\nId: %d, Nomb: %s, DNI: %ld", (*tech)->id, (*tech)->Nombre, (*tech)->DNI);
                    EncolarTecnico(tech, et, st);
                    a = strtok(NULL, d);
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        fclose(p);
	}
}

void CargaTrabajos (FILE  *p, struct trabajos **trab, struct trabajos **ent, struct trabajos **sal){
	int band=0;
	int fecha=0;
	p=NULL;
	if((p=fopen("trabajos.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Trabajos durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a, *b, cadauxFec[11]="";
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            while ((a != NULL) && (band == 0)) {
                *trab = (struct trabajos *) malloc(sizeof(struct trabajos));
                if (*trab == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                	if(a != NULL){
                		(*trab)->id_trabajo = atoi(a);
					}
                  
                    a = strtok(NULL, d);
                    if (a != NULL) {
                         (*trab)->id_opcion=atoi(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        (*trab)->id_cliente=atoi(a);
                    }
                    
                	a = strtok(NULL, d);
                    if (a != NULL) {
                       	(*trab)->id_tecnico=atoi(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        (*trab)->cuatromtrs=atoi(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        strcpy((*trab)->direccion,a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                    	strncpy(cadauxFec, a, 10);
                    	b = strtok(cadauxFec, "/");
                    	if(b!=NULL){
                    		(*trab)->fc_fin.dia = atoi(b);
						}
                    	
                    	b = strtok(NULL,"/");
                    	if(b!=NULL){
                    		(*trab)->fc_fin.mes = atoi(b);
						}
                    	
                    	b = strtok(NULL,"/");
                    	if(b!=NULL){
                    		(*trab)->fc_fin.anio = atoi(b);
						}
                    	
                    }
                    
                    printf("\nTrabajo: ");
                    printf("\nId: %d", (*trab)->id_trabajo);
                    printf("\nFecha: %d/%d/%d", (*trab)->fc_fin.dia, (*trab)->fc_fin.mes, (*trab)->fc_fin.anio);
					(*trab)->sgte = NULL;
                    EncolarTrabajos(trab, ent, sal);
                    a = strtok(NULL, d);
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        fclose(p);
	}
	
	/*Orden:
		fprintf(p, "%d;", trab->id_trabajo);  
		fprintf(p, "%d;", trab->id_opcion);   
		fprintf(p, "%d;", trab->id_cliente);  
		fprintf(p, "%d;", trab->id_tecnico);  
		fprintf(p, "%d;", trab->cuatromtrs); 
		fprintf(p, "%s;", trab->direccion);  
		fprintf(p, "%d\n", trab->fc_fin);  	f
											
			EncolarTrabajos(*trab, ent, sal);
	*/
}

void CargaOpciones (FILE *p, struct opcion *opc, struct opcion *anto, struct opcion **iniopc) {
    int band = 0;
    if ((p = fopen("opciones.txt", "r")) == NULL) {
        printf("||||||| Error de apertura de archivo Opciones durante la carga |||||||\n");
    } else {
        char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                opc = (struct opcion *) malloc(sizeof(struct opcion));
                if (opc == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                    opc->id = atoi(a);
                    a = strtok(NULL, d);
                    
                    if (a != NULL) {
                        strcpy(opc->Nombre, a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        opc->cHoraMObra = atof(a);
                    }
					opc->sgte =NULL; //por si acaso
                    (*iniopc) = InsertarOpcion(opc, (*iniopc));
                    a = strtok(NULL, d);
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
        fclose(p);
    }
}

void CargaPendientes (FILE *p, struct pendientes **pend, struct pendientes **tope){
	int band=0;
	p=NULL;
	if((p=fopen("pendientes.txt", "r"))==NULL){
		printf("||||||| Error de apertura de archivo Pendientes durante la carga |||||||\n");
	}else{
		char d[] = ";", cadaux[1000]="", *a;
        char *prueba;
		
		prueba = fgets(cadaux, sizeof(cadaux), p);
        while (prueba != NULL) {
            a = strtok(cadaux, d);
            printf("COMPROBACION ARCH= %s \n", cadaux);
            
            while ((a != NULL) && (band == 0)) {
                *pend=(struct pendientes *) malloc(sizeof(struct pendientes));
                if (*pend == NULL) {
                    printf("-------No hay espacio de memoria-------\n");
					band = 1;
                } else {
                	//id tarea, id trabajo, desc, tiempo, orden
                    if(a != NULL){
                    	(*pend)->id_tarea=atoi(a);
					}
                    a = strtok(NULL, d);
                    
                    if (a != NULL) {
                        (*pend)->id_trabajo=atoi(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        strcpy((*pend)->descripcion,a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        (*pend)->tiempo=atof(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        (*pend)->orden=atoi(a);
                    }
                    
                    a = strtok(NULL, d);
                    if (a != NULL) {
                        (*pend)->completado=atoi(a);
                    }
                    
					(*pend)->sgte = NULL;
					Apilar (pend, tope);
                    a = strtok(NULL, d);
                }
            }
            prueba = fgets(cadaux, sizeof(cadaux), p);
        }
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
	printf("Entro CARGA CLIENTES\n");
	CargaClientes (p, cli, antc, inicli);
	printf("Entro CARGA MATERIALES\n");
	CargaMateriales (p, mat, auxm, raiz);
	printf("Entro CARGA MATERIALESOP\n");
	CargaMaterialesOpcion (p, mato, antm, inimat);
	printf("Entro CARGA TAREAS\n");
	CargaTareas (p, tar, antt, auxt, initar);
	printf("Entro CARGA TECNICOS\n");
	CargaTecnicos (p, &tech, et, st);
	printf("Entro CARGA TRABAJOS\n");
	CargaTrabajos (p, &trab, ent, sal);
	printf("Entro CARGA OPCIONES\n");
	CargaOpciones (p, opc, anto, iniopc);
	printf("Entro CARGA PENDIENTES\n");
	CargaPendientes (p, &pend, tope);
}

void completarlista(struct opcionesfav**Inicio, struct opcion *ini_opciones){
	struct opcionesfav *nuevo=NULL,*aux=NULL;
	int encontro=0;
	aux=(*Inicio);
	while(ini_opciones!=NULL){ //recorre toda la lista de opciones
		while(encontro!=1 || aux!=NULL){ //recorre las opciones fav buscando la que coincide con el id opc que esta leyendo
			if(ini_opciones->id==aux->id_op){
				encontro=1;
			}else{
				aux=aux->sgte;
			}
		}
		if(encontro==0){
			nuevo=(struct opcionesfav *) malloc(sizeof(struct opcionesfav));
			if(nuevo!=NULL){
				nuevo->id_op=ini_opciones->id;
				nuevo->ventas=0;
				nuevo->sgte=NULL;
				insertaropfav(&nuevo,&(*Inicio));

			}else{
				printf("No hay espacio en memoria");
			}
		}
		encontro=0;
		ini_opciones=ini_opciones->sgte;
		aux=(*Inicio);
	}

}

void Desapilar (struct pendientes **nodo, struct pendientes **tp){
	(*nodo) = (*tp);
	(*tp) = (*tp)->sgte;
	(*nodo)->sgte = NULL;
}

void DescargaClientes( FILE *p, struct cliente *cli, struct cliente *inicli){
	if((p=fopen("clientes.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Clientes durante la Descarga |||||||\n");
	}else{
		while(inicli != NULL){
			fprintf(p, "%d;%s;%ld\n" ,  inicli->id, inicli->Nombre ,inicli->DNI);
			//fprintf(p, "%d;" , inicli->id);
			//fprintf(p, "%s\n" , inicli->Nombre);
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
		//id mat, id op, cant
		while(inimat != NULL){
			fprintf(p, "%d;", inimat->idmat);
			fprintf(p, "%d;", inimat->id_opcion);
			fprintf(p, "%d\n", inimat->cantidad);
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
		while(initar != NULL){
			//ORDEN: id tarea, id opcion, descripcion, orden, tiempo
			fprintf(p, "%d;", initar->id_tarea);
			fprintf(p, "%d;", initar->id_op);
			fprintf(p, "%s;", initar->descripcion);
			fprintf(p, "%d;", initar->orden);
			fprintf(p, "%f\n", initar->tiempo);
			printf("CARGO\n");
			initar=initar->sgte;
		}
		fclose(p);
	}
}

void DescargaTecnicos (FILE *p, struct tecnico **tech, struct tecnico **et, struct tecnico **st){
	p=NULL;
	if((p=fopen("tecnicos.txt","w"))==NULL){
		printf("||||||| Error de apertura de archivo Tecnicos durante la carga |||||||\n");
	}else{
		while(*st!=NULL){
			DesencolarTecnico (tech, et, st);
			fprintf(p, "%d;", (*tech)->id);
			fprintf(p, "%s;", (*tech)->Nombre);
			fprintf(p, "%ld\n", (*tech)->DNI);
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
			fprintf(p, "%d;", trab->id_trabajo);
			fprintf(p, "%d;", trab->id_opcion);
			fprintf(p, "%d;", trab->id_cliente);
			fprintf(p, "%d;", trab->id_tecnico);
			fprintf(p, "%d;", trab->cuatromtrs);
			fprintf(p, "%s;", trab->direccion);
			fprintf(p, "%d/%d/%d\n", trab->fc_fin.dia, trab->fc_fin.mes, trab->fc_fin.anio);
		}
		fclose(p);
	}
}

void DescargaOpciones (FILE *p, struct opcion *opc, struct opcion *iniopc){
	printf("Entro OPCIONES \n");
	p=NULL;
	if((p=fopen("opciones.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Opciones durante la carga |||||||\n");
	}else{
		printf("Entro OPCIONES ELSE \n");
		while(iniopc != NULL){
			printf("Entro OPCIONES  WHILE \n");
			fprintf(p, "%d;", iniopc->id);
			fprintf(p, "%s;", iniopc->Nombre);
			fprintf(p, "%f\n", iniopc->cHoraMObra);
			printf("CARGO \n");
			iniopc = iniopc->sgte;
			printf("RECORRIO \n");
		}
		printf("Salio OPCIONES WHILE \n");
		fclose(p);
	}
	printf("Salio OPCIONES \n");
}

void DescargaPendientes (FILE *p, struct pendientes **pend, struct pendientes **tope){
	p=NULL;
	if((p=fopen("pendientes.txt", "w"))==NULL){
		printf("||||||| Error de apertura de archivo Pendientes durante la carga |||||||\n");
	}else{
		while(*tope != NULL){
			Desapilar (pend, tope);
			//id tarea, id trabajo, desc, tiempo, orden, completado
			printf("\nPROBANDO: %d", (*pend)->id_tarea);
			fprintf(p, "%d;", (*pend)->id_tarea);
			fprintf(p, "%d;", (*pend)->id_trabajo);
			fprintf(p, "%s;", (*pend)->descripcion);
			fprintf(p, "%f;", (*pend)->tiempo);
			fprintf(p, "%d;", (*pend)->orden);
			fprintf(p, "%d\n", (*pend)->completado);
		}
		fclose(p);
	}
}

void DescargaSupremaDeEstructuras (FILE *p, struct cliente *inicli, struct materiales *raiz, struct materialesop *inimat, struct tarea *initar, struct tecnico **et, struct tecnico **st, struct trabajos *ent, struct trabajos *sal, struct opcion *iniopc, struct pendientes **tope){
	printf("Entro DESCARGAS \n");
	struct cliente *cli=NULL;
	struct materialesop *mato=NULL;
	struct tarea *tar=NULL, *auxt=NULL;
	struct tecnico *tech=NULL;
	struct trabajos *trab=NULL;
	struct opcion *opc=NULL;
	struct pendientes *pend=NULL, *tpaux=NULL;
	printf("Entro DESCARGAS CLIENTES\n");
	DescargaClientes (p, cli, inicli);
	if((p = fopen("materiales.txt", "w")) != NULL){
		fclose(p); //lo abri en w primero porque adentro de descargar arbol se abre en a+ y se guardan datos de la otra ejecucion. O sea, se escribe lo mismo varias veces
		printf("Entro DESCARGAS ARBOL\n");
		raiz = DescargarArbol (raiz, p);	
	}		
	printf("Entro DESCARGAS MATERIALESOP\n");
	DescargaMaterialesOpcion(p, mato, inimat);
	printf("Entro DESCARGAS TAREAS\n");
	DescargaTareas (p, tar, auxt, initar);
	printf("Entro DESCARGAS TECNICOS\n");
	DescargaTecnicos (p, &tech, et, st);
	printf("Entro DESCARGAS TRABAJOS\n");
	DescargaTrabajos (p, trab, ent, sal);
	printf("Entro DESCARGAS OPCIONES\n");
	DescargaOpciones (p, opc, iniopc);
	printf("Entro DESCARGAS PENDIENTES\n");
	DescargaPendientes (p, &pend, tope);
}

void DesencolarTecnico (struct tecnico **ds, struct tecnico **e, struct tecnico **s){
	if(*s!=NULL){
		(*ds) = (*s);
		(*s)=(*s)->sgte;
		if (*s == NULL){
			(*e) = NULL;	
		} 
	}else{
		(*e) = NULL;
	}
	(*ds)->sgte = NULL;
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
	(*e)->sgte = NULL;
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

void insertaropcionordenada(struct opcionesfav **auxL,struct opcionesfav **Lord){
	struct opcionesfav *ant=NULL;
	ant=buscaropanterior(*auxL,*Lord);
	if(ant != NULL){
		(*auxL)->sgte = ant->sgte;
		ant->sgte=(*auxL);
	}else{
		(*auxL)->sgte=(*Lord);
		(*Lord)=(*auxL);
	}

}

void insertaropfav(struct opcionesfav **nv, struct opcionesfav **ini){
	struct opcionesfav *auxi=NULL;
	auxi = (*ini);
	while(auxi->sgte!=NULL){
		auxi=auxi->sgte;
	}
	auxi->sgte=(*nv);
	auxi=NULL;

}

void ListadoDeOpciones (struct opcion **iniopcion, struct materiales **raiz, struct materialesop **inimat, struct tarea **initar_){
    printf("HUHA/n");
	int o, cont=0;
    printf("HUHA/n");
	double auxc=0, auxtiempo=0, auxcosto=0, total=0;
	printf("HUHA/n");
	struct opcion *aux = (*iniopcion);
	
	printf("Las opciones disponibles son: \n");
	while (aux != NULL){
		cont = cont + 1;
		printf("\n--------------------------\n");
		printf("Opcion %d: %s. \n", cont, aux->Nombre);
		printf("ID de la opcion: %d. \n", aux->id);
		auxcosto = OperacionCosto ((*raiz), aux->id, inimat);
		auxtiempo = OperacionTiempo(aux->id, *initar_);
		printf("El precio de mano de obra es: %.2f.\n", aux->cHoraMObra);
		printf("El precio de los materiales es: %.2f. \n", auxcosto);
		total = auxcosto + aux->cHoraMObra;
		printf("El tiempo total de las tareas es de: %.2f.\n", total);
		printf("---> El precio total de la opcion es: %.2f", total);
		printf("\n--------------------------\n");
		auxcosto=0;
		auxtiempo=0;
		total = 0;       //se reincia todo para que no se vayan acumulando a lo largo del recorrido
		aux = aux->sgte;
	}
}

void ListadoPendientes(int id_trabajo,struct pendientes **tope){
	struct pendientes *tpaux=NULL,*nodoaux=NULL;
	while((*tope)!=NULL){
		Desapilar(&nodoaux,tope);
		if(nodoaux->id_trabajo=id_trabajo){
			printf("\nLa Tarea: ");
			puts(nodoaux->descripcion);
			printf("\nDe ID: %i",nodoaux->id_tarea);
			if(nodoaux->completado == 0){
				printf("No ha sido completada");
				printf("\nDesea completar la tarea?");
				printf("\n1) Si");
				printf("\n0) No");
				printf("\n---> ");
				scanf("%i",&nodoaux->completado);
			}else{
				printf("Ha sido completada");
			}
		}
		Apilar(&nodoaux,&tpaux);
	}
	nodoaux=NULL;
	while(tpaux!=NULL){
		Desapilar(&nodoaux,&tpaux);
		Apilar(&nodoaux,tope);
	}
}

void ListadoDeTrabajosDeTecnicos(struct trabajos **e, struct trabajos **s, struct tecnico **et, struct tecnico **st, struct opcion **l, struct cliente **r) {
    int id, tec = 0;
    char nombre_op[30], nombre_cli[30];
    struct tecnico *nodo = NULL;
    struct trabajos *aux = NULL;
    struct trabajos *eAux = NULL, *sAux = NULL;

    printf("Ingrese el ID del tÃ©cnico para ver sus trabajos: \n");
    scanf("%d", &id);
    tec = BuscarIDTecnico(id, &nodo, et, st);
    if (tec == 0) {
        printf("El tÃ©cnico no existe.\n");
        // hacer que vaya al menÃº
    } else {
        while (!ColaVacia(*s)) {
            DesencolarTrabajos(&aux, e, s);
            if (aux->id_tecnico == id) {
                printf("ID del trabajo: %d \n", aux->id_trabajo);
                strcpy(nombre_op, BuscarNombreOpcion(aux->id_opcion, *l)); // Copia el nombre de la opciÃ³n a nombre_op
                printf("El nombre de la opciÃ³n es: %s \n", nombre_op);
                strcpy(nombre_cli, BuscarNombreCliente(aux->id_cliente, *r)); // Copia el nombre del cliente a nombre_cli
                printf("El nombre del cliente es: %s \n", nombre_cli);
                printf("La ubicaciÃ³n es: %s \n", aux->direccion);
                if (aux->cuatromtrs == 1) {
                    printf("Requiere trabajo en altura.\n");
                } else {
                    printf("No requiere trabajo en altura.\n");
                }
                EncolarTrabajos(&aux, &eAux, &sAux);
            } else {
                EncolarTrabajos(&aux, &eAux, &sAux);
            }
        }
        
        while(!ColaVacia(sAux)){
        	DesencolarTrabajos(&aux, &eAux, &sAux);
        	EncolarTrabajos(&aux, e, s);
		}
    }
}

void recorrerIRD(struct materiales *r){
	if(r!=NULL){
		recorrerIRD(r->izq);
		printf("\n------------------------");
		printf("\nId material: %d", r->id);
		printf("\nDescripcion material: %s", r->descripcion);
		printf("\nUnidad de medida: %s", r->unimed);
		printf("\nPrecio unitario: %f", r->costo_uni);
		printf("\nCantidad disponible: %.0f", r->cantidad);
		recorrerIRD(r->derch);
	}
}

/*5) Listar los trabajos realizados (finalizados) entre dos fechas. 
Imprimir por pantalla: Nro de trabajo, nombre opción, importe total de materiales, 
importe total de mano de obra (tomando en cuenta si se hizo a más de 4 mentros) e importe total parcial. 
Al final del listado, imprimir el importe total de todos los trabajos realizados.*/

void trabajosentre(struct trabajos *entrada,struct trabajos *salida,struct opcion *iniopc,struct materiales *raiz,struct materialesop *inimat,struct tarea *initar){
	struct trabajos *ini=NULL,*aux=NULL;
	double totalfinal=0,materiales=0,manodeobra=0,totalparcial=0;
	struct fecha fecha1_1,fecha2_2;
	long fecha1,fecha2,mayor,menor,fecha_trabajo;
	
	printf("\n\nIngrese el dia de la primer fecha: ");
	scanf("%i",&fecha1_1.dia);
	printf("\nIngrese el mes de la primer fecha: ");
	scanf("%i",&fecha1_1.mes);
	printf("\nIngrese el anio de la primer fecha: ");
	scanf("%i",&fecha1_1.anio);
	fflush(stdin);
	
	printf("\n\nIngrese el dia de la segunda fecha: ");
	scanf("%i",&fecha2_2.dia);
	printf("\nIngrese el mes de la segunda fecha: ");
	scanf("%i",&fecha2_2.mes);
	printf("\nIngrese el anio de la segunda fecha: ");
	scanf("%i",&fecha2_2.anio);
	fflush(stdin);
	
	fecha1=(fecha1_1.anio * 10000) + (fecha1_1.mes * 100) + fecha1_1.dia;
	fecha2=(fecha2_2.anio * 10000) + (fecha2_2.mes * 100) + fecha2_2.dia;
	
	if(fecha1>fecha2){
		mayor=fecha1;
		menor=fecha2;
	}else{
		if(fecha2>fecha1){
			mayor=fecha2;
			menor=fecha1;
		}else{
			mayor=fecha1;
			menor=fecha1;
		}
	}
	fflush(stdin);
	
	ini=salida; //Guarda el inicio de la cola de trabajos
	DesencolarTrabajos(&aux,&entrada,&salida);
	
	/*struct trabajos{ //Cola.
    int id_trabajo, id_opcion, opcion, cuatromtrs;
    char direccion[30];
    int id_tecnico, id_cliente;
	struct fecha fc_fin;
    struct trabajos *sgte;
    };
    
    ------------------------------------------------------------------------------------------------------------------
*/
	while(salida->id_trabajo!=ini->id_trabajo){
		fecha_trabajo=(aux->fc_fin.anio * 10000) + (aux->fc_fin.mes * 100) + aux->fc_fin.dia; 
		if(fecha_trabajo<=mayor && fecha_trabajo>=menor){
			materiales = OperacionCosto(raiz,aux->id_opcion, &inimat);
			printf("\nEl costo de materiales es: %f",materiales);
			manodeobra = (OperacionTiempo(aux->id_opcion, initar) * BuscarPrecioManodeObra(aux->id_opcion,iniopc)) + (BuscarPrecioManodeObra(aux->id_opcion,iniopc)*aux->cuatromtrs*0.80);
			printf("\nEl costo de mano de obra es: %f",manodeobra);
			totalparcial = materiales + manodeobra;
			printf("\nEl total parcial del trabajo es: %f",totalparcial);
			printf("\nID trabajo: %i",aux->id_trabajo);
			printf("\nID opcion: %i",aux->id_opcion);
			fflush(stdin);
		}
		EncolarTrabajos(&aux,&entrada,&salida);
		aux=NULL;
		DesencolarTrabajos(&aux,&entrada,&salida);
	}
}

double BuscarPrecioManodeObra(float id,struct opcion *ini){
	struct opcion *aux=NULL;
	while(aux->id!=id){
		aux=aux->sgte;
	}
	printf("\nNombre de la opcion: ");
	puts(aux->Nombre);
	fflush(stdin);
	return(aux->cHoraMObra);
	
}

void OpcionesMasVendidas(struct trabajos *entrada,struct trabajos *salida,struct opcion *iniopc){
	struct trabajos *ini=NULL,*aux=NULL;
	struct opcionesfav *L=NULL,*auxL=NULL,*Lord=NULL;
	int band=0,i;
	struct fecha fecha1_1,fecha2_2;
	long fecha1,fecha2,mayor,menor,fecha_trabajo;
	
	printf("Ingrese el dia de la primer fecha: ");
	scanf("%i",&fecha1_1.dia);
	printf("Ingrese el mes de la primer fecha: ");
	scanf("%i",&fecha1_1.mes);
	printf("Ingrese el anio de la primer fecha: ");
	scanf("%i",&fecha1_1.anio);
	fflush(stdin);
	
	printf("Ingrese el dia de la segunda fecha: ");
	scanf("%i",&fecha2_2.dia);
	printf("Ingrese el mes de la segunda fecha: ");
	scanf("%i",&fecha2_2.mes);
	printf("Ingrese el anio de la segunda fecha: ");
	scanf("%i",&fecha2_2.anio);
	fflush(stdin);
	
	fecha1=(fecha1_1.anio * 10000) + (fecha1_1.mes * 100) + fecha1_1.dia;
	fecha2=(fecha2_2.anio * 10000) + (fecha2_2.mes * 100) + fecha2_2.dia;
	
	if(fecha1>fecha2){
		mayor=fecha1;
		menor=fecha2;
	}else{
		if(fecha2>fecha1){
			mayor=fecha2;
			menor=fecha1;
		}else{
			mayor=fecha1;
			menor=fecha1;
		}
	}
	fflush(stdin);


	ini=salida; //Guarda el inicio de la cola de trabajos
	completarlista(&L,iniopc);//Ahora tenemos una lista donde cada nodo tiene un id op y un int acumulativo
	auxL=L;
	DesencolarTrabajos(&aux,&entrada,&salida);
	while(salida->id_trabajo!=ini->id_trabajo){//El while se va a detener cuando recorra toda la cola de trabajos
		while(band=!1){//Se va a detener cuando auxL este en la posicion donde debe incrementarse la cantidad de ventas
			if(aux->id_opcion!=auxL->id_op){
				auxL=auxL->sgte;
			}else{
				band=1;
			}
		}

		fecha_trabajo=(aux->fc_fin.anio * 10000) + (aux->fc_fin.mes * 100) + aux->fc_fin.dia; 

		if(fecha_trabajo<=mayor && fecha_trabajo>=menor){
			auxL->ventas++;//Se incrementa la cantidad de ventas en esa opcion
		}
					
		band=0;
		auxL=L;
		EncolarTrabajos(&aux,&entrada,&salida);
		aux=NULL;
		DesencolarTrabajos(&aux,&entrada,&salida);
	}

	/*auxL=L;
	while(auxL!=NULL){
		printf("\nLa cantidad de ventas de la opcion %i es: %i",auxL->id_op,auxL->ventas);
	}*/
	auxL=NULL;
	while(L!=NULL){
		auxL=L;
		L=L->sgte;
		auxL->sgte=NULL; //Se "Desenlista" el nodo y se vuelve a INSERTAR ordenado
		insertaropcionordenada(&auxL,&Lord);
	}

	printf("\nTOP 4 opciones mas vendidas: ");
	for(i=1;i<=4;i++){
		printf("\n%i) Opcion %i, con %i ventas",i,Lord->id_op,Lord->ventas);
		Lord=Lord->sgte;
	}
}
