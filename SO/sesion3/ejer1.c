#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error en el número de argumentos.\n");
		exit(-1);
	}
	
	int val = atoi(argv[1]);
	int err = fork();
	
	if(err == 0){
		if(val % 2 == 0)
			printf("El número introducido es par.\n");
		else
			printf("El número introducido es impar.\n");
	}
	
	else if(err > 0){
		if(val % 4 == 0)
			printf("El número introducido es divisible por 4.\n");
		else
			printf("El número introducido no es divisible por 4.\n");
	}
}
