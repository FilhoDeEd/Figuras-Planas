#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "figura.h"
#define PI 3.14159265359

typedef struct elemento
{   
    Ponto ponto;
    struct elemento* prox;
}Elem;

struct figura
{
    Elem* inicio;
    int qtd;
};

Figura* cria_figura()
{
    Figura* fig = (Figura*) malloc(sizeof(Figura));
    if(fig != NULL)
    {
        fig->inicio = NULL;
        fig->qtd = 0;
    }

    return fig;
}

void libera_figura(Figura* fig)
{
    if(fig == NULL) return;

    if(fig->inicio == NULL)
    {
        free(fig);
        return;
    }

    Elem *no, *aux = fig->inicio->prox;

    while(aux != fig->inicio)
    {
        no = aux;
        aux = aux->prox;
        free(no);
    }

    free(fig->inicio);
    free(fig);
}

int cria_insere_ponto(Figura* fig, float x, float y, int ID, int pos)
{
    //Lista válida?
    if(fig == NULL) return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;

    no->ponto.x = x;
    no->ponto.y = y;
    no->ponto.ID = ID;

    //Lista vazia?
    if(fig->inicio == NULL)
    {
        no->prox = no;
        fig->inicio = no;
        (fig->qtd)++;
        return 1;
    }

    //pos é inválido?
    if(pos < 0 || pos > fig->qtd) return 0;

    //Inserção no início?
    if(pos == 0)
    {
        Elem* fim = fig->inicio;

        while(fim->prox != fig->inicio) fim = fim->prox;

        fim->prox = no;
        no->prox = fig->inicio;
        fig->inicio = no;
        (fig->qtd)++;
        return 1;
    }

    Elem* aux = fig->inicio;
    int i;

    for(i = 1; i != pos; i++) aux = aux->prox;

    no->prox = aux->prox;
    aux->prox = no;
    (fig->qtd)++;
    return 1;
}

int remove_ponto(Figura* fig, int ID)
{
    if(fig == NULL || fig->inicio == NULL) return 0;

    if(fig->inicio->ponto.ID == ID)
    {
        Elem *remover, *fim;

        remover = fig->inicio;
        fim = fig->inicio;

        while(fim->prox != fig->inicio) fim = fim->prox;

        if(fim == fig->inicio)
        {
            fig->inicio = NULL;
            (fig->qtd)--;
            free(remover);
            return 1;
        }

        fim->prox = fig->inicio->prox;
        fig->inicio = fig->inicio->prox;
        (fig->qtd)--;
        free(remover);
        return 1;
    }

    Elem *remover, *aux = fig->inicio;
    short int elem_encontrado = 0;

    do
    {
        if(aux->prox->ponto.ID == ID)
        {
            elem_encontrado = 1;
            break;
        }

        aux = aux->prox;

    }while(aux->prox != fig->inicio);

    if(!elem_encontrado) return 0;

    remover = aux->prox;
    aux->prox = remover->prox;
    (fig->qtd)--;
    free(remover);
    return 1;
}

int arq_desenho(Figura* fig)
{
    if(fig == NULL || fig->inicio == NULL) return 0;

    FILE *arq = fopen("desenhar.csv","w");
    if(arq == NULL) return 0;

    Elem* aux = fig->inicio;
    fprintf(arq,"x,y\n");
    do
    {
        fprintf(arq,"%f,%f",aux->ponto.x, aux->ponto.y);
        if(aux->prox != fig->inicio) fprintf(arq,"\n");
        aux = aux->prox;
    }while(aux != fig->inicio);

    fclose(arq);
    return 1;
}

int carregar_fig(Figura* fig, char* path_fileName)
{
    if(fig == NULL || fig->inicio != NULL) return 0;

    int ID, i = 0;
    float x, y;

    FILE* arq = fopen(path_fileName,"r");
    if(arq == NULL) return 0;

    while(!feof(arq))
    {
        fscanf(arq,"%d,",&ID);
        fscanf(arq,"%f,",&x);
        fscanf(arq,"%f,",&y);
        cria_insere_ponto(fig,x,y,ID,i);
        i++;
    }

    fclose(arq);
    return 1;
}

