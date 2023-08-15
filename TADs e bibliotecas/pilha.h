#include <stdio.h>
#include<stdlib.h>

typedef struct no {
	int dado;
	struct no *proximo;	
}no;


 typedef struct {
 	no *topo;
 }pilha;
 
 void criar (pilha *p){
 	p->topo=NULL;
 } 
 
 int vazia(pilha *p){
 	if (p->topo == NULL){
 		return 1;
	 }
	 else {
	 	return 0;
	 }
 }

void push (int c,pilha *p){
	no *novo;
	
	novo=(no *)malloc(sizeof(no));
	novo->proximo=NULL;
	novo->dado=c;
	
	
	if (vazia(p)){
		p->topo=novo; // caso o topo esteja vazio o novo é o topo
	}
	else {
        novo->proximo = p->topo;
        p->topo=novo;
	}

}

int pop (pilha *p){
	no *auxiliar;
	
if (vazia(p)){
	return 0;
}
else {
	auxiliar=p->topo;
	p->topo=auxiliar->proximo;
	free(auxiliar);
}
return 1;
}

void imprimir_pilha (pilha *p){
	no *auxiliar;

	if (vazia(p)){
		printf ("pilha vazia\n");
	}
	else {
		auxiliar=p->topo;
		while (auxiliar != NULL){
			printf ("%d\n", auxiliar->dado);
			auxiliar=auxiliar->proximo;
		}
	}	
}







