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
		printf("Je suis le fils et j'ai reçu res = %d\n", res);
		exit(2);
	} else {
		close(fds[0]);
		write(fds[1], &n, sizeof(int));
		printf("Je suis le père, j'ai envoyé n = %d\n", n);
		wait(&status);
	}
return (0);


}
