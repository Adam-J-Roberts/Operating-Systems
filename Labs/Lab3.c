#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int isprime(int a){
  int n;
  for(n=2;n<=a-1;n++){
    if(a%n == 0)
      return 0;
  }
  return 1;
}


int main(){

  srand(time(NULL));
  int fd[2];
  int fd2[2];
  int message;
 
  char result[10];
  pipe(fd);
  pipe(fd2);
  if(fork() == 0){ //child
    printf("CHILD_PID %d", getpid());
    int r = rand() % 100;
    printf(" random number sent is %d\n", r);
    write(fd[1], &r, sizeof(r)); /*Write arguments for the function write()*/ 
   
    
    read(fd2[0], result, sizeof(result)); /*Write arguments for the function read()*/ 
    printf("CHILD_PID %d, result is %s\n", getpid(), &result);
   
  }
  else{ //parent
    
    read(fd[0], &message, sizeof(message));/*Write arguments for the function read()*/ 
    printf("PARENT_PID %d received the message %d\n",getpid(), message);
    char pr[10]="prime";
    char co[10]="composite";
    if(isprime(message) == 1){
      
      printf("PARENT_PID %d, %d is prime\n",getpid(), message);
      
     write(fd2[1], pr, sizeof(pr)); /*Write arguments for the function write()*/ 
    }
    else{
      char* s= "composite";
      printf("PARENT_PID %d, %d is a composite\n",getpid(),message);
     write(fd2[1], co, sizeof(co));  
    }
     
   	
  }
  return 0;   

}
