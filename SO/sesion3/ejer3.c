#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main(){

	pid_t childpid;
	int nprocs = 21;
	int i;
	/*
		Jerarquía de procesos tipo 1
	*/
/*
	for	(i=1; i < nprocs; i++){
		if ((childpid = fork()) == -1){
			fprintf(stderr, "Could not create child %d: $s\n", i, strerror(errno));
			exit(-1);
		}
		
		if(childpid){
			break;
		}
	}
*/
	/*
		Jerarquía de procesos tipo 2
	*/


	for	(i=1; i < nprocs; i++){
		if ((childpid = fork()) == -1){
			fprintf(stderr, "Could not create child %d: $s\n", i, strerror(errno));
			exit(-1);
		}
	
		if(!childpid){
			printf("Padre: %d\n", i);
			break;
		}
	}
	
	return 0;
}
