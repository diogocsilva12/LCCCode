#define FILENAME "file_pessoas"

typedef struct pessoa{
    char name[50];
    int age;
}Pessoa;


int add_person(char* name, int age);

int list_persons(int nr);

int change_age1(char* name, int newage);

int change_age2(long pos, int newage);

