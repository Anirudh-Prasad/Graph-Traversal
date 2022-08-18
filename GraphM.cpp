// ---------------------------- GraphM.cpp ------------------------------------
// Anirudh Prasad, CSS 343 A
// Created: 2/24/2020
// Last Modified: 2/26/2020
// ----------------------------------------------------------------------------
// Purpose: This is the implementation file for a graph that utilizes
// Djikstra's Algorthm for finding the shortest path to all the nodes in a 
// graph from a source
// ----------------------------------------------------------------------------
// This implementation of graph utilizes a file to intialize the data of the 
// graph, and also finds the shortest path from the source to each node in the
// graph. Outputs all the data as cout statements
// ----------------------------------------------------------------------------

#include "GraphM.h"

//default constructor for GraphM
GraphM::GraphM() 
{
	for (int i = 0; i < MAXNODES; i++) 
	{
		for (int j = 0; j < MAXNODES; j++) 
		{
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
			T[i][j].visited = false;
			C[i][j] = INT_MAX;
		}
	}
}

//builds a graph from an ifStream object
//initializes the T, C, and Data arrays
void GraphM::buildGraph(ifstream& inFile)
{
	inFile >> size;

	string parser = "";
	getline(inFile, parser);
	
	for (int i = 1; i <= size; ++i) 
	{
		data[i].setData(inFile);
	}

	int n1;
	int n2;
	int distance;

	while (inFile >> n1 >> n2 >> distance)
	{
		if (n1 == 0) break;
		C[n1][n2] = distance;
	}
}

//inserts an edge distance if there is an existing edge between two nodes
bool GraphM::insertEdge(int n1, int n2, int distance)
{
	if (T[n1][n2].dist != INT_MAX) 
	{
		T[n1][n2].dist = distance;
		findShortestPath();
		return true;
	}
	return false;
}

//removes an edge if an edge exists between two nodes
bool GraphM::removeEdge(int n1, int n2)
{
	if (T[n1][n2].dist == INT_MAX) 
	{
		return false;
	}

	T[n1][n2].dist = INT_MAX;
	findShortestPath();
	return true;
}

//Djikstra's Algorithm
//Initializes a source value, and traverses the graph to find the shortest
//distance from a source node to every node in the graph
void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++)
	{

		T[source][source].dist = 0;
		T[source][source].visited = true;

		for (int i = 1; i <= size; i++)
		{

			if (C[source][i] != INT_MAX) 
			{
				T[source][i].dist = C[source][i];
				T[source][i].path = source;
			}

		}
		//find v, not visited, shortest dist at this point
		int v = 0;
		recDjikstra(source, v);
	}
}

//Recurisive helper function for findShortestPath()
//Helps loop through the graph to find every possible traversal
//and locate the shortest distance
void GraphM::recDjikstra(int source, int v) {
	for (int i = 0; i < size; i++)
	{
		int minVal = INT_MAX;
		v = 0;

		for (int j = 1; j <= size; j++)
		{

			if ((T[source][j].visited == false) &&
				(C[source][j] < minVal))
			{
				minVal = C[source][j];
				v = j;
			}

		}

		if (v == 0) break;
		//mark v as visited
		T[source][v].visited = true;

		for (int w = 0; w < size; w++) {

			if (!(T[source][w].visited) && (C[v][w] != INT_MAX) &&
				(T[source][v].dist + C[v][w]) < (T[source][w].dist))
			{
				T[source][w].dist = T[source][v].dist + C[v][w];
				T[source][w].path = v;
			}

		}
	}
	if (v != 0) recDjikstra(source, v);
}

//Displays all nodes in the graph, their shortest distance, and their paths
void GraphM::displayAll()
{
	cout << "Description         From node   To node   Dijkstra's     Path      "
		<< endl;

	for (int i = 1; i <= size; i++) 
	{
		cout << data[i] << endl << endl;
		for (int j = 1; j <= size; j++) 
		{
			if (T[i][j].dist != 0) 
			{
				cout << "                         " << i;
				cout << "         " << j;
				if (T[i][j].dist == INT_MAX) 
				{
					cout << "      ----";
				}
				else 
				{
					cout << "        " << T[i][j].dist;
					cout << "            ";
					nodePath(i, j);
					cout << endl;
				}
			}
			cout << endl;
		}
	}

}

//used for the displayAll() method
//outputs the path between two nodes in the graph, in the form of node numbers
void GraphM::nodePath(int n1, int n2)
{
	if (T[n1][n2].dist == INT_MAX) return;

	if (n1 == n2) {
		cout << n1 << " ";
		return;
	}

	int nStore = n2;
	n2 = T[n1][n2].path;
	nodePath(n1, n2);
	cout << nStore << " ";
}

//Displays the data for two nodes in the graph, and their relationship
void GraphM::display(int n1, int n2)
{
	cout << "                         " << n1;
	cout << "         " << n2;
	if (T[n1][n2].dist == INT_MAX)
	{
		cout << "      ----" << endl;
	}
	else 
	{
		cout << "        " << T[n1][n2].dist;

		cout << "            ";
		nodePath(n1, n2);
		cout << endl;
		nodePathNames(n1, n2);
		cout << endl;
	}
}

//used for the display() method
//Used to display the names of nodes in the path from n1 to n2
void GraphM::nodePathNames(int n1, int n2)
{
	if (T[n1][n2].dist == INT_MAX) return;

	if (n1 == n2) {
		cout << data[n1] << endl;
		return;
	}

	int nStore = n2;
	n2 = T[n1][n2].path;
	nodePathNames(n1, n2);
	cout << data[nStore] << endl;
}


