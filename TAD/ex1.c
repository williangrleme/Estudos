#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
	char elem;
	struct no *prox;
}no;

typedef struct
{
	no *topo;
}pilha;

int push(char a, pilha *p);
int pop(pilha *p);
int vazia(pilha *p);
void criar(pilha *p);
void imprimir(pilha *p);

int push(char a, pilha *p)
{
	no *novo;
	
	novo=malloc(sizeof(no));
	
	if(!novo)
	return 0;
	
	novo->prox=NULL;
	novo->elem=a;
	
	
	if(vazia(p))
	{
		p->topo=novo;
	}
	else
	{
		novo->prox=p->topo;
		p->topo=novo;	
	}
	return 1;	
}

int pop(pilha *p)
{
	no *aux;
	
	if(vazia(p))
	return 0;
	else
	{
		aux=p->topo;
		p->topo=p->topo->prox;
		free(aux);
	}	
	return 1;	
}

int vazia(pilha *p)
{
	if(p->topo==NULL)
	return 1;
	else
	return 0;
}

void criar(pilha *p)
{
	p->topo=NULL;
}

void imprimir(pilha *p)
{
	
	pilha p2;
	criar(&p2);
	
	char m;
	no *aux,*aux2;
	
	if(vazia(p))
	printf("pilha vazia\n");
	else
	{
		aux=p->topo;
		
		while(aux!=NULL)
		{
			m=aux->elem;
			push(m,&p2);
			aux=aux->prox;
			pop(p);
			
			if(p->topo==NULL)
			{
				aux2=p2.topo;
				while(aux2!=NULL)
				{
					m=aux2->elem;
					printf("%c",aux2->elem);
					push(m,p);
					aux2=aux2->prox;
					pop(&p2);
					
				}
			}
		}

	}
	
}

int main ()
{
	pilha p1;
	int x;
	char y;
	
	criar(&p1);

	do
	{
	printf("\nDigite 1:para inserir na pilha\n2:para remover da pilha\n3:para imprimir a pilha\n0:para sair\n");
	scanf("%d",&x);
	fflush(stdin);
	switch(x)
	{
		case 1:
			printf("Digite uma letra: ");
			y=getchar();
			push(y,&p1);
			break;
		case 2:
			pop(&p1);
			break;
		case 3:
			imprimir(&p1);
			break;			
	}
	}while(x!=0);
}





