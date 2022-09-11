#include <iostream>
#include <string>
#include <vector> // 排序資料使用vector實作 
#include <climits> // 紀錄函數執行時間相關函數
#include <ctime> //紀錄函數執行時間相關函數 
#include <fstream> // 輸出檔案相關函數 
#include <stdlib.h> // 亂數相關函數 
#include <time.h>   // 時間相關函數 
using namespace std;

class Sort
{
	public:
		vector<int> A; // Store data 
		int size; //A size
		clock_t Begin, End; //Record sorting time 
		double duration; // Record sorting time 
		string out; // Output Size、sorting time
		void InitialA(); // Initializing A with random value on [1,size)
		void PrintA(); // Use this function to print A
		void CountTime_Insertion_sort(); // This function calls insertion_sort to calculate Insertion_sort time
		void Insertion_sort(); // insertion_sort
		void CountTime_Merge_sort(); // This function calls insertion_sort to calculate Merge_sort time
		void Merge(int p, int q, int r);
		void Merge_sort(int p,int r);
		void Outputstring(); // Output size、 sorting time to out string
		void Fileout(string filename); // Output out string to output file
};

void Sort::PrintA()
{
	for(int i=0; i<size; i++)
	{
		if(i%10==0)
			cout<<endl;
		cout<<A[i]<<" ";	
	}
	cout<<endl<<endl;
}

void Sort::InitialA()
{
	
	srand( time(NULL) );
	//int up = size, low = 1;
	int r;
	for(int i=0; i<size; i++)
	{
		r = (int)((rand() / (RAND_MAX+1.0)) * (size - 1.0) + 1.0);
		A.push_back(r);
	}	
	/*for(int i=0; i<size; i++)
		A.push_back(size-i);	*/ //Insertion worst case
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

void Sort::CountTime_Insertion_sort()
{
	Begin = clock(); //Start counting time
	Insertion_sort();
	End = clock(); //Finish counting time
	//PrintA(); //Use this to test the correctness of the sorting function 
	A.clear();
	duration = (double)(End - Begin) ; // Evaluating ticking times
	cout << "duration = " << duration <<" ms."<< endl;
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

void Sort::Merge_sort(int p,int r)
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
	cout << "duration = " << duration <<" ms."<< endl;
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
	for(I.size = 100; I.size<=100000 ; I.size += 100)
	{
		cout<<"Size = "<<I.size<<endl;
		I.InitialA();
		I.CountTime_Insertion_sort();
		I.Outputstring(); 
	}
	I.Fileout("HW1_out1.txt");
	
	Sort M;
	//for(M.size = 10000; M.size<=500000 ; M.size += 10000) //for HW1_out2_test.txt
	for(M.size = 100; M.size<=100000 ; M.size += 100)
	{
		cout<<"size = "<<M.size<<" ";
		M.InitialA();
		M.CountTime_Merge_sort();
		M.Outputstring();
	}
	M.Fileout("HW1_out2.txt");
	//M.Fileout("HW1_out2_test.txt");
	
	return 0;
}
