#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
# define NUMBER 4

void *print(void * tid)
{
int *pvalor = (int *) tid;
int i;
for(i=0;i<NUMBER;i++)
{
printf("Thread %i executando...\n", *pvalor);
printf("%i\n",i);
sleep(2);
}
printf("Thread %i finalizado...\n", *pvalor);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUMBER];
	int status, i, args[NUMBER];
	
	for(i=0;i<NUMBER;i++)
	{
	args[i] =i +1;
	pthread_create(&threads[i], NULL, print, (void *)&args[i]);
	}
	
	for(i=0;i<NUMBER;i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_exit(NULL);
	return 0;
}


