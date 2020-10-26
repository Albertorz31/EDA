#include<string.h>
#include<stdlib.h>
#include<stdio.h>

/*ESTRUCTURA DEL PROGRAMA*/

typedef struct nodo{
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[4],fecha[11];
	int numeroFicha;
	int mes;
	int equilibrio; //diferencia entre la altura del subarbol izquierdo y derecha de un nodo
	struct nodo *derecho;
	struct nodo *izquierdo;
	struct nodo *padre;
}Ficha;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*FUNCIONES DEL PROGRAMA*/

void iniciar();
void opciones(Ficha **Arbol,int numero);
void imprimirMenu();
void imprimirFicha(Ficha *carac);
void InOrden(Ficha *nodo);
void InOrdenBuscar(Ficha *aux,char dato[]);
void InOrdenArchivo(Ficha *aux,int mes,FILE *archivo);
void LiberarMemoria(Ficha *arbol);
void PreOrden(Ficha *nodo);
void PostOrden(Ficha *nodo);
void leerTexto();
int agregarTeclado(Ficha **raiz,int numero);
void agregar(Ficha **raiz,Ficha *fich,int numero);
void eliminar(Ficha **raiz,int numero);
void modificar(Ficha **Arbol);
void buscar(Ficha **Arbol);
void equilibrar(Ficha **raiz,Ficha *nodo,int rama,int operacion);
void rotacionSimpleIzquierda(Ficha **raiz,Ficha *nodo);
void rotacionSimpleDerecha(Ficha **raiz,Ficha *nodo);
void rotacionDobleIzquierda(Ficha **raiz,Ficha *nodo);
void rotacionDobleDerecha(Ficha **raiz,Ficha *nodo);
void imprimirArchivo(Ficha **arbol);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*MENU PRINCIPAL*/

int main(){
	iniciar();
	return 0;
}

void iniciar(){
	leerTexto();
}

void opciones(Ficha **Arbol,int numero){
	Ficha *aux;
	int salir=0,opcion=-1;
	while(salir==0){
		printf(" Recorrido en InOrden:\n");
		InOrden(*Arbol);
		imprimirMenu();
		imprimirArchivo(Arbol);
		fflush(stdin);
		scanf("%d",&opcion);
		if(opcion==1)numero=agregarTeclado(Arbol,numero);
		if(opcion==2)eliminar(Arbol,numero);
		if(opcion==3)modificar(Arbol);
		if(opcion==4)buscar(Arbol);
		if(opcion==5){
			printf("\nRecorrido en PreOrden:\n");
			PreOrden(*Arbol);
		}
		if(opcion==6){
			printf("\nRecorrido en PostOrden:\n");
			PostOrden(*Arbol);
		}
		if(opcion==7){
			salir=1;
			LiberarMemoria(*Arbol);
		}	
	}
}	
	
void imprimirMenu(){
	printf("\n------------------------------\n");
	printf("Bienvenido al Bulto feliz\n");
	printf("Que desea hacer?\n");
	printf("Seleccione un numero\n");
	printf("1. Agregar registro\n");
	printf("2. Eliminar registro\n");
	printf("3. Modificar registro\n");
	printf("4. Buscar registro\n");
	printf("5. Recorrido en PreOrden\n");
	printf("6. Recorrido en PostOrden\n");
	printf("7. Salir\n");	
}

void imprimirFicha(Ficha *carac){
	printf("Ficha: (%i) %s %s %s %s %s %s %s %s %s %s\n",carac->numeroFicha,carac->nombre,carac->apellidop,carac->apellidom,carac->nomMascota,carac->especie,carac->edad,carac->telefono,carac->atenciones,carac->vacunas,carac->fecha);
}

void InOrden(Ficha *nodo){
	if(nodo->izquierdo!=NULL){
		InOrden(nodo->izquierdo);
	}
	imprimirFicha(nodo);
	if(nodo->derecho!=NULL){
		InOrden(nodo->derecho);
	}
}

void LiberarMemoria(Ficha *arbol){
	if(arbol->izquierdo!=NULL){
		LiberarMemoria(arbol->izquierdo);
	}
	if(arbol->derecho!=NULL){
		LiberarMemoria(arbol->derecho);
	}
	if(arbol->derecho==NULL && arbol->izquierdo==NULL){
		free(arbol);
		return;
	}
}

