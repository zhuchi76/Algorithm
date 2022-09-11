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

#include<bits/stdc++.h>
# define INF 0x3f3f3f3f
using namespace std;

// 創造一個(u、v)的pair的格式 
typedef pair<int, int> iPair;

struct Graph
{
	int V, E;
	// edges是一個儲存所有edge的vector 每個edge都有(w,(u,v)) 
	vector< pair<int, iPair> > edges;
	
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	list< pair<int, int> > *adj;
	
	// 先設定有幾個頂點跟邊 才能初始化每個點(Disjoint Sets) 
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
		adj = new list<iPair> [V];
	}

	// 增加edge
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

// To represent 每個點(Disjoint Sets) 
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	DisjointSets(int n)
	{
		// 初始化每個點 Allocate memory 給每個點 
		this->n = n;
		parent = new int[n+1];
		rnk = new int[n+1];

		// 初始化每個點的rank為0
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;

			//因為每個點一開始都是Disjoint Set 所以自己是自己的parent 
			parent[i] = i;
		}
	}

	// 尋找u的源頭parent 
	int find(int u)
	{
		// 因為 每個點一開始自己的parent 所以當 u != parent[u] 那就是到這條path的源頭 
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// 其中一個rank比較低的path要合併到另外一個rank比較高的path 
	void merge(int x, int y)
	{
		// 找到x、y的源頭 
		//cout<<"x="<<x<<"的源頭是"<<find(x)<<endl; 
		//cout<<"y="<<y<<"的源頭是"<<find(y)<<endl; 
		x = find(x), y = find(y);
		
		// 讓rank 較低的path要合併到rank比較高的path
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
			
		// 如果兩者rank一樣 其中一個rank+1 
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
		
		// 確認選到的u、v的源頭是不是一樣 如果一樣代表形成cycle 
		if (set_u != set_v)
		{
			// 沒有形成cycle代表現在的(u,v)就是min spanning tree的一個(u,v) 
			cout << u << " - " << v << endl;

			// 更新min spanning tree的weight 
			mst_wt += it->first;

			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

// 使用Prim演算法印出從頂點0出發的shortest path
int Graph::primMST()
{
	// 創造一個 存頂點的 priority queue 為 Prim min spanning tree 
	// 參考  http://geeksquiz.com/implement-min-heap-using-stl/
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	int src = 0; // 從頂點為0開始 src=0
	int mst_wst = 0;

	// 創造一個key vector並初始化每個元素為INF
	vector<int> key(V, INF);

	// 創建存MST的parent陣列 To store parent array which in turn store MST
	vector<int> parent(V, -1);

	// 追蹤每個MST的頂點
	vector<bool> inMST(V, false);

	// 把src=0的頂點輸入到 priority queue 並初始化 key 為 0 
	pq.push(make_pair(0, src));
	key[src] = 0;

	// 直到 priority queue空了之後才停止迴圈 
	while (!pq.empty())
	{
		// 為priority queue按照key大小來排 最小key的pair會放在前面 
		// priority queue裡面可能會存在 不同的key value對同一個頂點 
		// 最小的 key value 一定會先處理 
		// 讓pq第一個pair的頂點 extract出來 (label會存到u) 
		int u = pq.top().second;
		//cout<<"去掉pq的第一個pair，u = "<< pq.top().second << ", key = " << pq.top().first <<endl;
		if(inMST[u] == false)	mst_wst += pq.top().first;
		pq.pop();
		
		// 如果那個頂點已經在MST裡面 那就忽略這個頂點 
		if(inMST[u] == true)	continue;
	
		inMST[u] = true; // 果那個頂點不在MST裡面 把此頂點加進去MST 

		// 'i' 代表經歷這個頂點的所有adjacent vertices
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent of u.
			int v = (*i).first;
			int weight = (*i).second;

			// 如果v不在MST且(u,v)的weight比現在的v的key還小
			if (inMST[v] == false && key[v] > weight)
			{
				// Updating key of v
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				//cout<<"pq 被 push: v = "<<v<<" w = "<<weight<<endl;
				parent[v] = u;
			}
		}
	}

	// Print edges of MST using parent array
	cout << "Use Prim algorithm:\n\nEdges of MST are (by vertice label order)\n";
	for (int i = 1; i < V; ++i)
		printf("%d - %d\n", parent[i], i);
	
	// 以key value從小到大排edge的輸出順序 
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
	// 建立graph 
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

