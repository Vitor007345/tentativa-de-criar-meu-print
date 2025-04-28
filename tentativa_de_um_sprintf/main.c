#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int lenStr(char* str){
    if(!str)return -1; //valor para erro
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

void somaStrsAdd(char* strFinal, int qnt, ...){
    if (!strFinal){
        printf("Erro: strFinal nulo\n");
        return;
    }
    va_list args;
    va_start(args, qnt);
    int c = lenStr(strFinal);
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

void cutStr(char* strFinal, char* str, int init, int end){
    if(!strFinal || !str || init < 0 || end < init)return;
    int c = 0;
    int i = init;
    while(i <= end && str[i] != '\0'){
        strFinal[c++] = str[i++];
    }
    strFinal[c] = '\0';
}



#define _INDEX 0
#define _CMD 1
#define _TAN 2
#define _CASAS 3

/* //Versão antiga
void sprint(char* strFinal, char* str, ...){
    int cmd[50][4]; //0 é o index(qual posição inicia o comando), e 1 é o comando em si, o 2 é o tamanho do comando em caracteres e o 3 é o número de casas do float se existir, se não ele fica como 6 que é o padrão de casas
    int strC = 0;
    int cmdC =0;
    while(str[strC] != '\0'){
        if(str[strC] == '%'){
            if(str[(strC + 1)] == '\0'){
                printf("Erro: não coloque um %% ao final de da string\n");
                return;
            }
            if(str[(strC + 1)] == '%'){
                strC++;
            }else{
                if(str[(strC + 1)] == '.'){
                    int casas = 0;
                    char strCasas[50];
                    int strCasasC = 0;
                    for(int i = 2; str[(strC + i)] != 'f'; i++){
                        if(str[(strC + i)] == '\0'){
                            printf("Erro: letra f não encontrada após a expressão %%.\n");
                            return;
                        }
                        strCasas[strCasasC] = str[strC + i];
                        strCasasC++;
                    }
                    strCasas[strCasasC] = '\0';
                    if(strCasasC > 0)casas = strToInt(strCasas);

                    int tamanhoCMD = 2 + strCasasC + 1;  //%. (2 caracteres) numerodeCasas (quantidade de caracteres de strCasas)  f (1 caracter) ---> %.1241f  obs: o número ali pode ser qualquer

                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)'f';
                    cmd[cmdC][_TAN] = tamanhoCMD;
                    cmd[cmdC][_CASAS] = casas;
                    strC += tamanhoCMD - 1;


                }else{
                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)str[strC + 1];
                    cmd[cmdC][_TAN] = 2;
                    cmd[cmdC][_CASAS] = 6; //numero padrão de casas se um for só um %f, se for outro cmd ele nem le isso dai
                    strC++;
                }
                cmdC++;

            }

        }
        strC++;
    }


    va_list args;
    va_start(args, str);
    int lastIndex = 0;
    int lastTamanho = 0;
    strFinal[0] = '\0';
    if(cmdC == 0)somaStrsAdd(strFinal, 1, str); //caso não haja comandos apenas copia a string inicial
    for(int i = 0; i < cmdC; i++){
        int index = cmd[i][_INDEX];
        int lenStrParte = index - (lastIndex + (lastTamanho - 1));
        char strParte[lenStrParte];
        int cutInit = lastIndex + lastTamanho;
        int cutEnd = index - 1;
        cutStr(strParte, str, cutInit, cutEnd);
        char* strCmdExec = NULL;
        switch(cmd[i][_CMD]){
            case (int)'i':
            case (int)'d':{
                int inteiro = va_arg(args, int);
                strCmdExec = (char*)malloc((numDigits(inteiro) + 1)*sizeof(char));
                if(!strCmdExec){
                    printf("Erros na alocação de mémoria para int cmd %%i");
                    return;
                }
                intToStr(strCmdExec, inteiro);
                break;
            }
            case (int)'f':{
                double num = va_arg(args, double);
                strCmdExec = doubleToStr(num, cmd[i][_CASAS]);
                break;
            }
            case (int)'c':{
                char carac = (char)va_arg(args, int);
                strCmdExec = (char*)malloc(2*sizeof(char));
                if(!strCmdExec){
                    printf("Erros na alocação de mémoria para char cmd %%c");
                    return;
                }
                strCmdExec[0] = carac;
                strCmdExec[1] = '\0';
                break;
            }
            case (int)'s':{
                char* string = va_arg(args, char*);
                if(!string){
                    printf("string passada por argumento invalida");
                    return;
                }
                strCmdExec = (char*)malloc((lenStr(string) + 1)*sizeof(char));
                if(!strCmdExec){
                    printf("Erros na alocação de mémoria para string cmd %%s");
                    return;
                }
                somaStrs(strCmdExec, 1, string); //apenas copia a string
                break;
            }
            default:
                printf("Comando %%%c inválido", (char)cmd[i][_CMD]);
                return;
        }

        somaStrsAdd(strFinal, 2, strParte, strCmdExec);
        free(strCmdExec);
        strCmdExec = NULL;


        lastIndex = index;
        lastTamanho = cmd[i][_TAN];
    }
    va_end(args);

}
*/

void vsprint(char* strFinal, char* str, va_list args){
    int cmd[50][4]; //0 é o index(qual posição inicia o comando), e 1 é o comando em si, o 2 é o tamanho do comando em caracteres e o 3 é o número de casas do float se existir, se não ele fica como 6 que é o padrão de casas
    int strC = 0;
    int cmdC =0;
    while(str[strC] != '\0'){
        if(str[strC] == '%'){
            if(str[(strC + 1)] == '\0'){
                printf("Erro: não coloque um %% ao final de da string\n");
                return;
            }
            if(str[(strC + 1)] == '%'){
                strC++;
            }else{
                if(str[(strC + 1)] == '.'){
                    int casas = 0;
                    char strCasas[50];
                    int strCasasC = 0;
                    for(int i = 2; str[(strC + i)] != 'f'; i++){
                        if(str[(strC + i)] == '\0'){
                            printf("Erro: letra f não encontrada após a expressão %%.\n");
                            return;
                        }
                        strCasas[strCasasC] = str[strC + i];
                        strCasasC++;
                    }
                    strCasas[strCasasC] = '\0';
                    if(strCasasC > 0)casas = strToInt(strCasas);

                    int tamanhoCMD = 2 + strCasasC + 1;  //%. (2 caracteres) numerodeCasas (quantidade de caracteres de strCasas)  f (1 caracter) ---> %.1241f  obs: o número ali pode ser qualquer

                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)'f';
                    cmd[cmdC][_TAN] = tamanhoCMD;
                    cmd[cmdC][_CASAS] = casas;
                    strC += tamanhoCMD - 1;


                }else{
                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)str[strC + 1];
                    cmd[cmdC][_TAN] = 2;
                    cmd[cmdC][_CASAS] = 6; //numero padrão de casas se um for só um %f, se for outro cmd ele nem le isso dai
                    strC++;
                }
                cmdC++;

            }

        }
        strC++;
    }

    int lastIndex = 0;
    int lastTamanho = 0;
    strFinal[0] = '\0';
    if(cmdC == 0)somaStrsAdd(strFinal, 1, str); //caso não haja comandos apenas copia a string inicial
    for(int i = 0; i < cmdC; i++){
        int index = cmd[i][_INDEX];
        int lenStrParte = index - (lastIndex + (lastTamanho - 1));
        char strParte[lenStrParte];
        int cutInit = lastIndex + lastTamanho;
        int cutEnd = index - 1;
        cutStr(strParte, str, cutInit, cutEnd);
        char* strCmdExec = NULL;
        switch(cmd[i][_CMD]){
            case (int)'i':
            case (int)'d':{
                int inteiro = va_arg(args, int);
                strCmdExec = (char*)malloc((numDigits(inteiro) + 1)*sizeof(char));
                if(!strCmdExec){
                    printf("Erros na alocação de mémoria para int cmd %%i");
                    return;
                }
                intToStr(strCmdExec, inteiro);
                break;
            }
            case (int)'f':{
                double num = va_arg(args, double);
                strCmdExec = doubleToStr(num, cmd[i][_CASAS]);
                break;
            }
            case (int)'c':{
                char carac = (char)va_arg(args, int);
                strCmdExec = (char*)malloc(2*sizeof(char));
                if(!strCmdExec){
                    printf("Erros na alocação de mémoria para char cmd %%c");
                    return;
                }
                strCmdExec[0] = carac;
                strCmdExec[1] = '\0';
                break;
            }
            case (int)'s':{
                char* string = va_arg(args, char*);
                if(!string){
                    printf("string passada por argumento invalida");
                    return;
                }
                strCmdExec = (char*)malloc((lenStr(string) + 1)*sizeof(char));
                if(!strCmdExec){
                    printf("Erros na alocação de mémoria para string cmd %%s");
                    return;
                }
                somaStrs(strCmdExec, 1, string); //apenas copia a string
                break;
            }
            default:
                printf("Comando %%%c inválido", (char)cmd[i][_CMD]);
                return;
        }

        somaStrsAdd(strFinal, 2, strParte, strCmdExec);
        free(strCmdExec);
        strCmdExec = NULL;


        lastIndex = index;
        lastTamanho = cmd[i][_TAN];
    }

}

