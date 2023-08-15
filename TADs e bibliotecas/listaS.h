#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int dado;
	struct no *proximo;
}no;

typedef struct {
	no *primeiro;
}lista;
	

void criar (lista *l){
	l->primeiro=NULL;
}

int vazia (lista *l){
	if (l->primeiro == NULL){
		return 1;
	}
	else {
		return 0;
	}
	
}

int inserir (char c,lista *l){
	no *novo;
	
	novo=(no *)malloc(sizeof(no));

	
	if (!novo)
		return 0;
		
	
	novo->proximo=NULL;
	novo->dado= c;
	
	if (vazia(l)){
		l->primeiro=novo;
	}
	else {
		novo->proximo=l->primeiro;
		l->primeiro=novo;
		
	}
	return 1;

		
}

int remover (lista *l)
{
	no *auxiliar;
	if (vazia(l)){
		return 0;
	}
	else {
		
		l->primeiro=l->primeiro->proximo;
		
		
	}
}

void imprimir (lista *l){
	no *auxiliar;
	
	if (vazia(l)){
		printf ("lista vazia\n");
	}
	else{
		auxiliar=l->primeiro;
		while (auxiliar != NULL){
			printf ("%d\n", auxiliar->dado);
			auxiliar=auxiliar->proximo;
		}
	}
}

void busca (lista *l, char c)
{
		no *aux;
		aux=l->primeiro;
	
	if (vazia(l)){
		printf ("fila vazia\n");
	}
	
	while ((aux != NULL) && (aux->dado != c)){	
		aux = aux->proximo;
	}
	if (aux == NULL ){
		printf ("%d nao ta na lista\n", c);
	}
	else {
		printf ("%d esta na lista\n", c);
	}
	
}

