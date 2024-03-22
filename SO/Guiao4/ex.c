#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


void filho_to_pai(){
    int pipefd[2];
    int ret = pipe(pipefd);


    if(ret < 0){
        perror("Erro ao criar pipe...");
        
    }

    if(fork()==0){//filho
        int valor = 10;
        close(pipefd[0]);
        for(valor = 0;valor < 100000; valor++){
            printf("A escrever %d\n",valor);
            write(pipefd[1],&valor,sizeof(int));    
        }
        
        close(pipefd[1]);

        

    }
    else{   //pai
        int status;
    
        int res;
        close(pipefd[1]);
        while(read(pipefd[0],&res,sizeof(int))>0){
            printf("Recebi %d \n",res);
        }
        
        close(pipefd[0]);
        wait(&status);
        if(WIFEXITED(status)){
            printf("Filho terminou\n");
        }
        else{
            printf("Filho nao terminou\n");
        }

    }
}

void pai_to_filho(){
    int pipefd[2];
    int ret = pipe(pipefd);


    if(ret < 0){
        perror("Erro ao criar pipe...");
        
    }

    if(fork()==0){//filho
        int res;
        close(pipefd[1]);
        read(pipefd[0],&res,sizeof(int));

        printf("Recebi %d \n",res);

    }
    else{   //pai
        int status;
        int valor = 10;
        close(pipefd[0]);
        write(pipefd[1],&valor,sizeof(int));
        close(pipefd[1]);

        
        wait(&status);
        if(WIFEXITED(status)){
            printf("Filho terminou\n");
        }
        else{
            printf("Filho nao terminou\n");
        }

    }

}




int main(){
   // pai_to_filho();
    filho_to_pai();
    return 0;
}