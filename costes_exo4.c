#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    long valeur = 0;
    int status;
    int fdsPere[2];
    int fdsChild[2];
    //const int Nbuff = 100;

    // pid_t p = getpid();
    pipe(fdsPere);
    pipe(fdsChild);
    int nbEnfant = 3;
    pid_t children[nbEnfant];
    for (int i = 0; i < nbEnfant; i++) {
        children[i] = fork();
        if (children[i] == 0) {
            long res;
            close(fdsPere[1]);
            read(fdsPere[0], &res, sizeof(long));
            printf("ligne 31 %ld\n", res);
            printf("children[i] :  %d\n", children[i]);
            // int pid = children[i];
            res = res + children[i];
            printf("ligne 34 %ld\n", res);
            close(fdsChild[0]);
            write(fdsChild[1], &res, sizeof(long));
            exit(1);

        } else {
            close(fdsPere[0]);
            write(fdsPere[1], &valeur, sizeof(long));
            wait(&status);
            close(fdsChild[1]);
            read(fdsChild[0], &valeur, sizeof(long));
        }
    }
    return (0);
}
