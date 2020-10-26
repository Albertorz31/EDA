#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


/*ESTRUCTURAS DEL PROGRAMA*/

typedef struct Tabla{
	int numeroClase;
	struct Lista *puntero;
}Hash;

Hash *hash;

typedef struct Lista{
	int dato;
	struct Lista *siguiente;
}List;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*FUNCIONES DEL PROGRAMA*/

void iniciar();
void leerTextos();
void agregarLista(int aletorio,int dato);
void buscar(int valor,FILE *archivoSalida);
void borrar(int valor,FILE *archivoSalida);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*MENU PRINCIPAL*/

int main(){
	iniciar();
	return 0;
}

void iniciar(){
	leerTextos();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion que lee ambos textos ingresados por el usuario, el primero almacena los datos en la tabla hash y la segunda es para poder realizar las operaciones
despues crear el archivo "salidasEsperadasListas" donde entrega si es TRUE o FALSE y el tiempo que se demoro en ejecutar para cada operacion*/

void leerTextos(){
	int i,numero;
	char linea[100],operacion[2];
	FILE *archivoDatos;
	archivoDatos = fopen("datos.txt","r");
	if (archivoDatos == NULL)
	{
		printf("No se pudo abrir el archivo");
		exit(1);
	}
	hash =(Hash*)malloc(997*sizeof(Hash));  //se asigna 997 de memoria a la tabla hash, que equivale a las 997 clases 
	for(i=0;i<997;i++){
		hash[i].numeroClase=i;
		hash[i].puntero = NULL;
	}
	srand(time(NULL)); //funcion para generar numero aleatorio 
	while(!feof(archivoDatos)){
		int dato;
	    numero = rand() % 997; // numero es equivalente al recorrido de la funcion h(x) de la tabla hash , que equivale a la clase seleccionada
		fscanf(archivoDatos,"%s",linea);
		dato = atoi(linea);
		agregarLista(numero,dato);		
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
	archivoSalida=fopen("salidasEsperadasListas.txt","w");
	if(archivoSalida == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	fprintf(archivoSalida,"Tabla Hash implementada con listas enlazadas\n");
	while(!feof(archivoOp)){
		int valor,j;
		clock_t inicio = clock();
		fscanf(archivoOp,"%s",operacion);
		fscanf(archivoOp,"%s",linea);
		valor = atoi(linea);
		if(strcmp(operacion,"B")==0){
			buscar(valor,archivoSalida);
		}else if(strcmp(operacion,"E")==0){
			borrar(valor,archivoSalida);
		}else if(strcmp(operacion,"A")==0){
			numero = rand() %997;
			agregarLista(numero,valor);
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
		List* actual=NULL;
		List* aux=NULL;
		if(hash[i].puntero!=NULL){
			actual=hash[i].puntero;
			while(actual!=NULL){
				aux=actual;
				actual=actual->siguiente;
				free(aux);
			}
		}
	}
	printf("Se ha creado archivo salidasEsperadasListas.txt con las respuestas de cada operacion\n");
}

/*Funcion que agrega un nuevo nodo a la lista enlazada de una clase especifica*/

void agregarLista(int aleatorio,int dato){
	List* actual;
	actual = hash[aleatorio].puntero;
	if(hash[aleatorio].puntero==NULL){
		List* nuevo;
		nuevo=(List*)malloc(sizeof(List));
		nuevo->dato=dato;
		nuevo->siguiente=NULL;
		hash[aleatorio].puntero=nuevo;
		hash[aleatorio].puntero->siguiente=NULL;	
	}else{
		while(actual !=NULL){
			if(actual->siguiente == NULL){
				List* nodo;
				nodo=(List*)malloc(sizeof(List));
				nodo->dato=dato;
				actual->siguiente = nodo;
				actual->siguiente->siguiente=NULL;
				break;	
			}else{
				actual = actual->siguiente;
			}
		}
	}
	
}

/* Funcion que busca el dato dentro de la tabla hash, si este se encuentra imprimira un TRUE, si no un FALSE, los 2 con el tiempo de ejecucion*/

void buscar(int valor,FILE *archivoSalida){
	List* actual;
	int i,j=0,verdadero=0,repetido=0;
	for(i=0;i<997;i++){
		if(hash[i].puntero !=NULL){
			actual = hash[i].puntero;
			if(hash[i].puntero->dato==valor && repetido==0){
				verdadero=1;
				repetido=1;
				fprintf(archivoSalida,"TRUE ");
			}else{
				actual = actual->siguiente;
				while(actual!=NULL){
					if(actual->dato == valor && repetido== 0){
						verdadero=1;
						repetido=1;
						fprintf(archivoSalida,"TRUE ");
					}else{
						actual = actual->siguiente;
					}			
				}
				
			}
		}
	}
	if(verdadero==0){
		fprintf(archivoSalida,"FALSE ");
	}
}

/* Funcion que borra un nodo en la lista de una clase en especifico donde se encuentra el dato,
 si este se encuentra imprimira un TRUE, si no un FALSE, los 2 con el tiempo de ejecucion*/

void borrar(int valor,FILE *archivoSalida){
	List* actual;
	List* sup_ficha;
	int i,verdadero=0;
	for(i=0;i<997;i++){
		if(hash[i].puntero !=NULL){
			actual= hash[i].puntero;
			if(hash[i].puntero->dato==valor){
				sup_ficha= hash[i].puntero;
				hash[i].puntero = hash[i].puntero->siguiente;
				free(sup_ficha);
				verdadero=1;
				fprintf(archivoSalida,"TRUE ");
			}else{
				actual=actual->siguiente;
				while(actual!=NULL){
					if(actual->siguiente==NULL){
						if(actual->dato==valor){
							actual=NULL;
							verdadero=1;
							break;
						}else{
							break;
						}
					}
					if(actual->siguiente->dato==valor){
						sup_ficha=actual->siguiente;
						actual->siguiente=actual->siguiente->siguiente;
						free(sup_ficha);
						verdadero=1;
				        fprintf(archivoSalida,"TRUE ");
					}else{
						actual=actual->siguiente;
					}
				}
			}	
		}
	}
	if(verdadero==0){
		fprintf(archivoSalida,"FALSE ");
	}
}

