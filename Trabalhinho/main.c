#include <stdio.h>
#include <stdlib.h>
#include "trab.h"

int main(){
	TAD *novo = criar(0);
	
	if(eDiretorio(novo)){
		
		TD* aux = (TD*)novo -> info;
		printf(" %s\n",aux -> nome);
	}else{
		TA* aux = (TA*)novo -> info;
		printf(" %s\n",aux -> nome);
	}
	return 0;
}
