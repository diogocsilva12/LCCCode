#include <stdio.h>
#include "mysystem.h"


void controller(int N, char** commands) {
	int status[N]; 
    int num_exec[N];

    for (int i = 0; i < N; i++) {
        status[i] = 0;
        num_exec[i] = 0;
    }

    while (1) {
        for (int i = 0; i < N; i++) {
            if (status[i] == 0) {
                pid_t pid = fork();
                if (pid == 0) {
                    mysystem(commands[i]); 
                    perror("exec");
                    exit(1);
                } else if (pid > 0) {
                    wait(&status[i]);
                    if (WIFEXITED(status[i])) {
                        num_exec[i]++;
                        status[i] = WEXITSTATUS(status[i]); 
                    }
                } else {
                    perror("fork");
                    exit(1);
                }
            }
        }

        int finished = 1;
        for (int i = 0; i < N; i++) {
            if (status[i] != 0) {
                finished = 0;
                break;
            }
        }

        if (finished) {
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%s: %d\n", commands[i], num_exec[i]);
    }
}


int main(int argc, char* argv[]) {

	char *commands[argc-1];
	int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
		N++;
	}

	controller(N, commands);

	return 0;
}


/**
 * CONTROLADOR SÓ PARA DE EXECUTAR QUANDO TODOS DAO 0. 
 * GUARDAR O NÚMERO DE VEZES QUE 
 * 
 */