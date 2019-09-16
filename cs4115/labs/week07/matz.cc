#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

int main(int argc, char *argv[])
{
	if (argc == 2 || argc > 3)
	{
		std::cerr << "Usage: matz (-e int)" << std::endl;
		exit(1); 
	}
	std::string matLine;
	float limit = ((argc == 3 && std::string(argv[1]).compare("-e") == 0) ? atof(argv[2]) : 0);
	while (std::getline(std::cin, matLine))
	{
		std::istringstream lstream(matLine);
		double val;
		for (int i = 1; lstream >> val; ++i)
			if (fabs(val) > limit)
				std::cout << i << " " << val << " ";
		std::cout << std::endl;
	}
}
