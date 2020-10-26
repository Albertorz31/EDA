#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ESRTRUCTURAS DEL PROGRAMA */

typedef struct nodo{
	char nombreConsultorio[30];
	char especialidad[30];
	int capacidad;
	int pacientesActuales;
	int id;
	int distancia;
	int nodoDestino;
	struct nodo* siguiente;
}nodo;

typedef struct lista{
	nodo* inicio;
	nodo* final;
}lista;

typedef struct grafo{
	nodo *vertice;
	int nodos;
	double** adj;
}grafo;

///////////////////////////////////////////

/* FUNCIONES DEL PROGRAMA */

void iniciar();
void leerTextos();
void imprimirMenu();
void dijkstra(grafo G);
void encolar(lista* Q,nodo* c);
nodo* crearNodo(char* nombreConsultorio,char* especialidad,int capacidad,int pacientesActuales);
lista* crearLista();
nodo* minimo(lista* L);
void extraerNodo(lista *L,nodo *n);
void ajustarDistancia(grafo G,int u,int v);
void darAlta(grafo G);
void guardar(grafo G);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* MENU PRINCIPAL */

int main(){
	iniciar();
	return 0;
}

void iniciar(){
	leerTextos();
}

void opciones(grafo G){
	int salir=0,opcion=-1,i=0;
	while(salir==0){
		imprimirMenu();
		fflush(stdin);
		scanf("%d",&opcion);
		if(opcion==1) dijkstra(G);
		if(opcion==2) darAlta(G);
		if(opcion==3) guardar(G);
		if(opcion==4){
			salir=1;
			free(G.adj);
			free(G.vertice);
			i++;
		}
	}
	
}

void imprimirMenu(){
	printf("\n------------------------------\n");
	printf("Bienvenido al Bulto feliz\n");
	printf("Que desea hacer?\n");
	printf("1. Ingresar un paciente\n");
	printf("2. Dar de alta un paciente\n");
	printf("3. Guardar consultorios\n");
	printf("4. Salir\n");	
}

//////////////////////////////////////////////////////////////////////////////////////

/* Funcion que lee los dos textos ingresados y los almacena en la estructura grafo */

