#include <stdio.h>
#include <stdlib.h>

typedef struct arrdir{
	int tipo;         //0 é diretório e 1 é arquivo
	struct arrdir *pai, *filho , *prox_irmao;
	void *info;
}TAD;

typedef struct diretorio{
	char *nome , *data_criacao , *data_atualizacao;
	int *permissao;  //read(r) write(w) 
	int n;
}TD;

typedef struct arquivo{
	char tipo_arq;
	char *nome , *data_criacao , *data_atualizacao;
	int *permissao;  //read(r) write(w) execute(x)
}TA;

//Funções de Arvore Diretório
TAD* criar(int tipo);

int eDiretorio(TAD *a);

void mover(TAD *raiz ,TAD *a , TAD *novo_pai);
void renomear(TAD *a , char *novo_nome);

void transformar_geral(TAD *a);
TD* transformar_AD(TAD *a);
TA* transformar_DA(TAD *a);

void destruir(TAD *a , TAD *no);
void liberar(TAD *a);

//Funções de tipo Arquivo

TA* cria_arquivo(char *nome, char tipo, int *perm);

//Funções de tipo Diretório

TD* cria_diretorio(char *nome, int *perm);

//Declarações das funções
TAD* criar(int tipo){
	TAD *novo = (TAD*)malloc(sizeof(TAD));
	novo -> tipo = tipo;
	novo -> filho = NULL;
	novo -> prox_irmao = NULL;
	novo -> pai = NULL;
	char *nome = (char*)malloc(sizeof(char)*40);
	int p;
	if(eDiretorio(novo)){
		int *perm= (int*)malloc(sizeof(int)*2);                                   //***********FALTA O N DO DIRETÓRIO ***********
		printf("Digite o nome do diretorio: ");
		scanf("%s",nome);
		printf("Ele tem permissao de escrever? [1 para sim / 0 para nao]: ");
		scanf(" %d",&p);
		perm[0]=p;
		printf("Ele tem permissao de ler? [1 para sim / 0 para nao] : ");
		scanf(" %d",&p);
		perm[1]=p;
		TD *i = cria_diretorio(nome,perm);
		novo -> info=i;
		
		
	}else{
	    char t;
		int *perm= (int*)malloc(sizeof(int)*3);    
		printf("Digite o nome do arquivo: ");
		scanf("%s",nome);
		scanf("Qual e o tipo de arquivo? T para texto/B para binario %c", &t);
		printf("Ele tem permissao de escrever? [1 para sim / 0 para nao]: ");
		scanf(" %d",&p);
		perm[0]=p;
		printf("Ele tem permissao de ler? [1 para sim / 0 para nao]: ");
		scanf(" %d",&p);
		perm[1]=p;
		printf("Ele tem permissao de executar? [1 para sim / 0 para nao]: ");
		scanf(" %d",&p);
		perm[2]=p;
		TA *i = cria_arquivo(nome,t,perm);
		novo -> info=i;
		
	}
}

int eDiretorio(TAD *a){
	if(!a)return -1;
	return !(a->tipo);
}

TA* cria_arquivo(char *nome, char tipo, int *perm){   //Falta definir Data e Hora de Criação 
	TA *novo = (TA*)malloc(sizeof(TA));
	novo -> nome = nome;
	novo -> tipo_arq = tipo;
	novo -> permissao = perm;
	return novo;
}

TD* cria_diretorio(char *nome, int *perm){         //Falta definir Data e Hora de Criação, e inicializar n
	TD *novo = (TD*)malloc(sizeof(TD));
	novo -> nome = nome;
	novo -> permissao = perm;
	novo -> n = 0;
	return novo;
}
