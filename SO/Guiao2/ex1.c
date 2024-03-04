#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


//EX1 E EX2

int main(){

    int i = 10;
    pid_t pid = fork();
//AQUI ESTAMOS NO PROCESSO FILHO PORQUE PID = 0
    if(pid == 0){ //SO É IMPRESSO UMA VEZ

        i++;

        //printf("FILHO: i %d\n",i);
        printf("FILHO: o meu pid: %d\n",getpid());
        printf("FILHO: o pid do meu pai: %d\n",getppid());
        //printf("FILHO: Retorno fork: %d\n",pid);
        _exit(1); //funcao tipo return, liberta recursos do processo pai

    }
        //printf("PAI: i %d\n",i);
        printf("PAI: o meu pid: %d\n",getpid());
        printf("PAI: o pid do meu pai: %d\n",getppid());
        //printf("PAI: Retorno fork: %d\n",pid);

        int status;
        pid_t wait_pid = wait(&status); //retorna o valor do filho que acabou e guarda na status

        printf("wait_pid %d\n",wait_pid);
        if(WIFEXITED(status)){
            printf("Valor exit filho %d\n",WEXITSTATUS(status));
        }else{
            printf("ERRO AO TERMINAR");
        }

    
    i++;
    printf("Coisas %d\n",i);

    return 0;
}