#include <stdio.h>
#include "mysystem.h"


void controller(int N, char** commands){
    int i;
    int pids[N];
    for(i = 0;i < N; i++){
        pid_t pid = fork();
        if(pid == 0){
            int res = 1;
            int count_ite = 0;
            while(res > 0){
                res = mysystem(commands[i]);
                count_ite++;
            }
            _exit(count_ite);
    }
    else{
        pids[i] = pid;
    }
    }

    for(i = 0 ;i< N;i++){
        int status;
        waitpid(pids[i],&status,0); //retorna o valor do filho que acabou e guarda na status

        if(WIFEXITED(status)){
            printf("Comando %s executed %d times\n",commands[i],WEXITSTATUS(status));
        }else{
            printf("ERRO AO TERMINAR");
        }
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