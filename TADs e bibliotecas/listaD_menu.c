#include<stdio.h>
#include<stdlib.h>
#include "listaD.h"



int main(void)
{
	listaD l1,l2;
	
	int c;
	int op;
	
	
	criar(&l1);
	
	
	do{
	
	printf("Digite 1-para inserir na lista\n2-para remover da lista\n3 para imprimir a lista\n4-para sair\n");
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			printf("Digite o numero\n");
			scanf(" %d",&c);
			if(inserir(c,&l1))
				printf("Sucesso\n")	;
			else
				printf("Overflow de memória\n");
			break;
		case 2:
			printf("digite o numero a ser removido\n");
 			scanf("%d",&c);
			if(remover(&l1,&c))
			{
				printf("O elemento removido foi %d\n",c);
			}
				
			else
				printf("underflow de lista\n");
			break;
		case 3:
			imprimir(&l1);
			break;
		
			
		
	}
	}while(op!=4);
	
}

