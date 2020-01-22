#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#define n 10

int a[n][n];
int b[n][n];
int c[n][n];
clock_t start;
clock_t end;
double t;

int main() 
{
	int i,j,k;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
            		a[i][j] = 2;
            		b[i][j] = 2;
		}

	}

	start=clock();	
	#pragma omp parallel for private(i,j,k) shared(a,b,c)
        for (i=0;i<n;++i) 
	{
        	for (j=0;j<n;++j) 
		{
            		for (k=0;k<n;++k) 
			{
                		c[i][j]+=a[i][k]* b[k][j];
            		}
        	}
    	}

	end= clock();
	t =((double)(end-start))/CLOCKS_PER_SEC;

 	for (i=0;i<n;i++)
    	{
		for (j=0;j<n;j++)
	        {
	        	printf("%d\t",c[i][j]);
        	}
        	printf("\n");
    	}

	printf("Time for the script = %f seconds.\n",t);
}

