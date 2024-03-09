#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h> 
#define MAX 1000


void runProgram(char *command[]){
    char *buffer = malloc(sizeof(char)*MAX);

    pid_t pid = fork();
    
    if(pid < 0){
        perror("Erro ao fazer fork!");
    }

    /**
     * @brief Processo Filho
     * 
     */
    if (pid == 0)
    {

        printf("RODANDO");
        execvp(command[0],command);
        printf("RODOU");
        write(2,"Error: Exec failed\n",sizeof("Error: Exec failed\n"));
        
        _exit(0);
    }

    int status;
    wait(&status);


    int fd = open("tmp/ficheiro.txt", O_WRONLY | O_CREAT | O_APPEND, 0600);


    if (WIFEXITED(status) == 1) {
        int nbytes = sprintf(buffer, "Pid: %d\nProgram: %s\n", getpid(), command[0]);
        write(fd, buffer, nbytes);

    } else {
        int nbytes = sprintf(buffer, "Pid: %d\nProgram: %s\nFilho interrompido\n\n", getpid(), command[0]);
        write(fd, buffer, nbytes);
    }

    write(fd, buffer, MAX);
    free(buffer);
    close(fd);

}
    






int main(int argc, char* argv[]){
    /**
     * @brief Alocação de memória para um buffer
     */
    char *buffer = malloc(sizeof(char)*MAX);

    /**
     * @brief Controla a entrada de argumentos no terminal.
     * 
     */
    if(argc == 1){
        int nbytes = sprintf(buffer,"Não foi encontrado nenhum comando válido!\n");
        write(1,buffer,nbytes);
        return -1;
    }
    
    /**
     * @brief Funcionalidade de correr o programa. 
     * É feito um strcmp para verificar se a opção execute é passada no terminal. Após essa verificação,
     * é feito outro strcmp para verificar que o tipo de execute é "-u", ou seja, se é executado apenas um programa.
     * 
     */
    if(strcmp(argv[1],"execute")==0){
        if(strcmp(argv[2],"-u")==0){
            runProgram(&argv[3]);
            //TODO -> CODIGO PARA CORRER UM PROGRAMA COM UM TEMPO NECESSÁRIO(ARGV[2]) E UM PROGRAMA(ARGV[4])
        }
    }

    free(buffer);
    return 0;
}