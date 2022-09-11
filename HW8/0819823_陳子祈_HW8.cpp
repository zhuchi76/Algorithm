#include <iostream>
#include <vector>
#include <string>
/* 
#include <climits> // ������ư���ɶ��������
#include <ctime> //������ư���ɶ�������� 
#include <stdlib.h> // �üƬ������ 
#include <time.h>   // �ɶ�������� 
#include <limits.h>

#include <iomanip> // setw
*/

#include<bits/stdc++.h>
# define INF 0x3f3f3f3f
using namespace std;

// �гy�@��(u�Bv)��pair���榡 
typedef pair<int, int> iPair;

struct Graph
{
	int V, E;
	// edges�O�@���x�s�Ҧ�edge��vector �C��edge����(w,(u,v)) 
	vector< pair<int, iPair> > edges;
	
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	list< pair<int, int> > *adj;
	
	// ���]�w���X�ӳ��I���� �~���l�ƨC���I(Disjoint Sets) 
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
		adj = new list<iPair> [V];
	}

	// �W�[edge
	void addEdge(int u, int v, int w)
	{
		edges.push_back({w, {u, v}});
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
	}

	// Kruskal's MST algorithm
	int kruskalMST();
	// Print MST using Prim's algorithm
	int primMST();
	
};

// To represent �C���I(Disjoint Sets) 
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	DisjointSets(int n)
	{
		// ��l�ƨC���I Allocate memory ���C���I 
		this->n = n;
		parent = new int[n+1];
		rnk = new int[n+1];

		// ��l�ƨC���I��rank��0
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;

			//�]���C���I�@�}�l���ODisjoint Set �ҥH�ۤv�O�ۤv��parent 
			parent[i] = i;
		}
	}

	// �M��u�����Yparent 
	int find(int u)
	{
		// �]�� �C���I�@�}�l�ۤv��parent �ҥH�� u != parent[u] ���N�O��o��path�����Y 
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// �䤤�@��rank����C��path�n�X�֨�t�~�@��rank�������path 
	void merge(int x, int y)
	{
		// ���x�By�����Y 
		//cout<<"x="<<x<<"�����Y�O"<<find(x)<<endl; 
		//cout<<"y="<<y<<"�����Y�O"<<find(y)<<endl; 
		x = find(x), y = find(y);
		
		// ��rank ���C��path�n�X�֨�rank�������path
		if (rnk[x] > rnk[y])
		{
			//cout<<"rnk["<<x<<"] = "<<rnk[x]<<" > ";
			//cout<<"rnk["<<y<<"] = "<<rnk[y]<<endl;
			parent[y] = x;
		}
			
		else // If rnk[x] <= rnk[y]
		{
			//cout<<"rnk["<<x<<"] = "<<rnk[x]<<" <= ";
			//cout<<"rnk["<<y<<"] = "<<rnk[y]<<endl;
			parent[x] = y;
		}
			
		// �p�G���rank�@�� �䤤�@��rank+1 
		if (rnk[x] == rnk[y])
		{
			rnk[y]++;
			//cout<<"rnk["<<y<<"] = "<<rnk[y]<<endl;
		}
			
	}
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
	int mst_wt = 0; // Initialize result

	// Sort edges in increasing order on basis of cost
	sort(edges.begin(), edges.end());

	// Create disjoint sets
	DisjointSets ds(V);

	// Iterate through all sorted edges
	vector< pair<int, iPair> >::iterator it;
	for (it=edges.begin(); it!=edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);
		
		// �T�{��쪺u�Bv�����Y�O���O�@�� �p�G�@�˥N��Φ�cycle 
		if (set_u != set_v)
		{
			// �S���Φ�cycle�N��{�b��(u,v)�N�Omin spanning tree���@��(u,v) 
			cout << u << " - " << v << endl;

			// ��smin spanning tree��weight 
			mst_wt += it->first;

			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

// �ϥ�Prim�t��k�L�X�q���I0�X�o��shortest path
int Graph::primMST()
{
	// �гy�@�� �s���I�� priority queue �� Prim min spanning tree 
	// �Ѧ�  http://geeksquiz.com/implement-min-heap-using-stl/
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	int src = 0; // �q���I��0�}�l src=0
	int mst_wst = 0;

	// �гy�@��key vector�ê�l�ƨC�Ӥ�����INF
	vector<int> key(V, INF);

	// �ЫئsMST��parent�}�C To store parent array which in turn store MST
	vector<int> parent(V, -1);

	// �l�ܨC��MST�����I
	vector<bool> inMST(V, false);

	// ��src=0�����I��J�� priority queue �ê�l�� key �� 0 
	pq.push(make_pair(0, src));
	key[src] = 0;

	// ���� priority queue�ŤF����~����j�� 
	while (!pq.empty())
	{
		// ��priority queue����key�j�p�ӱ� �̤pkey��pair�|��b�e�� 
		// priority queue�̭��i��|�s�b ���P��key value��P�@�ӳ��I 
		// �̤p�� key value �@�w�|���B�z 
		// ��pq�Ĥ@��pair�����I extract�X�� (label�|�s��u) 
		int u = pq.top().second;
		//cout<<"�h��pq���Ĥ@��pair�Au = "<< pq.top().second << ", key = " << pq.top().first <<endl;
		if(inMST[u] == false)	mst_wst += pq.top().first;
		pq.pop();
		
		// �p�G���ӳ��I�w�g�bMST�̭� ���N�����o�ӳ��I 
		if(inMST[u] == true)	continue;
	
		inMST[u] = true; // �G���ӳ��I���bMST�̭� �⦹���I�[�i�hMST 

		// 'i' �N��g���o�ӳ��I���Ҧ�adjacent vertices
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent of u.
			int v = (*i).first;
			int weight = (*i).second;

			// �p�Gv���bMST�B(u,v)��weight��{�b��v��key�٤p
			if (inMST[v] == false && key[v] > weight)
			{
				// Updating key of v
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				//cout<<"pq �Q push: v = "<<v<<" w = "<<weight<<endl;
				parent[v] = u;
			}
		}
	}

	// Print edges of MST using parent array
	cout << "Use Prim algorithm:\n\nEdges of MST are (by vertice label order)\n";
	for (int i = 1; i < V; ++i)
		printf("%d - %d\n", parent[i], i);
	
	// �Hkey value�q�p��j��edge����X���� 
	// Print edges of MST using parent array
	typedef pair<int,int> value_index;

   	vector<value_index> vi;
   	int min, min_i;
   	vector<int> k = key;
   	int i;
   	for(int _=0; _<V; _++)
   	{
   		i=0;
   		vector<int>::iterator it;
   		min = INF-1;
		for (it=k.begin(); it < k.end(); ++it, ++i)
		{
			//cout<<"k[i] = "<<*it<<endl;
			if ( (*it) < min )		
   			{
	   			min = *it;
	   			min_i = i;
			}
		}
		//cout<<"min = "<<min<<" min_i = "<<min_i<<endl;
		vi.push_back(make_pair(min,min_i));
		//for (vector<value_index>::iterator vit=vi.begin(); vit < vi.end(); ++vit)
		//	cout<<"value: "<< (*vit).first <<" index: "<< (*vit).second <<endl; //printf("%d\n", *it);
		k[min_i] = INF;
	}
   	
   	vi.erase(vi.begin());
   	cout << "\nEdges of MST are (by key value order)\n";
	for (vector<value_index>::iterator it=vi.begin(); it < vi.end(); ++it)
		printf("%d - %d\n", parent[(*it).second], (*it).second);
	return mst_wst;
}

int main()
{
	// �إ�graph 
	int V = 9, E = 14;
	Graph g(V, E);

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	cout << "Use Kruskal algorithm:\nEdges of MST are \n";
	int mst_wt = g.kruskalMST();
	cout << "Weight of MST is " << mst_wt << "\n\n";
	
	
	mst_wt = g.primMST();
	cout << "\nWeight of MST is " << mst_wt << "\n\n";
	
	return 0;
}

