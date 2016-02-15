#ifndef FLOYD_CPP
#define FLOYD_CPP

#include <vector>
#include <limits>

#include "Matrix.h"

extern bool DEBUG; // from Main.cpp

/*
	@return: the vector's first element is the d matrix
		and the second elemnt is the p matrix
*/
void executeFloydAlgorithm(const Graph* G)
{
	std::cout << "Executing floyd algorithm..." << std::endl;

	const int numberOfVertices = G -> size();
	const int numberOfEdges = G -> edges.size();

	Matrix d = Matrix(numberOfVertices), p = Matrix(numberOfVertices);

	//
	// initialize the d and the p matrix
	//

	for (int i = 0; i < numberOfVertices; ++i) 
	{
		for (int j = 0; j < numberOfVertices; ++j) 
		{
			if (i != j) d(i, j) = std::numeric_limits<int>::max(); // set "infinity"
			// else: 0 is fine for d where i==j
			// p all elements is 0, which is fine here
		}
	}
	
	for (std::set<Edge>::iterator it = G -> edges.begin(); it != G -> edges.end(); ++it)
	{
		const Edge e = *it;
		d(e.start - 1, e.end - 1) = e.cost;
		p(e.start - 1, e.end - 1) = e.start;
	}
	
	if (DEBUG)
	{
		std::cout << std::endl << "d matrix after init:" << std::endl;
		d.print();
		std::cout << std::endl << "p matrix after init:" << std::endl;
		p.print();
	}

	stopIfNecesseary();

	//
	// revise where we can
	//

	for (int k = 0; k < numberOfVertices; ++k)
	{
		for (int i = 0; i < numberOfVertices; ++i)
		{
			for (int j = 0; j < numberOfVertices; ++j)
			{
				const long long sum = d(i,k) + (long long) d(k,j);
				if (sum >= d(i,j)) continue;

				d(i,j) = sum;
				p(i,j) = p(k,j);


			}
		}
		if (!DEBUG) continue;

		std::cout << std::endl << "d matrix for k = " << k << std::endl;
		d.print();
		std::cout << std::endl << "p matrix for k = " << k << std::endl;
		p.print();

		stopIfNecesseary();
	}
}

#endif // FLOYD_CPP