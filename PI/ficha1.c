#include <stdio.h>

void ex1(){
    int argu;
    printf("Introduza uma dimensão para o quadrado: ");
    scanf("%d", &argu);
    int i,j;
    for(i=0;i<argu;i++){
        for (j = 0;j<argu;j++){
            printf("#");
        }
        printf("\n");
    }
}

void ex2(){
    int argu;
    printf("Introduza uma dimensão para o quadrado: ");
    scanf("%d", &argu);
    int i,j;
    for(i=0;i<argu;i++){
        for (j = 0;j<argu;j++) {
            if ((i+j)%2 == 0) {
                printf("#");
            } else {
                printf("_");
            }
        }
        printf("\n");
    }
}


void ex3(){

}




int main() {
    int exercicio;
    printf("Exercício: ");
    scanf("%d",&exercicio);

    switch (exercicio) {
        case 1:
            ex1();
            break;
        case 2:
            ex2();
            break;
        default:
            printf("Número Inválido!");
    }

}


