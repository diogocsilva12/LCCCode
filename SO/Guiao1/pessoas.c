//
// Created by diogokeeper12 on 19-02-2024.
//

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 4096

typedef struct Pessoa{
    char nome[50];
    char apelido[50];
    int idade;
}Pessoa;


// -i - Acrescentar pessoas a um ficheiro de dados binario
int adicionaPessoas(char* nome,char* apelido, int idade){
    int fd_ficheiro = open("pessoas.bin",O_CREAT|O_RDWR|O_APPEND,0640);
    Pessoa p;

//EVITAR REPETIDOS
    while(read(fd_ficheiro, &p, sizeof(Pessoa)) == sizeof(Pessoa)) {
        if(strcmp(p.nome, nome) == 0) {
            if(strcmp(p.apelido,apelido)==0)
            printf("Pessoa com o nome: %s %s já existe!\n", nome,apelido);
            close(fd_ficheiro);
            return 1;
        }
    }

    strcpy(p.nome, nome);
    strcpy(p.apelido,apelido);
    p.idade = idade;
    int pos = lseek(fd_ficheiro, 0, SEEK_END); // Obter a posição atual (final do arquivo)
    write(fd_ficheiro,&p,sizeof(Pessoa));
    printf("Pessoa inserida na posição: %d",pos);
    close(fd_ficheiro);
    return 0;
}


// l - Listar as N primeiras pessoas no ficheiro de dados binario. ´
int lePessoas(int limite){
    int fd_ficheiro = open("pessoas.bin",O_RDONLY,0640);
    Pessoa p;
    for(int i = 0; i < limite; ++i) {
        ssize_t bytesRead = read(fd_ficheiro, &p, sizeof(Pessoa));
        if(bytesRead != sizeof(Pessoa)) {
            printf("Não há mais pessoas na lista.\n");
            break;
        }
        printf("Nome: %s %s, Idade: %d\n",p.nome,p.apelido,p.idade);
    }
    close(fd_ficheiro);
    return 0;
}

void resetaLista() {
    if(remove("pessoas.bin") == 0)
        printf("A lista foi resetada com sucesso.\n");
    else
        perror("Erro ao resetar a lista");
}


//-u - Atualizar a idade de uma determinada pessoa no ficheiro de dados.
void atualizaIdade(char* nome,char* apelido,int idade){
    int fd_ficheiro = open("pessoas.bin",O_RDWR,0640);
    Pessoa p;
    while(read(fd_ficheiro, &p, sizeof(Pessoa)) == sizeof(Pessoa)) {
        if(strcmp(p.nome, nome) == 0) {
            if(strcmp(p.apelido,apelido)==0)
                p.idade = idade;
                lseek(fd_ficheiro, -sizeof(Pessoa), SEEK_CUR); //perguntar o que faz ao certo
                write(fd_ficheiro, &p, sizeof(Pessoa));
                break;
        }
    }
    close(fd_ficheiro);
}

void atualizarIdadePorPosicao(int pos, int novaIdade) {
    int fd_ficheiro = open("pessoas.bin", O_RDWR);
    Pessoa p;
    lseek(fd_ficheiro, pos, SEEK_SET); // Ir para a posição especificada
    if(read(fd_ficheiro, &p, sizeof(Pessoa)) == sizeof(Pessoa)) {
        p.idade = novaIdade;
        lseek(fd_ficheiro, pos, SEEK_SET); // Voltar para a posição especificada
        write(fd_ficheiro, &p, sizeof(Pessoa));
    }
    close(fd_ficheiro);
}

int main(int argc,char* argv[]){
    if(argc < 2) {
        printf("Por favor, forneça uma opção.\n");
        return 1;
    }
    if(strcmp(argv[1], "-i") == 0) {
        int idade = atoi(argv[4]); // isto converte a string para um int
        adicionaPessoas(argv[2],argv[3],idade);
    }
    if(strcmp(argv[1], "-l") == 0) {
        if(argc != 3) {
            printf("Por favor, forneça um número de pessoas para listar.\n");
            return 1;
        }
        int limite = atoi(argv[2]); // isto converte a string para um int
        lePessoas(limite);
    }
    if(strcmp(argv[1], "-removeList") == 0) {
        resetaLista();
    }
    if(strcmp(argv[1], "-u") == 0) {
        int idade = atoi(argv[4]);
        atualizaIdade(argv[2],argv[3],idade);
    }
    if(strcmp(argv[1], "-o") == 0) {
        int idade = atoi(argv[3]);
        int pos = atoi(argv[2]);
        atualizarIdadePorPosicao(pos,idade);
    }


    return 0;
}



