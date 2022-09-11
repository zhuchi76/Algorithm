#include <iostream>
#include <vector>
#include <string>
/* 
#include <climits> // 紀錄函數執行時間相關函數
#include <ctime> //紀錄函數執行時間相關函數 
#include <stdlib.h> // 亂數相關函數 
#include <time.h>   // 時間相關函數 
#include <limits.h>

#include <iomanip> // setw
*/

#include <list>

using namespace std;

// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
#include<bits/stdc++.h>
using namespace std;


char int_to_char(int i)
{
	return 'A'+i;
}

int char_to_int(char c)
{
	return int(c) - int('A');
}
// This class represents a directed graph using
// adjacency list representation
class Graph
{
	int V; // No. of vertices
	vector<bool> visited; 	// Mark all the vertices as not visited
	vector<char> visited_order;	// visited_order
	
	// Pointer to an array containing adjacency
	// lists
	vector<list<int>> adj;
	
	public:
		Graph(int V); // Constructor
	
		// function to add an edge to graph
		void addEdge(int v, int w);
	
		// prints BFS traversal and minimum distance from a given source s
		void BFS(int s);
		
		// prints DFS traversal from a given source s
		void DFS_Visit(int s);

		void Print_visited_order();
		void Reset();
};

Graph::Graph(int V)
{
	this->V = V;
	adj.resize(V);
	// Mark the current node as visited and enqueue it
	visited.resize(V,false);
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::Print_visited_order()
{
	for (auto v: visited_order)
		cout <<"'" << v <<"',";
}

void Graph::Reset()
{
	for (auto v: visited)
		v = false;
	visited_order.clear();
}

void Graph::BFS(int s)
{
	// d[i] => The min distance s->i 
	vector<int> d;
	d.resize(V, INT_MAX); // Initialize distance = INT_MAX
	d[s] = 0; // s->s : 0 distance
	
	// path[i] => from which vertice that minimum s->i distance
	vector<int> path;
	path.resize(V, -1);

	// Create a queue for BFS
	list<int> queue;

	
	visited[s] = true;
	queue.push_back(s);

	while(!queue.empty())
	{
		// Dequeue a vertex from queue and print it
		s = queue.front();
		//cout << "'" << int_to_char(s) << "', ";
		visited_order.push_back(int_to_char(s));
		queue.pop_front();

		// Get all adjacent vertices of the dequeued
		// vertex s. If a adjacent has not been visited,
		// then mark it visited and enqueue it
		for (auto adjecent: adj[s])
		{
			if (!visited[adjecent])
			{
				d[adjecent] = d[s] + 1;
				path[adjecent] = s;
				visited[adjecent] = true;
				queue.push_back(adjecent);
			}
		}
	}
	
	cout<<"visit order : [";
	for(auto v: visited_order)
		cout << "'" << v << "',";
	cout<<"\b"<<"]"<<endl;
	
	cout<<"minimum distance : [";
	for (auto v: visited_order)
		cout << d[char_to_int(v)] <<",";
	cout<<"\b"<<"]"<<endl;
	
	/*
	cout<<"path : [";
	for (auto p: path)
		cout << int_to_char(p) <<", ";
	cout<<"]"<<endl;
	*/
}

void Graph::DFS_Visit(int s)
{
    // Mark the current node as visited and
    // print it
    visited[s] = true;
    /*
    for (auto v: visited)
    	cout<<"Visited: "<<v<<endl;
    cout << "This turn: " << s << " \n";
    */
    visited_order.push_back(int_to_char(s));
    
    // Recur for all the vertices adjacent
    // to this vertex
    for (auto adjecent: adj[s])
		if (!visited[adjecent])
            DFS_Visit(adjecent);    
}
// Driver program to test methods of graph class
int main()
{
	// Create a graph given in the above diagram
	
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(0,3);
	g.addEdge(0,4);
	
	g.addEdge(1,0);
	g.addEdge(1,2);
	
	g.addEdge(2,1);
	g.addEdge(2,4);
	
	g.addEdge(3,0);
	g.addEdge(3,4);
	
	g.addEdge(4,0);
	g.addEdge(4,3);
	g.addEdge(4,5);
	g.addEdge(4,2);
	
	g.addEdge(5,4);

	g.BFS(0);
	g.Reset();
	
	g.DFS_Visit(0);
	cout<<"\nvisit order : [";
	g.Print_visited_order();
	cout<<"\b]"<<endl;
	g.Reset();
	
	return 0;
}

