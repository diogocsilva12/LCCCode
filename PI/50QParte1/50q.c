#include <stdio.h>
#include <string.h>


/**
 * @brief Ex1.Definir um programa que leia uma sequencia de números inteiros,
 * e que imprima o maior da sequencia.
 * @param lista 
 * @return int 
 */
int ex1(int lista[]){
    int max = 0;
    for(int i = 0; lista[i] != 0; i++){ 
        if(lista[i]>max){
            max = lista[i];
        }
    }
    printf("O maior elemento da lista é: %d", max);
    return 0;
}


int ex2(int lista[]){
    int count = 0;
    int contador = 0;
    for(int i = 0 ;lista[i] != 0;i++){
        count += lista[i];
        contador +=1;
    }
    int res = count / contador; 
    printf("A média da lista é: %d", res);
    return 0;
}


//Ex3
int ex3(int lista[]){
    int max = -1;
    int sndMax = -1;
    for(int i = 0;lista[i] != 0;i++){
        if(lista[i] > max) {
            sndMax = max;
            max = lista[i];
        } else if(lista[i] > sndMax && lista[i] < max) {
            sndMax = lista[i];
        }
    }   
    printf("O maior elemento da lista é %d, e o segundo maior é %d",max,sndMax);
    return 0;
}

//Ex4 int bitsUm (unsigned int n) -> calcula o número de bits iguais a 1
int ex4(unsigned int n){
    int res = 0;
    while(n>0){
        if(n%2 != 0){
            res +=1;
        }
        n = n/2;
    }
    printf("Numero de bits a um: %d",res); //tmb podia dar return logo ao res, mas para testar prefiro assim
    return 0;
}

/*
//Ex5 int trailingZ(unsigned int n)
int ex5(unsigned int n){


}

*/


//Ex6 int qDig(unsigned int n) -> que calcula o nº de digitos necessários para escrever um numero inteiro n em base decimal

int ex6(unsigned int n){
    int count = 0;
    while(n != 0){
        count +=1;
        n = n /10;
    }
    printf("São necessários %d digitos para representar o número em base decimal.",count);
    return count;
}

//Ex7 *strcat (char s1[], char s2[]) que concatena duas strings
char *ex7(char s1[], char s2[]){
    int i = 0;
    while(s1[i] != '\0'){
        i++;
    }
    int j = 0;
    while(s2[j] != '\0'){
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0'; // Adiciona o caractere nulo ao final

    printf("s1: %s\n",s1);
    printf("Endereço da string 1: %d",*s1);  
    return s1;
}

//Ex8 *strcpy (char *dest, char source[]) que copia a string source para dest retornando o valor desta última.

char *ex8(char *dest, char source[]){
    int i =0;
    char *start = dest;
    while(source[i]!='\0'){
        *dest = *source;
        dest++;
        source++;
    }   
    return start;
}

//Ex9 int strcmp(char s1[], char s2[]) que compara duas strings.
int ex9(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] && s2[i]) {  
        if (s1[i] != s2[i]) { 
            return s1[i] - s2[i]; 
        }
        i++;
    }

    return strlen(s1) - strlen(s2); // Return difference in lengths
}

/*
//Ex10 char *strstr (char s1[], char s2[]) ->determina a posicao onde a string s2 ocorre em s1.
char *ex10(char s1[],char s2[]){
    for(int i = 0;s1[i] != '\0';i++){
        for(int j=0;s2[j] != '\0';j++){
            if(s1[i] == s2[j]){
                return &(s1[i]);
            }
        }
    }
    return NULL;
}
*/

//Ex11 -> Inverte uma string
void sttrev (char s[]){
    int i, temp;
    for(i=0;i<strlen(s)/2;i++){ //só vamos até ao meio da string, porque assim evitamos trocar os mesmos elementos 2 vezes
        temp = s[i];
        s[i] = s[strlen(s)-i-1];
        s[strlen(s)-i-1] = temp;
    }
}



//Ex12 -> void strnoV que retira todas as vogais de uma string.
void strnoV(char s[]) {
    int i, j;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||
            s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {  

            for (j = i; s[j] != '\0'; j++) {
                s[j] = s[j + 1];
            }

            i--; 
        }
    }
}

/*
//Ex13 -> void truncW(char t[], int n) -> que dado um texto t e um inteiro, trunca todas as palavras de forma a terem no máximo n caracteres.

void trunW(char t[],int n){
    int i,j;
    for (i = 0, j = 0; t[i] != '\0'; i++) {
        if (t[i] == ' ') {
            t[j++] = '\0';
            j = i + 1;
        }
        else if (j + 1 < n) {
            t[j++] = t[i];
        }      
}
    t[j] = '\0';
}

*/


//EX14 -> Determina qual é o char mais frequente

char charMaisfreq (char s[]) {
    char maisfrequentechar;
    int maisFreq = 0;
    int contador = 0;
    int i,j;
    for(i = 0;s[i]!='\0';i++){
        contador = 0;
        for(j = 0;s[j]!='\0';j++){
            if(s[i] == s[j]){
                contador++;
            }
        }
        if(contador > maisFreq){
            maisFreq = contador;
            maisfrequentechar = s[i];
        }
    }
    return maisfrequentechar;
}


/*
//Ex15 -> Dada uma string s calcula o comprimento da maior sub-string com caracteres iguais

int iguaisConsecutivos (char s[]) {
  int contador = 0; 
  int maxCount = 0;
  int i; 

  for (i = 0; s[i] != '\0'; i++) {
    if(s[i] == s[i+1]) {
      contador++; 
    } else {
      if(contador > maxCount) {
        maxCount = contador;
      }
      contador = 0; 
    }
  }
  return maxCount; 
}

*/

//Ex16 -> int difConsecutivos (char s[])

int difConsecutivos(char s[]) {
  int i = 0;
  int contador = 0;
  int maxContador = 0;
  while (s[i] != '\0') {
    if (s[i] != s[i + 1]) {
      contador++;
      // Atualiza o valor máximo dentro do loop
      if (contador > maxContador) {
        maxContador = contador;
      }
      i++;
    }
  }
  return maxContador;
}


//Ex17 -> int maiorPrefixo (char s1[], char s2[])