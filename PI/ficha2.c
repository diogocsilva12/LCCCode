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

//Exercicio 3
int mdc1(int a, int b){
    int menor = a < b ? a:b;
    int mdc = 1;
    for(int i = 1;i<=menor;i++){
        mdc = i;
    }
    return mdc;
}

//Exercicio 6
//EX 6.A
int fib1(int n){
    if(n<2){
        return 1;
    }
    else{
        return fib1(n-1) + fib1(n-2);
    }
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
        case 3:{
            int num1 = 0;
            int num2 = 0;
            printf("Insira o primeiro número: ");
            scanf("%d", &num1);
            printf("Insira o segundo número: ");
            scanf("%d", &num2);
            resultado = mdc1(num1,num2);
            printf("Resultado: %f\n",resultado);
            break;
        }
        case 6: {
            int num1 = 0;
            printf("Insira o primeiro número: ");
            scanf("%d", &num1);
            resultado = fib1(num1);
            printf("Resultado: %f\n",resultado);
            break;
        }
        default:
            printf("Número Inválido!");
    }
    return 0;
}
