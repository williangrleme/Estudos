#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "pilha.h"


int main (){
	
char c,b;
int op;
pilha *p1;
criar_pilha (&p1);



do {
	
	setlocale(LC_ALL, "Portuguese");
	printf("escolha uma das opções:\n1-emplilhar(push)\n2-desempilhar(pop) o topo\n3-esvaziar a pilha\n4-imprimir pilha\n5-busca\n6-sair\n");	
	scanf ("%d", &op);	
	fflush(stdin);
	
	switch (op){
		case 1:
			printf ("digite o numero que quer inserir:\n");
			scanf ("%d",&c);
			inserir_pilha(c,&p1);
			break;
		case 2:
			if (!remover_pilha(&p1)){
				printf ("pilha vazia\n");
			}
			break;
		case 3:
			if (vazia(&p1)){
				printf ("pilha vazia\n");
			}
			else {
				for (;remover_pilha(&p1););
				printf ("pilha vazia\n");
			}		
		case 4:
		imprimir_pilha(&p1);
		break;
		case 5:
		scanf ("%d",&b);
		buscar_pilha (b,&p1);
		break;	
		
		default:
			printf ("Comando invalido\n");
			exit (1);
	}
	
}
while (op!=6);
	
}

