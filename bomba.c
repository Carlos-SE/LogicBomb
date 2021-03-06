// gcc -Og bomba.c -o bomba -no-pie -fno-guess-branch-probability -lm

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval
#include <math.h>

#define SIZE 100
#define TLIM 5

char password[]="JbjUnpxrq!\n";	// contraseña
int  passcode  = 2642;			// pin

void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"·························\n"
		"··· bomba desactivada ···\n"
		"·························\n"
		"\n");
	exit(0);
}

/**
 * @brief aplicación de ROT13 a la contraseña
 * @param pw password
 * @param size strlen(password)
 */
char * encode(char * pw, int size){
	const int ROT = 13;
	char * encoded = malloc((size)*sizeof(*encoded));
	char c;
	for (int i = 0; i < size; i++){

		c = pw[i];
		if (c >= 'a' && c <= 'z'){	//si el caracter es una letra minúscula
			if(c + ROT <= 'z'){
				c += ROT;
			}
			else{
				c -= ROT;
			}
		}
		else if ( c >= 'A' && c <= 'Z'){ //si el caracter es letra mayúscula
			if (c + ROT <= 'Z'){
				c += ROT; 
			}
			else{
				c -= ROT;
			}
		}

		encoded[i] = c;
		
	}

	

	return encoded;
}


int pinEncode(int pin){
    const int MAX = 10000;
    int encoded;

	encoded = MAX - pin;

	return encoded;
}

int main(){
	char pw[SIZE];
	int  pc, n;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	if    (	strncmp(encode(pw, strlen(pw)),password,sizeof(password)) )   //compare string pw codificada con password
	    boom();

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );
	
	if    (	pinEncode(pc) != passcode )
	    boom();

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}
