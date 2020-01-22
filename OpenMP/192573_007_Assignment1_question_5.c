#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#define n 2
static long num_steps = 100000;
double step;
    
void main()
{
	omp_set_num_threads (n);
	clock_t start,end;
	int i;
	double aux ,x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;
	start = clock();
#pragma omp parallel private(aux)
   	{
#pragma omp for
      		for (i=0; i<num_steps; i=i+1)
		{

		         x=(i+0.5)*step;
		         aux=4.0/(1.0+x*x);
#pragma omp atomic
         		 sum = sum + aux;
      		}

   	}
	pi=step*sum;
	end= clock();
	double t = ((double)(end-start))/CLOCKS_PER_SEC;

	printf("%f\n", t);
   	printf("%f",pi);
	
}

