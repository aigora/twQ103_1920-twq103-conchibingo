#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#define NFIL 3  //La cantidad de filas que hay en un carton
#define NCOL 5  //La cantidad de columnas que hay en un carton


//Creamos la estrucutra necesaria para los datos de cada usuario
struct Tusuarios {
	char nickname[100];  //Nombre de jugador
	float dinero;  //Dinero de jugador
	int cartones;  //Numero de cartones para la partida
};

void titulo();

int main  () {
	
	//DECLARACION DE VARIABLES
	FILE * fusuarios;  //Fichero para la partida
	int i=0, j=-1, a,b,c,d,e,k, l,q, m, n, z, numero, nusuarios, repetido,contador_linea1=0,contador_linea2=0,contador_linea3=0;  //Variables para bucles
	int contador=0;
	int bombo[100];  //Numeros del bombo
	float ingreso = 0;  //Cantidad de ingreso
	char opcion [50];  //Para elecciones
	char igual_nickname[100];  //Para la busqueda de nicknames iguales
	float dinero_partida = 0;  //Dinero total que se va a repartir entre el que cante linea y bingo
	
	struct Tusuarios usuario[200];  //200 es el nÃºmero mÃ¡ximo de usuarios que podemos introducir
	int carton[NFIL][NCOL]; //Matriz con el tamaÃ±o del carton
	srand(time(NULL));  //Iniciamos numero aleatorio
	
	// MenÃº
	titulo();
	system("cls");
	
	//Volvemos a abrir el fichero en modo write para trabajar con esos datos
	fusuarios = fopen("usuarios.txt","w");
	
	//En caso de no encontrar el fichero se crea el error al encontrarlo
	if (fusuarios == NULL) {
		printf ("***ERROR***\tNo se ha encontrado el archivo\n");
		return 0;
	}
	
	//Pedir la cantidad de usuarios por partida
	printf("\nIngresar el numero de jugadores de la partida: ");
	scanf("%d", &nusuarios);

	//Controlar el numero de usuarios con los que se juegan
	if (nusuarios < 1 || nusuarios > 200) {
		do {
			printf("No se puede jugar con esos jugadores. Escriba de nuevo la cantidad de jugadores de la partida: "); 
			fflush(stdin);
			scanf("%i", &nusuarios);
		} while (nusuarios < 1  ||  nusuarios > 200);
	}

	system ("cls");
	
	//Pedir el nombre, nÂºcartones y el dinero de los usuarios 
	i = 0;
	ingreso = 0;
	
	//Pedida de datos
	do{
		//Pedir nicknames
		printf ("\nNickname %i: ", i+1);
		fflush(stdin);
		gets(usuario[i].nickname);
		
		//En caso de repetirse el nombre, pedirlo de nuevo
		do {
			if (strcmp(usuario[j].nickname,usuario[i].nickname) == 0) {  //Si la del fichero es igual a la escrita:
				printf("El nickname %s no es valido puesto que ya es usado por otro jugador del inscrito en el ranking. Introduzca otro nickname para el usuario %i: ", usuario[i].nickname, i+1);
				fflush(stdin);
				gets(usuario[i].nickname);
			}
			j++;
		} while (j<i);
		j = -1;
		
		
		//Pedir nÂº de cartones
		printf ("\nCantidad de cartones de %s: ", usuario[i].nickname);
		scanf("%i", &usuario[i].cartones);
		
		//En caso de comando no valido, pedirlo de nuevo
		if(usuario[i].cartones < 1  ||  usuario[i].cartones > 20) {
			do {
				printf("La cantidad de cartones introducida no es valida. Introduce otra cantidad para %s: ", usuario[i].nickname);
				scanf("%i", &usuario[i].cartones);
			} while (usuario[i].cartones < 1  ||  usuario[i].cartones > 20);
		}
		
		//Pedir dinero
		printf ("\nDinero de %s: ", &usuario[i].nickname);
		scanf("%f", &usuario[i].dinero);
		
		//En caso de no tener dinero (el carton vale 2$)
		if (usuario[i].dinero < (usuario[i].cartones * 2)) {
			printf("El usuario %s no tiene suficiente dinero como para jugar. Escriba si desea hacer un ingreso: ", usuario[i].nickname);
			fflush(stdin);
			gets(opcion);
			
			//Si ingresa
			if (strcmp(opcion,"SI") == 0 || strcmp(opcion,"Si") == 0 || strcmp(opcion,"sI") == 0 || strcmp(opcion,"si") == 0 ) {
				printf("Cantidad de ingreso: ");
				scanf("%f", &ingreso);
				printf("El usuario %s disponia de %0.2f$. Tras el ingreso dispone de %0.2f$\n", usuario[i].nickname, usuario[i].dinero, (usuario[i].dinero + ingreso));
				usuario[i].dinero = usuario[i].dinero + ingreso;
				
				//Si ingresa y tiene menos de 2$
				if (usuario[i].dinero < 2) {
					printf("\n\n*NOTIFICACION: El usuario %s no puede jugar con ningun carton.\n\n\n", usuario[i].nickname);
				} else {  //Si no le llega ingresando pero tiene mas de 2$, reducir cartones
					if (usuario[i].dinero < (usuario[i].cartones * 2)) {
						printf("El usuario %s no puede jugar con esa cantidad de cartones. Reduzca la cantidad de estos: ", usuario[i].nickname);
						scanf("%i", &usuario[i].cartones);
						
						//Bucle para reducir cartones
						if (usuario[i].dinero < (usuario[i].cartones * 2)) {
							do {
								printf("El usuario %s no puede jugar con esa cantidad de cartones. Reduzca la cantidad de estos: ", usuario[i]. nickname);
								scanf("%i", &usuario[i].cartones);
							} while (usuario[i].dinero < (usuario[i].cartones * 2));
						}
						
						printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
					} 
					else {  //Si ingresa y le llega para jugar 
						printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
					}
				}
			}  
			else {  //No ingresa y tienes menos de 2$
				if (usuario[i].dinero < 2) {
				printf("\n\n*NOTIFICACION: El usuario %s no puede jugar con ningun carton.\n\n\n", usuario[i].nickname);
				} 
				else {  //No ingresa y tienes mas de 2$
					if (usuario[i].dinero < (usuario[i].cartones * 2)) {
						printf("\nEl usuario %s no puede jugar con esa cantidad de cartones. Reduzca la cantidad de estos: ", usuario[i].nickname);
						scanf("%i", &usuario[i].cartones);
						
						//Bucle para reducir cartones
						if (usuario[i].dinero < (usuario[i].cartones * 2)) {
							do {
								printf("El usuario %s no puede jugar con esa cantidad de cartones. Reduzca la cantidad de estos: ", usuario[i].nickname);
								scanf("%i", &usuario[i].cartones);
							} while (usuario[i].dinero < (usuario[i].cartones * 2));
						}
						
						printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
					} 
					else {
						printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
					}
				}
			} 
		} //Si tiene dinero
		else {
			printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
		}
		printf("Estos son los cartones de %s:\n\n", usuario[i].nickname);
		

		//Para crear los cartones:
		for (z=0; z<usuario[i].cartones; z++) {  //Esto se repite tantas veces como cartones haya
			for (k=0; k<NFIL; k++) {  //Elementos de la fila i
				for (l=0; l<NCOL; l++) {  //Elementos de la fila j
					
					do{
						numero = (rand()%90)+1; //Se crea el numero aleatorio
						repetido = 0;
						
						for (m=0; m<=k; m++) {  //Se leen todos los numeros hasta la Ãºltima columna
							for (n=0; n<=l; n++) {  //Se leen todos los numeros hasta la Ãºltima columna
								a=carton[m][n];
								if(a == numero) {  //Si alguno de los numeros estÃ¡ repetido se crea un nuevo numero hasta que no lo estÃ©
									repetido = 1;  //Suponemos que estÃ¡ repetido
								}
							}	
						} 
					} while (repetido>0); //El bucle se repite mientras que el numero sea igual a cualquier numero comprobado en el cartÃ³n
					
					
					carton[k][l] = numero;
					printf("%d\t", numero);
				}
				printf("\n"); // para dejar un salto de linea entre cada fila
			}
			printf("\n");
			printf("\n");
		}
		
		dinero_partida += usuario[i].cartones*2;
		
		system("pause");
		system ("cls");
		ingreso = 0;
		
		//Escribir todo esto en el fichero
		i++;	
	} while (i<nusuarios);
	

	//FUNCIONAMIENTO DEL BOMBO	
	for(z=0;z<90;z++){  //Hacemos un bucle para que se repita hasta bingo 
		do { 
				numero=(rand()%90)+1;  //Queremos sacar un numero aleatoriamente entre el 1 y el 90
				repetido=0;  //Suponemos que no esta repetido 
				
				for(q=0;q<z;q++) {  //Comprobamos que no lo esta con los numeros salidos anteriormente
					if(bombo[q] == numero) { 
						repetido=1;  //Si esta repetido, sale del bucle for
						
					}
				}
				for (i=0; i<nusuarios; i++) {  //Recorres todos los usuarios
	    			for (j=0; j<usuario[i].cartones; j++) {  //Recorres todos los cartones
	    				for (k=0; k<NFIL; k++) {  //Recorrer todas las filas
							for (l=0; l<NCOL; l++) {  //Recorrer todas las columnas
								b=carton[k][l];
								if(numero == b) {
									carton[k][l]= 0;  //Si el numero del bombo coincide con el del carton, se sustituye por 0
									contador++;
							
									if(contador==15){
										printf("El usuario %s ha cantado BINGO\n", usuario[i].nickname);
										usuario[i].dinero=usuario[i].dinero+(dinero_partida/2);
										break;
									}
									/*
									c=carton[0][l];
									d=carton[1][l];
									e=carton[2][l];
							
									if (c!=((c>0)&&(c<0))) {  //Para comprobar si hay linea
										contador_linea1++;
									} 
									else if (d!=((d>0)&&(d<0))){
										contador_linea2++;
									} 
									else if(e!=((e>0)&&(e<0))) {
										contador_linea3++; 
									}
									if (contador_linea1 == 5 || contador_linea2 == 5 || contador_linea3 == 5) {
										printf("¡El usuario %s ha cantado linea!", usuario[i].nickname);
										usuario[i].dinero += (1/10)*dinero_partida;
									}
									*/
								}	
							}
							if (contador == 15) {
								break;
							}
						}
						if (contador == 15) {
							break;
						}
					}
					if (contador == 15) {
						break;
					}
				}
			} while(repetido>0);
		
	    bombo[z]=numero;
	    printf("\n\t----\t\n");
	    printf("\t| %d |\t", numero);
	    printf("\n\t----\t");
	    system ("pause");
		if (contador == 15) {
			break;
		}
	}
	//usuario[bingo].dinero = usuario[bingo].dinero + (1/2)*dinero_partida;
	//usuario[linea].dinero = usuario[linea].dinero + (1/10)*dinero_partida;
	for (i=0; i<nusuarios; i++) {
	printf("%s\t  %0.2f \n", usuario[i].nickname, usuario[i].dinero-2*usuario[i].cartones);
	}
	
	i=0;
	for(i=0;i<nusuarios; i++) {
		fprintf(fusuarios, "%s\t  %0.2f \n", usuario[i].nickname, usuario[i].dinero);
	}
	
	//Cerramos el fichero
	fclose (fusuarios);
}
void titulo() {
	printf("\n");
	printf("+------   +------+   +        +   +------  +      +    -----    +-----+     -----   +        +   +-------   +------+\n");
	printf("|         |      |   |\\       |   |        |      |      |      |      \\      |     |\\       |   |          |      |\n");
	printf("|         |      |   |  \\     |   |        |______|      |      |_____ /      |     |  \\     |   |          |      |\n");
	printf("|         |      |   |    \\   |   |        |      |      |      |      \\      |     |    \\   |   |  ----+   |      |\n");
	printf("|         |      |   |      \\ |   |        |      |      |      |      /      |     |      \\ |   |      |   |      |\n");
	printf("+------   +------+   +        +   +------  +      +    -----    +-----+     -----   +        +   +------+   +------+\n");
	
	printf ("EL BINGO AL QUE VIENES PARA UNA HORA Y TE QUEDAS CINCO!!\n\n\nNORMAS:\n-En caso de afirmacion, contestar con \"SI\". En caso de negacion, contestar con \"NO\".\n-Maximo de 200 personas por partida.\n-Maximo de 20 cartones por partida.\n-Coste del carton: 2$\n\n\n");  //Normas
	system ("pause");
}
