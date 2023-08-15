
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int dado;
	struct no *prox;
}no;

typedef	struct {
	no *ini;
	no *fim;
}fila;

void criar(fila *f)
{
	f->ini = NULL;
	f->fim = NULL;
}

int vazia(fila *f)
{
	if(f->ini == NULL)
	return 1;
	else return 0;
}

int inserir(fila *f, int c)
{
	no *novo = (no *) malloc(sizeof(no));
	novo->dado = c; 
	novo->prox = NULL;
	
	if(!novo) return 0;
	
	if(f->ini == NULL) f->ini = novo;
	else f->fim->prox = novo;
	f->fim = novo;
	return 1;

}

int remover(fila *f)
{
	no *aux;
	int c;
	if (vazia(f)){
		printf("Fila vazia!\n"); 
		exit(1);
	}
	
	aux = f->ini;
	f->ini = aux->prox;
	if (f->ini == NULL)
		f->fim = NULL;
	free(aux);
	return 1;
}

void esvaziar(fila *f)
{
	no *aux = f->ini;
	no *aux2;
	while (aux != NULL){
		aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
	free(f);
}

void imprimir(fila *f)
{
	no *aux;
	printf("Fila: ");
	if (vazia(f)){
		printf("Lista Vazia\n");
	} else {
		aux = f->ini;
		while(aux!=NULL){
		printf("%d ", aux->dado);
		aux = aux->prox;
	}
		printf("\n");
	}
}

void buscar (fila *f, int c)
{
		no *aux;
		aux=f->ini;
	
	if (vazia(f)){
		printf ("fila vazia\n");
	}
	
	while ((aux != NULL) && (aux->dado != c)){	
		aux = aux->prox;
	}
	if (aux == NULL ){
		printf ("%d nao ta na fila\n", c);
	}
	else {
		printf ("%d esta na fila\n", c);
	}
	
}


