#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
  if (argc != 4){
    printf("Error en el número de argumentos");
    exit(-1);
  }

  if(*argv[2] != '|'){
    printf("Error en el segundo argumento\n");
    exit(-1);
  }

  int fd[2];
  pipe(fd);

  pid_t pid;

  if((pid = fork()) < 0){
    perror("Error en fork");
  }

  if(pid == 0){   // Hijo
    close(1);         // Cerrar salida estándar
    close(fd[0]);     // Cerrar entrada pipe
    if(fcntl(fd[1], F_DUPFD, 1) == -1){     // Redireccionar salida estándar a salida pipe
      perror("Fallo en fcntl");
    }
    execlp(argv[1],argv[1],NULL);

  } else {       // Padre
    close(0);         // Cerrar entrada estándar
    close(fd[1]);     // Cerrar salida pipe
    if(fcntl(fd[0], F_DUPFD, 0) == -1){     // Redireccionar entrada estándar a entrada pipe
      perror("Fallo en fcntl");
    }

    wait(NULL);
    execlp(argv[3],argv[3],NULL);
  }
}