void PreOrden(Ficha *nodo){
	imprimirFicha(nodo);
	if(nodo->izquierdo!=NULL){
		PreOrden(nodo->izquierdo);
	}
	if(nodo->derecho!=NULL){
		PreOrden(nodo->derecho);
	}
}

void PostOrden(Ficha *nodo){
	if(nodo->izquierdo!=NULL){
		PreOrden(nodo->izquierdo);
	}
	if(nodo->derecho!=NULL){
		PreOrden(nodo->derecho);
	}
	imprimirFicha(nodo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion que lee el texto ingresado por el usuario y los almacena es la estructura Ficha mediante arboles AVL*/

void leerTexto(){
	char linea[192];
	char *num,*temp; 
	int cont=0,numero=1,mes;
	FILE* archivo;	
	Ficha* Arbol=NULL;
	Ficha* fich;
	archivo = fopen("Bultos.in","r");
	if(archivo==NULL){
		printf("No se puedo abrir el archivo");
		exit(1);
	}
	while(!feof(archivo)){
		fich=(Ficha*)malloc(sizeof(Ficha));
		if(cont==0){
			fscanf(archivo,"%s",linea);
			cont++;
		}
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->nombre,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->apellidop,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->apellidom,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->nomMascota,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->especie,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->edad,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->telefono,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->atenciones,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->vacunas,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich->fecha,temp);
		num=strtok(temp,"/");
		num=strtok(NULL,"/");
		fich->mes=atoi(num);
		if(Arbol==NULL){
			fich->numeroFicha=numero;
			fich->izquierdo=NULL;
			fich->derecho=NULL;
			fich->padre=NULL;
			fich->equilibrio=0;
			Arbol=fich;
		}else{
			agregar(&Arbol,fich,numero);		
		}
		numero++;		
	}
	fclose(archivo);
	opciones(&Arbol,numero);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion agregar: agrega un nuevo nodo al arbol, el nodo lo ingresa a continuacion del ultimo nodo visitado, ingresa el nodo en el
lado izquierdo o derecho dependiendo si es menor o mayor, despues de insertar hay que reequilibrar el arbol*/

void agregar(Ficha **raiz,Ficha *fich,int numero){
	Ficha *actual;
	Ficha *padre;
	actual=(*raiz);
	while(actual!=NULL && numero!=actual->numeroFicha){
		padre=actual;
		if(numero > actual->numeroFicha){
			actual=actual->derecho;
		}else{
			actual=actual->izquierdo;
		}
	}
	if(numero > padre->numeroFicha){
		padre->derecho=fich;
		fich->numeroFicha=numero;
		fich->izquierdo=NULL;
		fich->derecho=NULL;
		fich->padre=padre;
		fich->equilibrio=0;
		equilibrar(raiz,padre,1,1);	
	}
}

/*Funcion agregar por teclado: el usuario escribe los datos por teclados con los cuales se crea un nodo que es agregado al arbol*/

int agregarTeclado(Ficha **raiz,int numero){
	Ficha *nuevoRegistro;
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[3],fecha[11];
	char *num;
	nuevoRegistro=(Ficha*)malloc(sizeof(Ficha));
	nuevoRegistro->padre=NULL;
	nuevoRegistro->izquierdo=NULL;
	nuevoRegistro->derecho=NULL;
	printf("Ingrese nombre del cliente:\n");
	scanf("%s",&nombre);
	strcpy(nuevoRegistro->nombre,nombre);
	printf("Ingrese el apellido paterno:\n");
	scanf("%s",&apellidop);
	strcpy(nuevoRegistro->apellidop,apellidop);
	printf("Ingrese el apellido materno:\n");
	scanf("%s",&apellidom);
	strcpy(nuevoRegistro->apellidom,apellidom);
	printf("Ingrese el nombre de la mascota:\n");
	scanf("%s",&nomMascota);
	strcpy(nuevoRegistro->nomMascota,nomMascota);
	printf("Ingrese la especie:\n");
	scanf("%s",&especie);
	strcpy(nuevoRegistro->especie,especie);
	printf("Ingrese edad:\n");
	scanf("%s",&edad);
	strcpy(nuevoRegistro->edad,edad);
	printf("Ingrese telefono:\n");
	scanf("%s",&telefono);
	strcpy(nuevoRegistro->telefono,telefono);
	printf("Ingrese numero de atenciones:\n");
	scanf("%s",&atenciones);
	strcpy(nuevoRegistro->atenciones,atenciones);
	printf("Ingrese si tiene vacunas:\n");
	scanf("%s",&vacunas);
	strcpy(nuevoRegistro->vacunas,vacunas);
	printf("Ingrese la fecha:\n");
	scanf("%s",&fecha);
	strcpy(nuevoRegistro->fecha,fecha);
	num=strtok(fecha,"/");
	num=strtok(NULL,"/");
	nuevoRegistro->mes=atoi(num);
	agregar(raiz,nuevoRegistro,numero);	
	numero++;
	return numero;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion eliminar: elimina el dato solicitado si esta en el arbol*/

void eliminar(Ficha **raiz,int numero){
	Ficha *padre=NULL;
	Ficha *actual;
	Ficha *nodo;
	int aux,opcion;
	actual=(*raiz);
	if(numero<=1){
		printf("No se pueden eliminar mas registro, se debe quedar con uno\n");
	}
	printf("Cual registro desea eliminar?\n");
	InOrden(*raiz);
	scanf("%i",&opcion);
	while(actual!=NULL){
		if(opcion==actual->numeroFicha){
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
						equilibrar(raiz,padre,1,0);
					}else{
						equilibrar(raiz,padre,0,0);
					}
				}
				return;
			}else{
				padre=actual;
				if(actual->derecho!=NULL){
					nodo=actual->derecho;
					while(nodo->izquierdo!=NULL){
						padre=nodo;
						nodo=nodo->izquierdo;
					}
				}else{
					nodo=actual->izquierdo;
					while(nodo->derecho!=NULL){
						padre=nodo;
						nodo=nodo->derecho;
					}
				}
				aux=actual->numeroFicha;
				actual->numeroFicha=nodo->numeroFicha;
				nodo->numeroFicha=aux;
				actual=nodo;	
			}	
		}else{
			padre=actual;
			if(opcion > actual->numeroFicha){
				actual=actual->derecho;
			}else if(opcion < actual->numeroFicha){
				actual=actual->izquierdo;
			}		
		}		
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

/*Funcion Modificar: modifica un dato especifico de algun nodo del arbol*/

void modificar(Ficha **Arbol){
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[3],fecha[11];
	char *num;
	int opcion,mod;
	Ficha *aux;
	Ficha *actual;
	actual=(*Arbol);
	InOrden(*Arbol);
	scanf("%i",&opcion);
	while(actual!=NULL){
		if(opcion==actual->numeroFicha){
			aux=actual;
			actual=NULL;
		}else if(opcion < actual->numeroFicha){
			actual=actual->izquierdo;
		}else if(opcion > actual->numeroFicha){
			actual=actual->derecho;
		}
	}
	printf("Que desea modificar?\n");
	printf("Seleccione un numero\n");
	printf("(%i) Nombre: %s\n",1,aux->nombre);
	printf("(%i) Apellido paterno: %s\n",2,aux->apellidop);
	printf("(%i) Apellido materno: %s\n",3,aux->apellidom);
	printf("(%i) Nombre de la mascota: %s\n",4,aux->nomMascota);
	printf("(%i) Especie de la mascota: %s\n",5,aux->especie);
	printf("(%i) Edad de la mascota: %s\n",6,aux->edad);
	printf("(%i) Numero de Telefono: %s\n",7,aux->telefono);
	printf("(%i) Numero de atencion: %s\n",8,aux->atenciones);
	printf("(%i) Vacunas al dia: %s\n",9,aux->vacunas);
	printf("(%i) Fecha del proximo control: %s\n",10,aux->fecha);
	scanf("%i",&mod);
	if(mod==1){
		printf("Modifique nombre:\n");
		scanf("%s",&nombre);
		strcpy(aux->nombre,nombre);
	}else if(mod==2){
		printf("Modifique apellido paterno:\n");
		scanf("%s",&apellidop);
		strcpy(aux->apellidop,apellidop);
	}else if(mod==3){
		printf("Modifique apellido materno:\n");
		scanf("%s",&apellidom);
		strcpy(aux->apellidom,apellidom);
	}else if(mod==4){
		printf("Modifique nombre de la mascota:\n");
		scanf("%s",&nomMascota);
		strcpy(aux->nomMascota,nomMascota);
	}else if(mod==5){
		printf("Modifique la especie:\n");
		scanf("%s",&especie);
		strcpy(aux->especie,especie);
	}else if(mod==6){
		printf("Modifique la edad:\n");
		scanf("%s",&edad);
		strcpy(aux->edad,edad);
	}else if(mod==7){
		printf("Modifique telefono:\n");
		scanf("%s",&telefono);
		strcpy(aux->telefono,telefono);
	}else if(mod==8){
		printf("Modifique numero de atenciones:\n");
		scanf("%s",&atenciones);
		strcpy(aux->atenciones,atenciones);
	}else if(mod==9){
		printf("Modifique vacunas:\n");
		scanf("%s",&vacunas);
		strcpy(aux->vacunas,vacunas);
	}else if(mod==10){
		printf("Modifique fecha del proximo control:\n");
		scanf("%s",&fecha);
		strcpy(aux->fecha,fecha);
		num=strtok(fecha,"/");
	    num=strtok(NULL,"/");
	    aux->mes=atoi(num);
	}	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion Buscar: Tiene la capacidad de buscar el nombre del cliente, el nombre de alguna mascota y la fecha de algun control
El usuario ingresa alguna palabra que quiere buscar dentro de estos parametros y la funcion te dice si se encuentra el registro,
si se encuentra se imprime todo el registro por pantalla */

void buscar(Ficha **Arbol){
	char nombre[31],nomMascota[21],fecha[11];
	int numero,val=0;
	do{
		printf("Que esta buscando? Ingrese un numero\n");
		printf("(1) nombre de algun cliente\n");
		printf("(2) nombre de alguna mascota\n");
		printf("(3) fecha de algun control\n");
		scanf("%i",&numero);
	}while(numero>3|| numero<1);
	if(numero==1){
		printf("Ingrese el nombre que busca:\n");
		scanf("%s",&nombre);
		InOrdenBuscar(*Arbol,nombre);
    }else if(numero==2){
    	printf("Ingrese el nombre de alguna mascota\n");
		scanf("%s",&nomMascota);
		InOrdenBuscar(*Arbol,nomMascota);
	}else if(numero==3){
		printf("Ingrese la fecha del control\n");
		scanf("%s",&fecha);
		InOrdenBuscar(*Arbol,fecha);
	}
}

void InOrdenBuscar(Ficha *aux,char dato[]){
	if(strcmp(aux->nombre,dato)==0){
		printf("El registro que busca es este: %s %s %s %s %s %s %s %s %s %s\n\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);	
	}else if(strcmp(aux->nomMascota,dato)==0){
		printf("El registro que busca es este: %s %s %s %s %s %s %s %s %s %s\n\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
	}else if(strcmp(aux->fecha,dato)==0){
		printf("El registro que busca es este: %s %s %s %s %s %s %s %s %s %s\n\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
	}
	if(aux->izquierdo!=NULL){
		InOrdenBuscar(aux->izquierdo,dato);
	}
	if(aux->derecho!=NULL){
		InOrdenBuscar(aux->derecho,dato);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion Equilibrar: funcion que equilibra el arbol cuando sufre algun desequilibrio, al insertar o eliminar un nodo, aplicando la rotacion 
adecuada, se recorre el camino desde el nodo insertado o eliminado hacia el nodo raiz*/

void equilibrar(Ficha **raiz,Ficha *nodo,int rama,int operacion){
	int salir=0;
	while(nodo!=NULL && salir!=1){
		if(operacion==1){//insertar nodo
			if(rama==0){
				nodo->equilibrio++;
			}else{
				nodo->equilibrio--;
			}
		}else{//eliminar nodo
			if(rama==0){
				nodo->equilibrio--;
			}else{
				nodo->equilibrio++;
			}
		}
		if(nodo->equilibrio==0){
			salir=1;
		}else if(nodo->equilibrio==2){
			if(nodo->izquierdo->equilibrio==-1){
				rotacionDobleDerecha(raiz,nodo);
			}else{
				rotacionSimpleDerecha(raiz,nodo);
			}
			salir=1;
		}else if(nodo->equilibrio==-2){
			if(nodo->derecho->equilibrio==1){
				rotacionDobleIzquierda(raiz,nodo);
			}else{
				rotacionSimpleIzquierda(raiz,nodo);
			}
			salir=1;
		}
		if(nodo->padre!=NULL){
			if(nodo->padre->derecho==nodo){
				rama=1;
			}else{
				rama=0;
		    }
		}
		nodo=nodo->padre;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*ROTACIONES*/

/*Funcion Rotacion simple a la izquierda: esta funcion lo que hace es rotar el arbol hacia la izquierda, se usará cuando el subarbol derecho
de un nodo sea 2 unidades mas alto que el izquierdo, es decir, cuando el equilibrio es de -2 y la raiz del subarbol derecho tenga un 
equilibrio de -1 o 0*/

void rotacionSimpleIzquierda(Ficha **raiz,Ficha *nodo){
	Ficha *Padre=nodo->padre;
	Ficha *nodoA=nodo;
	Ficha *nodoB=nodoA->derecho;
	Ficha *nodoC=nodoB->izquierdo;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoB;
		}else{
			Padre->izquierdo=nodoB;
		}
	}else{
		(*raiz)=nodoB;
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

void rotacionSimpleDerecha(Ficha **raiz,Ficha *nodo){
	Ficha *Padre = nodo->padre;
	Ficha *nodoA = nodo;
	Ficha *nodoB = nodoA->izquierdo;
	Ficha *nodoC = nodoB->derecho;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoB;
		}else{
			Padre->izquierdo=nodoB;
		}
	}else{
		(*raiz)=nodoB;
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

void rotacionDobleIzquierda(Ficha **raiz,Ficha *nodo){
	Ficha *Padre = nodo->padre;
	Ficha *nodoA = nodo;
	Ficha *nodoB = nodoA->derecho;
	Ficha *nodoC = nodoB->izquierdo;
	Ficha *nodoCI = nodoC->izquierdo;
	Ficha *nodoCD = nodoC->derecho;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoC;
		}else{
			Padre->izquierdo=nodoC;
		}
	}else{
		(*raiz)=nodoC;
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

void rotacionDobleDerecha(Ficha **raiz,Ficha *nodo){
	Ficha *Padre= nodo->padre;
	Ficha *nodoA = nodo;
	Ficha *nodoB = nodoA->izquierdo;
	Ficha *nodoC = nodoB->derecho;
	Ficha *nodoCI = nodoC->izquierdo;
	Ficha *nodoCD = nodoC->derecho;
	if(Padre!=NULL){
		if(Padre->derecho==nodoA){
			Padre->derecho=nodoC;
		}else{
			Padre->izquierdo=nodoC;
		}
	}else{
		(*raiz) = nodoC;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

/*Funcion ImprimirArchivo: cre un archivo y escribe cada registro en la posicion del mes que le corresponde*/

void imprimirArchivo(Ficha **arbol){
	Ficha *aux;
	Ficha *actual;
	actual=(*arbol);
	int mes;
	mes=(*arbol)->mes;
	FILE *archivo;
	archivo=fopen("Bultos.out","w");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	fprintf(archivo,"Registros:\n");
	fprintf(archivo,"Enero:\n");
	InOrdenArchivo(*arbol,1,archivo);
	fprintf(archivo,"Febrero:\n");
	InOrdenArchivo(*arbol,2,archivo);
	fprintf(archivo,"Marzo:\n");
	InOrdenArchivo(*arbol,3,archivo);
	fprintf(archivo,"Abril:\n");
	InOrdenArchivo(*arbol,4,archivo);
	fprintf(archivo,"Mayo:\n");
	InOrdenArchivo(*arbol,5,archivo);
	fprintf(archivo,"Junio:\n");
	InOrdenArchivo(*arbol,6,archivo);
	fprintf(archivo,"Julio:\n");
	InOrdenArchivo(*arbol,7,archivo);
	fprintf(archivo,"Agosto:\n");
	InOrdenArchivo(*arbol,8,archivo);
	fprintf(archivo,"Septiembre:\n");
	InOrdenArchivo(*arbol,9,archivo);
	fprintf(archivo,"Octubre:\n");
	InOrdenArchivo(*arbol,10,archivo);
	fprintf(archivo,"Noviembre:\n");
	InOrdenArchivo(*arbol,11,archivo);
	fprintf(archivo,"Diciembre:\n");
	InOrdenArchivo(*arbol,12,archivo);
	fclose(archivo);
}

void InOrdenArchivo(Ficha *aux,int mes,FILE *archivo){
	if(aux->mes==mes){
		fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
	}
	if(aux->izquierdo!=NULL){
		InOrdenArchivo(aux->izquierdo,mes,archivo);
	}
	if(aux->derecho!=NULL){
		InOrdenArchivo(aux->derecho,mes,archivo);
	}
}








