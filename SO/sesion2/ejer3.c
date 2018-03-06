#define _XOPEN_SOURCE 500
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include <ftw.h>

int visitar(const char* path, const struct stat* atributos, int flags, struct FTW* s) {
    if(stat(path,atributos) < 0) {
      printf("\nError al intentar acceder a los atributos de %s", path);
      perror("\nError en latributos");
      exit(-1);
      }

      if (S_ISREG(atributos->st_mode)){
        printf("%s \t %ld \n", path, atributos->st_ino);
      }

    return 0;
}

int main(int argc, char* argv[]) {
  printf("Los i-nodos son:\n");
  if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
    perror("nftw");
  }
}
