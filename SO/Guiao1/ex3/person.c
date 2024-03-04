#include "person.h"
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



int add_person(char* name, int age) {
    clock_t inicio, fim;
    inicio = clock();
    Pessoa p;
    p.age = age;
    strcpy(p.name, name);
    int fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0600);
    write(fd, &p, sizeof(p));
    int pos = lseek(fd,-sizeof(Pessoa),SEEK_CUR);
    char msg[200];
    int s = sprintf(msg,"Pessoa inserida na posição: %d\n",pos);
    write(1,msg,s);
    fim = clock();
    double tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    printf("A função levou %f segundos para executar \n", tempo_gasto);
    close(fd);
    return 0;
}

int list_persons(int nr) {
    Pessoa p;
    int fd = open(FILENAME, O_RDONLY);
    for(int i=0; i<nr && read(fd, &p, sizeof(p))>0; i++) {
        char msg[200];
        int s = sprintf(msg, "Registo: %s %d\n", p.name, p.age); //sprintf já devolve o numero de bytes escritos
        write(1, msg, s);
    }
    close(fd);
    return 0;
}

int change_age1(char* name, int new_age) {
    Pessoa p;
    int fd = open(FILENAME, O_RDWR);
    clock_t inicio, fim;
    inicio = clock();
    while (read(fd, &p, sizeof(p)) > 0) {
        if (strcmp(name, p.name) == 0) {
            p.age = new_age;
            lseek(fd, -sizeof(p), SEEK_CUR);
            write(fd, &p, sizeof(p));
            char msg[200];
            int s = sprintf(msg, "Idade alterada! Nova idade: %d\n",new_age); //sprintf já devolve o numero de bytes escritos
            write(1, msg, s);
            return 1;
        }

    }
    fim = clock();
    double tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("A função levou %f segundos para executar \n", tempo_gasto);
    close(fd);
    return 0;
}

int change_age2(long pos, int newage){
    Pessoa p;
    int fd = open(FILENAME,O_RDWR);
    clock_t inicio, fim;
    inicio = clock();
    lseek(fd, pos*sizeof(p), SEEK_SET); // Ir para a posição especificada
    if(read(fd, &p, sizeof(Pessoa)) == sizeof(Pessoa)) {
        p.age = newage;
        int curpos = lseek(fd, pos, SEEK_SET); // Voltar para a posição especificada
        write(fd, &p, sizeof(Pessoa));
        char msg[200];
        int s = sprintf(msg, "Idade alterada no registo:%d\n",curpos); //sprintf já devolve o numero de bytes escritos
        write(1, msg, s);
    }
    fim = clock();
    double tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("A função levou %f segundos para executar \n", tempo_gasto);
    close(fd);
    return 0;
}



