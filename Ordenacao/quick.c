#include<stdio.h>
#include<stdlib.h>

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



int main ()
{
	int x, i, j, aux,c;

	printf("Digite o tamanho do vetor:\n");
	scanf("%d", &x);
  int v[x];
	printf("Digite os elementos do vetor:\n");  

	for (i = 0; i < x; i++)
  {
    scanf("%d",&c);
    v[i] = c;
  }
  
  printf("Desordenado:\n");
  	for (i = 0; i < x; i++)
  {
   printf("%d ", v[i]); 
  }
  
  
  int in=0, fi=x-1;
  quickS(v, in, fi);
 
printf("\nOrdenado:\n");   
	for (i = 0; i < x; i++)
  {
   printf("%d ", v[i]);
  }
}
