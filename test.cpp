#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node
{
	int value;
	int arrayNum;
	Node(){}
	Node(int value, int arrayNum):value(value),arrayNum(arrayNum){}
	bool operator<(const Node &n2) const
	{
		return value > n2.value;
	}
};

int main()
{
	priority_queue<Node> pq;
	pq.push(Node(10,2));
	pq.push(Node(100,20));
	cout <<pq.top().value << " " <<pq.top().arrayNum << endl;
	
	
	vector<int> v;
	v.resize(10000);
	v.push_back(10);
	cout << v.size() << endl;
}
