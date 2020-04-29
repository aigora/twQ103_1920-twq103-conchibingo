#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NFIL 3
#define NCOL 5
/*
IDEAS
-Numeros calientes
-Guardar datos para futuras partidas con partidas jugadas, ganadas y perdidos
-Errores en caso de introducir datos iguales
-Variacion del coste de cada partida
- Ingresos

*/


//Creamos la estrucutra de cada usuario
struct Tusuarios {
	char nickname[100];
	float dinero;
	int cartones;
	int part_jugadas, part_ganadas, part_perdidas;
};
struct TCartones{
	int linea1[100];
	int linea2[100];
	int linea3[100];
};

int rellenar_cartones();

int main  () {
	//DECLARACION DE VARIABLES
	FILE * fusuarios;
	int i=0, nusuarios;
	float ingreso = 0;
	char opcion[3] = "SI";
	struct Tusuarios usuario[200]; //200 es el número máximo de usuarios que podemos introducir
	
	// Menú
	printf("\n");
	printf("+------   +------+   +        +   +------  +      +    -----    +-----+     -----   +        +   +-------   +------+\n");
	printf("|         |      |   |\\       |   |        |      |      |      |      \\      |     |\\       |   |          |      |\n");
	printf("|         |      |   |  \\     |   |        |______|      |      |_____ /      |     |  \\     |   |          |      |\n");
	printf("|         |      |   |    \\   |   |        |      |      |      |      \\      |     |    \\   |   |  ----+   |      |\n");
	printf("|         |      |   |      \\ |   |        |      |      |      |      /      |     |      \\ |   |      |   |      |\n");
	printf("+------   +------+   +        +   +------  +      +    -----    +-----+     -----   +        +   +------+   +------+\n");
	
	printf("\n\n\nNORMAS:\n-Maximo de 200 personas por partida.\n-Maximo de 20 cartones por partida.\n\n\n");
	
	//Abrimos fichero en modo write para escribir los datos de los usuarios en él
	fusuarios = fopen("usuarios.txt", "a");
	
	//En caso de no encontrar el fichero se crea el error al encontrarlo
	if (fusuarios == NULL) {
		printf ("No se ha encontrado el archivo\n");
		return 0;
	}
	
	//Escribir el nº de usuarios que van a jugar la partida
	printf ("Ingresar el numero de usuarios que van a jugar la partida: ");
	scanf ("%i", &nusuarios);
	
	if (nusuarios < 1  ||  nusuarios > 200) {
		do {
			printf("\nNo se puede jugar con ese numero de jugadores. Escriba de nuevo la cantidad de jugadores de la partida: ");
			scanf("%i", &nusuarios);
		} while (nusuarios < 1  ||  nusuarios > 200);
	}
	
	printf("\n");
	
	system("cls");
	
	//Pedir el nombre, nºcartones y el dinero de los usuarios 
	do{
		//Pedir nicknames
		printf ("\nNickname %i: ", i+1);
		scanf("%s", usuario[i].nickname);
		
		//En caso de repetirse el nombre, pedirlo de nuevo
		if (strcmp(usuario[i].nickname,usuario[i-1].nickname) == 0) {
			do {
				printf("El nickname introducido no es valido puesto que ya esta en uso. Introduzca otro para el usuario %i: ", i+1);
				scanf("%s", usuario[i].nickname);
			} while (strcmp(usuario[i].nickname,usuario[i-1].nickname) == 0);
		}
		
		//Pedir nº de cartones
		printf ("\nCantidad de cartones de %s: ", usuario[i].nickname);
		scanf("%i", &usuario[i].cartones);
		
		//En caso de comando no valido, pedirlo de nuevo
		if (usuario[i].cartones < 1  ||  usuario[i].cartones > 20) {
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
			
			//Pedir ingresar dinero
			printf("El usuario %s no tiene suficiente dinero como para jugar la partida con ese numero de cartones. Contestar \"SI\" si desea realizar algun ingreso: ", usuario[i].nickname);
			scanf("%s", opcion);
				
			//Si ingresa dinero
			if (strcmp(opcion,"SI") == 0  || strcmp(opcion,"si") == 0  ||  strcmp(opcion,"Si") == 0) {
				printf("Ingresar dinero: ");
				scanf("%f", &ingreso);
				usuario[i].dinero = usuario[i].dinero + ingreso;
				printf("El usuario %s ha realizado un ingreso de %0.2f $ por lo que ahora dispone de %0.2f $", usuario[i].nickname, ingreso, usuario[i].dinero);
			} 
			//Si no ingresa dinero
			else {
				if (usuario[i].dinero <2) {
					printf("\nNo puede reducir mas el numero de cartones. No puede jugar");
				}
				printf("No puede jugar con esos cartones, por lo que debe reducir la cantidad. Escriba cuantos quiere: ");
				scanf("%i", &usuario[i].cartones);
		 	}
			ingreso = 0;
			
			if (usuario[i].dinero >= (usuario[i].cartones * 2)) {
				printf(" Ahora puede jugar la partida.\n");
			} else {
				do{
					if (usuario[i].dinero < (usuario[i].cartones * 2)) {
						printf("No puede jugar con esos cartones, por lo que debe reducir la cantidad. Escriba cuantos quiere: ");
						scanf("%i", &usuario[i].cartones);
						
						if (usuario[i].cartones < 1) {
							printf("No puede reducir mas el numero de cartones. No puede jugar");
							break;
						}
					}					
				} while (usuario[i].dinero < (usuario[i].cartones * 2));
			}
		}
		
		printf("\n");
		
		//Escribir todo esto en el fichero
		fprintf(fusuarios, "%s\t\t%d\t\t%0.2f\n", usuario[i].nickname, usuario[i].cartones, usuario[i].dinero);
		i++;	
	} while (i<nusuarios);
	
	//Cerramos el fichero
	fclose (fusuarios);

	//Volvemos a abrir el fichero en modo lectura para trabajar con esos datos
	fusuarios = fopen("usuarios.txt","r");
	
	//Leemos todos os datos del fichero
	i = 0;
	while (fscanf (fusuarios, "%s %d %f", usuario[i].nickname, &usuario[i].cartones, &usuario[i].dinero) != EOF) {
		fscanf (fusuarios, "%s %d %f", usuario[i].nickname, &usuario[i].cartones, &usuario[i].dinero);
		i++;
	}
}

