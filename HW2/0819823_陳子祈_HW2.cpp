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

class Findmaxarr
{
	public:
		vector<int> A; // Store data 
		int size; //A size
		clock_t Begin, End; //Record sorting time 
		double duration=0; // Record sorting time 
		string out; // Output Size、sorting time
		void InitialA(); // Initializing A with random value on [1,size)
		void PrintA(); // Use this function to print A
		void CountTime_Brute_force(); // This function calls insertion_sort to calculate Insertion_sort time
		int Brute_force(); // Brute-force algorithm
		void CountTime_Divide_and_Conquer(); // This function calls insertion_sort to calculate Divide and Conquer time
		int max(int a,int b); // return larger
		int max(int a,int b,int c); // return larger
		int Find_maxsubarrsum(int l,int r); // Divide and Conquer
		int Find_maxcrossarrsum(int l,int m,int r);
		void Outputstring(); // Output size、 sorting time to out string
		void Fileout(string filename); // Output out string to output file
};

void Findmaxarr::InitialA()
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

void Findmaxarr::PrintA()
{
	for(int i=0; i<size; i++)
	{
		if(i%10==0)
			cout<<endl;
		cout<<A[i]<<" ";	
	}
	cout<<endl;
}

int Findmaxarr::Brute_force()
{
	int max = 0, temp = 0;
	for(int i=0;i<size;i++)
	{
		for(int j=i;j<size;j++)
		{
			temp = 0;
			for(int k=i;k<=j;k++)
			{
				temp += A[k];
			}
			if(temp>max)
				max = temp;
		}
	}
	return max;
} 

int Findmaxarr::max(int a,int b)
{
	return (a>b)? a:b;
}
int Findmaxarr::max(int a,int b,int c)
{
	return max(max(a,b),c);
}
		

int Findmaxarr::Find_maxcrossarrsum(int l,int m,int r)
{
	int leftsum = INT_MIN;
	int sum = 0;
	for(int i=m; i>=l; i--)
	{
		sum += A[i];
		if(sum > leftsum)
			leftsum = sum;
	}
	
	int rightsum = INT_MIN;
	sum = 0;
	for(int i=m+1; i<=r; i++)
	{
		sum += A[i];
		if(sum > rightsum)
			rightsum = sum;
	}
	
	return max( leftsum, rightsum, leftsum + rightsum );
}

int Findmaxarr::Find_maxsubarrsum(int l,int r)
{
	if(l>=r)
		return A[l];
		
	int m = (l+r)/2;
	return max(Find_maxsubarrsum(l,m),Find_maxcrossarrsum(l,m,r),Find_maxsubarrsum(m+1,r));
	
}

void Findmaxarr::Outputstring()
{
	out += to_string(size).c_str();
	out += ' ';
	out += to_string((int)duration).c_str();
	out += '\n';		
}

void Findmaxarr::Fileout(string filename)
{
	ofstream FILEOUT; 
	FILEOUT.open(filename,ios::out);
	
	if(!FILEOUT.is_open())
		cout<<"failed to write";
	else
		FILEOUT << out;
			
	FILEOUT.close();
}

void Findmaxarr::CountTime_Brute_force()
{
	double exd,d;
	exd = duration;
	Begin = clock(); //Start counting time
	int max = Brute_force();
	End = clock(); //Finish counting time
	cout<<"max = "<<max<<" | "; 
	A.clear();
	duration = (double)(End - Begin) ; // Evaluating ticking times
	cout << "duration = " << duration <<" ms.";	
	if(exd)	cout<<" | "<<duration<<" / "<<exd<<" = "<< duration/exd ;
	d = (size/100)*(size/100)*(size/100);
	cout<<" | d/(n/100)^3 = "<< duration/d ;
	cout<<endl;
}

void Findmaxarr::CountTime_Divide_and_Conquer()
{
	double exd,d;
	exd = duration;
	Begin = clock(); //Start counting time
	int max = Find_maxsubarrsum(0,size-1);
	End = clock(); //Finish counting time
	cout<<"max = "<<max<<" | ";
	A.clear();
	duration = (double)(End - Begin) ; // Evaluating ticking times
	cout << "duration = " << duration <<" ms.";
	if(exd)	cout<<" | "<<duration<<" / "<<exd<<" = "<< duration/exd ;
	d = size * log2(size);
	cout<<" | d/(nlg(n)) = "<< duration/d *1000000;
	cout<<endl;
}

int main()
{
	
	Findmaxarr B;
	cout<<"Brute-force Performance:\n";	
	//for(B.size = 100; B.size<=10000 ; B.size *= 10)
	for(B.size = 250; B.size<=10000 ; B.size *= 2)
	{
		//B.size = 10;
		cout<<"Size = "<<B.size<<" | ";
		B.InitialA();
		B.CountTime_Brute_force();
		B.Outputstring(); 
	}
	B.Fileout("HW2_out1.txt");
	Findmaxarr D;
	cout<<"Devide and Conquer Performance:\n";
	//for(B.size = 100; B.size<=100000 ; B.size *= 10)	
	for(D.size = 10000; D.size<=10000000 ; D.size *= 2)
	{
		//D.size = 10;
		cout<<"Size = "<<D.size<<" | ";
		D.InitialA();
		D.CountTime_Divide_and_Conquer();
		D.Outputstring();
	}
	D.Fileout("HW2_out2.txt");
	
	return 0;
}


