#include <iostream>
//#include <vector> // 排序資料使用vector實作 
#include <string> 
#include <stdlib.h> // 亂數相關函數 
#include <time.h>   // 時間相關函數 
#include <limits.h>
//#include <math.h> // 計算lg(n) 
#include <iomanip>
#include <windows.h>
#define COUNT 10
using namespace std;

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
} 

struct Node
{
	int key;
	bool Target;
	Node *left = NULL;
	Node *right = NULL;
	Node *p = NULL;
	Node(int k)
	{
		this->key = k;
		this->Target = false;
		this->left = NULL;
		this->right = NULL;
		this->p = NULL;
	}
	Node()
	{
		this->Target = false;
		this->left = NULL;
		this->right = NULL;
		this->p = NULL;
	}
		
};

class BST
{
	public:
		int A[50]; // Store initial data 
		Node *root;
		
		BST(){root = new Node;};
		int Random_unrepeated_num(int size);
		void InitialA(); // Initializing A with random value on all integer
		void print2Dtree(const string& prefix, Node* node, bool isLeft); // print 2D binary tree: l:left; r:right
		void print2Dalltree(Node* node);
		//void print2Dtree(Node *root, int space); // Not a good way to print 2D tree
		
		void Tree_insert(Node *z); // Insert node z in tree
		void Build_tree(); // Use function Tree_insert with initial A data to build tree
		
		void Inorder_tree_walk(Node *x); // Print out all the keys in the subtrees of a node x
		Node* Tree_minimum(Node *x); // Return node with minimum key
		Node* Tree_maximum(Node *x); // Return node with maximum key
		
		Node* Tree_search(Node *x, int k); // Search a pointer to node with key k if one exists in the subtree of x
		void Transplant(Node *u, Node *v); // Replace the subtree rooted at node u with the subtree rooted at node v
		void Tree_delete(Node *z); // Delete a node z from BST 
};

void BST::print2Dtree(const string& prefix, Node* node, bool isRight) // print 2D binary tree: l:left; r:right
{
    if( node != NULL )
    {
        cout << prefix;

		if(node == root) cout<< "    ";
		else cout << ( isRight ? ( (node->p->left != NULL)? "├──  r: " : "└──  r: "): "└──  l: " );
		
        // print the value of the node
        if(node->Target) SetColor(240);
        cout << setw(3) << node->key ;
        SetColor();
        cout<<endl;

        // enter the next tree level - left and right branch
        string r = (node->p->left != NULL)? "│   " : "    ", l = "    ";
        print2Dtree( prefix + (isRight ? r : l), node->right, true);
        print2Dtree( prefix + (isRight ? r : l), node->left, false);
        
        
    }
}

void BST::print2Dalltree(Node* node)
{
    print2Dtree("", node, false);    
}

/*
void BST::print2Dtree(Node *node, int space)
{
    // Base case
    if (node == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 	
    // Process right child first
    print2Dtree(node->right, space);
 
    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<setw(3)<<node->key<<"\n";
 
    // Process left child
    print2Dtree(node->left, space);
}
*/

int BST::Random_unrepeated_num(int size)
{
	srand( time(NULL) );
	//int up = 1000, low = 1;
	//r = (int)((rand() / (RAND_MAX+1.0)) * (RAND_MAX - 1.0) + 1.0);
	//r = (int)((rand() / (up + 1.0)) * (up - 1.0) + low);
	int r = rand()%1000;
	bool same = false;
	for(int i=0;i<size;i++)
		if(A[i]==r)
			same = true;
	while(same)
	{
		same = false;
		for(int i=0;i<size;i++)
			if(A[i]==r)
				same = true;
		if(same) r = rand()%1000; //r = (int)((rand() / (up + 1.0)) * (up - 1.0) + low);	
	}
	
	same = false;
	for(int i=0;i<size;i++)
		if(A[i]==r)
			same = true;
	if(same) cout<<"Wrong!!!!!!!!\n";
	return r;
}

