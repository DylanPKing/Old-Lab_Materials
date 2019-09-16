#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

int main(int argc, char* argv[])
{
	/* Checking cmd args */
	int rCheck = 0, tCheck = 0;
				 
	float num, range;
	for(int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-r") == 0 && !strcmp(argv[i + 1], "-t") == 0)
		{
			num = strtof(argv[i + 1], NULL);
			rCheck = 1;
		}
		else if (strcmp(argv[i], "-t") == 0 && !strcmp(argv[i], "-r") == 0)
		{
			range = strtof(argv[i + 1], NULL);
			tCheck = 1;
		}
	}
	
	if (!rCheck || !tCheck)
	{
		fprintf(stderr, "Usage: %s -r ref -t tol\n", argv[0]);
		exit(1);
	}
	
	struct tm *local;
	time_t start, end;

	time(&start);
	local = localtime(&start);
	fprintf(stdout, "# Start time and date: %s", asctime(local));
  
	/* Getting rows amd columns of matrix */
	int rows, columns;
	fscanf(stdin, "%d" "%d", &rows, &columns);
	
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
			fscanf(stdin, "%f", &matrix[i][j]);
			
	/* The actual checking */
	int counter = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (approxEqual(matrix[i][j], num, range) == 1)
			{
				fprintf(stdout, "r=%d, c=%d: %.6f\n", i, j, matrix[i][j]);
				counter++;
			}
	
	fprintf(stdout, "Found %d approximate matches.\n", counter);
	
	time(&end);
	local = localtime(&end);
	fprintf(stdout, "# End time and date: %s", asctime(local));
	
	exit(0);
}
