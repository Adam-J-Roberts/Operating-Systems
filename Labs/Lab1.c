#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main() {
	
	pid_t main = getpid();
	pid_t CPIDb;
	pid_t CPIDc;
	int p0[2]; 
	int p1[2]; 
	int p2[2]; 
	int p3[2]; 
	pipe(p0); 
	pipe(p1); 
	pipe(p2); 
	pipe(p3); 
	
	//Creating second layer of fork tree and passing CPIDb through pipe
	CPIDb = fork();
	if (main == getpid()) //&& CPIDb = 0)
	{
		close(p0[0]); 
		write(p0[1], &CPIDb, sizeof(CPIDb));
		//printf("Parent(%d) send value: %d\n", getpid(), CPIDb);
		close(p0[1]);
	}
	else
	{
		read(p0[0], &CPIDb, sizeof(CPIDb));	//  read(fd[0], buf, len);
		close(p0[0]);
	}	
	//This is for 3rd layer of fork tree
	if(getpid() == CPIDb)
	{
		CPIDc = fork();	
	} 
	if (CPIDc == 0)
	{
		CPIDc = getpid();
		close(p1[0]);
		write(p1[1], &CPIDc, sizeof(CPIDc));
		close(p1[1]);	
	} 
	if (CPIDb== getpid())
	{
		read(p1[0], &CPIDc, sizeof(CPIDc));	//  read(fd[0], buf, len);
		close(p1[0]);
		close(p2[0]);
		write(p2[1], &CPIDc, sizeof(CPIDc));
		close(p2[1]);
	}
	if (main == getpid())
	{
		read(p2[0], &CPIDc, sizeof(CPIDc));	//  read(fd[0], buf, len);
		close(p2[0]);
		printf("This CPID : %d \n    CPIDa: %d CPIDb: %d CPIDc: %d \n", getpid(), main, CPIDb, CPIDc);
		kill(CPIDb, SIGKILL);
		kill(CPIDc, SIGKILL);
	}

	
return 0;
}
