Sistemas_Operacionais.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VAL 10
#define quantum 1

typedef struct no {
	int tempo;
	int prioridade;
	int id;
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

int inserir(fila *f, int id,int prioridade, int tempo)
{
	no *novo = (no *) malloc(sizeof(no));
	novo->id = id;
	novo->prioridade = prioridade;
	novo->tempo = tempo;
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
	if (f->ini == NULL){
		exit(1);
	}
	
	aux = f->ini;
	f->ini = aux->prox;
	if (f->ini == NULL)
		f->fim = NULL;
	free(aux);
	return 1;
}

void imprimir(fila *f){
    no *aux = f->ini;
    while(aux != NULL){
        printf ("Processo: %d prioridade: %d tempo: %d\n",aux->id,aux->prioridade,aux->tempo);
        aux = aux->prox;
    }
}

void robin_round (fila *f){
	no *aux;
	int i;
	int vet[VAL];
	for(i=0;i<VAL;i++){vet[i]=0;}

	while (f->ini != NULL){
		aux = f->ini;
		if(aux->tempo - quantum <= 0){
			vet[aux->id] = vet[aux->id]+1;
			remover(f);
		}
		else {
			vet[aux->id] =vet[aux->id]+1;
			aux->tempo = aux->tempo - quantum;
			inserir(f,aux->id,aux->prioridade,aux->tempo);
			remover(f);
		}
	}
	printf("\n");
	for(i=0;i<VAL;i++){
		printf("O processo %d demorou %d quantuns\n",i,vet[i]);
	}
}

void FIFO (fila *f){
	no *aux;
	int vet[VAL];
	int i;
	for(i=0;i<VAL;i++){vet[i]=0;}

	while(f->ini != NULL){
		aux = f->ini;
		vet[aux->id] = aux->tempo/quantum;
		remover(f);
	}
	for(i=0;i<VAL;i++){
		printf("O processo %d demorou %d quantuns\n",i,vet[i]);
	}
}

void remover_prioridade (fila *f){
	no *aux,*aux2,*aux3,*maior;
	
	aux = f->ini;
	maior = f->ini;
	aux2 = aux;
	aux3 = aux2;

	while(aux != NULL){
		if(aux->prioridade > maior->prioridade){
			aux3 = aux2;
			maior = aux;
		}
		aux2 = aux;
		aux = aux->prox;
	}
	if (maior == f->ini){
		remover(f);
		}
		else {
			aux3->prox = maior->prox;
			free(maior);
		}
}

void remover_SJF (fila *f){
	no *aux,*aux2,*aux3,*maior;
	
	aux = f->ini;
	maior = f->ini;
	aux2 = aux;
	aux3 = aux2;

	while(aux != NULL){
		if(aux->tempo > maior->tempo){
			aux3 = aux2;
			maior = aux;
		}
		aux2 = aux;
		aux = aux->prox;
	}
	if (maior == f->ini){
		remover(f);
		}
		else {
			aux3->prox = maior->prox;
			free(maior);
		}
}

void prioridade (fila *f){
	no *aux, *maior;
	int vet[VAL];
	int i;
	for(i=0;i<VAL;i++){vet[i]=0;}

	while (f->ini != NULL){
		aux = f->ini;
		maior = f->ini;
		while(aux!= NULL){
			if(aux->prioridade > maior->prioridade){
				maior = aux;
				aux = aux->prox;
			}
			else {
				aux = aux->prox;
			}
		}
		vet[maior->id] = maior->tempo/quantum;
		remover_prioridade(f);
	}	
		for(i=0;i<VAL;i++){
		printf("O processo %d demorou %d quantuns\n",i,vet[i]);
	}
}

void SJF (fila *f){
	no *aux, *maior;
	int vet[VAL];
	int i;
	for(i=0;i<VAL;i++){vet[i]=0;}

	while (f->ini != NULL){
		aux = f->ini;
		maior = f->ini;
		while(aux!= NULL){
			if(aux->tempo > maior->tempo){
				maior = aux;
				aux = aux->prox;
			}
			else {
				aux = aux->prox;
			}
		}
		vet[maior->id] = maior->tempo/quantum;
		remover_SJF(f);
	}	
		for(i=0;i<VAL;i++){
		printf("O processo %d demorou %d quantuns\n",i,vet[i]);
	}
}

int main (){
    fila f;
    criar(&f);
    int i,r1,r2;

    for(i=0; i <VAL; i++){      //preenchendo
        r1 = 1+rand()%100;
        r2 = 1+rand()%100;
        inserir(&f,i,r1,r2);
    }
	int c;
	imprimir(&f);
	printf ("\n1- Robin Round\n2- FIFO\n3-Prioridade\n4-SJF\n");
	scanf("%d",&c);

	switch(c){
		case 1:
		robin_round(&f);
		break;

		case 2:
		FIFO(&f);
		break;

		case 3:
		prioridade(&f);
		break;

		case 4:
		SJF(&f);
		break;

		default:
		break;
	}
return 1;
}

