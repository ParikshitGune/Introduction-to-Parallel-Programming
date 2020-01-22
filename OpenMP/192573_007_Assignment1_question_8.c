#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#define N 10000
int flag = 0;

void producer(int val,double *a)
{
	if(flag==0)
	{
		for(int i=0;i<val;i++)
		{
			a[i]=rand()%val;
		}
		flag=1;
#pragma omp flush (flag)
	}

	
}

double consumer(int val, double *a)
{
   	double s=0;
	if(flag==1)
	{
		for(int i=0;i<val;i++)
		{
			s=s+a[i];
		}

	}
	return s;
}

int main()
{
	clock_t start ,end ,flag;
	double *a,sum,runtime;
	a = (double*)malloc(N* sizeof (double));
	start = clock();
#pragma omp parallel num_threads(8)
	{
#pragma omp parallel sections
		{
#pragma omp section 
			{ 
			producer(N,a);
#pragma omp flush
			flag= 1;
#pragma omp flush (flag)
			}
#pragma omp section
			{
#pragma omp flush (flag)
			while (flag==0)
				{
#pragma omp flush (flag)
				}
#pragma omp flush
			sum= consumer(N,a);
			}
		}
	}
	end = clock();
	double t = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("The sum is %f \n execution time is %f\n",sum,t);

}