// Aqui esta la funcion de como rellenar los cartones que se les darán a los jugadores
/*int rellenar_cartones() {    
	struct TCartones carton[100];
	int i, j=0, k, numero, repetido;
	int numeros[NFIL][NCOL];
	int cartones;
	srand(time(NULL));
	scanf("%d", &cartones);
	
	for(i=0;i<cartones;i++) {
		for(j=0;j<5;j++) {
		do { 
		numero=(rand()%89)+1;// Queremos sacar un numero aleatoriamente entre el 1 y el 90
		repetido=0; //Suponemos que no esta repetido 
		for(k=0;k<i;k++) { //Comprobamos que no lo esta con los numeros salidos anteriormente
			if(carton[i].linea1[k]==numero) { 
				repetido=1; //si esta repetido, sale del bucle for
				break;
				}
			}
		}while(repetido); 
	carton[i].linea1[j]=numero; // Aqui ya sabemos que es distinto y vamos a por el siguiente 
	}
	for(j=0;j<5;j++) {
		do { 
		numero=(rand()%89)+1;// Queremos sacar un numero aleatoriamente entre el 1 y el 90
		repetido=0; //Suponemos que no esta repetido 
		for(k=0;k<i;k++) { //Comprobamos que no lo esta con los numeros salidos anteriormente
			if(carton[i].linea2[k]==numero) { 
				repetido=1; //si esta repetido, sale del bucle for
				break;
				}
			}
		}while(repetido); 
	carton[i].linea2[j]=numero; // Aqui ya sabemos que es distinto y vamos a por el siguiente 
	}
	for(j=0;j<5;j++) {
		do { 
		numero=(rand()%89)+1;// Queremos sacar un numero aleatoriamente entre el 1 y el 90
		repetido=0; //Suponemos que no esta repetido 
		for(k=0;k<i;k++) { //Comprobamos que no lo esta con los numeros salidos anteriormente
			if(carton[i].linea3[k]==numero) { 
				repetido=1; //si esta repetido, sale del bucle for
				break;
				}
			}
		}while(repetido); 
	carton[i].linea3[j]=numero; // Aqui ya sabemos que es distinto y vamos a por el siguiente 
	}
}
	for(i=0;i<cartones;i++) {
		for(j=0;j<5;j++) {
			printf("%d\t", carton[i].linea1[j]);
		}
		printf("\n");
		for(j=0;j<5;j++) {
			printf("%d\t", carton[i].linea2[j]);
		}
		printf("\n");
		for(j=0;j<5;j++) {
			printf("%d\t", carton[i].linea3[j]);
		}
		printf("\n \n");
	}
} */
