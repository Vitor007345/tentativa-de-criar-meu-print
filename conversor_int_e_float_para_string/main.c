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
    char* str = malloc((numD + 1)*sizeof(char));
    if(str == NULL){
        printf("erro na alocação da intToStr");
        fflush(stdout);
        exit(1);
    }
    for(int i = (numD - 1); i >= 0; i--){
        str[i] = digitosChar[(num % 10)];
        num /= 10;
    }
    str[numD] = '\0';
    return str;

}

char* floatToStr(float num, int casas){
    int parteInteira = (int)num;
    int numDParteInt = numDigits(parteInteira);
    char* strInteira = intToStr(parteInteira);
    //char* digitosChar = "0123456789";
    int parteFloat = round((num - (float)parteInteira) * pow(10, casas));
    int numDparteFloat = numDigits(parteFloat);
    char* strFloatPrevia = intToStr(parteFloat);
    int qntDeCaracteresStrFinal = numDParteInt + 1 + casas;
    char* strFinal = calloc(qntDeCaracteresStrFinal + 1,sizeof(char));
    char* strFloat;
    if(numDparteFloat != casas){
        strFloat = malloc((casas + 1)*sizeof(char));
        int i = 0;
        for(; i < (casas - numDparteFloat); i++){
            strFloat[i] = '0';
        }
        for(int j = 0; j < numDparteFloat; j++, i++){
            strFloat[i] = strFloatPrevia[j];
        }
        strFloat[i] = '\0';
        numDparteFloat = casas;
        free(strFloatPrevia);

    }else{
        strFloat = strFloatPrevia;
    }
    int c = 0;
    for(; c < numDParteInt; c++){
        strFinal[c] = strInteira[c];
    }
    strFinal[c] = '.';
    c++;
    for(int i = 0; i < casas; i++, c++){
        strFinal[c] = strFloat[i];
    }
    strFinal[c] = '\0';

    free(strInteira);
    free(strFloat);

    return strFinal;



}

int main()
{
    //(stdout, NULL, _IONBF, 0);
    printf("teste\n");
    char* texto = floatToStr(54321.252315, 4);
    printf("%s", texto);
    printf("\nFoi essa trolha");
    free(texto);
    return 0;
}