void sprint(char* strFinal, char* str, ...){
    va_list args;
    va_start(args, str);
    vsprint(strFinal, str, args);
    va_end(args);
}

int somaTamanhos(int** cmd, int max){
    int soma = 0;
    for(int i = 0; i < max; i++){
        soma += cmd[i][_TAN];
    }
    return soma;
}

int getTamanhoDaStrPraPrintar(char* str, ...){ //basicamente refazer o código inteiro só pra contar, é mais eficiente do q realocar sempre q aumentar e melhor doq alocar um tamanho max fixo
    int cmd[50][4];
    int strC = 0;
    int cmdC =0;
    while(str[strC] != '\0'){
        if(str[strC] == '%'){
            if(str[(strC + 1)] == '\0'){
                printf("Erro: não coloque um %% ao final de da string\n");
                return -1;
            }
            if(str[(strC + 1)] == '%'){
                strC++;
            }else{
                if(str[(strC + 1)] == '.'){
                    int casas = 0;
                    char strCasas[50];
                    int strCasasC = 0;
                    for(int i = 2; str[(strC + i)] != 'f'; i++){
                        if(str[(strC + i)] == '\0'){
                            printf("Erro: letra f não encontrada após a expressão %%.\n");
                            return -1;
                        }
                        strCasas[strCasasC] = str[strC + i];
                        strCasasC++;
                    }
                    strCasas[strCasasC] = '\0';
                    if(strCasasC > 0)casas = strToInt(strCasas);

                    int tamanhoCMD = 2 + strCasasC + 1;  //%. (2 caracteres) numerodeCasas (quantidade de caracteres de strCasas)  f (1 caracter) ---> %.1241f  obs: o número ali pode ser qualquer

                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)'f';
                    cmd[cmdC][_TAN] = tamanhoCMD;
                    cmd[cmdC][_CASAS] = casas;
                    strC += tamanhoCMD - 1;


                }else{
                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)str[strC + 1];
                    cmd[cmdC][_TAN] = 2;
                    cmd[cmdC][_CASAS] = 6; //numero padrão de casas se um for só um %f, se for outro cmd ele nem le isso dai
                    strC++;
                }
                cmdC++;

            }

        }
        strC++;
    }

    int tamanhoFinal = strC - somaTamanhos(cmd, cmdC); //inicializa o calculo do tamanho final
    va_list args;
    va_start(args, str);
    int lastIndex = 0;
    int lastTamanho = 0;
    for(int i = 0; i < cmdC; i++){
        switch(cmd[i][_CMD]){
            case (int)'i':
            case (int)'d':{
                int inteiro = va_arg(args, int);
                tamanhoFinal += numDigits(inteiro) + (inteiro < 0);
                break;
            }
            case (int)'f':{
                double num = va_arg(args, double);
                tamanhoFinal += cmd[i][_CASAS] + numDigits((int)num) + (num < 0);
                break;
            }
            case (int)'c':{
                va_arg(args, int);
                tamanhoFinal++;
                break;
            }
            case (int)'s':{
                char* string = va_arg(args, char*);
                if(!string){
                    printf("string passada por argumento invalida");
                    return -1;
                }
                tamanhoFinal += lenStr(string);
                break;
            }
            default:
                printf("Comando %%%c inválido", (char)cmd[i][_CMD]);
                return -1;
        }


    }
    va_end(args);

    return tamanhoFinal + 1; //adiciona 1 que seria o caracter '\0'

}

