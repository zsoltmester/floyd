#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Graph.h"

std::set<Vertex> getVerticesFromFile(std::ifstream* fs);
std::set<Edge> getEdgesFromFile(std::ifstream* fs);

Graph* Graph::constructFromFile(const char* fileName) 
{
	std::cout << "Construct the graph from the file..." << std::endl;

    std::ifstream fs;
    fs.open(fileName);

    if (fs.fail()) 
    {
    	std::cout << "Failed to open file: " << fileName << "!" << std::endl;
    	fs.close();
    	return NULL;
    }

    std::set<Vertex> vertices;
	std::set<Edge> edges;

    std::string row;
    std::stringstream converter;

    while(!fs.eof())
    {
	    std::getline(fs, row);
	    if (row.length() == 0 || row[0] != '#') continue; // skip row

    	const std::size_t startTag = row.find(TAG_START);
    	const std::size_t verticesTag = row.find(TAG_VERTICES);
    	const std::size_t edgesTag = row.find(TAG_EDGES);
		if (startTag == std::string::npos 
			|| (verticesTag == std::string::npos 
				&& edgesTag == std::string::npos)
			|| (verticesTag != std::string::npos
				&& edgesTag != std::string::npos)) 
		{
	    	std::cout << "File format is wrong!" << std::endl;
	    	if (DEBUG) std::cout << "at line: " << row << std::endl;
	        fs.close();
	        return NULL;
		}

		if (verticesTag != std::string::npos)
		{
			vertices = getVerticesFromFile(&fs);
		}
		else if (edgesTag != std::string::npos)
		{
			edges = getEdgesFromFile(&fs);
		}
    }





    if (vertices.size() > 0 && edges.size() > 0) {
    	return new Graph(vertices, edges);
    } else {
    	return NULL;
    }
}

std::set<Vertex> getVerticesFromFile(std::ifstream* fs)
{
	if (DEBUG) std::cout << "Reading vertices..." << std::endl;

	std::set<Vertex> vertices;

    std::string row;
    std::stringstream converter;

    while(!fs -> eof())
    {
	    converter.clear(); // reset converter

    	Vertex v;

	    std::getline(*fs, row);
	    if (row[0] == '#' 
	    	&& row.find(TAG_END) != std::string::npos) 
	    	break; // reach #END

	    converter.str(row);
	    converter >> v;

        if (converter.fail()) 
        {
	    	std::cout << "Fail to read vertex: " << row << std::endl;
        	continue; // skip wrong row
        } 

        vertices.insert(v);
    }

    return vertices;
}

std::set<Edge> getEdgesFromFile(std::ifstream* fs)
{
	if (DEBUG) std::cout << "Reading edges..." << std::endl;

	std::set<Edge> edges;

    std::string row;
  	char ch;
    std::stringstream converter;

    while(!fs -> eof())
    {
	    converter.clear(); // reset converter

    	int start, end, cost;

	    std::getline(*fs, row);
	    if (row[0] == '#' 
	    	&& row.find(TAG_END) != std::string::npos) 
	    	break; // reach #END

	    converter.str(row);
	    converter >> start >> end >> cost;

        if (converter.fail()) 
        {
	    	std::cout << "Fail to read edge: " << row << std::endl;
        	continue; // skip wrong row
        } 

        Edge e;
        e.start = start;
        e.end = end;
        e.cost = cost;
        edges.insert(e);
    }

    return edges;
}

Graph::Graph(const std::set<Vertex> vertices, const std::set<Edge> edges) 
	: vertices(vertices), edges(edges)
{
	if (!DEBUG) return;

	std::cout << "Vertices: " << std::endl;
	for (Vertex v : vertices)
	{
		std::cout << v << std:: endl;
	}

	std::cout << "Edges: " << std::endl;
	for (Edge e : edges)
	{
		std::cout << e.start << " "  << e.end << " "  << e.cost << " " << std:: endl;
	}
}

const bool Graph::isValid() const 
{
	for (Edge e : edges)
	{
		if (vertices.find(e.start) == vertices.end()
			|| vertices.find(e.end) == vertices.end()) 
		{
			if (DEBUG) std::cout << "\'" << e.start << "\'" <<  "or" << "\'" << e.end << "\'" <<
						" is not a declared vertex." << std::endl;
			return false;
		}
	}

	return true;
}

const int Graph::size() const 
{
	return vertices.size();
}