#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h> 
#define SIZE 1024


/**
 * @brief Função responsável por executar o commando "execute -u"
 * 
 * @param command  
 * @param tempoEstimado 
 */

void runProgram(char *command[], int tempoEstimado) {
    char *buffer = malloc(sizeof(char) * SIZE);  //Alocação na memória para um buffer

    struct timeval start, end;                   // TODO
    gettimeofday(&start, NULL);                  // Função gettimeofday, para calcular o tempo que demora a executar uma tarefa

    pid_t pid = fork();                          // Criação de um processo filho para executar a tarefa

    if (pid < 0) {                               //Caso controlo: Se o pid não for igual a 0 (ou seja, for o processo filho) ou menor do que zero, quer dizer que não foi possivel criar um processo filho.
        perror("Não foi possível criar um processo filho!");    
    } else if (pid == 0) { // Processo Filho     //Neste else if, estão as instruções de código que o processo filho vai executar.
        execvp(command[0], command);
        write(2, "Error: Exec failed\n", sizeof("Error: Exec failed\n"));
        _exit(1);          // O processo filho acaba com o status 1.
    } else {
        int status;        //O processo pai espera que o filho acabe, e executa as instruções dentro do else.
        wait(&status);
        if (WIFEXITED(status) == 1) {
            gettimeofday(&end, NULL); // Get the end time after the child process finishes

            double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0; // sec to ms
            elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;      // us to ms

            int nbytes = sprintf(buffer, "Pid: %d\nProgram: %s\nTempo estimado: %d milissegundos\nTime Elapsed: %.2f milliseconds\n", getpid(), command[0], tempoEstimado, elapsedTime);
            write(1, buffer, nbytes);            // É impresso para o std output uma mensagem com informações relativas a tarefa realizada.
        }
    }
    free(buffer);                                // É libertado o espaço de memória referente ao buffer.
}


    
int main(int argc, char* argv[]){
    /**
     * @brief Alocação de memória para um buffer
     */
    char *buffer = malloc(sizeof(char)*SIZE);

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
        if(strcmp(argv[3],"-u")==0){
            int time = atoi(argv[2]);
            runProgram(&argv[4],time);
            //TODO -> CODIGO PARA CORRER UM PROGRAMA COM UM TEMPO NECESSÁRIO(ARGV[2]) E UM PROGRAMA(ARGV[4])
        }
    }

    free(buffer);
    return 0;
}


