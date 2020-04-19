#include <stdio.h>
#include <stdlib.h> //para srand() y rand() 
#include <time.h> //para time() 

struct Tusuarios {
	char nickname[100];
	float dinero;
	int cartones;
};

int main  (){
	//Zona de declaracion de variables
	FILE*pusuarios(entrada)*pusuarios(salida);
	int nusuarios=0,i1, i2, a , v[10]={a};
	struct Tusuarios usuarios[200];

	printf("Bienvenidos a ConchiBingo.");
	// Abrimos el fichero de los usuarios
	pusuarios=fopen("usuarios.txt","r");
	
	if (pusuarios==NULL){
		printf("No se ha encontrado el fichero usuarios");
		return 0 ;
	}
	//Escribir los datos de los usuarios	
		while (fscanf(pusuarios, "%s %d %f",usuarios[nusuarios].nickname,&usuarios[nusuarios].cartones,&usuarios[nusuarios].dinero) != EOF) {
		fprintf("%s %d %f",usuarios[nusuarios].nickname,usuarios[nusuarios].cartones,usuarios[nusuarios].dinero);
		nusuarios++;
	}
	printf("Hemos registrado %d\n usuarios", nusuarios);
	// Cerramos el fichero
	fclose(pusuarios);
	/*
	printf("\nCada carton cuesta 2 euros y consta de 10 numeros. Jugadores introducir el numero de cartones deseados\n");//Pedimos a cada jugador el numero de cartones 
	
	for(i1=1;i1<=jugadores;i1++) {
		printf("\nJugador %d cuantos cartones quiere: ", i1, cartones);
		scanf("%d",&cartones);
		dinero = cartones*2;
		printf("Son un total de %0.0f euros\n", dinero);
		
		for (i2=1;i2<=cartones;i2++) {
			printf("Este es su carton %d\n", i2);
		}
	}
	*/
}
