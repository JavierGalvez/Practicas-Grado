#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>


int main(int argc, char* argv[]){
  if(argc != 3){
    printf("Error en el número de argumetos\n");
    exit(-1);
  }

  char* path;
  unsigned int octal;
  DIR* dir;
  struct dirent* leido;
  char pathfile[100];
  unsigned int permisos;
  struct stat atributos;

  path = argv[1];
  octal = strtol(argv[2], NULL, 8);

  dir = opendir(path);

  while ((leido=(readdir(dir))) != NULL){
    sprintf(pathfile, "%s/%s", path, leido->d_name);

    if(stat(pathfile,&atributos) < 0) {
      printf("\nError al intentar acceder a los atributos de %s", pathfile);
      perror("\nError en lstat");
      exit(-1);
      }

    if(S_ISREG(atributos.st_mode)){
      permisos = atributos.st_mode;

      if(chmod(pathfile, octal) < 0) {
      	printf("\nError: %s", strerror(errno));
      	exit(EXIT_FAILURE);
      } else {
        printf("%s : <%o> <%o>\n", pathfile, permisos, octal);
      }
    }
  }
}
