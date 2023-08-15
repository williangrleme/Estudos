#include <stdio.h>
#include <stdlib.h>
#include "listaS.h"

int main () {
	
	lista l1;
	criar (&l1);
	int op;
	char c;
	
	do {
		printf ("1-Inserir\n2-Remover do fim\n3-Imprimir\n4-Sair\n");
		scanf ("%d",&op);
		fflush(stdin);
		
		switch (op) {
			case 1:
				printf ("Digite o numero para inserir\n");
				scanf (" %d", &c);
				fflush(stdin);
				if (inserir(c,&l1))
				printf ("Sucesso\n");
				else 
				printf ("Falhou\n");
				break;
			case 2:
				remover (&l1);
				break;
			case 3:
				imprimir(&l1);
				break;
			case 4:
				busca (&l1,c);
				break;
		}
	}
	while (op!=5);
}



