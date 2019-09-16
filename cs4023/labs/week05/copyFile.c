#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char* argv[])
{
	int flipping = (strcmp(argv[1], "-f") == 0);

	char c;
	FILE *from;

	
	if (flipping)
		from = fopen(argv[2], "r");
	else
		from = fopen(argv[1], "r");

	if (from == NULL)
	{
		perror(argv[1]);
		exit(1);
	}

	FILE *to;

	if (flipping)
		to = fopen(argv[3], "w");
	else
		to = fopen(argv[2], "w");
		
	if (to == NULL)
	{
		perror(argv[2]);
		exit(1);
	}

	/* file exists, so start reading */
	while ((c = getc(from)) != EOF)
	{
		if (flipping)
			putc(flipChar(c), to);
		else
			putc(c, to);
	}
	fclose(from);
	fclose(to);
	
	exit(0);
}
