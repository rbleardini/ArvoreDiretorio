#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
typedef struct arrdir {
    int tipo; // 0 = diretório / 1 = arquivo
    struct arrdir *pai, *filho, *prox_irmao;
    void *info;
} TAD;
 
typedef struct diretorio {
    char *nome, *data_criacao, *data_atualizacao;
    int *permissao; // R(read) W(write)
    int n; // número de arquivos
} TD;
 
typedef struct arquivo {
    char tipo_arq;
    char *nome, *data_criacao, *data_atualizacao;
    int *permissao; // R(read) W(write) X(execute)
} TA;
 
 
// Funções da árvore
TAD* criar(int tipo);
 
int eDiretorio(TAD *a);
 
void mover(TAD *raiz, TAD *a, TAD *novo_pai);
void renomear(TAD *a, char *novo_nome);
 
void transformar_geral(TAD *a);
TD* transformar_AD(TAD *a);
TA* transformar_DA(TAD *a);
 
void destruir(TAD *a, TAD *no);
void liberar(TAD *a);
 
// Funções do tipo Arquivo
TA* cria_arquivo(char *nome, char tipo, int *perm);
 
// Funções do tipo Diretório
TD* cria_diretorio(char *nome, int *perm);
 
char* data_hora(void);
 
 
// CRIAR NÓ
TAD* criar(int tipo) {
    TAD *novo = (TAD*) malloc(sizeof(TAD));
    novo -> tipo = tipo;
    novo -> filho = NULL;
    novo -> prox_irmao = NULL;
    novo -> pai = NULL;
 
    char *nome = (char*) malloc(sizeof(char) * 40);
    int p;
 
    if(eDiretorio(novo)) {
        int *perm = (int*) malloc(sizeof(int) * 2);
        printf("Nome do diretorio: ");
        scanf("%s", nome);
        printf("Permissao para escrever [1 para sim / 0 para nao]: ");
        scanf(" %d", &p);
        perm[0] = p;
        printf("Permissao para ler [1 para sim / 0 para nao]: ");
        scanf(" %d", &p);
        perm[1] = p;
 
        TD *i = cria_diretorio(nome, perm);
        novo -> info = i;
    }
 
    else {
        char t;
        int *perm = (int*) malloc(sizeof(int) * 3);
        printf("Nome do arquivo: ");
        scanf("%s", nome);
        scanf("Tipo de arquivo [T para texto / B para binario] %c", &t);
 
        printf("Permissao para escrever [1 para sim / 0 para nao]: ");
        scanf(" %d", &p);
        perm[0] = p;
        printf("Permissao para ler [1 para sim / 0 para nao]: ");
        scanf(" %d", &p);
        perm[1] = p;
        printf("Permissao para executar [1 para sim / 0 para nao]: ");
        scanf(" %d", &p);
        perm[2] = p;
        TA *i = cria_arquivo(nome, t, perm);
        novo -> info = i;
    }
 
    return novo;
}
 
int eDiretorio(TAD *a) {
    if (!a) return -1;
    return !(a -> tipo);
}
 
TA* cria_arquivo(char *nome, char tipo, int *perm) {
    TA *novo = (TA*) malloc(sizeof(TA));
    novo -> nome = nome;
    novo -> tipo_arq = tipo;
    novo -> permissao = perm;
 
    char *data = data_hora();
    novo -> data_criacao = novo -> data_atualizacao = data;
    return novo;
}
 
TD* cria_diretorio(char *nome, int *perm) {
    TD *novo = (TD*) malloc(sizeof(TD));
    novo -> nome = nome;
    novo -> permissao = perm;
    novo -> n = 0;
 
    char *data = data_hora();
    novo -> data_criacao = novo -> data_atualizacao = data;
 
    return novo;
}
 
char* data_hora(void) {
    char *timestamp = (char*) malloc(sizeof(char) * 40);
 
    time_t rawtime;
    struct tm *timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
 
    sprintf(timestamp, "%d/%d/%d %d:%d:%d", timeinfo -> tm_mday, timeinfo -> tm_mon + 1,
            timeinfo -> tm_year + 1900, timeinfo -> tm_hour, timeinfo -> tm_min, timeinfo -> tm_sec);
 
    return timestamp;
}
