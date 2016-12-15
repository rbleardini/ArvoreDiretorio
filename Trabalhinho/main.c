#include <stdio.h>
#include <stdlib.h>
#include "trab.h"

int main(){
	TAD* raiz = criar_arvore("exemplo_EDI.txt");
	imprimir_TAD(raiz);
	//NÃO CONFUNDIR SAIDA COM O ARQUIVO DE ENTRADA -> imprimir mostra filhos antes de irmãos!
	return;
}
