#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*ESTRUCTURA DEL PROGRAMA */

typedef struct Ficha{
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[4],fecha[11];	
	int mes;
}fichas;

fichas *fich;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*FUNCIONES DEL PROGRAMA*/

void iniciar();
void imprimirMenu();
void leerTexto(int numero);
void opciones(int tamano,int numero);
void agregar();
void eliminar(int tamano);
void modificar(int tamano);
void buscar(int tamano);
void imprimirFicha(int tamano);
void ImprimirArchivo(int tamano);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*MENU PRINCIPAL*/

int main(){
	iniciar();
	return 0;
}

void iniciar(){
	leerTexto(0);
}

void opciones(int tamano,int numero){
	int num,salir=0,opcion=-1;
	while(salir==0){
		imprimirFicha(tamano);
		ImprimirArchivo(tamano);
		imprimirMenu();
		fflush(stdin);
		scanf("%d",&opcion);
		if(opcion==1) agregar(numero);
		if(opcion==2) eliminar(tamano);
		if(opcion==3) modificar(tamano);
		if(opcion==4) buscar(tamano);
		if(opcion==5) {
			salir=1;
			free(fich);
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

void imprimirFicha(int tamano){
	int i;
	for(i=0;i<tamano;i++){
		printf("Ficha: (%i) %s %s %s %s %s %s %s %s %s %s\n",i+1,fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
	}	
}

////////////////////////////////////////////////////////////////////////////////////////

/*Funcion que lee texto ingresado por el usuario y los almacena en la estructura Ficha mediante arreglos*/

void leerTexto(int numero){
	char linea[192],temp2[52];
	char *temp,*num;
	int count=0,tamano=0,i=0;
	FILE *archivo;
	archivo = fopen("Bultos.in","r");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	while(!feof(archivo)){
		fgets(temp2,50,archivo);
		count++;
	}
	rewind(archivo);
	
	fich=(fichas*)malloc(count*sizeof(fichas));
	while(!feof(archivo)){
		if(numero==0){
			fscanf(archivo,"%s",linea);
			numero=1;
		}
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].nombre,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].apellidop,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].apellidom,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].nomMascota,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].especie,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].edad,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].telefono,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].atenciones,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].vacunas,temp);
		fscanf(archivo,"%s",linea);
		temp=linea;
		strcpy(fich[i].fecha,temp);
		num=strtok(temp,"/");
	    num=strtok(NULL,"/");
		fich[i].mes=atoi(num);
	    i++;
		tamano++;
	}
	fclose(archivo);
	numero=0;
	opciones(tamano,numero);	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funcion agregar: agregra un registro al final del archivo y el programa vuelve a leer el texto
para guardar todo en la estructura Ficha */

void agregar(int numero){
	char *num,*registro;
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[3],fecha[11];
	printf("Ingrese Nombre del dueno:\n");
	scanf("%s",&nombre);
	printf("Ingrese apellido paterno:\n");
	scanf("%s",&apellidop);
	printf("Ingrese apellido materno:\n");
	scanf("%s",&apellidom);
	printf("Ingrese nombre de la mascota:\n");
	scanf("%s",&nomMascota);
	printf("Ingrese especie de la mascota:\n");
	scanf("%s",&especie);
	printf("Ingrese edad de la mascota:\n");
	scanf("%s",&edad);
	printf("Ingrese telefono del cliente:\n");
	scanf("%s",&telefono);
	printf("Numero de atenciones:\n");
	scanf("%s",&atenciones);
	printf("Vacunas al dia?\n");
	scanf("%s",&vacunas);
	printf("Fecha del proximo control:\n");
	scanf("%s",&fecha);

	FILE *archivo;
	archivo=fopen("Bultos.in","a");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	
	registro=(char*)malloc(192*sizeof(char));
	strcpy(registro,nombre);
	strcat(registro," ");
	strcat(registro,apellidop);
	strcat(registro," ");
	strcat(registro,apellidom);
	strcat(registro," ");
	strcat(registro,nomMascota);
	strcat(registro," ");
	strcat(registro,especie);
	strcat(registro," ");
	strcat(registro,edad);
	strcat(registro," ");
	strcat(registro,telefono);
	strcat(registro," ");
	strcat(registro,atenciones);
	strcat(registro," ");
	strcat(registro,vacunas);
	strcat(registro," ");
	strcat(registro,fecha);
	
	fprintf(archivo,"\n");
	fprintf(archivo,"%s",registro);
	fclose(archivo);
	leerTexto(0);
}
/////////////////////////////////////////////////////////////////////////////7

