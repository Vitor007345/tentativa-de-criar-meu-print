#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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



int main()
{
    printf("%s", intToStr(2353));
    return 0;
}
