#include <stdlib.h>
#include <stdio.h>

//Exercicio1
float multInt1 (int n, float m){
    float res = 0;
    for(int i=0;i<n;i++){
        res +=m;
    }
    return res;
}

//Exercicio2
float multInt2(int n, float m){
    float res = 0;
    while(n > 0){
        if(n % 2 != 0){
            res += m;
        }
        n = n / 2;
        m = m * 2;
    }
    return res;
}


int main(int argc,char* argv[]) {
    int exercicio;
    float resultado;
    printf("Exercício: ");
    scanf("%d", &exercicio);
    switch (exercicio) {
        case 1: {
            int num1 = 0; // Inicialize num1
            int num2 = 0; // Inicialize num2
            printf("Insira o primeiro número: ");
            scanf("%d", &num1);
            printf("Insira o segundo número: ");
            scanf("%d", &num2);
            resultado = multInt1(num1, num2);
            printf("Resultado: %f\n", resultado);
            break;
        }
        case 2:{
            int num1 = 0;
            int num2 = 0;
            printf("Insira o primeiro número: ");
            scanf("%d", &num1);
            printf("Insira o segundo número: ");
            scanf("%d", &num2);
            resultado = multInt2(num1,num2);
            printf("Resultado: %f\n",resultado);
            break;
        }
        default:
            printf("Número Inválido!");
    }
    return 0;
}
