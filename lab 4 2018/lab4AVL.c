#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

/*ESTRUCTURAS DEL PROGRAMA*/

typedef struct Tabla{
	int numeroClase;
	int cantidadNodo;
	struct Arbol *puntero;
}Hash;

Hash *hash;


typedef struct Arbol{
	int numeroNodo;
	int equilibrio; //diferencia entre la altura del subarbol izquierdo y derecha de un nodo
	struct Arbol *derecho;
	struct Arbol *izquierdo;
	struct Arbol *padre;
}Nodo;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*FUNCIONES DEL PROGRAMA*/

void iniciar();
void leerTextos();
void agregarRaiz(int aleratorio,int dato);
void agregarArbol(Nodo **raiz,Nodo *nodoNuevo,int numero,int aleatorio);
void equilibrar(Nodo **raiz,Nodo *nodo,int rama,int operacion,int aleatorio);
void buscar(int valor,FILE *archivoSalida);
void rotacionSimpleIzquierda(Nodo **raiz,Nodo *nodo,int aleatorio);
void rotacionSimpleDerecha(Nodo **raiz,Nodo *nodo,int aleatorio);
void rotacionDobleIzquierda(Nodo **raiz,Nodo *nodo,int aleatorio);
void rotacionDobleDerecha(Nodo **raiz,Nodo *nodo,int aleatorio);
void eliminar(int valor,FILE *archivoSalida);
int borrar(Nodo **raiz,int numero,int aleatorio);
void liberarMemoria(Nodo **arbol);
void FREE(Nodo *arbol);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*MENU PRINCIPAL*/

int main(){
	iniciar();
	return 0;
}

