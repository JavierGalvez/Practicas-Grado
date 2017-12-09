//  según la versión de gcc y opciones de optimización usadas, tal vez haga falta
//  usar gcc -fno-omit-frame-pointer si gcc quitara el marco pila (%ebp)

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE (1<<16)	// tamaño suficiente para tiempo apreciable
#define WORD_SIZE 8*sizeof(int)
// unsigned lista[SIZE] = {0x80000000, 0x0010000, 0x00000800, 0x00000001};
unsigned lista[SIZE] = {0x7fffffff, 0xffefffff, 0xfffff7ff, 0xfffffffe, 0x01000024, 0x00356700, 0x8900ac00, 0x00bd00ef};
// unsigned lista[SIZE] = {0x0       , 0x10204080, 0x3590ac06, 0x70b0d0e0, 0xffffffff, 0x12345678, 0x9abcdef0, 0xcafebeef};
// unsigned lista[SIZE];
int resultado=0;

int popcount1(unsigned* array, int len){
  int i, j, ret=0;
  unsigned k;
  for(i=0; i<len; i++){
    k = array[i];
    for(j=0; j<WORD_SIZE; j++){
      ret += k & 0x1;
      k >>= 1;
    }
  }
  return ret;
}

int popcount2(unsigned* array, int len){
  int i, j, ret=0;

  for(i=0; i<len; i++){
    unsigned k = array[i];
    while(k){
      ret += k & 0x1;
      k >>= 1;
    }
  }
  return ret;
}


int popcount3(unsigned* array, int len){
  int i, ret=0;

  for(i=0; i<len; i++){
    unsigned k = array[i];
    asm(
    "bucle:   \n\t"
      "shr %[val] \n"
      "adc $0, %[ret] \n"
      "cmp $0, %[val]  \n"
      "jne bucle  \n"
    : [ret]"+r" (ret)
    : [val] "r" (k)
  );
  }
  return ret;
}

int popcount4(unsigned* array, int len){

  int k, val = 0;
  for(k=0; k<len; k++){
    unsigned x = array[k];
    int i;
    for (i = 0; i < 8; i++) {
      val += x & 0x01010101;
      x >>= 1;
    }
    val += (val >> 16);
    val += (val >> 8);
    val &= 0xFF;
  }
  return val;
}

int popcount5(unsigned* array, int len){
  int k, val = 0;
  for(k=0; k<len; k++){
    unsigned x = array[k];
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    val += (((x + (x >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
  }
  return val;
}

void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;	// gettimeofday() secs-usecs
    long           tv_usecs;	// y sus cuentas

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
}

int main()
{

    crono(popcount1, "popcount (en lenguaje C, for)");
    crono(popcount2, "popcount (en lenguaje C, while)");
    crono(popcount3, "popcount (asm)");
    crono(popcount4, "popcount (libro)");
    crono(popcount5, "popcount (Google)");

    exit(0);
}
