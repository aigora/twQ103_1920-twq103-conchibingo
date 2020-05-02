#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int main (){
	srand(time(NULL)); // iniciamos numero aleatorio
	int i,j,num,repetido,vector[3];
	char c,linea,bingo;

for(i=0;i<90;i++){ // hacemos un bucle para que se repita hasta bingo 
	num =(rand()%89)+1;
	repetido=0;
	system("pause");
		for(j=0; j < i; j++){
        	if(num==vector[j])
          repetido=-1;           
          }
    vector [ i ] =num;
    printf("     ----  \n "  );
    printf("    | %d |    " ,num);
    printf("     ----  \n "  );
	}
}