int salvar_fig(Figura* fig, char* path_fileName)
{
    if(fig == NULL || fig->inicio == NULL) return 0;

    FILE *arq = fopen(path_fileName,"w");
    if(arq == NULL) return 0;

    Elem* aux = fig->inicio;
    do
    {
        fprintf(arq,"%d,%f,%f",aux->ponto.ID, aux->ponto.x, aux->ponto.y);
        if(aux->prox != fig->inicio) fprintf(arq,"\n");
        aux = aux->prox;
    }while(aux != fig->inicio);

    fclose(arq);
    return 1;
}

void imprime_figura(Figura* fig)
{
    if(fig == NULL)
    {
        printf("Figura inexistente.\n");
        return;
    }

    if(fig->inicio == NULL)
    {
        printf("Figura sem pontos.\n");
        return;
    }

    Elem* aux = fig->inicio;
    int i = 0;

    printf("pos | ID | (x,y)\n");
    do
    {
        printf("%d | %d | (%.2f,%.2f)\n", i, aux->ponto.ID, aux->ponto.x, aux->ponto.y);
        i++;
        aux = aux->prox;
    }while(aux != fig->inicio);
    printf("----------------\n");
    printf("qtd pontos = %d\n",fig->qtd);
    printf("----------------\n");
}

int transformacao_linear_por_ponto(Figura* fig, float *matriz)
{
    if(fig == NULL || fig->inicio == NULL) return 0;

    Elem* aux = fig->inicio;
    float x,y;

    float a = matriz[0];
    float b = matriz[1];
    float c = matriz[2];
    float d = matriz[3];

    do
    {
        x = aux->ponto.x;
        y = aux->ponto.y;

        aux->ponto.x = a*x + b*y;
        aux->ponto.y = c*x + d*y;

        aux = aux->prox;

    }while(aux != fig->inicio);

    return 1;
}

int deslocar(Figura* fig, float delta_x, float delta_y)
{
    if(fig == NULL || fig->inicio == NULL) return 0;

    Elem* aux = fig->inicio;

    do
    {
        aux->ponto.x += delta_x; 
        aux->ponto.y += delta_y;

        aux = aux->prox;

    }while(aux != fig->inicio);

    return 1;
}

int refletir_x(Figura* fig)
{
    float matriz[4];

    matriz[0] = 1;
    matriz[1] = 0;
    matriz[2] = 0;
    matriz[3] = -1;

    return transformacao_linear_por_ponto(fig,matriz);
}

int refletir_y(Figura* fig)
{
    float matriz[4];

    matriz[0] = -1;
    matriz[1] = 0;
    matriz[2] = 0;
    matriz[3] = 1;

    return transformacao_linear_por_ponto(fig,matriz);
}

int refletir_o(Figura* fig)
{
    float matriz[4];

    matriz[0] = -1;
    matriz[1] = 0;
    matriz[2] = 0;
    matriz[3] = -1;

    return transformacao_linear_por_ponto(fig,matriz);
}

int escalar_x(Figura* fig, float alfa)
{
    float matriz[4];

    matriz[0] = alfa;
    matriz[1] = 0;
    matriz[2] = 0;
    matriz[3] = 1;

    return transformacao_linear_por_ponto(fig,matriz);
}

int escalar_y(Figura* fig, float alfa)
{
    float matriz[4];

    matriz[0] = 1;
    matriz[1] = 0;
    matriz[2] = 0;
    matriz[3] = alfa;

    return transformacao_linear_por_ponto(fig,matriz);
}

int escalar(Figura* fig, float alfa)
{
    float matriz[4];

    matriz[0] = alfa;
    matriz[1] = 0;
    matriz[2] = 0;
    matriz[3] = alfa;

    return transformacao_linear_por_ponto(fig,matriz);
}

int rotacionar(Figura* fig, float angulo)
{
    float matriz[4];

    float ang_rad = (angulo*PI)/180.0;

    matriz[0] = cos(ang_rad);
    matriz[1] = -sin(ang_rad);
    matriz[2] = sin(ang_rad);
    matriz[3] = cos(ang_rad);

    return transformacao_linear_por_ponto(fig,matriz);
}