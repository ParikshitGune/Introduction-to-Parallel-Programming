#include "stdio.h"
#include "omp.h"

void printHello(int threadID)
{
	printf("Hello(%d)",threadID);
	printf("World(%d) \n",threadID);
}

void main()
{
#pragma omp parallel
	{
	int id = omp_get_thread_num();
	printHello(id);
	}

}
/* Output:
parikshit@parikshit-Lenovo-ideapad-330-15IKB:~/Documents/M-Tech Sem 1/HPC/HPC LAB/fwdhpc$ gcc -o hello helloworld2.c -fopenmp
parikshit@parikshit-Lenovo-ideapad-330-15IKB:~/Documents/M-Tech Sem 1/HPC/HPC LAB/fwdhpc$ ./hello
Hello(0)World(0) 
Hello(7)World(7) 
Hello(1)World(1) 
Hello(4)World(4) 
Hello(5)World(5) 
Hello(2)World(2) 
Hello(3)World(3) 
Hello(6)World(6) 
*/
