//
// Created by diogokeeper12 on 16-02-2024.
//

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>




/*
 * 1. Implemente em C um programa mycat com funcionalidade similar ao comando cat, que le do seu
stdin e escreve para o seu stdout.
 * */


int mycat(){

    char buffer[1024];
    ssize_t res_read;
    ssize_t res_write;

    while((res_read = read(0,buffer,1024))>0){

        res_write = write(1,buffer,res_read);

        if(res_read != res_write){ //se o tamanho de bytes lidos for diferente dos bytes escritos returnamos 1.
            return 1;
        }
    }

    write(2,"fim",3); //ctrl+d -> mata o programa e exibe a mensagem de erro.
    return 0;
}

int main(int argc, char* argv[]){
    mycat();
    mycp(argv[1],argv[2]);
    return 0;
}