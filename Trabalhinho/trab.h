#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
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
    char tipo;
    char *nome, *data_criacao, *data_atualizacao;
    int *permissao; // R(read) W(write) X(execute)
} TA;
 
 
// Funções da árvore
TAD* criar(int tipo); // ajeitar
 
int eDiretorio(TAD *a);
 
void mover(TAD *raiz, TAD *a, TAD *novo_pai);
void renomear(TAD *a, char *novo_nome);
TAD* busca(TAD *raiz, int tipo, char *nome);
void inserir(TAD *raiz, char *pai, int tipo, char *nome, int *perm);
 
void transformar_geral(TAD *a);
TD* transformar_AD(TAD *a);
TA* transformar_DA(TAD *a);
 
void destruir(TAD *a, TAD *no); //falta esse
void liberar(TAD *a); //falta esse
 
// Funções do tipo Arquivo
TA* cria_arquivo(char *nome, char tipo, int *perm); // ajeitar
 
// Funções do tipo Diretório
TD* cria_diretorio(char *nome, int *perm); // ajeitar
 
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
    novo -> tipo = tipo;
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
 
char* data_hora(void) {                                 //BOA JULIA
    char *timestamp = (char*) malloc(sizeof(char) * 40);
 
    time_t rawtime;
    struct tm *timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
 
    sprintf(timestamp, "%d/%d/%d %d:%d:%d", timeinfo -> tm_mday, timeinfo -> tm_mon + 1,
            timeinfo -> tm_year + 1900, timeinfo -> tm_hour, timeinfo -> tm_min, timeinfo -> tm_sec);
 
    return timestamp;
}


// INICIALIZA ARVORE

TAD* criar_arvore() {
	TD *raiz = (TD*) malloc(sizeof(TD));
	raiz -> nome = "/";
	int *perm = (int*) malloc(sizeof(int) * 2);
	perm[0] = 1; perm[1] = 0;
	raiz -> permissao = perm;
	char *data = data_hora();
	raiz -> data_criacao = raiz -> data_atualizacao = data;
	
	TAD *a = (TAD*) malloc(sizeof(TAD));
	a -> pai = a -> filho = a -> prox_irmao = NULL;
	a -> tipo = 0;
	a -> info = raiz;
	
	return a;	
}

TAD* busca(TAD *raiz, int tipo, char *nome) {
	if (!raiz) return NULL;
	
	if (tipo == raiz -> tipo){
		if(eDiretorio(raiz)) {
			TD* no = (TD*)raiz -> info;
			if(!strcmp(no -> nome, nome)) return raiz;
		}
		
		else {
			TA* no = (TA*) raiz -> info;
			if (!strcmp(no -> nome, nome)) return raiz;
		}
	}
	TAD *resp;
	resp = busca(raiz -> prox_irmao, tipo, nome);
	if(resp)return resp;
	return busca(raiz -> filho, tipo, nome);
	
}

void inserir(TAD *raiz, char *linha) {
	char *tipo, *nome, *pai, *data;
	//split( linha, tipo, nome, pai, data); 
	

}

