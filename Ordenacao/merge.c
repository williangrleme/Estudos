#include<stdio.h>
#include<stdlib.h>

void mergeS(int v[], int ini, int fim)
{
	int m;
	if (ini < fim){
		int m = ini+(fim-ini)/2; 
		mergeS(v,ini,m);
		mergeS(v,m+1,fim);
		merge(v,ini,m,fim);
	}
}

void merge(int v[], int ini,int m, int fim){
	int i, j, k; 
    int n1 = m - ini + 1; 
    int n2 = fim - m; 
	
	int x[n1], y[n2]; 
  
   
    for (i = 0; i < n1; i++) 
        x[i] = v[ini + i]; 
    for (j = 0; j < n2; j++) 
        y[j] = v[m + 1+ j]; 
        
    i = 0;  
    j = 0; 
    k = ini; 
    while (i < n1 && j < n2) 
    { 
        if (x[i] <= y[j]) 
        { 
            v[k] = x[i]; 
            i++; 
        } 
        else
        { 
            v[k] = y[j]; 
            j++; 
        } 
        k++; 
    } 
    
    
     while (i < n1) 
    { 
        v[k] = x[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        v[k] = y[j]; 
        j++; 
        k++; 
    } 
  
}

int main ()
{
	int x, i, j, c;
	printf("insira o tamanho do vetor:\n");
	scanf("%d", &x);
	int v[x];
    printf("insira valores no vetor\n");

	for (i = 0; i < x; i++)
  {
    scanf("%d", &c);
    v[i] = c;
  }

    printf ("desordenado:\n");
  	for (i = 0; i < x; i++)
  {
   printf("%d ", v[i]); 
  }

    int in=0, fi=x-1;
    mergeS(v, in, fi);
    printf("\nordenado:\n");  
	for (i = 0; i < x; i++)
  {
   printf("%d ", v[i]);
  }
}


