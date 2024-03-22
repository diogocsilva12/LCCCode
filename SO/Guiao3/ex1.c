#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    
    //execl("/bin/ls","ls","-l",NULL); //path to command, argv[0],argv[1], NULL -> é a dizer que já nao tem mais argumentos
    //int ret = execlp("ls","ls","-l", NULL);

    char *arr[20] = {"ls","-l",NULL};
    int ret = execvp("ls",arr);
    //int ret = execv("/bin/ls",arr);

    if(ret == -1){
        perror("erro exect");
    }

    printf("%s\n",argv[0]);

    return 0;
}