void leerTextos(){
	grafo G;
	int i,j,indice,rutas,tiempo,x,y;
	char numero[180],linea[180],nodo_origen[30],nodo_destino[30];
	char *consul;
	FILE* archivo_consultorio;
	archivo_consultorio= fopen("Consultorios.in","r");
	if(archivo_consultorio==NULL){
		printf("no se ha podido abrir el archivo");
		exit(1);
	}
	fscanf(archivo_consultorio,"%s",numero);
	G.nodos=atoi(numero);
	printf("el grafo tiene %i nodos\n",G.nodos);
	G.vertice=(nodo*)malloc(sizeof(nodo)*G.nodos);
	G.adj = (double**)malloc(sizeof(double*)*G.nodos);
	for(i=0;i < G.nodos;i++){
		G.adj[i] = (double*)malloc(sizeof(double)*G.nodos);
	}
	for(i=0;i< G.nodos;i++){
		for(j=0;j < G.nodos;j++){
			G.adj[i][j]=0;
		}
	}
	indice=0;
	while(!feof(archivo_consultorio)){
		fscanf(archivo_consultorio,"%s",linea);
		consul=linea;
		strcpy(G.vertice[indice].nombreConsultorio,consul);
		fscanf(archivo_consultorio,"%s",linea);
		consul=linea;
		strcpy(G.vertice[indice].especialidad,consul);
		fscanf(archivo_consultorio,"%s",linea);
		G.vertice[indice].capacidad=atoi(linea);
		fscanf(archivo_consultorio,"%s",linea);
		G.vertice[indice].pacientesActuales=atoi(linea);
		G.vertice[indice].id = indice;
		printf("(%i) %s, %s,capacidad: %i,pacientes actuales: %i\n",indice+1,G.vertice[indice].nombreConsultorio,G.vertice[indice].especialidad,G.vertice[indice].capacidad,G.vertice[indice].pacientesActuales);
		indice++;	
	}
	fclose(archivo_consultorio);
	FILE* archivo_aristas;
	archivo_aristas=fopen("DondeLlevarAlBulto.in","r");
	if(archivo_aristas==NULL){
		printf("no se ha podido abrir el archivo");
		exit(1);
	}
	fscanf(archivo_aristas,"%s",numero);
	rutas=atoi(numero);
	while(!feof(archivo_aristas)){
		fscanf(archivo_aristas,"%s",linea);
		consul=linea;
		strcpy(nodo_origen,consul);
		fscanf(archivo_aristas,"%s",linea);
		consul=linea;
		strcpy(nodo_destino,consul);
		fscanf(archivo_aristas,"%s",linea);
		tiempo=atoi(linea);
		for(i=0;i < G.nodos;i++){
			if(strcmp(G.vertice[i].nombreConsultorio,nodo_origen)==0){
				x = i;
			}
			if(strcmp(G.vertice[i].nombreConsultorio,nodo_destino)==0){
				y = i;
			}
		}
		G.adj[x][y] = tiempo;
	}
	fclose(archivo_aristas);
	opciones(G);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funcion que busca el camino minimo desde un nodo inicial a una especialidad especifica, para despues crear un archivo con los resultados */

void dijkstra(grafo G){
	int indice,correcto=0,i,j,nodoInicial,primero,distanciaP;
	char consultorioInicial[30],especialidad[30],destino[30];
	char *camino;
	lista* L= crearLista();
	nodo* u;
	while(correcto==0){
		indice=0;
		printf("Ingrese nombre del consultorio de partida\n");
		scanf("%s",&consultorioInicial);
		while(indice < G.nodos){
			if(strcmp(G.vertice[indice].nombreConsultorio,consultorioInicial)==0){
				correcto=1;
				nodoInicial=indice;
				break;
			}
			indice++;
		}
	}
	correcto=0;
	while(correcto==0){
		indice=0;
		printf("Ingrese especialidad que busca\n");
		scanf("%s",&especialidad);
		while(indice < G.nodos){
			if(strcmp(G.vertice[indice].especialidad,especialidad)==0){
				correcto=1;
				break;
			}
			indice++;
		}
	}
	for(i=0;i < G.nodos;i++){
		if(i==nodoInicial){
			G.vertice[i].distancia=0;
		}else{
			G.vertice[i].distancia=45000;
		}
		encolar(L,&G.vertice[i]);
	}
	while(L->inicio != NULL){
		u = minimo(L);
		extraerNodo(L,u);
		for(i=0;i < G.nodos;i++){
			if(G.adj[u->id][i] != 0){
				ajustarDistancia(G,u->id,i);
			}
		}	
	}
	primero=0;
	for(i=0;i<G.nodos;i++){
		if(strcmp(G.vertice[i].especialidad,especialidad)==0 && (G.vertice[i].pacientesActuales < G.vertice[i].capacidad)){
			if(primero==0){
				strcpy(destino,G.vertice[i].nombreConsultorio);
				distanciaP=G.vertice[i].distancia;
				primero=1;
			}else{
				if(G.vertice[i].distancia < distanciaP){
					strcpy(destino,G.vertice[i].nombreConsultorio);
					distanciaP=G.vertice[i].distancia;
				}
			}	
		}	
	}
	if(primero==0){
		strcpy(destino,"No hay ningun nodo que cumpla estos requisitos ");
	}
	FILE *archivo;
	archivo=fopen("WiiuuWiiuu.out","w");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	for(i=0;i<G.nodos;i++){
		if(strcmp(G.vertice[i].nombreConsultorio,destino)==0){
			fprintf(archivo,"%s %s %i\n\n",consultorioInicial,destino,G.vertice[i].distancia);
			G.vertice[i].pacientesActuales=G.vertice[i].pacientesActuales+1;
			fprintf(archivo,"Tiempo Total: %i",G.vertice[i].distancia);
		}if(strcmp(destino,"No hay ningun nodo que cumpla estos requisitos ")==0){
			fprintf(archivo,"No hay ningun nodo que cumpla estos requisitos ");
			fprintf(archivo,"Tiempo Total: 0");
		}
	}
	fclose(archivo);	
	printf("\nSe ha creado el archivo\n\n");	
}

void encolar(lista* Q,nodo* c){
	if(Q->inicio==NULL){
		Q->inicio=c;
		Q->final=c;
	}else{
		Q->final->siguiente=c;
		Q->final=c;
	}
	c->siguiente=NULL;
}

lista* crearLista(){
	lista *l;
	l = (lista*)malloc(sizeof(lista));
	l->inicio=NULL;
	l->final=NULL;
}

nodo* minimo(lista* L){
	nodo* cursor=L->inicio;
	nodo* aux=L->inicio;
	while(cursor != NULL){
		if(cursor->distancia < aux->distancia){
			aux = cursor;
		}
		cursor=cursor->siguiente;
	}
	return aux;
}

void extraerNodo(lista *L,nodo *n){
	if(L->inicio == n){
		if(L->final == n){
			L->inicio=NULL;
			L->final=NULL;
			return;
		}
		L->inicio=L->inicio->siguiente;
		return;
	}
	nodo* anterior = L->inicio;
	nodo* cursor = L->inicio->siguiente;
	while(cursor!=n){
		anterior=cursor;
		cursor=cursor->siguiente;
	}
	if(cursor==n){
		anterior->siguiente=cursor->siguiente;
	}
}

void ajustarDistancia(grafo G,int u,int v){
	if(G.vertice[v].distancia > G.vertice[u].distancia + G.adj[u][v]){
		G.vertice[v].distancia = G.vertice[u].distancia + G.adj[u][v];
			
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funcion que da de alta un paciente de un nodo determinado*/

void darAlta(grafo G){
	int correcto=0,indice,nodoInicial,i;
	char consultorioInicial[30];
	while(correcto==0){
		indice=0;
		printf("Ingrese nombre del consultorio del cual quiere dar de alta un paciente\n");
		scanf("%s",&consultorioInicial);
		while(indice < G.nodos){
			if(strcmp(G.vertice[indice].nombreConsultorio,consultorioInicial)==0){
				correcto=1;
				nodoInicial=indice;
				break;
			}
			indice++;
		}
	}
	for(i=0;i < G.nodos;i++){
		if(i == nodoInicial){
			G.vertice[i].pacientesActuales = G.vertice[i].pacientesActuales-1;
		}
		printf("(%i) %s, %s,capacidad: %i,pacientes actuales: %i\n",i+1,G.vertice[i].nombreConsultorio,G.vertice[i].especialidad,G.vertice[i].capacidad,G.vertice[i].pacientesActuales);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funcion que solo vuelve a imprimir los consultorios, ya que la actualizacion de pacientes se hace automaticamente */

void guardar(grafo G){
	int i;
	for(i=0;i < G.nodos;i++){
		printf("(%i) %s, %s,capacidad: %i,pacientes actuales: %i\n",i+1,G.vertice[i].nombreConsultorio,G.vertice[i].especialidad,G.vertice[i].capacidad,G.vertice[i].pacientesActuales);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7









