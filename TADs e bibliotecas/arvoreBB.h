#include<stdio.h>
#include<stdlib.h>

typedef struct no
{
	int info;
	struct no *esq;
	struct no *dir;
	
}no;


typedef struct
{
	no *raiz;
}arvore;

//funções de manipulação de uma arvore binária
//1 - info(p) - retorna a informação armazenada no nó p
//2 - left(p) - retorna o filho à esquerda do nó p
//3 - rigth(p) - retorna o filho à direita do nó p
//4 - father(p) - retorna um ponteiro para o nó pai do nó p
//5 - brother(p) - retorna um ponteiro para o nó irmão do nó p
//6 - criar(avr) - retorna um ponteiro para uma árvore, ou seja, um ponteiro para sua raiz
//7 - setleft(p) - cria um nó filho à esquerda do no p.
//8 - setrigth(p) - cria um nó filho à direita do nó p.


void criar(arvore *av);//cria uma arvore vazia
int criarR(arvore *av,int e);//cria uma árore com raiz diferente de nulo
void info(no *p,int *i);//
no* left(no *pai);
void rigth(no *pai, no *fdir);
void setrigth(no *pai, int n);
void setleft(no *pai, int n);
no* busca(arvore *av,int chave);
int vazia(arvore *av);
int inserir(no *raiz,int n);
void imprimir(no *raiz);
no* remover(no *raiz,int v);


void imprimir(no *raiz)
{
	if(raiz == NULL)
	{
		return;
	}
	else
	{
		imprimir(raiz->esq);
		printf("%d  ",raiz->info);
		imprimir(raiz->dir);
		
	}
}

void criar(arvore *av)
{
	av->raiz = NULL;
}

int criarR(arvore *av,int e)
{
	no *novo;
	
	novo = (no*) malloc(sizeof(no));
	
	if(!novo)
		return 0;
	else
	{
		novo->info = e;
		novo->dir = NULL;
		novo->esq = NULL;
		av->raiz = novo;
		return 1;
	}
}






int vazia(arvore *av)
{
	if(av->raiz == NULL)
		return 1;
	else
		return 0;
}


no* busca(arvore *av, int chave)
{
	no *aux,*aux2;
	int  n;
	aux = av->raiz;
	aux2 = aux;//aux2 guarda o nó pai de aux, e no fim da busca o próprio nó que contém a chave
	//isto por que, no fim da busca, aux guarda o nó filho do nó que contém a chave
	if(!vazia(av))
	{
		printf("inicio da busca....\n");
		 	n = aux->info;
			printf("%d  ",n);
	}
	else
		return NULL;
		
	while((aux!=NULL)&&(n!=chave))
	{
		
		if(chave < n)
		{
			aux2 = aux;
			aux = aux->esq;//atualiza aux para o nó filho esquerdo
			if(aux!=NULL)
			{
				n = aux->info;//passo o no atual e recebe o campo info deste no para comparação
				printf("%d  ",aux->info);
			}
			
			
		}
		else
		{
			aux2 = aux;
			aux = aux->dir;//atualiza aux para o nó filho direito
			if(aux!=NULL)
			{
					n = aux->info;//passo o no atual e recebe o campo info deste no para comparação
					printf("%d  ",aux->info);
			}
			
		}
			
		
		
	}
	if(n == chave)//chave encontrada
	{
		printf("chave = %d\n",n);
		return aux2;
	}
	
	else
	{
		return NULL;
		
	}
	
	
	
}
int inserir(no *raiz, int n)
{
	no *aux,*novo;
	
	aux = raiz;
	
	
		if(n < aux->info)//
		{
			if(aux->esq == NULL)//fim da recursão
			{
				novo = (no*)malloc(sizeof(no));
				novo->esq = NULL;
				novo->dir = NULL;
				novo->info = n;
				aux->esq = novo;
				return 1;
			}
			else
			{
				return inserir(aux->esq,n);
			}
		}
		else
		{
			if(aux->dir == NULL)//fim da recursão
			{
				novo = (no*)malloc(sizeof(no));
				novo->esq = NULL;
				novo->dir = NULL;
				novo->info = n;
				aux->dir = novo;
				return 1;
			}
			else
			{
				return inserir(aux->dir,n);
			}
		
		}
}
no* remover(no* r, int v)
{
 	if (r == NULL)
    	return NULL;
 	else if (r->info > v)
    	r->esq = remover(r->esq, v);
 	else if (r->info < v)
    	r->dir = remover(r->dir, v);
 	else { 
 		if (r->esq == NULL && r->dir == NULL) {
       		free (r);
      		r = NULL;
    	}else if (r->esq == NULL) {
       		no* aux = r;
       		r = r->dir;
       		free (aux);
    	}else if (r->dir == NULL) {
       		no* aux = r;
       		r = r->esq;
       		free (aux);
    	}else {
       		no* aux = r->esq;
       		while (aux->dir != NULL) {
          		aux = aux->dir;
       		}
       		r->info = aux->info;
      		aux->info = v;
       		r->esq = remover(r->esq,v);
   		}
 	}
	return r;
}
