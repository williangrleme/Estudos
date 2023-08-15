#include<stdio.h>
#include<stdlib.h>


typedef struct no
{
	int elem;
	struct no *prox;
	struct no *ant;
}noD;//estrutura de um nó de uma lista duplamente encadeada


typedef struct 
{
	noD *topo;
}pilha;


//declaração de duas variáveis do tipo lista

void criar(pilha *p);//recebe uma lista
int push(int c, pilha *p);
int pop(pilha *p);
int vazia(pilha *p);
void imprimir(pilha *p);

int removerIni(pilha *l);

void criar(pilha *p)
{
	p->topo = NULL;
	
}

int push(int c, pilha *p)
{
	
	noD *novo,*aux;
	
	novo = malloc(sizeof (noD));
	
	if(!novo)
		return 0;
	
	novo->prox=NULL;
	novo->ant = NULL;
	novo->elem = c;
	
	
	if(vazia(p))
	{
		p->topo = novo;
	}
	else
	{
		aux = p->topo;
		aux->prox = novo;
		novo->ant = aux;
		p->topo = novo;
	}
	
	return 1;
}

int vazia(pilha *p)
{
	if(p->topo == NULL)//se o ponteiro para inicia da lista estiver nulo
		return 1;
	else
		return 0;
}
 int pop(pilha *p)
 {
 	int c;
 	noD *aux;
 	
 	aux = p->topo;
 	
 	if(vazia(p))
 		return 0;
 	else {
 		p->topo = aux->ant;
 		c = aux->elem;
 		free(aux);
 	
		return c;	
	}

}
void imprimir(pilha *p)
{
	noD *aux;
	
	
	if(vazia(p))
		printf("Lista vazia\n");
	
	else
	{
		aux=p->topo;
		while(aux->ant!=NULL)
		{
			aux = aux->ant;
		}
		
		while(aux!=NULL){
			printf("%d ",aux->elem);
			aux = aux->prox;
		}
		puts("\n");
	}
}

int removerInt(pilha *l)
{
	pilha l2;
	criar(&l2);
	
	int auxInt, c;

	while(vazia(l) != 1){
	auxInt = pop(l);
	push(auxInt, &l2);
	}
	
	c = pop(&l2);
	
	while(vazia(&l2) != 1){
	auxInt = pop(&l2);
	push(auxInt, l);
	
	}
	
	return c;
	
}


int main(void)
{
	pilha l1;
	
	int c, e;
	int op;
	
	
	criar(&l1);
	
	
	
	do{
	
	printf("Digite\n 1-para inserir na fila\n2-para remover da fila\n3 para imprimir a fila\n4-para sair\n");
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			printf("Digite o numero a ser inserido:\n");
			scanf(" %d",&c);
			if(push(c,&l1))
				printf("Sucesso\n")	;
			else
				printf("Overflow de memória\n");
			break;
		case 2:
			printf("O numero do inicio sera removido!\n");
			e = removerInt(&l1);
			printf("O elemento removido foi %d\n", e);
			break;
				
		case 3:
			imprimir(&l1);
			break;
		
			
		
	}
	}while(op!=4);
	
}




 
