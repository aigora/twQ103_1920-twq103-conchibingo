#include <stdio.h>
#include <stdlib.h> //para srand() y rand() 
#include <time.h> //para time() 

int main  (){
	int j ,c,i,a , v[10]={a};

	
	printf("Bienvenidos a ConchiBingo .\n Por favor introduzca el numero de jugadores\n");// Introduccion al bingo. Pedimos numero de jugadores
	scanf("%d",&j);
	printf("Cada carton consta de 10 numeros. Jugadores introducir el numero de cartones\n");//Pedimos a cada jugador el numero de cartones 
	
	for (i=1;i<=j;i++) {
		printf("Jugador %d cuantos cartones quiere:",i,c);
		scanf("%d",&c);
	}
	
	srand(time(NULL));//Iniciamos numeros aleatorios
	a=rand()%101; //generaramos numero aleatorio de 0 a 100
	printf("%d",&v[10]); //hola ambalmejwkbfueg
}
