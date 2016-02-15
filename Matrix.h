 #ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

// represents a row in the matrix
typedef std::vector<int> row;

class Matrix 
{
private:
	// size of the matrix (NxN)
	unsigned int size;

	// matrix data structure
	std::vector<row> M;

public:
	// the only constructor
	Matrix(unsigned int n) : M(n, row(n, 0)), size(n) {}

	int& operator()(unsigned int i, unsigned int j) 
	{
		return M[i][j];
	}

	unsigned int getSize() const 
	{
		return size;
	}

	// prints the matrix
	void print() const
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < size; ++j)
			{
				std::cout << M[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

#endif // MATRIX_H
