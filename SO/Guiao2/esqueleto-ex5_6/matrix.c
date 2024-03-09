#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
//Return's 1 if number exists and 0 if not
int valueExists(int **matrix, int value) {
    int i;
    for(i = 0;i<ROWS;i++){
        pid_t pid = fork();
        if(pid==0){
            for(int j=0;j<COLUMNS;j++){
                if(matrix[i][j] == value){
                    _exit(1);
                }
            }
            _exit(-1);
        }
    }

    int res = 0;
    for(i = 0;i<ROWS;i++){
        int status;
        pid_t wait_pid = wait(&status); //retorna o valor do filho que acabou e guarda na status

        printf("wait_pid %d\n",wait_pid);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) == 1){
                res = 1;
            }
        }else{
            printf("Erro ao sair!");
        }
    }
    return res;
}


// ex.6
void linesWithValue(int **matrix, int value) {

    pid_t pids[ROWS];
    int i;
    for(i = 0;i<ROWS;i++){
        pid_t pid = fork();
        if(pid==0){
            for(int j=0;j<COLUMNS;j++){
                if(matrix[i][j] == value){
                    _exit(1);
                }
            }
            _exit(-1);
        }
        else{
            pids[i] = pid;
        }
    }

    for(i = 0;i<ROWS;i++){
        int status;
        pid_t wait_pid = waitpid(pids[i],&status,0); //retorna o valor do filho que acabou e guarda na status

        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) == 1){
                printf("Encontrei o valor %d na linha %d\n",value,i);
            }
            else{
                printf("Nao encontrei o valor %d na linha %d\n",value,i);
            }
        }else{
            printf("Erro ao sair!");
        }
    }
}


//TODO EXTRA