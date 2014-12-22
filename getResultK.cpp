#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int main()
{
	fstream in;
	in.open("testK", ios::in);
	
	string tmp;
	in >> tmp;
	char a[1000];
	for (int i = 0; i < 13; ++ i)
	{
		in.getline(a, 1000);in.getline(a, 1000);
		//int start = 4;
		//int end = strlen(a)-5;
		//for (int j = start; j < end; ++ j)	cout << a[j];
		//cout << endl;
		//cout << a << endl;
		for (int k = 0; k < 7; ++ k)
		{
			in >> tmp;
			//cout << tmp << endl;
			for (int j = 0; j < 6; ++ j)
			in.getline(a, 1000);
		
			//cout << a << endl;
			in >> tmp >> tmp >> tmp;
			//if (k == 6)
			//cout << tmp << endl;
			in >> tmp;
		
			in >> tmp >> tmp;
			if (k == 6)
			cout << tmp << endl;
			in >> tmp;
		
			in >> tmp >> tmp;
			//cout << tmp << endl;
			in >> tmp;
			in.getline(a,1000);
			//cout << a << endl;
		}
	}
	
	in.close();
} 
