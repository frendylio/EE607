#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP


//////////////////////////////////////////////////////
// A simple representation of graph using STL 
//////////////////////////////////////////////////////
#include<bits/stdc++.h> 
using namespace std; 
  
// A utility function to add an edge in an 
// undirected graph. 
void addEdge(vector<int> adj[], int u, int v);

// A utility function to print the adjacency list 
// representation of graph 
void printGraph(vector<int> adj[], int V);

#endif // LINKEDLIST_HPP