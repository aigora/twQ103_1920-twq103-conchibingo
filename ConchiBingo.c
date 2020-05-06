#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NFIL 3  //La cantidad de filas que hay en un carton
#define NCOL 5  //La cantidad de columnas que hay en un carton

/*
IDEAS
-Numeros calientes
-Guardar datos para futuras partidas con partidas jugadas, ganadas y perdidos
-Ranking
*/

//Creamos la estrucutra necesaria para los datos de cada usuario
struct Tusuarios {
	char nickname[100];  //Nombre de jugador
	float dinero;  //Dinero de jugador
	int cartones;  //Numero de cartones para la partida
	int part_jugadas, bingos_totales, lineas_totales;  //Datos para el ranking total
};

//Creamos la estructura necesaria para crear los cartones
struct TCartones {
	int linea1[100];  
	int linea2[100];
	int linea3[100];
};

int rellenear_cartones();


int main  () {
	
	//DECLARACION DE VARIABLES
	FILE * fusuarios;  //Fichero para la partida
	FILE * franking;  //Fichero para el ranking general
	int i=0, j=-1;  //Variables para bucles
	int num, nusuarios, repetido;  //Para la bola del bombo y el numero de usuarios
	int vector[3];  //Para la bola del bombo
	float ingreso = 0;  //Cantidad de ingreso
	char c, linea, bingo;  //Para cantar linea y bingo
	char opcion [50];  //Para elecciones
	char igual_nickname[100];  //Para la busqueda de nicknames iguales
	
	struct Tusuarios usuario[200]; //200 es el número máximo de usuarios que podemos introducir
	
	srand(time(NULL)); //Iniciamos numero aleatorio
	
	// Menú
	printf("\n");
	printf("+------   +------+   +        +   +------  +      +    -----    +-----+     -----   +        +   +-------   +------+\n");
	printf("|         |      |   |\\       |   |        |      |      |      |      \\      |     |\\       |   |          |      |\n");
	printf("|         |      |   |  \\     |   |        |______|      |      |_____ /      |     |  \\     |   |          |      |\n");
	printf("|         |      |   |    \\   |   |        |      |      |      |      \\      |     |    \\   |   |  ----+   |      |\n");
	printf("|         |      |   |      \\ |   |        |      |      |      |      /      |     |      \\ |   |      |   |      |\n");
	printf("+------   +------+   +        +   +------  +      +    -----    +-----+     -----   +        +   +------+   +------+\n");
	
	printf ("EL BINGO AL QUE VIENES PARA UNA HORA Y TE QUEDAS CINCO!!\n\n\nNORMAS:\n-En caso de afirmacion, contestar con \"SI\". En caso de negacion, contestar con \"NO\".\n-Maximo de 200 personas por partida.\n-Maximo de 20 cartones por partida.\n-Coste del carton: 2$\n\n\n");  //Normas
	system ("pause");
//	system("cls");
	
/*	//Volvemos a abrir el fichero en modo lectura para trabajar con esos datos
	fusuarios = fopen("usuarios.txt","r");
	
	//En caso de no encontrar el fichero se crea el error al encontrarlo
	if (fusuarios == NULL) {
		printf ("No se ha encontrado el archivo\n");
		return 0;
	}
	
	//Leemos todos os datos del fichero
	while (fscanf (fusuarios, "%s %d %f", usuario[i].nickname, &usuario[i].cartones, &usuario[i].dinero) != EOF) {
		fscanf (fusuarios, "%s %d %f", usuario[i].nickname, &usuario[i].cartones, &usuario[i].dinero);
		i++;
	}
	i = 0;
	//Cerramos el fichero abierto en modo "read"
	fclose (fusuarios);
	
	//Abrimos fichero en modo write para escribir los datos de los usuarios en él
	fusuarios = fopen("usuarios.txt", "a");
	
	//En caso de no encontrar el fichero se crea el error al encontrarlo
	if (fusuarios == NULL) {
		printf ("No se ha encontrado el archivo\n");
		return 0;
	}
	
	printf("\nIngresar el numero de jugadores de la partida: ");
	fflush(stdin);
	scanf("%i", &nusuarios);
*/
	
	
	//PRUEBA
	//Pedir mantener o borrar jugadores
	printf ("\nEscribir\"MANTENER\" si se desea que jueguen tambien los jugadores de la partida anterior.\nEscribir \"BORRAR\" si se desea borrar a todos los usuarios anteriores de la partida actual.\n\n\n*NOTA: Si se selecciona borrar, se borran a todos los usuarios de la partida, no del ranking.\n\n\n");  //Dar la opcion de borrar o de mantener los datos de los usuarios
	fflush(stdin);
	gets(opcion);
	
	//En caso de no introducir algo válido
	do{
		if (strcmp(opcion,"MANTENER") == 0  ||  strcmp(opcion,"mantener") == 0  ||  strcmp(opcion,"BORRAR") == 0  ||  strcmp(opcion,"borrar") == 0) {
			break;
		}
		printf ("Se ha introducido una respuesta no valida.\n\"MANTENER\" si se desea que jueguen tambien los jugadores de la partida anterior.\n\"BORRAR\" si se desea borrar a los usuarios anteriores de la partida actual.\n\n");
		fflush(stdin);
		gets(opcion);
	} while (strcmp(opcion,"MANTENER") != 0  ||  strcmp(opcion,"mantener") != 0  ||  strcmp(opcion,"BORRAR") != 0  ||  strcmp(opcion,"borrar") != 0);
	
	
	//En caso de mantener los usuarios en la partida
	if (strcmp(opcion,"MANTENER") == 0  ||  strcmp(opcion,"mantener") == 0) {
		
		//Abrir el fichero para añadir datos. Se mantienen
		fusuarios = fopen("usuarios.txt", "r");
		
		//En caso de no encntrar el fichero
		if (fusuarios == NULL) {
			printf ("\n***ERROR***\nNo se ha encontrado el fichero necesario para la correcta realizacion del programa\n");
			return 0;
		}
		
//		system("cls");
		printf("\nEn la partida constan los jugadores con los siguientes datos:\n");
		
		//Leer el fichero entero
		i = 0;
		while (fscanf (fusuarios, "%s %d %f", usuario[i].nickname, &usuario[i].cartones, &usuario[i].dinero) != EOF) {
			fscanf (fusuarios, "%s %d %f", usuario[i].nickname, &usuario[i].cartones, &usuario[i].dinero);
			printf("\nUsuario %d: %s\nDinero de %s: %0.2f\n", i+1, usuario[i].nickname, usuario[i].nickname, usuario[i].dinero);  //Escribir los datos del fichero por pantalla
			i++;
		}
		
		//Preguntar si se quieren añadir usuarios
		printf ("Escribir si se desea agregar usuarios: ");
		fflush(stdin);
		gets(opcion);
		
		do{  //Se pide de nuevo la respuesta por no escribir "SI"  "si"  "NO" o "no"
			if (strcmp(opcion,"SI") == 0  ||  strcmp(opcion,"si") == 0  ||  strcmp(opcion,"NO") == 0  || strcmp(opcion,"no") == 0) {
				break;
			}
			printf("Se ha introducido una respuesta no valida.\n\"SI\" si se desea agregar jugadores.\n\"NO\" si no se desea agregar jugadores.\n\n");
			fflush(stdin);
			gets(opcion);
		} while (strcmp(opcion,"SI") != 0  ||  strcmp(opcion,"si") != 0  ||  strcmp(opcion,"NO") != 0  || strcmp(opcion,"no") != 0);	
	}  
	//En caso de borrar los usuarios del partida
	else if (strcmp(opcion,"BORRAR") == 0  ||  strcmp(opcion,"borrar") == 0) {
		fusuarios = fopen("usuarios.txt","w");
	}

	//SEGURO
	//Controlar el numero de usuarios con los que se juegan
	if (nusuarios < 1 || nusuarios > 200) {
		do {
			printf("No se puede jugar con esos jugadores. Escriba de nuevo la cantidad de jugadores de la partida: "); 
			fflush(stdin);
			scanf("%i", &nusuarios);
		} while (nusuarios < 1  ||  nusuarios > 200);
	}
	
	
//	system ("cls");
	
	//Pedir el nombre, nºcartones y el dinero de los usuarios 
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
		
		
		//Pedir nº de cartones
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
					system("pause");
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
						system ("pause");
					} 
					else {  //Si ingresa y le llega para jugar 
						printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
						system ("pause");
					}
				}
			}  
			else {  //No ingresa y tienes menos de 2$
				if (usuario[i].dinero < 2) {
				printf("\n\n*NOTIFICACION: El usuario %s no puede jugar con ningun carton.\n\n\n", usuario[i].nickname);
				system("pause");
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
						system ("pause");
					} 
					else {
						printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
						system ("pause");
					}
				}
			} 
		} //Si tiene dinero
		else {
			printf ("\n\n*NOTIFICACION: El usuario %s ahora puede jugar\n\n\n", usuario[i].nickname);
			system ("pause");
		}
		
		system ("cls");
		ingreso = 0;
		
		//Escribir todo esto en el fichero
		fprintf(fusuarios, "%s\t %d\t %0.2f \n", usuario[i].nickname, usuario[i].cartones, usuario[i].dinero);
		i++;	
	} while (i<nusuarios);
	
	//Cerramos el fichero
	fclose (fusuarios);
	
	
	//FUNCIONAMIENTO DEL BOMBO	
	for(i=0;i<90;i++){  //Hacemos un bucle para que se repita hasta bingo 
		num =(rand()%89)+1;  //Sacar numero aleatorio
		repetido = 0;
		system("pause");
			for(j=0; j<i; j++){
	        	if(num == vector[j])
	          repetido =-1;   
			  break;        
	          }
	    vector [ i ] =num;
	    printf("\t----\t\n");
	    printf("\t| %d |\t" ,num);
	    printf("\t----\t\n");
	}
	
}


