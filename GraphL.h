// ---------------------------- GraphL.h --------------------------------------
// Anirudh Prasad, CSS 343 A
// Created: 2/24/2020
// Last Modified: 2/26/2020
// ----------------------------------------------------------------------------
// Purpose: This is the header file for a graph that utilizes depth first 
// search
// ----------------------------------------------------------------------------
// This header file describes the functions of this graph, which specializes
// in performing a depth-first search. A depth-first search allows one to
// explore each part of the graph before backtracking and eventually covering
// the whole tree.
// ----------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits.h>

//Sets maximum number of nodes in graphArr
const int L_MAXNODES = 101;

using namespace std;

class GraphL
{

public:
	//default contructor
	GraphL();
	//destructor 
	~GraphL();
	//initializes the graph's key values using an ifstream object
	void buildGraph(ifstream& inFile);
	//displays the nodes and edges of the graph
	void displayGraph();
	//traverses the tree and outputs values in depth-first order
	void depthFirstSearch();


private:
	struct EdgeNode;      // forward reference for the compiler

	struct GraphNode {    // structs used for simplicity, use classes if desired

		EdgeNode* edgeHead; // head of the list of edges

		NodeData* data;     // data information about each node

		bool visited;

	};

	//used for the edges of the graph
	struct EdgeNode {

		int adjGraphNode;  // subscript of the adjacent graph node

		EdgeNode* nextEdge; //link to next edge in graph

	};
	
	//array of GraphNodes that is used to hold graph's data
	GraphNode graphArr[L_MAXNODES];
	//holds amount of specific, initialized data in the graph array
	int size;

	//recursize function that assists the main DFS function
	void depthFirstHelper(int node);
};
#endif

