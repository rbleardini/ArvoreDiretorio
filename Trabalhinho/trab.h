#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
 
typedef struct arrdir {
    char tipo; // D = diretório / T = arquivo de texto / B = arquivo binário
    struct arrdir *pai, *filho, *prox_irmao;
    void *info;
} TAD;
 
typedef struct diretorio {
    char *nome, *data_criacao, *data_atualizacao;
    int *permissao; // R(read) W(write)
    int n; // número de arquivos
} TD;
 
typedef struct arquivo {
    char *nome, *data_criacao, *data_atualizacao;
    int *permissao; // R(read) W(write) X(execute)
} TA;

#define DIRETORIO 'D'
#define TEXTO 'T'
#define BINARIO 'B'
#define MAXLENGTHLINE 1+1+256+1+256+1+3+1+2+1+4+1+8+1
 
// Funções da árvore
//TAD* criar(int tipo); // ajeitar

TAD* criar_arvore(char* nomeArquivo);

//******************************************************AUXILIARES*************************************************** 
TAD* addLine(TAD* raiz, char* linha);
TAD* parseLinha(char* linha,char** nomePai);
void imprimir_TAD(TAD *a);
char* getNome(TAD *a);
char* getData(TAD *a);
//*******************************************************************************************************************
 
void mover(TAD *raiz, TAD *a, TAD *novo_pai);
void renomear(TAD *a, char *novo_nome);
TAD* busca(TAD *raiz, char tipo, char *nome);
void inserir(TAD *raiz, char *pai, int tipo, char *nome, int *perm);

void transformar_geral(TAD *a);
TD* transformar_AD(TAD *a);
TA* transformar_DA(TAD *a);
 
void destruir(TAD *a, TAD *no); //falta esse
void liberar(TAD *a); //falta esse

char* getNome(TAD *a){
	if(!a)return NULL;
	if(a -> tipo == DIRETORIO){
		TD* nod = (TD*)a -> info;
		return nod->nome;
	}else{
		TA* noa = (TA*)a -> info;
		return noa->nome; 
	}
}

char* getData(TAD *a){
	if(!a)return "NULL";
	if(a -> tipo == 'D'){
		TD* nod = (TD*)a -> info;
		return nod->data_criacao;
	}else{
		TA* noa = (TA*)a -> info;
		return noa->data_criacao; 
	}
}

void imprimir_TAD(TAD *a){
	if(!a)return;
	//tipo + info + pai + data/hora
	char str[2] = { a -> tipo, '\0'};
	printf(str);
	printf("/");
	printf(getNome(a));
	printf("/");
	printf(getNome(a -> pai));
	printf("/");
	printf(getData(a));
	printf("\n");
	imprimir_TAD(a -> filho);
	imprimir_TAD(a -> prox_irmao);
}
 
// Funções do tipo Arquivo
TA* cria_arquivo(char *nome, int *perm); // ajeitar
 
// Funções do tipo Diretório
TD* cria_diretorio(char *nome, int *perm); // ajeitar
 
char* data_hora(void);

/* 
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
*/ 
TA* cria_arquivo(char *nome, int *perm) {
    TA *novo = (TA*) malloc(sizeof(TA));
    novo -> nome = (char*)calloc(sizeof(char),strlen(nome)+1);
    strcpy(novo -> nome,nome);
    novo -> permissao = perm;
    novo -> data_criacao = novo -> data_atualizacao = NULL;
    return novo;
}
 
TD* cria_diretorio(char *nome, int *perm) {
    TD *novo = (TD*) malloc(sizeof(TD));
    novo -> nome = (char*)calloc(sizeof(char),strlen(nome)+1);
    strcpy(novo -> nome,nome);
    novo -> permissao = perm;
    novo -> n = 0;
    
	novo -> data_criacao = novo -> data_atualizacao = NULL;
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

TAD* parseLinha(char* linha,char** nomePai)
{	
	char tipo;
	char* auxiliar= NULL;
	TAD* aux=(TAD*)calloc(sizeof(TAD),1);
	if(!aux)return NULL;
	
	auxiliar=strtok(linha,"/");
	aux->tipo= !strcmp(auxiliar,"D")?DIRETORIO:(!strcmp(auxiliar,"T")?TEXTO:BINARIO);
	auxiliar=strtok(NULL,"/");
	
	int *vet1 = (int*)malloc(sizeof(int)*2);
	int *vet2 = (int*)malloc(sizeof(int)*3);
	
	if(aux->tipo==DIRETORIO)
	{
		TD *d = cria_diretorio(auxiliar,vet1);
		aux -> info = d;
	}
	else
	{
		TA *a = cria_arquivo(auxiliar,vet2);
		aux -> info = a;
	}
	auxiliar = strtok(NULL,"/");
	*nomePai = (char*)calloc(sizeof(char),strlen(auxiliar)+1);
	strcpy(*nomePai,auxiliar);
	if(aux->tipo==DIRETORIO)
	{
		auxiliar=strtok(NULL,"\n");
		TD* d=(TD*)aux->info;
		d->data_criacao=(char*)calloc(sizeof(char),strlen(auxiliar)+1);
		strcpy(d->data_criacao,auxiliar);
		d->data_atualizacao=(char*)calloc(sizeof(char),strlen(auxiliar)+1);
		strcpy(d->data_atualizacao,auxiliar);
	}
	else
	{
		auxiliar=strtok(NULL,"/");
		auxiliar=strtok(NULL,"\n");
		TA* a=(TA*)aux->info;
        a->data_criacao=(char*)calloc(sizeof(char),strlen(auxiliar)+1);
		strcpy(a->data_criacao,auxiliar);
		a->data_atualizacao=(char*)calloc(sizeof(char),strlen(auxiliar)+1);
		strcpy(a->data_atualizacao,auxiliar);
	}
	return aux;
}


TAD* addLine(TAD* raiz, char* linha)
{
	TAD* pai;
	TAD* atual;
	char* nomePai;
	atual=parseLinha(linha,&nomePai);
	if(!raiz)return atual;	
	pai=busca(raiz,DIRETORIO,nomePai);
	TAD *aux=pai->filho;
	pai->filho=atual;
	atual->pai=pai;
	atual->prox_irmao=aux;
	return raiz;
}


// INICIALIZA ARVORE

//Veja o formato do arquivo


TAD* criar_arvore(char* nomeArquivo)
{
	TAD *raiz=NULL;
	FILE* fp;
	char* linha;
	linha=(char*)calloc(sizeof(char),MAXLENGTHLINE+1); 
	fp=fopen(nomeArquivo,"r");
	if(!fp || !linha)
	{
		return NULL;
	}
	fgets(linha,MAXLENGTHLINE,fp);
	int i,n = 0;
	for(i = 0;linha[i] != '\0';i++){
		if(linha[i] == '\n')n++;
	}
	if(!n)
	{
		printf("Erro, arquivo inválido!");
		free(linha);
		fclose(fp);
		free(raiz);
		return NULL;
	}
	while(!feof(fp))
	{	
		raiz=addLine(raiz,linha);
		fgets(linha,MAXLENGTHLINE,fp);
	}

	return raiz;	
}


TAD* busca(TAD *raiz, char tipo, char *nome) {
	if (!raiz) return NULL;
	
	if (tipo == raiz -> tipo){
		if(raiz -> tipo == DIRETORIO) {
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

