#include <iostream>
#include <string>
#include <vector> // 排序資料使用vector實作 
#include <climits> // 紀錄函數執行時間相關函數
#include <ctime> //紀錄函數執行時間相關函數 
#include <fstream> // 輸出檔案相關函數 
#include <stdlib.h> // 亂數相關函數 
#include <time.h>   // 時間相關函數 
#include <limits.h>
#include <math.h> // 計算lg(n) 
using namespace std;

class Sort
{
	public:
		vector<int> A; // Store data 
		int size; //A size
		clock_t Begin, End; //Record sorting time 
		double duration; // Record sorting time 
		string out; // Output Size、sorting time
		void InitialA(); // Initializing A with random value on all integer
		void PrintA(); // Use this function to print A
		//For Insertion sort
		void CountTime_Insertion_sort(); // This function calls insertion_sort to calculate Insertion_sort time
		void Insertion_sort(); // insertion_sort
		//For Merge sort
		void CountTime_Merge_sort(); // This function calls Merge_sort to calculate Merge_sort time
		void Merge(int p, int q, int r);
		void Merge_sort(int p,int r);
		//For Heap sort
		void CountTime_Heap_sort(); // This function calls Heap_sort to calculate Heap_sort time
		int heap_size;
		void exchange(int i, int j); // Exchange A[i] and A[j]
		void Max_Heapify(int i); // Max Heapify A[i]、A[i(left)]、A[i(right)] 
		void Build_Max_Heap(); // Build Max Heap A
		void Heap_sort();
		//Build Output file
		void Outputstring(); // Output size、 sorting time to out string
		void Fileout(string filename); // Output out string to output file
};

void Sort::PrintA() // Use this function to print A
{
	for(int i=1; i<size; i++)
	{
		if(i%10==0)
			cout<<endl;
		cout<<A[i]<<" ";	
	}
	cout<<endl<<endl;
}

void Sort::InitialA() // Initializing A with random value on integer
{
	srand( time(NULL) );
	//int up = size, low = 1;
	int r;
	for(int i=0; i<size; i++)
	{
		r = (int)((rand() / (RAND_MAX+1.0)) * (size - 1.0) + 1.0);
		if(rand() / (RAND_MAX+1.0) > 0.5)
			r = -r;
		A.push_back(r);
	}	
	//PrintA();
}

void Sort::Insertion_sort()
{
	int key;
	for(int j=1; j<size; j++)
	{
		key = A[j]; // Insert A[j] into the sorted sequence A[0,1,..j-1]
		int i = j-1;
		while( i>=0 && A[i]>key )
		{
			A[i+1] = A[i];
			i = i-1;
		}
		A[i+1] = key;
	}	
} 

void Sort::CountTime_Insertion_sort() // This function calls insertion_sort to calculate Insertion_sort time
{
	Begin = clock(); //Start counting time
	Insertion_sort();
	End = clock(); //Finish counting time
	//PrintA(); //Use this to test the correctness of the sorting function 
	A.clear();
	duration = (double)(End - Begin) ; // Evaluating ticking times
	cout << "Runtime = " << duration <<"\t ms.";	
	double d = (size/1000)*(size/1000);
	cout<<"\t1000000 * Runtime/(size^2) = "<< duration/d ;
	cout<<endl;
}

