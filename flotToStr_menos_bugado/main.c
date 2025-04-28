#include <stdio.h>
#include <stdlib.h>
#include <math.h>]
#include <stdarg.h>


int numDigits(int num){
    if(num == 0)return 1;
    if(num < 0)num *= -1;
    return ((int)log10(num)) + 1;
}


void intToStr(char* str, int num){
    int numT = numDigits(num);
    int ehNegativo = 0;
    if(num < 0){
        ehNegativo = 1;
        str[0] = '-';
        num *= -1;
        numT++;
    }
    char* digitosChar = "0123456789";
    str[numT] = '\0';
    for(int i = (numT - 1); i >= (ehNegativo?1:0); i--){
        str[i] = digitosChar[(num % 10)];
        num /= 10;
    }

}


void somaStrs(char* strFinal, int qnt, ...){
    if (!strFinal){
        printf("Erro: strFinal nulo\n");
        return;
    }
    va_list args;
    va_start(args, qnt);
    int c = 0;
    for(int i = 0; i < qnt; i++){
        char* str = va_arg(args, char*);
        int j = 0;
        while(str[j] != '\0'){
            strFinal[c] = str[j];
            j++;
            c++;
        }
    }
    strFinal[c] = '\0';
    va_end(args);
}

void fillStr(char* str, char c, int qnt){ //qnt é a quantidade de vezes q caracter selcionado q irá aparecer na string
    int i = 0;
    for(; i < qnt; i++){
        str[i] = c;
    }
    str[i] = '\0';
}


char* doubleToStr(double num, int casas){
    //parte inteira
    int parteInt = (int)num;
    int numDparteInt = numDigits(parteInt);
    int lenStrInt = numDparteInt + 1 + (num < 0 ? 1 : 0); //numero de digitos + 1 pelo '0' e + 1 caso seja negativo para o '-'
    char strInt[lenStrInt];
    intToStr(strInt, parteInt);

    //parte double
    double parteDouble = num - (double)parteInt;
    if(num < 0)parteDouble *= -1;
    int parteDoubleInt = (int)round(parteDouble * pow(10, casas));
    int numDparteDouble = numDigits(parteDoubleInt);
    char strDoublePrevia[(numDparteDouble + 1)];
    intToStr(strDoublePrevia, parteDoubleInt);

    //correção dos 0 perdidos
    int numDeZeros = casas - numDparteDouble;
    char strDeZeros[(numDeZeros + 1)];
    fillStr(strDeZeros, '0', numDeZeros);
    char strDouble[(casas + 1)];
    somaStrs(strDouble, 2, strDeZeros, strDoublePrevia);


    //somando as partes                                 // pq n o numDpartInt? pq ele n considera qnd é negativo ou n
    int lenStrFinal = lenStrInt - 1 + 1 + casas + 1;  //lenStr - 1 (-1 pra desconsiderar 0 \0)  +1(o caracter ponto) + casas (quantidade de casas decimais) + 1 (caracter '\0' no final sa strFinal)
    char* strFinal = (char*)malloc(lenStrFinal*sizeof(char));
    if(!strFinal){
        printf("Erro na alocação de mémoria de strFinal");
        return NULL;
    }
    somaStrs(strFinal, 3, strInt, ".", strDouble);


    return strFinal;
}


int charToInt(char numCarac){
    int num;
    if(numCarac >= '0' && numCarac <= '9'){
        num = (int)(numCarac - '0');
    }else{
        num = -1;
    }
    return num;
}
int strToInt(char* str){
    if(!str)return -1;
    int num = 0;
    int i = 0;
    while(str[i] != '\0'){
        int digito = charToInt(str[i]);
        if(digito == -1)return -1;
        num *= 10;
        num += digito;
        i++;
    }
    return num;
}







int lenStr(char* str){
    if(!str)return -1; //valor para erro
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int main()
{
    char* teste = doubleToStr(123243.00121276, 6);
    printf("%s", teste);
    free(teste);

    printf("\n%i", strToInt("242135423"));
    return 0;
}



/*
void somaStr(char* strFinal, char* strA, char* strB){
    int c = 0;
    while(strA[c] != '\0'){
        strFinal[c] = strA[c];
        c++;
    }
    for(int i = 0; strB[i] != '\0'; i++){
        strFinal[c] = strB[i];
        c++;
    }
    strFinal[c] = '\0';
}
*/
