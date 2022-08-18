// ---------------------------- GraphM.h --------------------------------------
// Anirudh Prasad, CSS 343 A
// Created: 2/24/2020
// Last Modified: 2/26/2020
// ----------------------------------------------------------------------------
// Purpose: This is the header file for a graph that utilizes depth first 
// search
// ----------------------------------------------------------------------------
// This header file describes the functions of this graph, which specializes
// in performing Dijkstra's Algorigthm, a method that allows one to find the
// shortest path to every item in a graph from a certain point.
// ----------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits.h>

//Sets maximum number of nodes in graph's various data structures
const int MAXNODES = 101;

using namespace std;

class GraphM
{
public:
	//default constructor
	GraphM();
	//initializes the graph's key values using an ifstream object
	void buildGraph(ifstream& inFile);
	//inserts an edge in the graph if applicable
	bool insertEdge(int n1, int n2, int distance);
	//removes an edge from the graph if applicable
	bool removeEdge(int n1, int n2);
	//find the shortest path from a source node to the rest of the nodes
	void findShortestPath(); //Dijkstra's Algorithm
	//displays every node, path, and distance in graph
	void displayAll();
	//displays the path, distance, and data for two nodes
	void display(int n1, int n2);

private:

	//holds the main data for the graph
	struct TableType {

		bool visited;          // whether node has been visited

		int dist;              // shortest distance from source known so far

		int path;              // previous node in path of min dist

	};

	NodeData data[MAXNODES];              // data for graph nodes

	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix

	int size;                           // number of nodes in the graph

	TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

	//outputs the path from one node to another, by node number
	void nodePath(int n1, int n2);
	//outputs the path from one node to another, by node name
	void nodePathNames(int n1, int n2);
	//recursive helper function for Djikstra's Algorithm method
	void recDjikstra(int source, int v);
};

#endif



