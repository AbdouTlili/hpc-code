#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[])
{


	struct timeval startTime, stopTime;

	int m;
	int n;
	double tol; // = 0.0001;

	long totalTime;

	int i, j, iter;

	m = atoi(argv[1]);
	n = atoi(argv[2]);
	tol = atof(argv[3]);

	double t[m + 2][n + 2], tnew[m + 1][n + 1], diff, difmax,tmp_difmax;

	int z;
	// ANCHOR  the start of the parallel region 
	#pragma omp parallel private(tmp_difmax,i,j,diff)
	for (z = 0; z < 11; z++) //10 iterations
	{
		//printf("%d %d %lf\n",m,n, tol);
		#pragma omp master
		gettimeofday(&startTime, NULL);
		// initialise temperature array

		#pragma omp for collapse(2) schedule(static) nowait
		for (i = 0; i <= m + 1; i++)
		{
			for (j = 0; j <= n + 1; j++)
			{
				t[i][j] = 30.0;
			}
		}

		// fix boundary conditions
		#pragma omp sections 
		{
			#pragma omp section
			{
				for (i = 1; i <= m; i++)
				{
					t[i][0] = 10.0;
					t[i][n + 1] = 140.0;
				}
			}

			#pragma omp section
			{
				for (j = 1; j <= n; j++)
				{
					t[0][j] = 20.0;
					t[m + 1][j] = 100.0;
				}
			}
		}


		// main loop
		#pragma omp single nowait
		{
			iter = 0;
		}
		tmp_difmax = 1000000.0;



		while (difmax > tol)
		{
			#pragma omp single nowait 
			iter++;

			#pragma omp for collapse(2) schedule(static)
			// update temperature for next iteration
			for (i = 1; i <= m; i++)
			{
				for (j = 1; j <= n; j++)
				{
					tnew[i][j] = (t[i - 1][j] + t[i + 1][j] + t[i][j - 1] + t[i][j + 1]) / 4.0;
				}
			}

			// work out maximum difference between old and new temperatures
			difmax = 0.0;
			#pragma omp for collapse(2) schedule(static) 	
			for (i = 1; i <= m; i++)
			{
				for (j = 1; j <= n; j++)
				{
					diff = fabs(tnew[i][j] - t[i][j]);
					if (diff > tmp_difmax)
					{
						tmp_difmax = diff;
					}
					// copy new to old temperatures
					t[i][j] = tnew[i][j];
				}
			}

			#pragma omp critical
			{
				if (tmp_difmax > difmax)
					{
						difmax = tmp_difmax;
					}
			}
			#pragma omp barrier
		}
		gettimeofday(&stopTime, NULL);
		totalTime = (stopTime.tv_sec * 1000000 + stopTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec);

		printf("toatal time : %ld\n", totalTime);
	}
	return 0;

	/*
	// print results
	printf("iter = %d  difmax = %9.11lf", iter, difmax);
	for (i=0; i <= m+1; i++) {
		printf("\n");
		for (j=0; j <= n+1; j++) {
			printf("%3.5lf ", t[i][j]);
		}
	}
	printf("\n");
	*/
}
