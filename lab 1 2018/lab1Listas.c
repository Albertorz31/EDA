#include<string.h>
#include<stdlib.h>
#include<stdio.h>

/*ESTRUCTURA DEL PROGRAMA*/

typedef struct Registro{
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[4],fecha[11];
	int mes;
	struct Registro *siguiente;
}Ficha;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*FUNCIONES DEL PROGRAMA*/

void iniciar();
void imprimirMenu();
void leerTexto();
void opciones(Ficha *inicio,int tamano,Ficha *ultimo);
void imprimirFicha(Ficha *carac,int i);
void imprimirLista(Ficha* inicio);
void agregarTexto(Ficha* inicio,Ficha* fich);
void agregar(Ficha *inicio,int tamano,Ficha *ultimo);
void eliminar(Ficha *inicio,int tamano,Ficha *ultimo);
void modificar(Ficha *inicio);
void buscar(Ficha *inicio);
void ImprimirArchivo(Ficha *inicio);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*MENU PRINCIPAL*/

int main(){
	iniciar();
	return 0;
}

void iniciar(){
	leerTexto();
}

void opciones(Ficha *inicio,int tamano,Ficha *ultimo){
	Ficha* aux;
	int num,salir=0,opcion=-1;
	while(salir==0){
		imprimirLista(inicio);
		ImprimirArchivo(inicio);
		imprimirMenu();
		fflush(stdin);
		scanf("%d",&opcion);
		if(opcion==1)agregar(inicio,tamano,ultimo);
		if(opcion==2)eliminar(inicio,tamano,ultimo);
		if(opcion==3)modificar(inicio); 
		if(opcion==4)buscar(inicio); 
		if(opcion==5){
			salir=1;
			while(inicio!=NULL){
				aux=inicio;
				inicio=inicio->siguiente;
				free(aux);
			}
		}	
	}	
}

void imprimirMenu(){
	printf("\n------------------------------\n");
	printf("Bienvenido al Bulto feliz\n");
	printf("Que desea hacer?\n");
	printf("1. Agregar registro\n");
	printf("2. Eliminar registro\n");
	printf("3. Modificar registro\n");
	printf("4. Buscar registro\n");
	printf("5. Salir\n");	
}

void imprimirFicha(Ficha *carac,int i){
	printf("Ficha: (%i) %s %s %s %s %s %s %s %s %s %s\n",i+1,carac->nombre,carac->apellidop,carac->apellidom,carac->nomMascota,carac->especie,carac->edad,carac->telefono,carac->atenciones,carac->vacunas,carac->fecha);
}

