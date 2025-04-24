#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define _max 500

float somaValores(int qnt, ...){
    va_list args;
    va_start(args,qnt);
    float soma = 0;
    for(int i = 0; i < qnt; i++){
        double num = va_arg(args, double);
        soma += (float)num;
    }
    va_end(args);
    return soma;
}

int numDigits(int num){
    if(num == 0)return 1;
    return ((int)log10(abs(num))) + 1;
}


char* intToStr(int num){
    int numD = numDigits(num);
    char* digitosChar = "0123456789";
    char* str = malloc((numD + 1)*sizeof(int));
    for(int i = (numD - 1); i >= 0; i--){
        str[i] = digitosChar[(num % 10)];
        num /= 10;
    }
    str[numD] = '\0';
    return str;

}

void print(char* str, ...){
    va_list args;
    int i = 0;
    int c = 0;
    char cmd[50];
    int posIndex[50];
    while(str[i] != '/0'){
        if(str[i] == '%'){
            if(str[(i + 1)] != '%'){
                cmd[c] = str[(i + 1)];
                posIndex[c] = i;
                c++;
            }
            i++;
        }
        i++;
    }
    va_start(args, c);
    char printStr[_max];

    int strCounter = 0;
    int printCounter = 0;
    for(int j = 0; j < c; j++){
        for(; strCounter < posIndex[j]; strCounter++, printCounter++){
            printStr[printCounter] = str[strCounter];
        }
        strCounter ++;
        switch(cmd[j]){
            case 'i':
                int inteiro = va_arg(args, int);

                break;
            case 'd':
                break;
            case 'f':
                break;
            case 'c':
                break;
        }



    }
}


int main()
{
    printf("%f", somaValores(3, 10.0, 12.0, 3.2));
    return 0;
}
