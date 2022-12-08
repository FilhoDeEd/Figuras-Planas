#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "figura.h"

char* concat_str(char* str1, char* str2)
{
    int tam1, tam2, i, j;

    tam1 = strlen(str1);
    tam2 = strlen(str2);

    char* strOut = (char*) malloc((tam1+tam2+1)*sizeof(char));

    for(i = 0, j = 0; j < tam1; j++, i++) strOut[i] = str1[j];
    
    for(j = 0; j < tam2; j++, i++) strOut[i] = str2[j];

    strOut[i] = '\0';

    return strOut;
}

int main()
{
    Figura* fig = cria_figura();
    char* workFolderPath = "/home/edson/Área de Trabalho/Códigos/C/Figuras_planas/";
    char* path_fileName = concat_str(workFolderPath,"figs/casa.csv");

    carregar_fig(fig,path_fileName);
    escalar(fig,3);
    imprime_figura(fig);
    arq_desenho(fig);

    free(path_fileName);
    libera_figura(fig);

    return 0;
}
