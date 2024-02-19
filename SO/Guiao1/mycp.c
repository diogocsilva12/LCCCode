//
// Created by diogokeeper12 on 16-02-2024.
//
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>


#define BUFFER_SIZE 4096

int mycp(char* origem,char* destino){
    int fd_origem = open(origem,O_CREAT|O_RDONLY);
    int fd_destino = open(destino,O_CREAT|O_WRONLY,0640);
    if(fd_destino < 0){
        perror("Erro");
    }

    char buffer[BUFFER_SIZE];
    ssize_t res_read;


    while((res_read = read(fd_origem,buffer,BUFFER_SIZE))>0){


        ssize_t res_write = write(fd_destino, buffer, res_read);

        if(res_read != res_write){
            return 1;
        }
}
    close(fd_origem);
    close(fd_destino);
    return 0;
}

int main(int argc, char* argv[]){

    mycp(argv[1],argv[2]);
    return 0;
}