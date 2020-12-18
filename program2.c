#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define SEED 35791246
 
void main()
{
	int n = 0, i, count = 0, t = 2;
	double z, pi, x, y;


	printf("Enter the number of iterations used to estimate pi: ");
	scanf("%d", &n);
	printf("Enter the number of threads: ");
	scanf("%d", &t);
	srand(SEED); //the seed provides starting point for pseudo random number generation by rand()
	double t1 = omp_get_wtime();
	omp_set_num_threads(t);
	#pragma omp parallel for private(x,y,z) reduction( +: count) //count is synchronized
	
	for ( i=0; i<n; i++) //runs n = Ntotal times
	{
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		z = x*x+y*y;
		if (z<=1) count++; //assuming radius = 1 and side of square = 2, count = Ninner
	}
	double t2 = omp_get_wtime();
	printf("%lf\n", t2-t1);
	pi=(double)count/n*4; // pi/4 = Ninner/Nouter
	
	printf("# of trials= %d , estimate of pi is %g, # of threads= %d \n",n,pi, t);
}
