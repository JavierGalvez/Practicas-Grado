#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
  if(argc != 3)
    exit(-1);

  int fd1[2];
  int fd2[2];
  pid_t PID1, PID2;
  int leidos;

  char middle[10];

  int min, max, mid, val;
  min = atoi(argv[1]);
  max = atoi(argv[2]);
  mid = (max + min) / 2;

  pipe(fd1);
  pipe(fd2);

  if ( (PID1= fork())<0) {
  	perror("\nError en fork");
  	exit(EXIT_FAILURE);
  }
  if(PID1 == 0){
    close(fd1[0]);
    dup2(fd1[1], STDOUT_FILENO);
    sprintf(middle, "%d", mid);
    execl("./esclavo","esclavo",argv[1],middle,NULL);
  }
  else{
    close(fd1[1]);
    while(leidos = read(fd1[0],&val,sizeof(int)) > 0){
      printf("%d\n", val);
    }

    int status;
    wait(&status);
    if ( (PID2= fork())<0) {
      perror("\nError en fork");
      exit(EXIT_FAILURE);
    }
    if(PID2 == 0){
      close(fd2[0]);
      dup2(fd2[1], STDOUT_FILENO);
      sprintf(middle, "%d", mid);
      execl("./esclavo","esclavo",middle,argv[2],NULL);
    }
    else{
      close(fd2[1]);
      while(leidos = read(fd2[0],&val,sizeof(int)) > 0){
        printf("%d\n", val);
      }
    }
  }
}