/*Funcion Eliminar: El usuario selecciona el registro que quiere eliminar y la funcion escribe denuevo el archivo, pero sin el registro seleccionado*/

void eliminar(int tamano){
	int numero,count=0,i,j;
	printf("Cual registro desea eliminar?\n");
	printf("Seleccione un numero:\n\n");
	for(i=0;i<tamano;i++){
		printf("(%i) %s %s %s %s %s %s %s %s %s %s\n",i+1,fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		count++;
	}
	scanf("%i",&numero);
	FILE *archivo;
	archivo=fopen("Bultos.in","w");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	fprintf(archivo,"%i\n",tamano-1);
	for(j=0;j<count;j++){
		if(j!=numero-1){
			fprintf(archivo,"%s ",fich[j].nombre);
			fprintf(archivo,"%s ",fich[j].apellidop);
			fprintf(archivo,"%s ",fich[j].apellidom);
			fprintf(archivo,"%s ",fich[j].nomMascota);
			fprintf(archivo,"%s ",fich[j].especie);
			fprintf(archivo,"%s ",fich[j].edad);
			fprintf(archivo,"%s ",fich[j].telefono);
			fprintf(archivo,"%s ",fich[j].atenciones);
			fprintf(archivo,"%s ",fich[j].vacunas);
			fprintf(archivo,"%s",fich[j].fecha);
			if((j+2)<count){
				fprintf(archivo,"\n");
			}	
		}
	}
	fclose(archivo);
	leerTexto(0);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion Modificar: El usuario elige que caracteristica de algun registro desea modificar */

void modificar(int tamano){
	char nombre[31],apellidop[31],apellidom[31],nomMascota[21],especie[21],edad[4],telefono[21],atenciones[4],vacunas[3],fecha[11];
	char *num;
	int count=0,numero,mod,i,k;
	printf("Cual registro desea modificar?\n");
	printf("Seleccione un numero:\n\n");
	for(i=0;i<tamano;i++){
		printf("(%i) %s %s %s %s %s %s %s %s %s %s\n",i+1,fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
	    count++;
	}
	scanf("%i",&numero);
	printf("Que desea modificar?\n");
	printf("Seleccione un numero:\n\n");
	printf("(%i) Nombre: %s\n",1,fich[numero-1].nombre);
	printf("(%i) Apellido paterno: %s\n",2,fich[numero-1].apellidop);
	printf("(%i) Apellido materno: %s\n",3,fich[numero-1].apellidom);
	printf("(%i) Nombre de la mascota: %s\n",4,fich[numero-1].nomMascota);
	printf("(%i) Especie de la mascota: %s\n",5,fich[numero-1].especie);
	printf("(%i) Edad de la mascota: %s\n",6,fich[numero-1].edad);
	printf("(%i) Numero de Telefono: %s\n",7,fich[numero-1].telefono);
	printf("(%i) Numero de atencion: %s\n",8,fich[numero-1].atenciones);
	printf("(%i) Vacunas al dia: %s\n",9,fich[numero-1].vacunas);
	printf("(%i) Fecha del proximo control: %s\n",10,fich[numero-1].fecha);
	scanf("%i",&mod);
	if(mod==1){
		printf("Modifique nombre:\n");
		scanf("%s",&nombre);
	    strcpy(fich[numero-1].nombre,nombre);
	}else if(mod==2){
		printf("Modifique Apellido Paterno:\n");
		scanf("%s",&apellidop);
		strcpy(fich[numero-1].apellidop,apellidop);
	}else if(mod==3){
		printf("Modifique Apellido Materno:\n");
		scanf("%s",&apellidom);
		strcpy(fich[numero-1].apellidom,apellidom);
	}else if(mod==4){
		printf("Modifique Nombre de la mascota:\n");
		scanf("%s",&nomMascota);
		strcpy(fich[numero-1].nomMascota,nomMascota);
	}else if(mod==5){
		printf("Modifique especie de la mascota:\n");
		scanf("%s",&especie);
		strcpy(fich[numero-1].especie,especie);
	}else if(mod==6){
		printf("Modifique edad de la mascota:\n");
		scanf("%s",&edad);
		strcpy(fich[numero-1].edad,edad);
	}else if(mod==7){
		printf("Modifique numero de telofono:\n");
		scanf("%s",&telefono);
		strcpy(fich[numero-1].telefono,telefono);
	}else if(mod==8){
		printf("Modifique numero de atenciones:\n");
		scanf("%s",&atenciones);
		strcpy(fich[numero-1].atenciones,atenciones);
	}else if(mod==9){
		printf("Modifique vacunas al dia:\n");
		scanf("%s",&vacunas);
		strcpy(fich[numero-1].vacunas,vacunas);
	}else if(mod==10){
		printf("Modifique fecha del proximo control:\n");
		scanf("%s",fecha);
		strcpy(fich[numero-1].fecha,fecha);
		num=strtok(fecha,"/");
		num=strtok(NULL,"/");
		fich[numero-1].mes=atoi(num);	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funcion Buscar: Tiene la capacidad de buscar el nombre del cliente, el nombre de alguna mascota y la fecha de algun control
El usuario ingresa alguna palabra que quiere buscar dentro de estos parametros y la funcion te dice si se encuentra o no el registro,
si se encuentra se imprime todo el registro por pantalla */

void buscar(int tamano){
	char nombre[31],nomMascota[21],fecha[11];
	int numero,i,val=0;
	
	do{
		printf("Que esta buscando? Ingrese un numero\n");
		printf("(1) nombre de algun cliente\n");
		printf("(2) nombre de alguna mascota\n");
		printf("(3) fecha de algun control\n");
		scanf("%i",&numero);
	}while(numero>3|| numero<1);
	
	if(numero==1){
		printf("Ingrese nombre que busca: ");
		scanf("%s",&nombre);
		for(i=0;i<tamano;i++){
			if(strcmp(fich[i].nombre,nombre)==0){
				printf("El registro que busca es este %s %s %s %s %s %s %s %s %s %s\n\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
				val=1;
			}
		}if(val==0){
			printf("No se ha encontrado registro con ese nombre\n\n");
		}	
	}else if(numero==2){
		printf("Ingrese el nombre de la mascota que busca: ");
		scanf("%s",&nomMascota);
		for(i=0;i<tamano;i++){
			if(strcmp(fich[i].nomMascota,nomMascota)==0){
				printf("El registro que busca es este %s %s %s %s %s %s %s %s %s %s\n\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
				val=1;
			}
		}if(val==0){
			printf("No se ha encontrado registro con ese nombre\n\n");
		}
	}else if(numero==3){
		printf("Ingrese la fecha de control de la mascota que busca: ");
		scanf("%s",&fecha);
		for(i=0;i<tamano;i++){
			if(strcmp(fich[i].fecha,fecha)==0){
				printf("El registro que busca es este %s %s %s %s %s %s %s %s %s %s\n\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
				val=1;
			}
		}if(val==0){
			printf("No se ha encontrado registro con ese nombre\n\n");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion ImprimirArchivo: crea un archivo y escribe cada registro en la posicion del mes que le corresponde*/
	
void ImprimirArchivo(int tamano){
	int i;
	FILE *archivo;
	archivo=fopen("Bultos.out","w");
	if(archivo == NULL){
		printf("No se puede abrir el archivo");
		exit(1);
	}
	fprintf(archivo,"Registros:\n");
	fprintf(archivo,"Enero:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==1){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Febrero:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==2){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Marzo:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==3){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Abril:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==4){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Mayo:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==5){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Junio:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==6){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Julio:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==7){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Agosto:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==8){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Septiembre:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==9){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Octubre:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==10){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Noviembre:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==11){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fprintf(archivo,"Diciembre:\n");
	for(i=0;i<tamano;i++){
		if(fich[i].mes==12){
			fprintf(archivo,"%s %s %s %s %s %s %s %s %s %s\n",fich[i].nombre,fich[i].apellidop,fich[i].apellidom,fich[i].nomMascota,fich[i].especie,fich[i].edad,fich[i].telefono,fich[i].atenciones,fich[i].vacunas,fich[i].fecha);
		}
	}
	fclose(archivo);
}

