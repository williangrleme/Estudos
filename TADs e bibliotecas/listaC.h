#include<stdio.h>
#include<stdlib.h>

typedef struct no
{
	int elem;
	struct no *prox;
}no;

typedef struct 
{
	no *ult;
}listaC;

void criar(listaC *l)
{
	l->ult = NULL;
}

int vazia(listaC *l)
{
	if(l->ult == NULL)
		return 1;
	else
		return 0;
}

int inserir(int c, listaC *l)
{
	
	no *novo,*aux;
	
	novo = (no *)malloc(sizeof (no));
	
	if(!novo)
		return 0;
	
	novo->prox=NULL;
	novo->elem = c;
	
	
	if(vazia(l))
	{
		l->ult = novo;
		l->ult->prox = l->ult;
		
	}
	else
	{
	

	
		novo->prox = l->ult->prox;
		l->ult->prox = novo;
		l->ult = novo;
		
	}
	
	return 1;
}


 int remover(listaC *l,int *e)
 {
 	no *aux1,*aux2;
 	
 	if(vazia(l))
 		return 0;
 	else
 	{
 		aux1=l->ult->prox;
 		aux2 = l->ult;
 		while((aux1!=l->ult) && (aux1->elem!=*e))
 		{	
 			
 			aux2 = aux1;
 			aux1 = aux1->prox;	
		}
		
		if(aux1->elem == *e)
		{
			if(aux1!=l->ult)
			{
				aux2->prox = aux1->prox;
				free(aux1);
			}
			else
			{
				if(aux2==aux1)
				{
					free(aux1);
					l->ult = NULL;
				}
				else
				{ 
					aux2->prox = aux1->prox;
					l->ult = aux2;
					free(aux1);
				}
				
			}
			return 1;	
		}
		else
		{
			printf("No não encontrado\n");
				
			return 0;
				
		}
		
		
	}
 	
 	
}

void imprimir(listaC *l)
{
	no *aux;
	
	if(vazia(l))
		printf("Lista vazia\n");
	
	else
	{
		aux=l->ult->prox;
		while(aux!=l->ult)
		{
			printf("%d\n",aux->elem);
			aux = aux->prox;
		}
		printf("%d\n",aux->elem);
		
	}
}
