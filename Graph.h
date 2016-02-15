#ifndef GRAPH_H
#define GRAPH_H

#include <set>

// tags for file format
#define TAG_START "START"
#define TAG_END "END"
#define TAG_VERTICES "vertices"
#define TAG_EDGES "edges"

extern bool DEBUG; // from Main.cpp

// define a vertex as a int
typedef int Vertex;

// define the edge data structure
struct Edge
{
	Vertex start, end;
	int cost;
};

// necessary for set
inline bool operator<(const Edge& lhs, const Edge& rhs)
{
  return lhs.start < rhs.start || lhs.end < rhs.end;
}


class Graph
{
private:
	Graph(const std::set<Vertex>,const std::set<Edge>); // private constructor

public:
	const std::set<Vertex> vertices;
	const std::set<Edge> edges;

	// constructs a Graph based on the given file
	static Graph* constructFromFile(const char* fileName);

	// check if the graph is valid
	const bool isValid() const;

	// returns the size of the graph
	const int size() const;
};

#endif // GRAPH_H