void imprimirLista(Ficha* inicio){
	int i=0;
	Ficha* cursor;
	cursor=inicio;
	while(cursor!=NULL){
		imprimirFicha(cursor,i);
		cursor=cursor->siguiente;
		i++;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion que lee el texto ingresado por el usuario y los almacena en la estructura Registro mediante Listas enlazadas*/

void leerTexto(){
	char linea[192];
	char *temp,*num;
	int tamano=0,cont=0;
	FILE* archivo;
	Ficha* fich;
	Ficha* inicio=NULL;
	Ficha* aux;
	Ficha* ultimo=NULL;	
	
	archivo = fopen("Bultos.in","r");
	if (archivo == NULL)
	{
		printf("No se pudo abrir el archivo");
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
		fich->siguiente = NULL;
		num=strtok(temp,"/");
		num=strtok(NULL,"/");
		fich->mes=atoi(num);
		if(inicio==NULL){
			inicio=fich;
		}else{
			agregarTexto(inicio,fich);
		}
	    tamano++;	
	}
	aux=inicio;
	while(aux!=NULL){
		if(aux->siguiente==NULL){
			ultimo=aux;
		}
		aux=aux->siguiente;	
	}
	fclose(archivo);
	opciones(inicio,tamano,ultimo);	
}

void agregarTexto(Ficha* inicio,Ficha* fich){
	Ficha* aux;
	Ficha* ultimo;
	aux=inicio;
	ultimo=inicio;
	while(aux!=NULL){
		ultimo=aux;
		aux=aux->siguiente;
	}
	ultimo->siguiente=fich;
	fich->siguiente=NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion agregar: agregar un nodo nuevo al final de la lista enlazada*/

void agregar(Ficha *inicio,int tamano,Ficha *ultimo){
	Ficha *nuevoRegistro;
	char *num;
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[3],fecha[11];
	nuevoRegistro=(Ficha*)malloc(sizeof(Ficha));
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
	ultimo->siguiente=nuevoRegistro;
	nuevoRegistro->siguiente=NULL;
	ultimo=nuevoRegistro;
	tamano++;	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion Eliminar: elimina el nodo de una posicion determinada y reduce el tamano de la lista enlazada*/

void eliminar(Ficha *inicio,int tamano,Ficha *ultimo){
	Ficha *aux;
	int count=1,numero,i;
	aux=inicio;
	if(tamano<=1){
		printf("No se pueden eliminar mas registro, se debe quedan con uno\n");
	}
	printf("Cual registro desea eliminar?\n");
	while(aux!=NULL){
		printf("(%i) %s %s %s %s %s %s %s %s %s %s\n",count,aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
		aux=aux->siguiente;
		count++;
	}
	scanf("%i",&numero);
	Ficha *actual;
	Ficha *sup_ficha;
	actual=inicio;
	if(numero==1){
		sup_ficha=inicio;
		inicio=inicio->siguiente;
		free(sup_ficha);
		tamano--;
	}else{
		for(i=2;i<numero;i++){
		    actual=actual->siguiente;
	    }
	    sup_ficha=actual->siguiente;
	    actual->siguiente=actual->siguiente->siguiente;
	    if(actual->siguiente==NULL){
	    	ultimo=actual;
		}
		free(sup_ficha);
		tamano--;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion Modificar: El usuario elige que caracterista de algun nodo desea modificar*/

void modificar(Ficha *inicio){
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[3],fecha[11];
	char *num;
	Ficha *aux;
	Ficha *actual;
	int count=1,numero,i,mod;
	aux=inicio;
	actual=inicio;
	printf("Cual registro desea modificar?\n");
	while(aux!=NULL){
		printf("(%i) %s %s %s %s %s %s %s %s %s %s\n",count,aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
		aux=aux->siguiente;
		count++;
	}
	scanf("%i",&numero);
	for(i=1;i<numero;i++){
		actual=actual->siguiente;	
	}
	printf("Que desea modificar?\n");
	printf("Seleccione un numero\n");
	printf("(%i) Nombre: %s\n",1,actual->nombre);
	printf("(%i) Apellido paterno: %s\n",2,actual->apellidop);
	printf("(%i) Apellido materno: %s\n",3,actual->apellidom);
	printf("(%i) Nombre de la mascota: %s\n",4,actual->nomMascota);
	printf("(%i) Especie de la mascota: %s\n",5,actual->especie);
	printf("(%i) Edad de la mascota: %s\n",6,actual->edad);
	printf("(%i) Numero de Telefono: %s\n",7,actual->telefono);
	printf("(%i) Numero de atencion: %s\n",8,actual->atenciones);
	printf("(%i) Vacunas al dia: %s\n",9,actual->vacunas);
	printf("(%i) Fecha del proximo control: %s\n",10,actual->fecha);
	scanf("%i",&mod);
	if(mod==1){
		printf("Modifique nombre:\n");
		scanf("%s",&nombre);
		strcpy(actual->nombre,nombre);
	}else if(mod==2){
		printf("Modifique apellido paterno:\n");
		scanf("%s",&apellidop);
		strcpy(actual->apellidop,apellidop);
	}else if(mod==3){
		printf("Modifique ape:\n");
		scanf("%s",&apellidom);
		strcpy(actual->apellidom,apellidom);
	}else if(mod==4){
		printf("Modifique nombre de la mascota:\n");
		scanf("%s",&nomMascota);
		strcpy(actual->nomMascota,nomMascota);
	}else if(mod==5){
		printf("Modifique la especie:\n");
		scanf("%s",&especie);
		strcpy(actual->especie,especie);
	}else if(mod==6){
		printf("Modifique la edad:\n");
		scanf("%s",&edad);
		strcpy(actual->edad,edad);
	}else if(mod==7){
		printf("Modifique telefono:\n");
		scanf("%s",&telefono);
		strcpy(actual->telefono,telefono);
	}else if(mod==8){
		printf("Modifique numero de atenciones:\n");
		scanf("%s",&atenciones);
		strcpy(actual->atenciones,atenciones);
	}else if(mod==9){
		printf("Modifique vacunas:\n");
		scanf("%s",&vacunas);
		strcpy(actual->vacunas,vacunas);
	}else if(mod==10){
		printf("Modifique fecha del proximo control:\n");
		scanf("%s",&fecha);
		strcpy(actual->fecha,fecha);
		num=strtok(fecha,"/");
	    num=strtok(NULL,"/");
	    actual->mes=atoi(num);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion Buscar: Tiene la capacidad de buscar el nombre del cliente, el nombre de alguna mascota y la fecha de algun control
El usuario ingresa alguna palabra que quiere buscar dentro de estos parametros y la funcion te dice si se encuentra o no el registro,
si se encuentra se imprime todo el registro por pantalla */

void buscar(Ficha *inicio){
	char nombre[31],nomMascota[21],fecha[11];
	int numero,val=0;
	Ficha *aux;
	aux=inicio;
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
		while(aux!=NULL){
			if(strcmp(aux->nombre,nombre)==0){
				printf("El registro que busca es este: %s %s %s %s %s %s %s %s %s %s\n\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
				val=1;
			}
			aux=aux->siguiente;
		}if(val==0){
			printf("No se ha encontrado registro con ese nombre\n\n");
		}	
	}else if(numero==2){
		printf("Ingrese el nombre de alguna mascota\n");
		scanf("%s",nomMascota);
		while(aux!=NULL){
			if(strcmp(aux->nomMascota,nomMascota)==0){
				printf("El registro que busca es este: %s %s %s %s %s %s %s %s %s %s\n\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
				val=1;
			}
			aux=aux->siguiente;
		}if(val==0){
			printf("No se ha encontrado registro con ese nombre\n\n");
		}
	}else if(numero==3){
		printf("Ingrese la fecha del control\n");
		scanf("%s",fecha);
		while(aux!=NULL){
			if(strcmp(aux->fecha,fecha)==0){
				printf("El registro que busca es este: %s %s %s %s %s %s %s %s %s %s\n\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
				val=1;
			}
			aux=aux->siguiente;
		}if(val==0){
			printf("No se ha encontrado registro con ese nombre\n\n");
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion ImprimirArchivo: cre un archivo y escribe cada registro en la posicion del mes que le corresponde*/

void ImprimirArchivo(Ficha *inicio){
	Ficha *aux;
	aux=inicio;
	FILE *archivo;
	archivo=fopen("Bultos.out","w");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	fprintf(archivo,"Registros:\n");
	fprintf(archivo,"Enero:\n");
	while(aux!=NULL){
		if(aux->mes==1){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Febrero:\n");
	while(aux!=NULL){
		if(aux->mes==2){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Marzo:\n");
	while(aux!=NULL){
		if(aux->mes==3){
			printf("holi");
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Abril:\n");
	while(aux!=NULL){
		if(aux->mes==4){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}
		aux=aux->siguiente;
	}
	aux=inicio;
	fprintf(archivo,"Mayo:\n");
	while(aux!=NULL){
		if(aux->mes==5){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Junio:\n");
	while(aux!=NULL){
		if(aux->mes==6){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}
	}
	aux=inicio;
	fprintf(archivo,"Julio:\n");
	while(aux!=NULL){
		if(aux->mes==7){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Agosto:\n");
	while(aux!=NULL){
		if(aux->mes==8){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Septiembre:\n");
	while(aux!=NULL){
		if(aux->mes==9){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Octubre:\n");
	while(aux!=NULL){
		if(aux->mes==10){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}
	}
	aux=inicio;
	fprintf(archivo,"Noviembre:\n");
	while(aux!=NULL){
		if(aux->mes==11){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	aux=inicio;
	fprintf(archivo,"Diciembre:\n");
	while(aux!=NULL){
		if(aux->mes==12){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",aux->nombre,aux->apellidop,aux->apellidom,aux->nomMascota,aux->especie,aux->edad,aux->telefono,aux->atenciones,aux->vacunas,aux->fecha);
			aux=aux->siguiente;
		}else{
			aux=aux->siguiente;
		}	
	}
	fclose(archivo);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
