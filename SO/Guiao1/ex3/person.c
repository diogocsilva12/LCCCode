#include "person.h"
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int add_person(char* name, int age) {

    Pessoa p;
    p.age = age;
    strcpy(p.name, name);

    int fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0600);

    write(fd, &p, sizeof(p));

    close(fd);

    return 0;
}

int list_persons(int nr) {

    Pessoa p;

    int fd = open(FILENAME, O_RDONLY);

    for(int i=0; i<nr && read(fd, &p, sizeof(p))>0; i++) {

        char msg[200];
        int s = sprintf(msg, "Registo: %s %d\n", p.name, p.age);
        write(1, msg, s);
    }

    close(fd);

    return 0;
}

int change_age1(char* name, int new_age) {
    Pessoa p;

    int fd = open(FILENAME,O_RDWR);
    while(read(fd, &p, sizeof(p))>0){
        if(strcmp(name,p.name)==0){
            p.age = new_age;
            lseek(fd,-sizeof(p),SEEK_CUR);
            write(fd,&p,sizeof(p));
            close(fd);

            return 1;
        }
    }


    return 0;
}