#include<iostream>
#include<windows.h>
using namespace std;

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
} 

int main()
{
	int a = 12;
	cout<<"789"<<endl;
	SetColor(252);
	cout<<"12345"<<endl;
	SetColor();
	cout<<"45678";
	return 0;
}
