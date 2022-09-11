#include<iostream>
#include<vector>
#include<climits>

using namespace std;

class Cut_Rod
{
	public:
		vector<int> solution;
		vector<int> r;
		int cut_time = 0;
		int Memoized_Cut_Rod(int p[], int n);
		int Memoized_Cut_Rod_Aux(int p[], int n);
		int Extended_Bottom_up_Cut_Rod(int p[], int n);
		void Print_Cut_Rod_Solution(int p[], int n, char ch);
		void Clear_sol();
};

int Cut_Rod::Memoized_Cut_Rod(int p[], int n)
{
	r.push_back(0);
	solution.push_back(0);
	for(int i=1; i<=n; i++)
	{
		r.push_back(INT_MIN);
		solution.push_back(0);
	}
	
	return Memoized_Cut_Rod_Aux(p, n);
}

int Cut_Rod::Memoized_Cut_Rod_Aux(int p[], int n)
{
	if(r[n]>=0) return r[n];
	else
	{
		int max = INT_MIN, d;
		for(int i=1; i<=n; i++)
		{
			if(i <= 10)
				d = p[i] + Memoized_Cut_Rod_Aux(p, n-i);
				
			else d = r[i] + Memoized_Cut_Rod_Aux(p, n-i);
			
			if(max < d) 
			{
				max = d;
				solution[n] = i;
			}
			
		}		
		r[n] = max;
		return max;
	}
	
}

int Cut_Rod::Extended_Bottom_up_Cut_Rod(int p[], int n)
{
	r.push_back(0);
	solution.push_back(0);
	for(int i=1; i<=n; i++)
	{
		r.push_back(0); //r.push_back(0);
		solution.push_back(0);
	}
	for(int j=1; j<=n; j++)
	{
		int max = INT_MIN;
		for(int i=1; i<=j; i++)
		{
			if(i <= 10)
				if(max < p[i] + r[j-i])
				{
					max = p[i] + r[j-i];
					solution[j] = i;
				}
						
			else if(max < r[i] + r[j-i])
			{
				max = r[i] + r[j-i];
				solution[j] = i;
			}	
		}
			
		r[j] = max;
	}
	return r[n];
}

void Cut_Rod::Print_Cut_Rod_Solution(int p[], int n, char ch)
{
	// 總長度 價格 如何切 切幾段
	if(ch == 'b')
	{
		cout << "\n\n-----------------------------\n";
		cout << "使用 bottom up 的方法 Cut rod\n";
		cout << "總長度: " << n << endl;
		cout << "價格: " << Extended_Bottom_up_Cut_Rod(p, n) << endl ;
		cout << "如何切: " ;
		while(n>0)
		{
			cout << solution[n] << " " ;
			n = n - solution[n];
			cut_time ++;
		}
		cout << endl;
		cout << cut_time << "根" << endl << endl;
		cout << "-----------------------------\n";
	}
	
	else if(ch == 't')
	{
		cout << "\n\n-----------------------------\n";
		cout << "使用 top down 的方法 Cut rod\n";
		cout << "總長度: " << n << endl;
		cout << "價格: "<< Memoized_Cut_Rod(p, n) << endl ;
		cout << "如何切: " ;
		while(n>0)
		{
			cout << solution[n] << " " ;
			n = n - solution[n];
			cut_time ++;
		}
		cout << endl;
		cout << cut_time << "根" << endl << endl;
		cout << "-----------------------------\n";
	}
	Clear_sol();
}

void Cut_Rod::Clear_sol()
{
	r.clear();
	solution.clear();
	cut_time = 0;
}

int main()
{
	int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	Cut_Rod cr;
	cr.Print_Cut_Rod_Solution(p, 14, 't'); // rod length = 14, top down solution
	cr.Print_Cut_Rod_Solution(p, 14, 'b'); // rod length = 14, botton up solution
	
	cr.Print_Cut_Rod_Solution(p, 87, 't'); // CANNOT RUN // rod length = 87, top down solution
	cr.Print_Cut_Rod_Solution(p, 87, 'b'); // rod length = 87, botton up solution
	
	return 0;
} 
