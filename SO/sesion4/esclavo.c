#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int isPrime (int n){
  int i;
  int root = sqrt(n);
  for(i=2; i <= root; i++){
    if(!(n % i))
      return 0;
  }
  return 1;
}

int main(int argc, char* argv[]){
  if(argc != 3)
    exit(-1);

  int min, max;

  min = atoi(argv[1]);
  max = atoi(argv[2]);

  int i;
  for(i = min; i <= max; i++){
    if(isPrime(i))
      write(STDOUT_FILENO, &i, sizeof(int));
  }

  return 0;
}
