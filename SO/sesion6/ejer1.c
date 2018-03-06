#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){
  if (argc != 4){
    printf("Error en el número de argumentos");
    exit(-1);
  }

  int fd;
  if((fd=open(argv[3], O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
    perror("Error en open");
    exit(-1);
  }

  int closed;
  if(*argv[2] == '<'){
    close(0);
  } else if(*argv[2] == '>'){
    close(1);
  } else {
    printf("Error en el segundo argumento\n");
    exit(-1);
  }

  if(fcntl(fd, F_DUPFD, 0) == -1){
    perror("Fallo en fcntl");
  }
  execlp(argv[1],argv[1],NULL);
}