void iniciar(){
	leerTextos();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion que lee ambos textos ingresados por el usuario, el primero almacena los datos en la tabla hash y la segunda es para poder realizar las operaciones
despues crear el archivo "salidasEsperadasListas" donde entrega si es TRUE o FALSE y el tiempo que se demoro en ejecutar para cada operacion*/

void leerTextos(){
	char linea[100],operacion[2];
	int i,numero;
	FILE *archivoDatos;
	Nodo* nodoRaiz=NULL;
	Nodo* nodoNuevo;
	 //funcion para generar numero aleatorio 
	archivoDatos = fopen("datos.txt","r");
	if (archivoDatos == NULL)
	{
		printf("No se pudo abrir el archivo");
		exit(1);
	}
	hash =(Hash*)malloc(997*sizeof(Hash));  //se asigna 997 de memoria a la tabla hash, que equivale a las 997 clases 
	for(i=0;i<997;i++){
		hash[i].numeroClase=i;
		hash[i].puntero=NULL;
		hash[i].cantidadNodo=0;
	}
	srand(time(NULL));
	while(!feof(archivoDatos)){
		int dato;
		numero = rand()%997;
		fscanf(archivoDatos,"%s",linea);
		dato=atoi(linea);
		if(hash[numero].puntero==NULL){
			hash[numero].cantidadNodo++;
			agregarRaiz(numero,dato);
		}else{
			nodoNuevo=(Nodo*)malloc(sizeof(Nodo));
			nodoRaiz=hash[numero].puntero;
			int nodoIngresar;
			nodoIngresar = dato;
			agregarArbol(&nodoRaiz,nodoNuevo,nodoIngresar,numero);
			hash[numero].cantidadNodo++;
		}		
	}
	fclose(archivoDatos);
	FILE *archivoOp;
	archivoOp = fopen("operaciones.txt","r");
	if (archivoOp == NULL)
	{
		printf("No se pudo abrir el archivo");
		exit(1);
	}
	FILE *archivoSalida;
	archivoSalida=fopen("salidasEsperadasAVL.txt","w");
	if(archivoSalida == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	fprintf(archivoSalida,"Tabla Hash implementada con arboles AVL\n");	
	while(!feof(archivoOp)){
		int valor,j;
		clock_t inicio = clock();
		fscanf(archivoOp,"%s",operacion);
		fscanf(archivoOp,"%s",linea);
		valor = atoi(linea);
		if(strcmp(operacion,"B")==0){
			buscar(valor,archivoSalida);
		}else if(strcmp(operacion,"E")==0){
			eliminar(valor,archivoSalida);
		}else if(strcmp(operacion,"A")==0){
			numero = rand() %997;
			if(hash[numero].puntero==NULL){
				agregarRaiz(numero,valor);
			}else{
				nodoNuevo=(Nodo*)malloc(sizeof(Nodo));
			    nodoRaiz=hash[numero].puntero;
			    int nodoIngresar;
			    nodoIngresar = valor;
			    agregarArbol(&nodoRaiz,nodoNuevo,nodoIngresar,numero);
			    hash[numero].cantidadNodo++;			
			}
			fprintf(archivoSalida,"TRUE ");
		}
		for(j=0;j< 1000000;j++){
			j++;
		}
		clock_t fin= clock();
		float tiempo = ((double)fin - inicio)/CLOCKS_PER_SEC;
		fprintf(archivoSalida,"Tiempo: %f en segundos\n",tiempo);	
	}
	fclose(archivoOp);
	fclose(archivoSalida);
	for(i=0;i<997;i++){
		Nodo *Raiz=NULL;
		if(hash[i].puntero!=NULL){
			Raiz = hash[i].puntero;
			liberarMemoria(&Raiz);
		}
	}
	printf("Se ha creado archivo salidasEsperadasAVL.txt con las respuestas de cada operacion\n");
}

/* Funcion para liberar memoria, es decir, eliminar el arbol indicado*/

void liberarMemoria(Nodo **arbol){
	FREE(*arbol);
}

void FREE(Nodo *arbol){
	if(arbol->izquierdo!=NULL){
		FREE(arbol->izquierdo);
	}
	if(arbol->derecho!=NULL){
		FREE(arbol->derecho);
	}
	if(arbol->derecho==NULL && arbol->izquierdo==NULL){
		free(arbol);
		return;
	}
}

	
/*Funcion que crear la raiz del arbol correspodiente, esto sucede si hash[] en esa posicion apunta a nulo*/

void agregarRaiz(int aleatorio,int dato){
	Nodo* arbol;
	arbol=(Nodo*)malloc(sizeof(Nodo));
	arbol->numeroNodo=dato;
	arbol->padre=NULL;
	arbol->izquierdo=NULL;
	arbol->derecho=NULL;
	arbol->equilibrio=0;
	hash[aleatorio].puntero=arbol;	
}

/*Funcion que agrega nodo a un arbol que ya tiene como minimo una raiz*/

void agregarArbol(Nodo **raiz,Nodo *nodoNuevo,int numero,int aleatorio){
	Nodo* actual;
	Nodo* padre;
	actual=(*raiz);
	while(actual!=NULL && numero!=actual->numeroNodo) {
		padre=actual;
		if(numero > actual->numeroNodo){
			actual=actual->derecho;
		}else{
			actual=actual->izquierdo;
		}
	}
	if(numero > padre->numeroNodo){
		padre->derecho=nodoNuevo;
		nodoNuevo->numeroNodo=numero;
		nodoNuevo->derecho=NULL;
		nodoNuevo->izquierdo=NULL;
		nodoNuevo->padre=padre;
		nodoNuevo->equilibrio=0;
		equilibrar(raiz,padre,1,1,aleatorio);	
	}else if(numero < padre->numeroNodo){
		padre->izquierdo=nodoNuevo;
		nodoNuevo->numeroNodo=numero;
		nodoNuevo->derecho=NULL;
		nodoNuevo->izquierdo=NULL;
		nodoNuevo->padre=padre;
		nodoNuevo->equilibrio=0;
		equilibrar(raiz,padre,0,1,aleatorio);
	}	
}

/*Busca el dato en una el arreglo hash, con ya encontra uno en algun arbol devolvera verdadero, si no encuentra ninguno devuelve  falso*/

void buscar(int valor,FILE *archivoSalida){
	int i,verdadero;
	Nodo* raiz;
	for(i=0;i<997;i++){
		if(hash[i].puntero !=NULL){
			raiz = hash[i].puntero;
			verdadero=traspasar(&raiz,valor);
			if(verdadero==1){
				break;
			}
		}
	}
	if(verdadero==0){
		fprintf(archivoSalida,"FALSE ");
	}else if(verdadero==1){
		fprintf(archivoSalida,"TRUE ");
	}
}

int traspasar(Nodo **arbol,int valor){
	int resultado;
	resultado=buscarInorden(*arbol,valor);
	return resultado;
}

int buscarInorden(Nodo *arbol,int dato){
	Nodo *actual;
	actual=arbol;
	while(actual!=NULL){
		if(dato== actual->numeroNodo){
			return 1;
		}else if(dato < actual->numeroNodo){
			actual = actual->izquierdo;
		}else if(dato > actual->numeroNodo){
			actual = actual->derecho;
		}
	}
	return 0;
}

/*Funcion donde elimina un nodo de un arbol AVL*/

void eliminar(int valor,FILE *archivoSalida){
	int i,verdadero;
	Nodo* raiz;
	for(i=0;i<997;i++){
		if(hash[i].puntero !=NULL){
			raiz = hash[i].puntero;
			verdadero=borrar(&raiz,valor,i);
			if(verdadero==1){
				break;
			}
		}
	}
	if(verdadero==0){
		fprintf(archivoSalida,"FALSE ");
	}else{
		fprintf(archivoSalida,"TRUE ");
	}
}

int borrar(Nodo **raiz,int numero,int aleatorio){
	Nodo *padre=NULL;
	Nodo *actual;
	Nodo *node;
	int aux;
	actual=(*raiz);
	if(numero == actual->numeroNodo && actual->derecho==NULL && actual->izquierdo==NULL){
		hash[aleatorio].puntero=NULL;
		return 1;
	}
	while(actual!=NULL){
		if(numero==actual->numeroNodo){
			if(actual->izquierdo==NULL && actual->derecho==NULL){
				if(padre!=NULL){
					if(padre->derecho==actual){
						padre->derecho=NULL;
					}else if(padre->izquierdo==actual){
						padre->izquierdo=NULL;
					}
				}
				free(actual);
				actual=NULL;
				if((padre->derecho == actual && padre->equilibrio==-1) || (padre->izquierdo==actual && padre->equilibrio==1)){
					padre->equilibrio=0;
					actual=padre;
					padre=actual->padre;
				}
				if(padre!=NULL){
					if(padre->derecho==actual){
						equilibrar(raiz,padre,1,0,aleatorio);
					}else{
						equilibrar(raiz,padre,0,0,aleatorio);
					}
				}
				return;
			}else{
				padre=actual;
				if(actual->derecho!=NULL){
					node=actual->derecho;
					while(node->izquierdo!=NULL){
						padre=node;
						node=node->izquierdo;
					}
				}else{
					node=actual->izquierdo;
					while(node->derecho!=NULL){
						padre=node;
						node=node->derecho;
					}
				}
				aux=actual->numeroNodo;
				actual->numeroNodo=node->numeroNodo;
				node->numeroNodo=aux;
				actual=node;	
			}
			return 1;	
		}else{
			padre=actual;
			if(numero > actual->numeroNodo){
				actual=actual->derecho;
			}else if(numero < actual->numeroNodo){
				actual=actual->izquierdo;
			}		
		}		
	}
	return 0;	
}

/*Funcion Equilibrar: funcion que equilibra el arbol cuando sufre algun desequilibrio, al insertar o eliminar un nodo, aplicando la rotacion 
adecuada, se recorre el camino desde el nodo insertado o eliminado hacia el nodo raiz*/

void equilibrar(Nodo **raiz,Nodo *newNodo,int rama,int operacion,int aleatorio){
	int salir=0;
	while(newNodo!=NULL && salir!=1){
		if(operacion==1){//insertar nodo
			if(rama==0){
				newNodo->equilibrio++;
			}else{
				newNodo->equilibrio--;
			}
		}else{//eliminar nodo
			if(rama==0){
				newNodo->equilibrio--;
			}else{
				newNodo->equilibrio++;
			}
		}
		if(newNodo->equilibrio==0){
			salir=1;
		}else if(newNodo->equilibrio==2){
			if(newNodo->izquierdo->equilibrio==-1){
				rotacionDobleDerecha(raiz,newNodo,aleatorio);
			}else{
				rotacionSimpleDerecha(raiz,newNodo,aleatorio);
			}
			salir=1;
		}else if(newNodo->equilibrio==-2){
			if(newNodo->derecho->equilibrio==1){
				rotacionDobleIzquierda(raiz,newNodo,aleatorio);
			}else{
				rotacionSimpleIzquierda(raiz,newNodo,aleatorio);
			}
			salir=1;
		}
		if(newNodo->padre!=NULL){
			if(newNodo->padre->derecho==newNodo){
				rama=1;
			}else{
				rama=0;
		    }
		}
		newNodo=newNodo->padre;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*ROTACIONES*/

/*Funcion Rotacion simple a la izquierda: esta funcion lo que hace es rotar el arbol hacia la izquierda, se usará cuando el subarbol derecho
de un nodo sea 2 unidades mas alto que el izquierdo, es decir, cuando el equilibrio es de -2 y la raiz del subarbol derecho tenga un 
equilibrio de -1 o 0*/

void rotacionSimpleIzquierda(Nodo **raiz,Nodo *nodo,int aleatorio){
	Nodo *Padre=nodo->padre;
	Nodo *nodoA=nodo;
	Nodo *nodoB=nodoA->derecho;
	Nodo *nodoC=nodoB->izquierdo;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoB;
		}else{
			Padre->izquierdo=nodoB;
		}
	}else{
		(*raiz)=nodoB;
		hash[aleatorio].puntero=nodoB;
		
	}
	nodoA->derecho=nodoC;
	nodoB->izquierdo=nodoA;
	nodoA->padre=nodoB;
	if(nodoC!=NULL){
		nodoC->padre=nodoA;
	}
	nodoB->padre=Padre;
	nodoA->equilibrio=0;
	nodoB->equilibrio=0;	
}

/*Funcion Rotacion simple a la derecha: esta funcion lo que hace es rota el arbol hacia la derecha, se usará cuando el subarbol izquierdo
de un nodo sea 2 unidades mas alto que el derecho, es decir, cuando el equilibrio es de 2 y la raiz del subarbol izquierdo tenga un 
equilibrio de 1 o 0*/

void rotacionSimpleDerecha(Nodo **raiz,Nodo *nodo,int aleatorio){
	Nodo *Padre = nodo->padre;
	Nodo *nodoA = nodo;
	Nodo *nodoB = nodoA->izquierdo;
	Nodo *nodoC = nodoB->derecho;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoB;
		}else{
			Padre->izquierdo=nodoB;
		}
	}else{
		(*raiz)=nodoB;
		hash[aleatorio].puntero=nodoB;
	}
	nodoA->izquierdo=nodoC;
	nodoB->derecho=nodoA;
	nodoA->padre=nodoB;
	if(nodoC!=NULL){
		nodoC->padre=nodoA;
	}
	nodoB->padre=Padre;
	nodoA->equilibrio=0;
	nodoB->equilibrio=0;
}

