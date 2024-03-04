#include <stdio.h>
#include "50q.h"

#define MAX_SIZE 100

int main(int argc,char* argv[]){
    int ex;
    int lista[MAX_SIZE];
    int size = 0;
    printf("Introduza o exercício: ");
    scanf("%d",&ex);
    int num1;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    switch (ex)
    {
    case 1:
            printf("Introduza os elementos da lista (termina com 0): ");
            while(size < MAX_SIZE) {
                int num;
                scanf("%d", &num);
                if(num == 0) break; 
                lista[size++] = num;
            }
        ex1(lista);
        break;

    case 2:
        
            printf("Introduza os elementos da lista (termina com 0): ");
            while(size < MAX_SIZE) {
                int num;
                scanf("%d", &num);
                if(num == 0) break; 
                lista[size++] = num;
            }
        ex2(lista);
        break;
    case 3:
            printf("Introduza os elementos da lista (termina com 0): ");
            while(size < MAX_SIZE) {
                int num;
                scanf("%d", &num);
                if(num == 0) break; 
                lista[size++] = num;
            }
        ex3(lista);
        break;
    case 4:            
        printf("Numero: ");
        scanf("%d",&num1);
        ex4(num1);
        break;

    case 6:
        printf("Numero: ");
        scanf("%d",&num1);
        ex6 (num1);
        break;
    case 7:
        printf("Introduza a primeira string: ");
        scanf("%s",s1);
        printf("Introduza a segunda string: ");
        scanf("%s",s2);
        ex7(s1,s2);
        break;
    case 8:
        char str1[100];
        char str2[100];
        printf("Introduza a primeira string: ");
        scanf("%s",str1);
        ex8(str2,str1);

    case 9:
        printf("Introduza a primeira string: ");
        scanf("%s",s1);
        printf("Introduza a segunda string: ");
        scanf("%s",s2);
        ex9(s1,s2);
        break;
    case 10:
        printf("Introduza a primeira string: ");
        scanf("%s",s1);
        printf("Introduza a segunda string: ");
        scanf("%s",s2);
        ex10(s1,s2);
    default:
        break;
    }
}

