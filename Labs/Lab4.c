#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define SIZE 10

// 0 and 1 are assumed to be prime
// function only works for single digits
int primeCheck(char digit){ //0 - not prime. 1 - prime.
	if(digit == '0' || digit == '1' || digit == '2' || digit == '3' || digit == '5' || digit == '7')
		return 1;
	return 0;
}

void *thread_fun(void *digit){
	int *check = malloc(sizeof(int));
	*check = primeCheck(*(char *)digit);
	pthread_exit((void *)check);	
}

int lencheck(char *buffer){
	int counter = 0;
	while(buffer[counter] != 0)
		counter++;
	return counter;
}

int main(){
	pthread_t tid[SIZE];
	char input[SIZE];
	printf("Enter an integer of atmost %d digits: ", SIZE);
	scanf("%s", &input);
	int count;		
	if((count = lencheck(input)) > SIZE){
		printf("Entered number has %d digits which is more than %d\n", count, SIZE);
		return 0;
	}

	int i;
	for(i = 0; i < count; i++){
		pthread_create(&tid[i], NULL, thread_fun, (void *)&input[i] ); /*write the last input argument*/
	}	
	
	for(i = 0; i < count; i++){
		void *digit;
		pthread_join(tid[i], &digit); /*write input arguments*/
		input[i] = *(int *)digit + '0';
		free(digit);
	}

	for(i = 0; i < count; i++){
		printf("%c from TH-%d\n", input[i], i);
	}
	printf("\nCOMPLETE BINARY STRING:\n%s\n", input);

	return 0;
}
