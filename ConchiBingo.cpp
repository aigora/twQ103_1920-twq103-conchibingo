#include <stdio.h>
#include <stdlib.h> //para srand() y rand() 
#include <time.h> //para time() 

int main  (){
	//Zona de declaracion de variables
	int jugadores ,cartones ,i1, i2, a , v[10]={a};
	float dinero;
	
	//Bieve
	printf("Bienvenidos a ConchiBingo.\n\nPor favor introduzca el numero de jugadores: ");// Introduccion al bingo. Pedimos numero de jugadores
	scanf("%d",&jugadores);
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
	
}
