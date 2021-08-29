#include <stdio.h>
#include <pthread.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() { 
	int n = 9;
	int status;
	int fds[2];

	pid_t pere = getpid();
	pipe(fds);
	pid_t p = fork();

	//get pid fils
	if(p == 0){
		close(fds[1]);
		int res;
		read(fds[0], &res, sizeof(int));
		printf("Je suis le fils \n", res);
		close(fds[0]);
		exit(1);
	} else {
		close(fds[0]);
		printf("Je suis le père \n", n);
		write(fds[1], &n, sizeof(int));
		wait(&status);
		close(fds[1]);
	}
return (0);


}
