#include <iostream>
#include <sstream>
#include <vector>

class nonZero
{
public:
	int column;
	double value;
	nonZero(int column, double value) : column(column), value(value) {}
};

int main(int argc, char *argv[])
{
	if (argc == 2 || argc > 3)
	{
		std::cerr << "Usage: matz (-e int)" << std::endl;
		exit(1); 
	}
	std::vector< std::vector<nonZero> > members;
	std::string matLine;
	int cols = 0;
	float limit = ((argc == 3 && std::string(argv[1]).compare("-e") == 0) ? atof(argv[2]) : 0);
	while (std::getline(std::cin, matLine))
	{
		std::vector<nonZero> mRow;
		std::istringstream lstream(matLine);
		int col = 0;
		double val = 0.0;
		while (lstream >> col >> val)
		{
			nonZero n(col, val);
			mRow.push_back(n);
			cols = (cols < col) ? col : cols;
		}
		members.push_back(mRow);
	}
	
	std::vector< std::vector<nonZero> > tMem;
	for (int i = 0; i < cols; ++i)
	{
		std::vector<nonZero> row;
		tMem.push_back(row);
	}
	
	for (int i = 0; i < members.size(); ++i)
	{
		std::vector<nonZero> tempRow = members[i];
		for (int j = 0; j < tempRow.size(); ++j)
		{
			std::vector<nonZero> tempTRow = tMem[tempRow[j].column - 1];
			nonZero n(i + 1, tempRow[j].value);
			tempTRow.push_back(n);
			tMem[tempRow[j].column - 1] = tempTRow;
		}
	}
	
	for (int i = 0; i < tMem.size(); ++i)
	{
		for (int j = 0; j < tMem[i].size(); ++j)
			std::cout << tMem[i][j].column << " " << tMem[i][j].value << " ";
		if (i != tMem.size() - 1)
			std::cout << std::endl;
	}
}
