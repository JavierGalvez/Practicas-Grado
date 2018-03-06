#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char* argv[]){
  int cont = 1, leidos;
  int fi, fo;
  char cadena[30];
  char cad_bloque[40];
  char newline[2] = "\n";
  char caracter[1];
  int num_char = 1;


  if (argc > 2){
    exit(-1);
  }

  if (argc == 2){
    fi = open(argv[1], O_RDONLY);
  } else {
    fi = STDIN_FILENO;
  }

  if ((fo = open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR)) < 0){
    printf("\nError al abrir el archivo");
    exit(-1);
  }

  sprintf(cad_bloque, "El numero de bloques es <%d>\n", cont);
  write(fo, cad_bloque, strlen(cad_bloque));
  sprintf(cad_bloque, "%s%d\n", "Bloque ", cont);
  write(fo, cad_bloque, strlen(cad_bloque));
  cont++;

  while((leidos = read(fi, caracter, 1)) != 0){
    if((num_char % 80) == 0){
        write(fo, newline, strlen(newline));
        sprintf(cad_bloque, "%s%d\n", "Bloque ", cont);
        write(fo, cad_bloque, strlen(cad_bloque));
        cont++;
      }
    write(fo, caracter, 1);
    num_char++;
  }

  sprintf(cad_bloque, "El numero de bloques es <%d>\n", cont);
  lseek(fo,0,SEEK_SET);
  write(fo, cad_bloque, strlen(cad_bloque));
  close(fi);
  close(fo);
  return 0;
}
