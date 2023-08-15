#include<stdio.h>
#include<stdlib.h>

typedef struct no
{
	int elem;
	struct no *prox;
	struct no *ant;
}noD;

typedef struct 
{
	noD *prim;
}listaD;


void criar(listaD *l)
{
	l->prim = NULL;
	
}


int vazia(listaD *l)
{
	if(l->prim == NULL)
		return 1;
	else
		return 0;
}

int inserir(int c, listaD *l)
{//insere numeros em uma lista duplamente encadeada ordenada
	
	noD *novo,*aux;
	
	novo = (noD *)malloc(sizeof (noD));
	
	if(!novo)
		return 0;
	
	novo->prox=NULL;
	novo->ant = NULL;
	novo->elem = c;
	
	
	if(vazia(l))
	{
		l->prim = novo;
		
	}
	else
	{
		aux = l->prim;
		while(aux->prox != NULL && aux->prox->elem<c )
		{
			aux = aux->prox;
		}
		
		if(aux == l->prim && aux->elem > c)
		{
			novo->prox = aux;
			l->prim = novo;
				
		}
		else
		{
			if(aux->prox == NULL)
			{
				novo->ant = aux;
				aux->prox = novo;
			}
			else
			{
				novo->prox = aux->prox;
				novo->ant = aux;
				aux->prox->ant = novo;
				aux->prox = novo;		
			}
		
		}
		
				
	}
	
	return 1;
}



noD* busca(listaD *l, int elem)
{
	
	noD *aux;
	
	aux = l->prim;
	
	while(( aux!=NULL) && (aux->elem != elem ))
	{
		aux = aux->prox;
	}
	
	if(aux == NULL)
	{
		printf("Elemento não enccontrado\n");
		
	}
	return aux;
		
	
}

 int remover(listaD *l,int *e)
 {
 	noD *aux;
 	
 	
 	aux = busca(l,*e);
 	
 	
 	
 	if(vazia(l) || !aux)
 		return 0;
 	else
 	{
 		if(aux!=l->prim && aux->prox !=NULL)
 		{
 			
			*e= aux->elem;
			aux->prox->ant = aux->ant;
			aux->ant->prox = aux->prox;
			free(aux);
		
		}
		else
		{
			if(aux == l->prim && aux->prox != NULL)
			{
				*e= aux->elem;
				aux->prox->ant = NULL;
				l->prim = aux->prox;
				free(aux);
			}
			else
			{
				if(aux == l->prim && aux->prox == NULL)
				{
					l->prim = NULL;
					free(aux);
				}
				
				else
				{
					*e= aux->elem;
					aux->ant->prox = NULL;
					free(aux);
				}
			}
			
		}
 		
	
	}
 	
 	return 1;
}

void imprimir(listaD *l)
{
	noD *aux;
	
	if(vazia(l))
		printf("Lista vazia\n");
	
	else
	{
		aux=l->prim;
		while(aux!=NULL)
		{
			printf("%d\n",aux->elem);
			aux = aux->prox;
		}
	}
}


