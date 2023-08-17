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
	pthread_t threads;
	int status, i;
	
	pthread_create(&threads, NULL, print, (void *)&i);

	
	for(i=0;i<NUMBER;i++)
	{
		pthread_join(threads, NULL);
	}
	pthread_exit(NULL);
	return 0;
}


