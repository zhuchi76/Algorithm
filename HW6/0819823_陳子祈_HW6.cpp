#include <iostream>
#include <vector>
#include <string>
#include <climits> // 紀錄函數執行時間相關函數
#include <ctime> //紀錄函數執行時間相關函數 
#include <stdlib.h> // 亂數相關函數 
#include <time.h>   // 時間相關函數 
#include <limits.h>

#include <iomanip> // setw

using namespace std;

class LCS
{
	public:
		int m, n;
		clock_t Begin, End; //Record LCS time 
		double duration; // Record LCS time 
		vector<vector<int>> C;
		vector<vector<char>> b;
		vector<int> output_seq;
		void Print(vector<int> v);
		vector<int> Random_vector(int size);
		void Initial_LCS(int x_len, int y_len);
		void LCS_length(vector<int> X, vector<int> Y);
		void Print_LCS(vector<int> X, int i, int j);
		void CountTime_LCS(); // This function calculates LCS_length(X, Y) time
		void Clear();
};

void LCS::Print(vector<int> v)
{
	//cout << "Print vector: ";
	for (vector<int>::iterator it = v.begin()+1; it != v.end(); ++it)
    	cout << ' ' << *it;
    cout<< "\n";
}

vector<int> LCS::Random_vector(int size)
{
	srand( time(NULL) );
	vector<int> A;
	//int up = 9, low = 0;
	int r;
	for(int i=0; i<size; i++)
	{
		r = (int)((rand() / (RAND_MAX+1.0)) * (9 - 0.0) + 0);
		A.push_back(r);
	}	
	return A;
}

void LCS::Initial_LCS(int x_len, int y_len)
{
	m = x_len;
	n = y_len;
	for(int i=0; i<=x_len; i++)
	{
		vector<int> c_temp(y_len+1, 0);
		vector<char> b_temp(y_len+1, '0');
		C.push_back(c_temp);
		b.push_back(b_temp);	
	}	
	output_seq.push_back(0);	
}

void LCS::LCS_length(vector<int> X, vector<int> Y)
{
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			if(X[i] == Y[j])
			{
				C[i][j] = C[i-1][j-1] + 1;
				b[i][j] = 'Q'; // up-left
			}
			else if(C[i-1][j] >= C[i][j-1])
			{
				C[i][j] = C[i-1][j];
				b[i][j] = 'U' ; // up
			}
			else
			{
				C[i][j] = C[i][j-1];
				b[i][j] = 'L' ; // left
			}
}
void LCS::Print_LCS(vector<int> X, int i, int j)
{
	if( i==0 || j==0 )
		return;
	if( b[i][j] == 'Q') // up-left arrow
	{
		Print_LCS(X, i-1, j-1);
		//cout<<"X["<<i<<"] = "<<X[i]<<"\n";
		//cout<<X[i]<<" ";
		output_seq.push_back(X[i]);
	}
	else if( b[i][j] == 'U') // up
		Print_LCS(X, i-1, j);
	else if( b[i][j] == 'L') // left
		Print_LCS(X, i, j-1); 
	else
	{
		cout<<"error!\n";
		cout<<"i = "<<i<<" j = "<<j<<endl;
	}
}

void LCS::CountTime_LCS() // This function calculates LCS_length(X, Y) time
{
	for(int m=10, n=10; m<=10000; n*=10,m*=10)
	//for(int m=10, n=10000; m<=10000; m*=10)
	{
		cout<<"m = n = " << setw(5) << m <<"\t";
		//cout<<"m = " << setw(5) << m <<"\t";
		//cout<<"n = " << setw(5) << n <<"\t";
		
		vector<int> X = Random_vector(m);
		//Print(X);
		vector<int> Y = Random_vector(n);
		//Print(Y);
		Initial_LCS(m, n);
		Begin = clock(); //Start counting time
		LCS_length(X, Y);
		End = clock(); //Finish counting time
		
		duration = (double)(End - Begin) ; // Evaluating ticking times
		cout << "LCS_length Runtime = " << setw(5) << duration <<" ms.";	
		double d = ((double)m) * ((double)n);
		cout<<"\t1000000 * LCS_length Runtime/(mn) = "<< duration*1000000.0/d ;
		cout<<endl;
		
		Clear();
	}
	
	cout<<"\n\n";
	
	for(int m=10, n=10; m<=10000; n*=10,m*=10)
	//for(int m=10, n=10000; m<=10000; m*=10)
	{
		cout<<"m = n = " << setw(5) << m <<"\t";
		//cout<<"m = " << setw(5) << m <<"\t";
		//cout<<"n = " << setw(5) << n <<"\t";
		vector<int> X = Random_vector(m);
		//Print(X);
		vector<int> Y = Random_vector(n);
		//Print(Y);
		Initial_LCS(m, n);
		LCS_length(X, Y);
		Begin = clock(); //Start counting time
		Print_LCS(X, m, n);
		End = clock(); //Finish counting time
		
		duration = (double)(End - Begin) ; // Evaluating ticking times
		cout << "Print_LCS Runtime = " << setw(5) << duration <<" ms.";	
		double d = ((double)m) + ((double)n);
		cout<<"\t1000000 * Print_LCS Runtime/(m+n) = "<< duration*1000000.0/d ;
		cout<<endl;
		
		Clear();
	}
}

void LCS::Clear()
{
	C.clear();
	b.clear();
	output_seq.clear();
}

int main()
{
	LCS lcs;
	vector<int> X {0, 6, 6, 6, 0, 8, 9, 4, 5, 7, 9, 4, 5, 3};
	vector<int> Y {0, 1, 6, 8, 0, 4, 8, 7, 5, 4, 8, 7, 7, 4, 1, 4};
	cout<<"X:";
	lcs.Print(X);
	cout<<"Y:";
	lcs.Print(Y);
	lcs.Initial_LCS(13, 15);
	lcs.LCS_length(X, Y);
	lcs.Print_LCS(X, 13, 15); 
	cout<<"Z:";
	lcs.Print(lcs.output_seq);
	cout<<"Length: "<<lcs.C[13][15]<<endl;
	cout<<"\n\n";
	lcs.Clear();
	
	lcs.CountTime_LCS();
	return 0;
} 
