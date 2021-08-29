#include <stdio.h>
#include <pthread.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() { 
	int n = 9;
	int status;
	int fds[2];
	const int Nbuff = 100;

	pid_t pere = getpid();
	pipe(fds);
	pid_t p = fork();

	//get pid fils
	if(p == 0){
		close(fds[1]);
		char res[Nbuff];
		char n;		
		n = read(fds[0], res, Nbuff-1);
		res[n] = '\0';
		printf("Message de mon père (de longueur %zu) : %s \n", n, res);
		close(fds[0]);
		exit(1);
	} else {
		close(fds[0]);
		char *phrase = "JE SUIS TON PERE LUKE!";
		write(fds[1], phrase, strlen(phrase));
		//printf("Je suis le père", n);
		wait(&status);
		close(fds[1]);
	}
return (0);


}
