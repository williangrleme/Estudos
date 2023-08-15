#include <stdio.h>

void quickS(int v[], int ini, int fim)  
{
    if (ini < fim)
    {
       int x;
        x = quick(v, ini, fim);
        quickS(v, ini, x - 1);  
        quickS(v, x + 1, fim); 
    }
}

int quick (int v[], int ini, int fim)  
{  
	int aux;
    int pivo = v[fim]; 
    int i = (ini - 1), j;  
  
    for (j = ini; j <= fim - 1; j++)  
    {  
        if (v[j] < pivo)  
        {  
            i++; 
            aux      = v[i];  
            v[i]     = v[j];
            v[j] = aux;
        }  
    }   
    		aux      = v[i+1];   
            v[i+1]     = v[fim];
            v[fim] = aux;
    return (i + 1);  
} 

//quickS(vet,0,fim); 

int busca_binaria(int vet[],int tamanho,int numero){
    int meio,ini,fim;
    ini = 0;
    fim = tamanho-1;
    meio = (ini+fim)/2;

    while(ini<= fim){
        if(vet[meio] < numero)
        ini =  meio + 1;
        else if (vet[meio] == numero){
            printf("achou na posicao %d\n",meio);
            return 1;   //achou
        }
        else
            fim = meio - 1;
            meio = (ini+fim)/2;
    }
     if(ini > fim)
        printf("\nnao achou\n");
    return 0;
}

int main (){
    int x,i;
    scanf("%d",&x);
    int vet[x];
    for(i=0;i<x;i++){
        scanf("%d",&vet[i]);
    }
    quickS(vet,0,x-1);
    for(i=0;i<x;i++){
        printf("%d  ",vet[i]);
    }
    busca_binaria(vet,x,25);


    return 0;
}
