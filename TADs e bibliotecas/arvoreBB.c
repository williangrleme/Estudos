//#include<stdio.h>
//#include<stdlib.h>
#include "arvoreBB.h"

	
int main(void)
{
	int num;
	int n, c;
	int op,chave;
	arvore av1;
	
	criar(&av1);
	
	
	do{
	
	printf("Digite 1-para inserir na arvore\n2-para remover da �rvore\n3 para imprimir a �rvore\n4-para buscar um elemento na �rvore\n5-para sair\n");
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			printf("Digite o n�mero\n");
			scanf("%d",&n);
			if(av1.raiz == NULL)
			{
				criarR(&av1,n);
			}
			else
			{
				if(inserir(av1.raiz,n))
					printf("Sucesso\n")	;
				else
					printf("Overflow de mem�ria\n");
			}
			
			break;
		case 2:
			printf("Digite o caractere a ser removido\n");
			scanf("%d",&c);
			if(remover(av1.raiz, c))
				printf("O elemento removido foi %d\n",c);
			else
				printf("underflow de lista\n");
			break;
		case 3:
			imprimir(av1.raiz);
			break;
		case 4:
			printf("Qual n�mero deseja localizar?\n");
			scanf("%d",&chave);
			if(busca(&av1,chave))
				printf("Elemento localizado\n");
			else
				printf("Elemento n�o localizado");
			break;
				
		
	}
	}while(op!=5);
	
}
	
	
	



