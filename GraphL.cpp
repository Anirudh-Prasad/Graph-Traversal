// ---------------------------- GraphL.cpp ------------------------------------
// Anirudh Prasad, CSS 343 A
// Created: 2/24/2020
// Last Modified: 2/26/2020
// ----------------------------------------------------------------------------
// Purpose: This is the implementation file for a graph that utilizes
// depth first search
// ----------------------------------------------------------------------------
// This implementation of graph utilizes a file to intialize the data of the 
// graph, and also utilizes a depth first search to list all the contents of
// the graph structure. Outputs all the data as cout statements
// ----------------------------------------------------------------------------

#include "GraphL.h"

//default constructor for GraphL
GraphL::GraphL()
{
	size = 0;
	for (int i = 0; i < L_MAXNODES; i++)
	{
		graphArr[i].edgeHead = NULL;
		graphArr[i].visited = NULL;
	}
}

//constructor for GraphL
//deletes everything in the graph, like the edges and data
GraphL::~GraphL()
{
	for (int i = 1; i <= size; i++) 
	{
		graphArr[i].visited = false;
		delete graphArr[i].data;
		graphArr[i].data = NULL;
		if (graphArr[i].edgeHead != NULL) 
		{
			EdgeNode* deleteHead = graphArr[i].edgeHead;
			while (deleteHead != NULL) 
			{
				graphArr[i].edgeHead = graphArr[i].edgeHead->nextEdge;
				delete deleteHead;
				deleteHead = NULL;
				deleteHead = graphArr[i].edgeHead;
			}
		}
	}
}

//builds a graph from an ifStream object
//initializes the edge nodes and graph nodes/data
void GraphL::buildGraph(ifstream& inFile)
{
	inFile >> size;

	string parser = "";
	getline(inFile, parser);

	for (int i = 1; i <= size; i++)
	{
		NodeData* tempData = new NodeData();
		tempData->setData(inFile);
		graphArr[i].data = tempData;
	}

	int n1;
	int n2;

	while (inFile >> n1 >> n2)
	{
		if (n1 == 0) break;
		if (graphArr[n1].edgeHead == NULL) 
		{
			EdgeNode* head = new EdgeNode();
			graphArr[n1].edgeHead = head;
			head->adjGraphNode = n2;

			graphArr[n1].edgeHead->nextEdge = NULL;
		}
		else 
		{
			EdgeNode* head = new EdgeNode();
			head->nextEdge = graphArr[n1].edgeHead;
			graphArr[n1].edgeHead = head;
			head->adjGraphNode = n2;
		}
	}
}

//displays the graph's data, such as the nodes and the edges per node
void GraphL::displayGraph()
{
	cout << "Graph: " << endl;
	for (int i = 1; i <= size; i++) 
	{
		cout << "Node" << i;
		cout << "         " << *graphArr[i].data << endl << endl;
		
		EdgeNode* current = graphArr[i].edgeHead;
		while (current != NULL) 
		{
			cout << "  edge  " << i << " " << current->adjGraphNode << endl;
			current = current->nextEdge;
		}
	}
}

//Depth First Search main function that calls the helper function for each
//node in the graph
void GraphL::depthFirstSearch()
{
	cout << "Depth - first ordering :  ";
	for (int i = 1; i <= size; i++) 
	{
		if (graphArr[i].visited == false)
		{
			depthFirstHelper(i);
		}
	}
	cout << endl << endl;
	
}

//Recursive helper function for Depth First Search. Outputs the nodes in the
//graph in depth-first order, calls itself to go through the whole graph
void GraphL::depthFirstHelper(int node) 
{
	EdgeNode* current = graphArr[node].edgeHead;
	graphArr[node].visited = true;
	cout << "   " << node;
	
	while (current != NULL) 
	{
		if (graphArr[current->adjGraphNode].visited == false) 
		{
			depthFirstHelper(current->adjGraphNode);
		}
		current = current->nextEdge;
	}
}
