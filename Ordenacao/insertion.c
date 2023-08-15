#include<stdio.h>
#include <stdlib.h>


int insert(int x , int v[x]){
    int i, j, aux;
  for(i = 1; i < x; i++)
 {
  aux = v[i];
  for(j = i-1; j >= 0 && aux < v[j]; j--)
  {
   v[j+1] = v[j];
  }
  v[j+1] = aux;
 }
}
int main ()
{
int x, i,c;	
  printf("insira o tamanho do vetor:\n");
	scanf("%d", &x);
	int v[x];
    printf("insira valores no vetor\n");
	for (i = 0; i < x; i++)
  {
      scanf("%d",&c);
      v[i] = c;
  }
    printf ("desordenado:\n");
  	for (i = 0; i < x; i++)
  {
   printf("%d ", v[i]); 
  }

printf("\n");   
insert(x, v);
printf("ordenado:\n");   

	for (i = 0; i < x; i++) 
  {
   printf("%d ", v[i]);
  }
  
}
