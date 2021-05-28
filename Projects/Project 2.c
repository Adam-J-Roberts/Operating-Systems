#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main() {
	
	pid_t main = getpid();
	pid_t CPIDb;
	pid_t CPIDc;
	pid_t CPIDd;
	pid_t CPIDe;
	pid_t CPIDf;
	int fd[2]; 
	pipe(fd); 
	
	//Creating second layer of fork tree and passing CPIDb through pipe
	CPIDb = fork();
	if (main == getpid()) //&& CPIDb = 0)
	{
		close(fd[0]); 
		write(fd[1], &CPIDb, sizeof(CPIDb));
		close(fd[1]);
		CPIDc = fork();	
	}
	else
	{
		read(fd[0], &CPIDb, sizeof(CPIDb));	//  read(fd[0], buf, len);
		close(fd[0]);
	}	
	//This is for 3rd layer of fork tree
	if(getpid() == CPIDb)
	{
		CPIDd = fork();
		if(getpid() == CPIDb)
		{
			CPIDe = fork();
		   	if(getpid() == CPIDb)
			{
				CPIDf = fork();
			}
		}
	}   
	//This is to check what is running and kill child processes.
	printf("This CPID : %d With this PPID: %d\n\n", getpid(), getppid()); 
	if (getpid() == CPIDb)
	{
		sleep(5);
		kill(CPIDd, SIGKILL);
		kill(CPIDe, SIGKILL);
		kill(CPIDf, SIGKILL);
	}
	sleep(6);
	printf("After first kill! \n");
	printf("This CPID : %d With this PPID: %d\n\n", getpid(), getppid());
	if(getpid() == main)
	{
		sleep(10);
		kill(CPIDb, SIGKILL);
		kill(CPIDc, SIGKILL);
	}
	sleep(12);
	printf("After second kill! \n");
	printf("This CPID : %d With this PPID: %d\n\n", getpid(), getppid());
	
return 0;
}