/*Funcion Rotacion doble a la izquierda: esta funcion realiza dos rotaciones simples, primero rotacion simple a la derecha y despues
rotacion simple a la izquierda, se usará cuando el subrbol derecho de un nodo sea 2 unidades mas alto que el izquierdo, es decir, cuando
el equilibrio es de -2 y la raiz del subarbol derecho tenga un equilibrio de 1, es decir, que este cargado a la izquierda*/

void rotacionDobleIzquierda(Nodo **raiz,Nodo *nodo,int aleatorio){
	Nodo *Padre = nodo->padre;
	Nodo *nodoA = nodo;
	Nodo *nodoB = nodoA->derecho;
	Nodo *nodoC = nodoB->izquierdo;
	Nodo *nodoCI = nodoC->izquierdo;
	Nodo *nodoCD = nodoC->derecho;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoC;
		}else{
			Padre->izquierdo=nodoC;
		}
	}else{
		(*raiz)=nodoC;
		hash[aleatorio].puntero=nodoC;
	}
	nodoA->derecho = nodoCI;
	nodoB->izquierdo = nodoCD;
	nodoC->izquierdo = nodoA;
	nodoC->derecho = nodoB;
	nodoC->padre=Padre;
	nodoA->padre = nodoC;
	nodoB->padre = nodoC;
	if(nodoCI!=NULL){
		nodoCI->padre=nodoA;
	}
	if(nodoCD!=NULL){
		nodoCD->padre=nodoB;
	}
	switch(nodoC->equilibrio){
		case 1:
		    nodoA->equilibrio=0;
		    nodoB->equilibrio=1;
		    break;
		case 0:
			nodoA->equilibrio=0;
			nodoB->equilibrio=0;
			break;
		case -1:
			nodoA->equilibrio=-1;
			nodoB->equilibrio=0;
			break;	         
	}
	nodoC->equilibrio=0;	
}

