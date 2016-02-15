//g++ -o Floyd Graph.cpp Main.cpp -std=c++11
//Floyd -f=example.graph -d

#include <iostream>
#include <string.h>

bool DEBUG = false;

namespace
{
	void stopIfNecesseary() 
	{
		if (!DEBUG) return;

		std::cout << std::endl << "Press enter to continue..." << std::endl;
		std::cin.get();	
	}
}

#include "Graph.h"
#include "Floyd.cpp"


int main(int argc, char* argv[])
{
	std::string fileName;

	for (short i = 0; i < argc; ++i)
	{
		std::string arg = argv[i];

		if (arg == "-d") DEBUG = true;

		if (arg.length() <= 3 
			|| arg[0] != '-' 
			|| arg[2] != '=') 
			continue; 

		switch(arg[1])
		{
		case 'f':
			fileName = arg;
			fileName = fileName.substr(3, fileName.length() - 3);
			break;
		}
	}

	delete argv;

	if (fileName == "") 
	{
		std::cout << "Missing file name! Syntax: -f=filename" << std:: endl;
		return 1;
	}

	std::cout << "Debug mode: " << DEBUG << std::endl;
	if (DEBUG) std::cout << "File name: " << fileName << std::endl;

	const Graph* G = Graph::constructFromFile(fileName.c_str());
	if (G == NULL || !G -> isValid()) 
	{
		std::cout << "Failed to contruct the graph." << std::endl;
		return 2;
	}

	std::cout << "The graph successfully constructed." << std::endl;

	stopIfNecesseary();

	executeFloydAlgorithm(G);

	delete G;
}