void BST::InitialA() // Initializing A with random value on integer
{
	srand( time(NULL) );
	//int up = 1000, low = 1;
	int r;
	for(int i=0; i<50; i++)
	{
		r = Random_unrepeated_num(i);
		A[i] = r;
	}	
	//Print_tree();
}

void BST::Tree_insert(Node *z) // Insert node z in tree
{
	Node *y = new Node;
	Node *x = root;
	while(x!=NULL)
	{
		y = x;
		if(z->key < x->key)
			x = x->left;
		else x = x->right;
	}
	z->p = y;
	if(y->p == NULL) root = z;
	else if(z->key < y->key) y->left = z;
	else y->right = z;
}

void BST::Build_tree() // Use function Tree_insert with initial A data to build tree
{
	Node *x;
	cout<<"Build tree!!!\n";
	for(int i=0;i<50;i++)
	{
		x = new Node(A[i]);
		Tree_insert(x);
	}
}

void BST::Inorder_tree_walk(Node *x) // Print out all the keys in the subtrees of a node x
{
	if(x!=NULL)
	{
		Inorder_tree_walk(x->left);
		cout<<x->key<<"\t";
		Inorder_tree_walk(x->right);
	}
}

Node* BST::Tree_minimum(Node *x) // Return node with minimum key
{
	while(x->left != NULL)
		x = x->left;
	return x;
}

Node* BST::Tree_maximum(Node *x) // Return node with maximum key
{
	while(x->right != NULL)
		x = x->right;
	return x;
}

Node* BST::Tree_search(Node *x, int k) // Search a pointer to node with key k if one exists in the subtree of x
{
	if(x==NULL || k==x->key)
	{
		x->Target = true;
		return x;
	}
	if(k < x->key) return Tree_search(x->left, k);
	else return Tree_search(x->right, k);
}

void BST::Transplant(Node *u, Node *v) // Replace the subtree rooted at node u with the subtree rooted at node v
{
	if(u->p == NULL) root = v;
	else if(u == u->p->left) u->p->left = v;
	else u->p->right = v;
	
	if(v != NULL) v->p = u->p;
}

void BST::Tree_delete(Node *z) // Delete a node z from BST 
{
	if(z->left == NULL) Transplant(z, z->right);
	else if(z->right == NULL) Transplant(z, z->left);
	else
	{
		Node *y = Tree_minimum(z->right);
		if(y->p != z)
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transplant(z, y);
		y->left = z->left;
		y->left->p = y;
	}
}

int main()
{
	BST t;
	t.InitialA();
	t.Build_tree();
	
	cout<<"Print tree:\n";
	t.print2Dalltree(t.root);
	//print2Dtree(t.root, 0);
	cout<<"root key = "<<t.root->key<<endl;
	cout<<"\n\n\n";
	
	t.Inorder_tree_walk(t.root);
	
	cout<<"\n\n\n";
	Node *min_node = t.Tree_minimum(t.root);
	cout<<"Min = "<<min_node->key<<endl;
	/*
	cout<<"Print tree:\n";
	t.print2Dalltree(t.root);
	cout<<"\n\n\n";
	
	cout<<"\n\n\n";
	*/
	Node *max_node = t.Tree_maximum(t.root);
	cout<<"\n\nMax = "<<max_node->key<<endl;
	/*
	cout<<"Print tree:\n";
	t.print2Dalltree(t.root);
	cout<<"\n\n\n";
	*/
	
	cout<<"\n\n\n";
	Node *x = t.Tree_search(t.root, t.A[rand()%50]);
	cout<<"Delete node with key = "<<x->key<<endl;
	cout<<"Before deleting the node, print tree:\n";
	t.print2Dalltree(t.root);
	t.Tree_delete(x);
	cout<<"After deleting the node, print tree:\n";
	t.print2Dalltree(t.root);
	cout<<"\n\n\n";
	
	int r = t.Random_unrepeated_num(50);
	x = new Node(r);
	x->Target = true;
	cout<<"Insert new node with key = "<<x->key<<endl;
	t.Tree_insert(x);
	cout<<"After inserting the new node, print tree:\n";
	t.print2Dalltree(t.root);
	cout<<"\n\n\n";
	
	return 0;
}