//FUNCION DE LOS CARTONES
int rellenar_cartones() { 
   
	struct TCartones carton[100];
	int i, j=0, k, numero, repetido;
	int numeros[NFIL][NCOL];
	int cartones;
	srand(time(NULL));
	scanf("%d", &cartones);
	
	//Para crear e imprimir los cartones
	for(i=0;i<cartones;i++) {
		
		//Para crear los numeros de la primera linea
		for(j=0;j<5;j++) {
			do { 
				numero=(rand()%89)+1;  //Queremos sacar un numero aleatoriamente entre el 1 y el 90
				repetido=0;  //Suponemos que no esta repetido 
				
				for(k=0;k<i;k++) {  //Comprobamos que no lo esta con los numeros salidos anteriormente
					if(carton[i].linea1[k]==numero) { 
						repetido=1;  //Si esta repetido, sale del bucle for
						break;
					}
				}	
			} while(repetido); 
			
			carton[i].linea1[j]=numero;  //Aqui ya sabemos que es distinto y vamos a por el siguiente 
		}
		
		//Para crear los numeros de la primera linea
		for(j=0;j<5;j++) {
			do { 
				numero=(rand()%89)+1;  //Queremos sacar un numero aleatoriamente entre el 1 y el 90
				repetido=0;  //Suponemos que no esta repetido 
				
				for(k=0;k<i;k++) {  //Comprobamos que no lo esta con los numeros salidos anteriormente
					if(carton[i].linea2[k]==numero) { 
						repetido=1;  //Si esta repetido, sale del bucle for
						break;
					}
				}
			} while(repetido); 
			
			carton[i].linea2[j]=numero;  //Aqui ya sabemos que es distinto y vamos a por el siguiente 
		}
		
		for(j=0;j<5;j++) {
			do { 
				numero=(rand()%89)+1;  //Queremos sacar un numero aleatoriamente entre el 1 y el 90
				repetido=0;  //Suponemos que no esta repetido
				 
				for(k=0;k<i;k++) {  //Comprobamos que no lo esta con los numeros salidos anteriormente
					if(carton[i].linea3[k]==numero) { 
						repetido=1;  //Si esta repetido, sale del bucle for
						break;
					}
				}
			} while(repetido); 
			
			carton[i].linea3[j]=numero;  //Aqui ya sabemos que es distinto y vamos a por el siguiente 
		}
	}
	
	for(i=0;i<cartones;i++) {
		for(j=0;j<5;j++) {
			printf("%d\t", carton[i].linea1[j]);  //Imprimir los numeros de la primera linea
		}
		printf("\n");
		for(j=0;j<5;j++) {
			printf("%d\t", carton[i].linea2[j]);  //Imprimr los numeros de la segunda linea
		}
		printf("\n");
		for(j=0;j<5;j++) {
			printf("%d\t", carton[i].linea3[j]);  //Imprimir los nueros de la tercera linea
		}
		printf("\n\n");
	}
}
