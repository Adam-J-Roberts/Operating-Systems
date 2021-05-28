#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#define MAXTHRDS 10

char *buff[5] = {"Adam", "Amanda", "Kathlyn", "Dutta", "Mr Miyagi"};

//arg is going to be the index of the thread (in this case 5)
void *dosomething(void *arg) 
{
	if(*(int *)arg <= sizeof(buff)/ sizeof(char)) 
	{
		printf("Admin: %s\n", buff[*(int *)arg]);
	}
	else 
	{
		pthread_exit(NULL);
	}
	
	//input argument is a void double pointer
	//returning to pthread_join()
	pthread_exit((void *)buff[*(int *)arg]);
}

int main(int argc, char **argv) {
	pthread_t tid[MAXTHRDS]; int arg[MAXTHRDS]; 
	int i; void *status; int rc;
	int numthrds = 5;//atoi(argv[1]);

	for(i=0; i<numthrds; i++) 
	{
		arg[i] = i;
		//first argument is the address of the thread ID
		//second argument is the attribute (don't want to change anything so pass NULL)
		//third argumet is the function name that you want your threads to execute
		//fourth argument is a void pointer to the address of each thread index
		rc = pthread_create(&tid[i], NULL, dosomething, (void *)&arg[i]);
	}
	//if we have 5 threads-- pthread_join() has to be called 5 times
	for(i=0; i<numthrds;i++) 
	{
		pthread_join(tid[i], &status);
		printf("%s\n", (char *)status);
	}
return 0;
}
