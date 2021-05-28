#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>

int main() {
	
	pid_t main = getpid();
	pid_t CPIDb; int prime = 0; int r; int i; int count = 0;
	int p0[2]; int p1[2];
	srand(time(NULL)); 
	pipe(p0); pipe(p1); 

	char *string3;
	char buf[1024];
	
	if(CPIDb = fork() == 0)
	{
		r = (rand() % (100) + 1);
		printf("Child Rando: %d\n", r);
		close(p0[0]); 
		write(p0[1], &r, sizeof(int));
		sleep(2);
		close(p1[0]);
		read(p1[0], buf, sizeof(buf)/sizeof(char));	//  read(fd[0], buf, len); /sizeof(char)

		printf("%s\n", buf);


    }
    if(main==getpid())
    {
		sleep(2);
		close(p0[1]);
		read(p0[0], &r, sizeof(int));
		printf("Parent Rando: %d\n", r);


		if(r == 0)
		{
			string3 = "Your number is not a prime";
			printf("%s", string3);
		}
		else
		{
			for(i = 2; i < r; ++i)
			{
				if (r%i == 0)
				{
					count++;
				}
			}
		}
		if (count>1) {	string3 = "Your number is not a prime";}
		else { string3 = "Your number is prime";}
			printf("%s", string3);

		close(p1[0]); 
		write(p1[1], string3, sizeof(buf)/sizeof(char));
		sleep(4);
	}	
return 0;
}