/*Funcion Rotacion doble a la derecha: esta funcion realiza 2 rotaciones simples, primero rotacion simple a la izquierda y despues
rotacion simple a la derecha, se usará cuando el subarbol izquierdo de un nodo sea 2 unidades mas alto que el derecho, es decir, cuando
su equilibrio sea de 2 y la raiz del subarbol izquierdo tenga un equilibrio de 1, es decir, que este cargado a la derecha*/

void rotacionDobleDerecha(Nodo **raiz,Nodo *nodo,int aleatorio){
	Nodo *Padre= nodo->padre;
	Nodo *nodoA = nodo;
	Nodo *nodoB = nodoA->izquierdo;
	Nodo *nodoC = nodoB->derecho;
	Nodo *nodoCI = nodoC->izquierdo;
	Nodo *nodoCD = nodoC->derecho;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoC;
		}else{
			Padre->izquierdo=nodoC;
		}
	}else{
		(*raiz) = nodoC;
		hash[aleatorio].puntero=nodoC;
	}
	nodoB->derecho=nodoCI;
	nodoA->izquierdo=nodoCD;
	nodoC->izquierdo=nodoB;
	nodoC->derecho=nodoA;
	nodoC->padre=Padre;
	nodoA->padre=nodoC;
	nodoB->padre=nodoC;
	if(nodoCI!=NULL){
		nodoCI->padre=nodoB;
	}
	if(nodoCD!=NULL){
		nodoCD->padre=nodoA;
	}
	switch(nodoC->equilibrio){
		case 1:
			nodoB->equilibrio=0;
			nodoA->equilibrio=1;
			break;
		case 0:
			nodoB->equilibrio=0;
			nodoA->equilibrio=0;
			break;
		case -1:
			nodoB->equilibrio=-1;
			nodoA->equilibrio=0;
			break;
	}
	nodoC->equilibrio=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




















