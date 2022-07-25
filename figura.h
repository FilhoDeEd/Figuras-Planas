typedef struct ponto
{
    int ID;
    float x;
    float y;
}Ponto;

typedef struct figura Figura;

//Cria a figura.
Figura* cria_figura();

//Exclui a figura.
void libera_figura(Figura* fig);

//Insere um ponto na posição pos da lista e retorna se a operação foi bem sucedida.
//Se pos for igual à quantidade de pontos da figura, a inserção é feita ao final.
//Se a lista está vazia, qualquer valor de pos é aceito.
int cria_insere_ponto(Figura* fig, float x, float y, int ID, int pos);

//Remove um ponto com base no ID do ponto e retorna se a operação foi bem sucedida.
int remove_ponto(Figura* fig, int ID);

//Salva a figura em um csv próprio para o script python poder desenhar e retorna se a operação foi bem sucedida.
int arq_desenho(Figura* fig);

//Carrega os pontos de um csv em uma figura e retorna se a operação foi bem sucedida.
//Passe uma figura vazia e o caminho de um csv válido para carregar uma figura.
//Exemplos de csv válidos na pasta figs.
int carregar_fig(Figura* fig, char* path_fileName);

//Salva a figura em formato csv no caminho especificado e retorna se a operação foi bem sucedida.
int salvar_fig(Figura* fig, char* path_fileName);

//Faz uma listagem ordenada do pontos com seus IDs.
void imprime_figura(Figura* fig);

//Desolca a figura com base em delta_x e delta_y e retorna se a operação foi bem sucedida.
int deslocar(Figura* fig, float delta_x, float delta_y);

//Reflete a figura em relação ao eixo das abscissas e retorna se a operação foi bem sucedida.
int refletir_x(Figura* fig);

//Reflete a figura em relação ao eixo das ordenadas e retorna se a operação foi bem sucedida.
int refletir_y(Figura* fig);

//Reflete a figura em relação à origem e retorna se a operação foi bem sucedida.
int refletir_o(Figura* fig);

//Escala a figura em um fator alfa na direção horizontal e retorna se a operação foi bem sucedida.
int escalar_x(Figura* fig, float alfa);

//Escala a figura em um fator alfa na direção vertical e retorna se a operação foi bem sucedida.
int escalar_y(Figura* fig, float alfa);

//Escala a figura em um fator alfa e retorna se a operação foi bem sucedida.
int escalar(Figura* fig, float alfa);

//Rotaciona a figura no sentido horário em angulo graus e retorna se a operação foi bem sucedida.
int rotacionar(Figura* fig, float angulo);

//Aplica uma transformação linear sobre a figura e retorna se a operação foi bem sucedida.
//Basta passar a figura não vazia e um vetor com 4 floats.
int transformacao_linear_por_ponto(Figura* fig, float *matriz);