#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


//Ex4

int main(){
    for(int idx = 1;idx<10;idx++){
        pid_t pid = fork();
//AQUI ESTAMOS NO PROCESSO FILHO PORQUE PID = 0
        if(pid == 0){ //SO É IMPRESSO UMA VEZ
        printf("NUMERO %d\n",idx);
        sleep(2);
        //printf("FILHO: Retorno fork: %d\n",pid);
        _exit(idx); //funcao tipo return, liberta recursos do processo pai
        }
    }
    
    for(int idx = 1;idx<10;idx++){    
        int status;
        pid_t wait_pid = wait(&status); //retorna o valor do filho que acabou e guarda na status

        printf("wait_pid %d\n",wait_pid);
        if(WIFEXITED(status)){
            printf("Valor exit filho %d\n",WEXITSTATUS(status));
        }else{
            printf("ERRO AO TERMINAR");
        }
    }
    return 0;
    }
    