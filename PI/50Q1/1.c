/*Define a program that reads (using the scanf function) a sequence of integers ending with the number
0 and prints the largest element of the sequence on the screen*/

#include <stdio.h>

int main(){
    int num, maior;
    printf("Insert a number sequence. Insert 0 to stop the program:");
    while(1){
        scanf("%d",&num); 
        if(num == 0){
            break;
        }
        else{
            if(num>maior){
                maior = num;
            }
        }
    }
    printf("The large");
}