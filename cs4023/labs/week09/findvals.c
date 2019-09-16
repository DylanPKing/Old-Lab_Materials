#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

#include "utils.h"

int main(int argc, char* argv[])
{
	/* Checking cmd args */
	int rCheck = 0, tCheck = 0, vCheck = 0;
	
	float num, range;
	for(int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-r") == 0) && !rCheck)
		{
			num = strtof(argv[i + 1], NULL);
			rCheck = 1;
		}
		else if ((strcmp(argv[i], "-t") == 0) && !tCheck)
		{
			range = strtof(argv[i + 1], NULL);
			tCheck = 1;
		}
		else if ((strcmp(argv[i], "-v") == 0) && !vCheck)
			vCheck = 1;
	}

	if (!rCheck || !tCheck)
	{
		printf("Usage: findvals -r float -t float < inputFile\n");
		exit(1);
	}
  
	/* Getting rows amd columns of matrix */
	int rows, columns;
	scanf("%d" "%d", &rows, &columns);
	
	/* Allocating space on array */
	float** matrix = (float**)malloc(rows * sizeof(float *));
	if (rows == 0)
	{
		fprintf(stderr, "Couldn’t allocate sufficient space.\n");
		exit(1);
	}
	for (int i = 0; i < rows; i++)
	{
		float* row = (float *) malloc(columns * sizeof(float));
		if (row == 0)
		{
			fprintf(stderr, "Couldn’t allocate sufficient row space.\n");
			exit(1);
		}
		matrix[i] = row;
	}
	
	/* Reading matrix into array */
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			scanf("%f", &matrix[i][j]);
			
	struct tm *local;
	time_t start;

	time(&start);
	local = localtime(&start);
	fprintf(stdout, "# Start time and date: %s", asctime(local));
	
	struct timeval timeStore;
	gettimeofday(&timeStore, NULL);
	double timeOne = timeStore.tv_sec + (timeStore.tv_usec / 1000000.0);		
			
	/* The actual checking */
	int i = 0, j = 0;
	int counter = 0;
	#pragma omp parallel for schedule(dynamic) reduction(+:counter) private(i, j)
	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++)
			if (approxEqual(matrix[i][j], num, range))
			{
				if (vCheck)
				{
					printf("r=%d, c=%d: %.6f (thread= %d)\n", i, j,
							matrix[i][j], omp_get_thread_num());
				}
				counter++;
			}
	printf("Found %d approximate matches.\n", counter);
	
	gettimeofday(&timeStore, NULL);
	double timeTwo = timeStore.tv_sec + (timeStore.tv_usec / 1000000.0);

	printf("Search time: %.6f(s)\n", timeTwo - timeOne);
	exit(0);
}
