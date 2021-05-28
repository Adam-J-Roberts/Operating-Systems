//---------------------------------------Lab_Assignment-7------------------------------------------------------------------
#include <stdlib.h>	/* needed to define exit() */
#include <unistd.h>	/* needed to define getpid() */
#include <stdio.h>	/* needed for printf() */

int main(int argc, char **argv) {
	char *args[] = {"ls", "-l", "/usr/foldername", 0}; /*specify foldername */

	printf("About to run ls\n");
	execvp("ls", args);/*write arguments command and path. It takes default environment*/
	perror("execvp");	/* if we get here, execvp failed */
	exit(1);
}
