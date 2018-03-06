#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(void){
	printf("Identificador del usuario: %d\n", getuid());
	printf("Identificador del usuario efectivo: %d\n", geteuid());
	printf("Identificador del grupo: %d\n", getgid());
	printf("Identificador del grupo efectivo: %d\n", getegid());
}
