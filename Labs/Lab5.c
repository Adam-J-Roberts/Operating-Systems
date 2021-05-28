#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define thrds 10

void *thread_fun(void *thrd){
	int tid = *((int *)thrd);
	printf("tid-%d\n",tid);
	pthread_exit(NULL);	
}

int main(){
	pthread_t tid[thrds];
	int i;
	int id[thrds];
	for(i = 0; i < thrds; i++){ 
	/*write your code to remove race-condition  */
		id[i] = i;
		pthread_create(&tid[i], NULL, thread_fun,); /*write the last input argument*/
	}	
	
	pthread_exit(NULL);
	return 0;
}
