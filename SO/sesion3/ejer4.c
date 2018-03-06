#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int n = 5;
  int status;
  pid_t pid;

  if(setvbuf(stdout, NULL, _IONBF,0)){
    perror("\nError en setvbuff");
  }

  int i;
  for(i=0; i < n; i++){
    if((pid = fork()) == -1){
      printf("\nError: %s", strerror(errno));
			exit(-1);
    }

    if(!pid){
			printf("Soy el hijo con PID: %i\n", getpid());
			exit(0);
		}
  }

  for(i=n; i > 0; i--){
    pid = wait(&status);
    printf("Acaba de finalizar mi hijo con pid <%i>\n", pid);
    printf("Sólo me quedan <%i> hijos vivos\n", i);
  }
}
