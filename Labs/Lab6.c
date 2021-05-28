//----------------------------------------------Lab_Assignment-6------------------------------------------------------------
//this code execute unix LIST command within main using execve
//int execve(const char *path, char *const argv[], char *const envp[]); [defination]

#include <stdlib.h>	/* needed to define exit() */
#include <unistd.h>	/* needed to define getpid() */
#include <stdio.h>	/* needed for printf() */

int
main(int argc, char **argv) {
	char *args[] = {"ls", "-l", "/", 0};	/* each element represents a command line argument */
	char *env[] = { 0 };	/* leave the environment list null */

	printf("About to run /bin/ls\n");/*path name you want to execute */
	execve("/bin/ls", args, env); /*Write all arguments (path, list of arguments and environment */
	perror("execve");	/* if we get here, execve failed */
	exit(1);
}