void Sort::Merge(int p, int q, int r)
{
	int n1 = q-p+1;
	int n2 = r-q;
	int L[n1+2],R[n2+2];
	
	for(int i=1; i<=n1; i++)
		L[i] = A[p+i-1];
		
	for(int j=1; j<=n2; j++)
		R[j] = A[q+j];
		
	L[n1+1] = INT_MAX;
	R[n2+1] = INT_MAX;
	int i = 1, j = 1;
	
	for(int k=p; k<=r; k++)
		if(L[i]<=R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
}

void Sort::Merge_sort(int p,int r) // This function calls Merge_sort to calculate Merge_sort time
{
	if(p<r)
	{
		int q = (p+r)/2;
		//cout<<"p = "<<p<<" q = "<<q<<" r = "<<r<<endl;
		Merge_sort(p,q);
		Merge_sort(q+1,r);
		Merge(p,q,r);
	}
}

void Sort::CountTime_Merge_sort() 
{
	Begin = clock();//開始計時
	Merge_sort(0,size-1);
	End = clock(); //結束計時
	//PrintA(); //Use this to test the correctness of the sorting function 
	A.clear();
	duration = (double)(End - Begin) ; // Evaluating ticking times
	cout << "Runtime = " << duration <<"\t ms.";
	double d = size * log2(size);
	cout<<"\t100000*Runtime/(size*lg(size)) = "<< 100000*duration/d ;
	cout<<endl;
}

void Sort::exchange(int i, int j) // Exchange A[i] and A[j]
{
	int t = A[i];
	A[i] = A[j];
	A[j] = t;
}

void Sort::Max_Heapify(int i) // Max Heapify A[i]、A[i(left)]、A[i(right)] 
{
	int l = i*2; // l=left(i)
	int r = i*2+1; // r = right(i)
	int largest;
	if( (l <= heap_size) && (A[l]>A[i]) )
		largest = l;
	else largest = i;
	if( (r <= heap_size) && (A[r]>A[largest]) )
		largest = r;
	if(largest != i)
	{
		exchange(i, largest);
		Max_Heapify(largest);
	}
}
void Sort::Build_Max_Heap() // Build Max Heap A
{
	heap_size = size;
	for(int i = size/2; i>=1; i--)
		Max_Heapify(i);
}
void Sort::Heap_sort()
{
	Build_Max_Heap();
	for(int i=size; i>=2; i--)
	{
		exchange(1,i);
		heap_size --;
		Max_Heapify(1);
	}
}

void Sort::CountTime_Heap_sort() // This function calls Heap_sort to calculate Heap_sort time
{
	Begin = clock();//開始計時
	Heap_sort();
	End = clock(); //結束計時
	//PrintA(); //Use this to test the correctness of the sorting function 
	A.clear();
	duration = (double)(End - Begin) ; // Evaluating ticking times
	cout << "Runtime = " << duration <<"\t ms.";
	double d = size * log2(size);
	cout<<"\t 100000*Runtime/(size*lg(size)) = "<< 100000*duration/d ;
	cout<<endl;
}

void Sort::Outputstring()
{
	out += to_string(size).c_str();
	out += ' ';
	out += to_string((int)duration).c_str();
	out += '\n';		
}

void Sort::Fileout(string filename)
{
	ofstream FILEOUT; 
	FILEOUT.open(filename,ios::out);
	
	if(!FILEOUT.is_open())
		cout<<"failed to write";
	else
		FILEOUT << out;
			
	FILEOUT.close();
}

int main()
{
	Sort I;	
	cout<<"For insertion sort\n";
	//for(I.size = 10000; I.size<=100000 ; I.size += 10000)
	for(I.size = 100; I.size<=100000 ; I.size *= 10)
	{
		cout<<"Size = "<<I.size<<"\t";
		I.InitialA();
		I.CountTime_Insertion_sort();
		I.Outputstring(); 
	}
	I.Fileout("HW3_out1.txt");
	
	Sort M;
	cout<<"For Merge sort\n";
	//for(M.size = 10000; M.size<=100000 ; M.size += 10000)
	for(M.size = 100; M.size<=100000 ; M.size *= 10)
	{
		cout<<"Size = "<<M.size<<"\t";
		M.InitialA();
		M.CountTime_Merge_sort();
		M.Outputstring();
	}
	M.Fileout("HW3_out2.txt");
	
	Sort H;
	cout<<"For Heap sort\n";
	//for(H.size = 10000; H.size<=100000 ; H.size += 10000)
	for(H.size = 100; H.size<=100000 ; H.size *= 10)
	{
		cout<<"Size = "<<H.size<<"\t";
		H.InitialA();
		H.CountTime_Heap_sort();
		H.Outputstring();
	}
	H.Fileout("HW3_out3.txt");
	
	return 0;
}
