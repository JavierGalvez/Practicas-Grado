//  según la versión de gcc y opciones de optimización usadas, tal vez haga falta
//  usar gcc -fno-omit-frame-pointer si gcc quitara el marco pila (%ebp)

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE (1<<16)	// tamaño suficiente para tiempo apreciable
#define WORD_SIZE 8*sizeof(int)
// unsigned lista[SIZE] = {0x80000000, 0x0010000, 0x00000800, 0x00000001};
// unsigned lista[SIZE] = {0x7fffffff, 0xffefffff, 0xfffff7ff, 0xfffffffe, 0x01000024, 0x00356700, 0x8900ac00, 0x00bd00ef};
// unsigned lista[SIZE] = {0x0       , 0x10204080, 0x3590ac06, 0x70b0d0e0, 0xffffffff, 0x12345678, 0x9abcdef0, 0xcafebeef};
unsigned lista[SIZE];
int resultado=0;

int parity1(unsigned* array, int len){
  int i, j;
  int ret = 0;
  for(i=0; i<len; i++){
    unsigned k = array[i];
    int val = 0;
    for(j=0; j<WORD_SIZE; j++){
      val ^= k & 0x1;
      k >>= 1;
    }
    ret += val;
  }
  return ret;
}

int parity2(unsigned* array, int len){
  int i;
  int ret = 0, val = 0;
  unsigned k;
  for(i=0; i<len; i++){
    val = 0;
    k = array[i];
    while(k){
      val ^= k & 0x1;
      k >>= 1;
    }
    ret += val;
  }
  return ret;
}

int parity3(unsigned* array, int len){
  int i;
  int ret = 0, val = 0;
  unsigned k;
  for(i=0; i<len; i++){
    val = 0;
    k = array[i];
    while(k){
      val ^= k;
      k >>= 1;
    }
    ret += val & 0x1;
  }
  return ret;
}

int parity4(unsigned* array, int len){
  int i, ret=0, val;
  unsigned k;
  for(i=0; i<len; i++){
    k = array[i];
    val = 0;
    asm(
    "bucle:             \n\t"
      "xor %[k], %[val] \n"
      "shr %[k]         \n"
      "jnz bucle        \n"
      "and $1, %[val]   \n"
    : [val]"+r" (val)
    : [k] "r" (k)
  );
    ret += val;
  }
  return ret;
}

int parity5(unsigned* array, int len){

  int k, i, val = 0, ret = 0;
  unsigned x;
  for(k=0; k<len; k++){
    x = array[k];
    for (i = 16; i >= 1; i /= 2) {
      x ^= x >> i;
    }
    ret += x & 0x1;
  }
  return ret;
}

int parity6(unsigned* array, int len){

  int k, ret = 0;
  unsigned x;
  for(k=0; k<len; k++){
    x = array[k];
    asm(
    "mov %[x], %%edx    \n"
    "shr $16, %[x]         \n"
    "xor %[x], %%edx  \n"
    "xor %%dh, %%dl   \n"
    "setpo %%dl       \n"
    "movzx %%dl, %[x]   \n"
    : [x] "+r" (x)
    :
    : "edx"
    );
    ret += x;
  }
  return ret;
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
    int i;			// inicializar array
    for(i=0; i < SIZE; i++){
      lista[i] = i;
    }

    crono(parity1, "parity (en lenguaje C, for)");
    crono(parity2, "parity (en lenguaje C, while)");
    crono(parity3, "parity (libro)");
    crono(parity4, "parity (asm)");
    crono(parity5, "parity (arbol)");
    crono(parity6, "parity (arbol + asm)");
    exit(0);
}
