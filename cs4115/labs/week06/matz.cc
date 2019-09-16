#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: matz int int" << std::endl;
		exit(1); 
	}
	
	std::cout << argv[1] << std::endl;
	int rows = atoi(argv[1]), cols = atoi(argv[2]);
	double **matrix = new double *[rows];
	for (int i = 0; i < rows; ++i)
		matrix[i] = new double [cols];
	
	int nonZeroTotal = 0;
	for (int i = 0; i < rows; ++i)
	{
		int nonZero = 0, j = 0;
		for (; j < cols; ++j)
		{
			std::cin >> matrix[i][j];
			if (matrix[i][j] != 0)
				nonZero++;
		}
		std::cout << nonZero << " ";
		for (j = 0; j < cols; ++j)
			if (matrix[i][j] != 0)
				std::cout << j + 1 << " " << matrix[i][j] << " ";
				
		std::cout << std::endl;
		nonZeroTotal += nonZero;
	}
	std::cout << nonZeroTotal << std::endl;
}
