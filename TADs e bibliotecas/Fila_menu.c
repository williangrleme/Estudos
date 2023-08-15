#include <stdio.h>
#include <stdlib.h>
#include "fila.h"



int main (){
	
	fila *f1;
	criar_fila(&f1);
	
	int op;
	char c,b;
	
	do {
		printf ("1-Inserir\n2-Remover\n3-Imprimir\n4-Esvaziar\n5-Busca\n6-Sair\n");
		scanf ("%d", &op);
		switch (op){
			case 1:
				scanf ("%d", &c);
				if (inserir_fila(&f1, c)){
					printf ("Inserido com sucesso\n");
				}
				break;
			case 2:
				if (remover_fila(&f1)){
					printf ("Remocao feita com sucesso\n");
				}
				break;
			case 3:
				imprimir_fila (&f1);
				break;
			case 4:
				esvaziar_fila(&f1);
				break;
			case 5:
				scanf ("%d", &b);
				buscar_fila (&f1, b);
				break;
			default:
				printf ("Comando invalido\n");
				exit (1);
		}
	}
	while (op!=6);
	
	
}


