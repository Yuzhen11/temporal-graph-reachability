#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int main()
{
	fstream in;
	in.open("finalTopChain", ios::in);
	
	string tmp;
	in >> tmp;
	cout << tmp << endl;
	char a[1000];
	for (int i = 0; i < 12; ++ i)
	{
		in.getline(a, 1000);in.getline(a, 1000);
		//int start = 4;
		//int end = strlen(a)-5;
		//for (int j = start; j < end; ++ j)	cout << a[j];
		//cout << endl;
		//cout << a << endl;
		
		in.getline(a, 1000);
		//cout << a << endl;
		in >> tmp >> tmp >> tmp >> tmp;
		//cout << tmp << endl;
		
		for (int j = 0; j < 5; ++ j)
		in.getline(a, 1000);
		
		in >> tmp >> tmp;
		//cout << tmp << endl;
		
		//cout << a << endl;
		in >> tmp >> tmp >> tmp;
		cout << tmp << endl;
		in >> tmp;
		
		in >> tmp >> tmp;
		//cout << tmp << endl;
		in >> tmp;
		
		in >> tmp >> tmp;
		//cout << tmp << endl;
		in >> tmp;
		in.getline(a,1000);
		//cout << a << endl;
		
	}
	
	in.close();
} 
