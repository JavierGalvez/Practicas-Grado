#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int contador[32] = {0};
static void handler (int sigNum){
  contador[sigNum]++;
  printf("La señal %d se ha recibido %d veces\n", sigNum, contador[sigNum]);
}

int main(){
  struct sigaction sa;

  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  int i;
  for(i=1; i<32; i++){
    sigaction(i, &sa, NULL
  }
  for(;;){}
}
