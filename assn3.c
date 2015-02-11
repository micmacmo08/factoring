//Michael Morris
//CS 3060-001 Fall 2014
//Assignment #3
/* Promise of Originality
I promise that this source code file has, in it's entirety, been
writthen by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person
this term, I understand that both myself and the student that submitted the
copy will receive a zero on this assignment.
*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int primes[100];
int ind = 0;

void* factor(void* input)
{
	int d = atoi(input);
	int i;
	ind = 0;
	for(i = 2; i <= d; i++){
		if(d % i == 0){
			d = d / i;
			primes[ind] = i;
			i = 1; //set i to 1 so that when it increments, it goes to 2 and tests 2 again for the d
			ind++;
		}
	}
	pthread_exit(0);
}//end factor

int main(int argc,  char *argv[])
{
	int i;
	int j;
	pthread_t t;
	if(argc < 2){ //make sure there are arguments to factor
		printf("Usage: ./assn3 <number to factor>...\n");
		return -1;
	}
	for(i = 1; i < argc; i++){ //make sure the arguments are positive integers
		if(atoi(argv[i]) <= 0){ 
			printf("Arguments must be positive integers\n");
			return -1;
		}
	}
	for(i = 1; i < argc; i++){
		pthread_create(&t, NULL, factor, (void*)argv[i]);
		pthread_join(t, NULL);
		printf("%d: %d", atoi(argv[i]), primes[0]);
		for(j = 1; j < ind; j++) printf(", %d", primes[j]);
		printf("\n");
	}
	return 0;
}//end main
