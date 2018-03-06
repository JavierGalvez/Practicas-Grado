// gcc -m32 bomba.c -o bomba
// Javier Gálvez Obispo
#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 5


char password1[] = "010b4f89c47aac50\n";
char password2[] = "385bf97387c65076\n";
char password3[] = "42464933d2bb41d8\n";
int  passcode = 40232423;

void bomb(int defuse){
	if(defuse){
		printf("·······························\n");
		printf("······ bomba desactivada ······\n");
		printf("·······························\n");
		exit(0);
	}
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

int time(int t1, int t2){
	if(t2 - t1 > TLIM)
		return 0;
	return 1;
}

int main(){
	char pass[SIZE];
	char password[] = "3c5573b36b02440a\n";
	int  pasv;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);

	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);

	printf("Introduce el código: ");
	scanf("%i",&pasv);

	gettimeofday(&tv2,NULL);
	if (!time(tv1.tv_sec,tv2.tv_sec)) bomb(0);

	char substr1[SIZE/2];
	char substr2[SIZE/2];

	if(strlen(password) == strlen(pass)){
		snprintf(substr1, 9, "%s", pass);
		snprintf(substr2, 10, "%s", pass+8);
		if(strncmp(substr1, password, 8)) bomb(0);
		if(strncmp(substr2, password+8, 8)) bomb(0);
		int k = pasv - passcode;
		if(k) bomb(0);
		bomb(1);
	}
	else
		bomb(0);
}
