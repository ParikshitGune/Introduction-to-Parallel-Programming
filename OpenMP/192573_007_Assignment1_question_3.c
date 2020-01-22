#include "stdio.h"
#include<stdlib.h>
#include "time.h"
#include "omp.h"
# define d 10000
# define n 2

void main()
{
	double time=0.0;
	int a[d];
	int b[d];
	int c =5;

	for(int i = 0; i<d ;i++){
	a[i] = rand() % 1000;

	}

	for(int i = 0; i<d ;i++){
	b[i] = rand() % 1000;
	}
	clock_t start=clock();
	for (int i=0;i<d;i=i+n)
		{
			a[i]=c*a[i]+b[i];

		}
	
	clock_t end=clock();

	clock_t begin=clock();
 	#pragma omp parallel
	{
		omp_set_num_threads(n);
		int id = omp_get_thread_num();
		for (int i=id;i<d;i=i+n)
		{
			a[i]=c*a[i]+b[i];

		}
	}
	clock_t end2=clock();

	double t1 = ((double)(end-start))/CLOCKS_PER_SEC;
	double t2 = ((double)(end2-begin))/CLOCKS_PER_SEC;
	for (int j =0;j<d;j++)
	printf("%d\t", a[j]);
	printf("%f", t1/t2);

}