int vgetTamanhoDaStrPraPrintar(char* str, va_list args){
    int cmd[50][4];
    int strC = 0;
    int cmdC =0;
    while(str[strC] != '\0'){
        if(str[strC] == '%'){
            if(str[(strC + 1)] == '\0'){
                printf("Erro: não coloque um %% ao final de da string\n");
                return -1;
            }
            if(str[(strC + 1)] == '%'){
                strC++;
            }else{
                if(str[(strC + 1)] == '.'){
                    int casas = 0;
                    char strCasas[50];
                    int strCasasC = 0;
                    for(int i = 2; str[(strC + i)] != 'f'; i++){
                        if(str[(strC + i)] == '\0'){
                            printf("Erro: letra f não encontrada após a expressão %%.\n");
                            return -1;
                        }
                        strCasas[strCasasC] = str[strC + i];
                        strCasasC++;
                    }
                    strCasas[strCasasC] = '\0';
                    if(strCasasC > 0)casas = strToInt(strCasas);

                    int tamanhoCMD = 2 + strCasasC + 1;  //%. (2 caracteres) numerodeCasas (quantidade de caracteres de strCasas)  f (1 caracter) ---> %.1241f  obs: o número ali pode ser qualquer

                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)'f';
                    cmd[cmdC][_TAN] = tamanhoCMD;
                    cmd[cmdC][_CASAS] = casas;
                    strC += tamanhoCMD - 1;


                }else{
                    cmd[cmdC][_INDEX] = strC;
                    cmd[cmdC][_CMD] = (int)str[strC + 1];
                    cmd[cmdC][_TAN] = 2;
                    cmd[cmdC][_CASAS] = 6; //numero padrão de casas se um for só um %f, se for outro cmd ele nem le isso dai
                    strC++;
                }
                cmdC++;

            }

        }
        strC++;
    }

    int tamanhoFinal = strC - somaTamanhos(cmd, cmdC); //inicializa o calculo do tamanho final
    int lastIndex = 0;
    int lastTamanho = 0;
    for(int i = 0; i < cmdC; i++){
        switch(cmd[i][_CMD]){
            case (int)'i':
            case (int)'d':{
                int inteiro = va_arg(args, int);
                tamanhoFinal += numDigits(inteiro) + (inteiro < 0);
                break;
            }
            case (int)'f':{
                double num = va_arg(args, double);
                tamanhoFinal += cmd[i][_CASAS] + numDigits((int)num) + (num < 0);
                break;
            }
            case (int)'c':{
                va_arg(args, int);
                tamanhoFinal++;
                break;
            }
            case (int)'s':{
                char* string = va_arg(args, char*);
                if(!string){
                    printf("string passada por argumento invalida");
                    return -1;
                }
                tamanhoFinal += lenStr(string);
                break;
            }
            default:
                printf("Comando %%%c inválido", (char)cmd[i][_CMD]);
                return -1;
        }


    }

    return tamanhoFinal + 1; //adiciona 1 que seria o caracter '\0'

}



void print(char* texto, ...){

    va_list args, args2;
    va_start(args, texto);
    va_copy(args2,args);

    char strAPrintar[vgetTamanhoDaStrPraPrintar(texto, args)];
    vsprint(strAPrintar, texto, args2);

    va_end(args);
    va_end(args2);
    fwrite(strAPrintar, sizeof(char), lenStr(strAPrintar), stdout);
}




int main()
{

    char teste[100];
    sprint(teste, "Hello World Com meu sprint %s  %i %d %f %.3f %c", "teste", 23, 10, 123.1243521535, 325.123552352, 'P');    //isso aqui funcionou
    printf("%s", teste);


    //print("Teste %i", 10);   //agora essa merda aqui n sei pq n sendo q fiz tudo igual

    //printf("%i\n", getTamanhoDaStrPraPrintar("teste%i %d %s %f %.2f", 10, 15, "teste2", 1.4, 9.2345235));

    return 0;
}


