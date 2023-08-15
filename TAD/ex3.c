#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cont = 0;

typedef struct no {
	char nome[20];
    int idade;
	int sentinela;
	struct no *prox;
	struct no *prox_prio;
}no;

typedef	struct {
	no *ini;
	no *fim;
	no *prioridade;
}fila;

void criar(fila *f)
{
	f->ini = NULL;
	f->fim = NULL;
	f->prioridade=NULL;	 // fila dentro da fila
}

int vazia_fila(fila *f)
{
	if(f->ini == NULL)
	return 1;
	else return 0;
}

int vazia_prio(fila *f){
	if(f->prioridade == NULL) return 1;
	else return 0;	
}

void inserir(fila *f, char *nome, int idade){
	no *novo;
	novo = malloc(sizeof(no));

	strcpy(novo->nome,nome);
	novo->idade=idade;
	novo->prox=NULL;
	novo->prox_prio=NULL;

	if(novo->idade >= 60){   // caso seja velho
		if(vazia_fila(f)){
			f->ini=novo;
			f->fim=novo;
			f->prioridade=novo;
			novo->sentinela = 1;
		}
		else {
			if (vazia_prio(f)){
				f->prioridade=novo;
				f->fim->prox=novo;
				f->fim=novo;
				novo->sentinela = 1;
			}
			else {
				no *aux;
				aux=f->prioridade;
				while(aux->prox_prio != NULL){
					aux=aux->prox_prio;
				}
				aux->prox_prio=novo;
				f->fim->prox=novo;
				f->fim=novo;
				novo->sentinela = 1;
			}
		}
	}
	else {
		if(vazia_fila(f)){
			f->ini=novo;
			f->fim=novo;
			novo->sentinela = 0;
		}
		else {
			f->fim->prox=novo;
			f->fim=novo;
			novo->sentinela = 0;
		}
	}
}

void remover_prio(fila *f){
	no *aux1, *aux2, *aux3, *aux4;

	if(vazia_prio(f)){
		printf ("Fila vazia\n");
	}
	else {
		aux1=f->prioridade;
		if (aux1 == f->ini){   // INICIO 
			f->ini=f->ini->prox;
			f->prioridade=f->prioridade->prox_prio;
			free(aux1);
		}
		else if (aux1 == f->fim){   // FIM
			aux2 = f->ini;
			aux3=aux2;
			while(aux2->prox != NULL){ // achar penultimo
				aux3=aux2;
				aux2=aux2->prox;
			}
			aux3->prox=NULL;
			f->fim=aux3;
			f->prioridade=NULL;
			free(aux1);
		}
		else{  
		aux2=f->ini;
		while(aux2 != aux1){ // achar anterior do prioridade
			aux3=aux2;
			aux2=aux2->prox;
		}
		aux4=aux1->prox;
		aux3->prox=aux4;
		f->prioridade=f->prioridade->prox_prio;
		free(aux1);
		}
	}
}

void remover_normal (fila *f){
	no *aux1, *aux2, *aux3;
	no *aux4;
	if(vazia_fila(f)){
		printf ("Fila vazia\n");
	}
	else {
		aux1 = f->ini;
		while (aux1->sentinela == 1){
			aux4=aux1;
			aux1=aux1->prox;
		}		
		if (aux1 == f->ini){ 
			f->ini=f->ini->prox;
			free(aux1);
		}
		else if (aux1 == f->fim){
			aux2 = f->ini;
			aux3=aux2;
			while(aux2->prox != NULL){ 
				aux3=aux2;
				aux2=aux2->prox;
			}
			aux3->prox=NULL;
			f->fim=aux3;
			free(aux1);
		}
		else {
			aux2=aux4;
			aux3=aux1->prox;
			aux2->prox=aux3;
			free(aux1);	
		}
		}
	}



void imprimir_normal(fila *f)
{
	printf ("FILA NORMAL:\n");
	no *aux;
	if (vazia_fila(f)){
		printf("Fila vazia\n");
	} else {
		aux = f->ini;
		while(aux!=NULL){
		printf("NOME:[%s] ",aux->nome);
        printf ("IDADE:[%d]\n", aux->idade);
		aux = aux->prox;
	}
		printf("\n");
	}
}

void imprimir_prio (fila *f){
	printf ("FILA PREFRENCIAL:\n");
	no *aux;
	if (vazia_prio(f)){
		printf ("\nFila vazia\n");
	}
	else {
		aux=f->prioridade;
		while (aux != NULL){
		printf("NOME:[%s] ",aux->nome);
        printf ("IDADE:[%d]\n",aux->idade);
		aux = aux->prox_prio;
		}
		printf ("\n");
	}
}

int main () {

fila *f1;
	criar(&f1);
	
	int op,i;
    char n[20];
	cont=0;
	
	
	do {
		printf ("1-Inserir na fila \n2-Atender \n3-Ver fila\n0-Sair\n");
		scanf ("%d", &op);
		fflush(stdin);
		switch (op){
			case 1:
				printf ("Nome:\n");
				gets(n);
                fflush(stdin);
				printf("Idade:\n");
				scanf("%d",&i);
				inserir(&f1,n,i);
				break;
			case 2:
               if (cont < 3){
				  if(vazia_prio(&f1)){
					  if (vazia_fila(&f1)){
						  printf ("Fila vazia\n");
					  }
					  else {
					printf ("Fila normal atendida\n");
					remover_normal(&f1);
					cont=0;
					  }

				  }
				  else {
					  printf ("Fila preferencial atendida\n");
					  remover_prio(&f1);
					  cont=cont+1;
				  }
			   }
			   else {
				   if (vazia_fila(&f1)){
					   printf ("Lista vazia\n");
					   cont=0;
				   }
				   else {
					   printf ("Fila normal atendida\n");
					   remover_normal(&f1);
					   cont=0;
				   }
			   }
				break;
			case 3:
				imprimir_normal(&f1);
				imprimir_prio(&f1);
				break;
		}
	}
	while (op!=0);
}
