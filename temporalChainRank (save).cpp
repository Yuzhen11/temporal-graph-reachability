#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
#include <cstring>
#include <assert.h>
#include <set>
#include <stack>
#include "Timer.h"
using namespace std;
vector<vector<int> > v;
vector<vector<int> > vr;
int n, m;
vector<int> ind;
vector<int> outd;
vector<int> Lup;
vector<int> Ldown;

class ReachIndex{
public:
	uint16_t layerup;
	uint16_t layerdown;
	uint8_t OutLimit;
	uint8_t InLimit;
	uint8_t HLimit;
	pair<int, int> * Label;

	ReachIndex(){
		Label=NULL;
	}

	~ReachIndex(){
		if(Label!=NULL)
			delete[] Label;
	}
};


struct DEG
{
	int d;
	int index;
};
vector<DEG> deg;
bool cmp(DEG d1, DEG d2)
{
	return d1.d > d2.d;
}

vector<vector<pair<int, int> > > Lin;
vector<vector<pair<int, int> > > Lout;

struct Node
{
	int value;
	int pos;
	int arrayNum;
	Node(){}
	Node(int value, int pos, int arrayNum):value(value),pos(pos), arrayNum(arrayNum){}
	Node(pair<int,int> p, int newPos)
	{
		value = p.first;
		pos = p.second;
		arrayNum = newPos;
	}
	bool operator<(const Node &n2) const
	{
		if (value == n2.value) return pos > n2.pos;
		return value > n2.value;
	}
};


struct Node1
{
	int value;
	int pos;
	int arrayNum;
	Node1(){}
	Node1(int value, int pos, int arrayNum):value(value),pos(pos), arrayNum(arrayNum){}
	Node1(pair<int,int> p, int newPos)
	{
		value = p.first;
		pos = p.second;
		arrayNum = newPos;
	}
	bool operator<(const Node1 &n2) const
	{
		if (value == n2.value) return pos < n2.pos;
		return value > n2.value;
	}
};
int k = 5;
int h;

Timer timer;

vector<int> rank_order;
vector<int> reverserank_order;

void readGraph(string s)
{
	timer.start();
	fstream in;
	in.open(s.c_str(), ios::in);
	in >> n >> m;
	v.resize(n);
	vr.resize(n);
	ind.resize(n);
	outd.resize(n);
	
	int u;int size;int to;
	while(in >> u)
	{
		in >> size;
		for (int i = 0; i < size; ++ i)
		{
			in >> to;
			v[u].push_back(to);
			vr[to].push_back(u);
			outd[u]++;
			ind[to]++;
		} 
	}
	in.close();
	timer.stop();
	cout << "read graph time: " << timer.GetRuntime() << endl;
	
	cout << "load done." << endl;
}

int chainNum;
vector<int> vis;
vector<int> toChain;
vector<int> toPos;
vector<vector<int> > toV;
vector< vector<int> > startT, arrivalT;
vector< int > curSize, sumSize;
vector< int > timeId, originalId;

int getVertexID(int u, int offset, int startOrArrival)
{
    //  0 arrival 1 start
    
    int base = u == 0 ? 0 : sumSize[u - 1];
    const vector<int> & arrival = arrivalT[u];
    const vector<int> & start = startT[u];
 
    if(startOrArrival == 0)
    {
        return base + offset;
    }
    else if(startOrArrival == 1)
    {
        return base +  arrival.size() + offset;
    }

}

vector <int> inOut;
vector <int> pNext;
void readChainInfo(string s)
{
	inOut.resize(n);
	pNext.resize(n);
	
	fstream in;
	in.open(s.c_str(), ios::in);
	in >> chainNum;
	startT = vector< vector<int> >(chainNum, vector<int>() );
    arrivalT = vector< vector<int> >(chainNum, vector<int>());
    curSize = vector<int>(chainNum, 0);
    sumSize = vector<int>(chainNum, 0);
    
    originalId.resize(n);
    
    toV.resize(n);
	toChain.resize(n);
	toPos.resize(n);
    
	int u;
	int size;
	int tmp;
	for (int i = 0; i < chainNum; ++ i)
	{
		in >> u >> size;
		for (int j = 0; j < size; ++ j)
		{
			in >> tmp;
			arrivalT[i].push_back(tmp);
		}
	}
	for (int i = 0; i < chainNum; ++ i)
	{
		in >> u >> size;
		for (int j = 0; j < size; ++ j)
		{
			in >> tmp;
			startT[i].push_back(tmp);
		}
	}
	in.close();
	cout << "chain info load done" << endl;
	for(int i = 0 ; i < chainNum; i ++){
        int cur = startT[i].size() + arrivalT[i].size();
        curSize[i] = cur;
        sumSize[i] = cur + (i > 0 ? sumSize[i-1] : 0);
    }
    
    for(int i=0; i < chainNum; i++){
		for(int j=0; j<arrivalT[i].size(); j++){
			timeId.push_back(arrivalT[i][j]);
		}
		
		for(int j=0; j<startT[i].size(); j++){
			timeId.push_back(startT[i][j]);
		}
	}
	
	//Mapping the new vertex id to original vertex id
    /*
    for(int i=0; i < chainNum; i++){
    	for(int j = 0 ; j < arrivalT[i].size(); j ++)
        {
            int u = getVertexID(i, j, 0);
            originalId[u]=i;
            toPos[u] = j;
            toV[i].push_back(u);
        }
        
        for(int j = 0 ; j < startT[i].size() ; j ++)
        {
            int u = getVertexID(i, j , 1);
            originalId[u]=i;
            toPos[u] = j+arrivalT[i].size();
            toV[i].push_back(u);
        }
    }
    */
    
    for (int i = 0; i < chainNum; ++ i)
    {
    	int p1 = 0;
    	int p2 = 0;
    	int j = 0;
    	while(j < arrivalT[i].size()+startT[i].size() )
    	{
    		if (p1 == arrivalT[i].size())
    		{
    			int u = getVertexID(i, p2, 1);
    			originalId[u] = i;
    			toPos[u] = toV[i].size();
    			toV[i].push_back(u);
    			p2++;	
    		}
    		else if (p2 == startT[i].size())
    		{
    			int u = getVertexID(i, p1, 0);
    			originalId[u] = i;
    			toPos[u] = toV[i].size();
    			toV[i].push_back(u);
    			p1++;
    		}
    		else if (arrivalT[i][p1] <= startT[i][p2])
    		{
    			int u = getVertexID(i, p1, 0);
    			originalId[u] = i;
    			toPos[u] = toV[i].size();
    			toV[i].push_back(u);
    			p1++;
    		}
    		else 
    		{
    			int u = getVertexID(i, p2, 1);
    			originalId[u] = i;
    			toPos[u] = toV[i].size();
    			toV[i].push_back(u);
    			p2++;
    		}
    		
    		j++;
    	}
    	
    }
    
    //set inOut and pNext;
    for (int i = 0; i < chainNum; ++ i)
    {      
        for(int j = int(arrivalT[i].size()) - 1; j >= 0 ; j --)
        {
            int u21 = getVertexID(i, j, 0);
            inOut[u21] = 1;
            vector<int>::iterator it = lower_bound( startT[i].begin(),startT[i].end(), arrivalT[i][j] );
            if( it != startT[i].end() )
            {
                int offset = it - startT[i].begin();
                int u1 = getVertexID(i , offset , 1);
                pNext[u21] = u1;
            }
            else
            {
            	pNext[u21] = -1;
            }
        }
        
        for (int j = 0; j < startT[i].size(); ++ j)
        {
        	int u22 = getVertexID(i,j,1);
        	inOut[u22] = 0;
        }
    }
    
    /*
    for (int i = 0; i < n; ++ i)
    {
    	cout << i <<  " " << inOut[i] << " " << pNext[i] << endl;
    } 
    */
    
    //test
	/*
    chainNum = n;
    for (int i = 0; i < chainNum; ++ i) 
    {
    	originalId[i] = i;
    	toPos[i] = 0;
    	toV[i].push_back(i);
    }
    */
    
    deg.resize(chainNum);
    for (int i = 0; i < chainNum; ++ i)
    {
    	deg[i].d = startT[i].size() + arrivalT[i].size();
    	deg[i].index = i;
    }
}


//feline

vector<int> flabel1;
vector<int> flabel2;

void feline()
{
	cout << "feline begin" << endl;
	vector<int> inds1;
	vector<int> inds2;
	stack<int> stack1;
    stack<int> stack2;
    inds1.resize(n);
    inds2.resize(n);
    flabel1.resize(n);
    flabel2.resize(n);
    //copy ind
    for (int i = 0; i < n; ++ i)
    {
		inds1[i]=inds2[i]=ind[i];	
    }
    
    for (int i = n-1; i >= 0; --i)
    {
    	if (ind[i] == 0) stack1.push(i);
    }
    int count1 = 0;
    while(!stack1.empty())
    {
    	//cout << "!!" << endl;
    	int tmp = stack1.top();
    	stack1.pop();
    	flabel1[tmp] = count1++;
    	for (int i = v[tmp].size()-1; i >= 0; --i)
    	{
    		inds1[v[tmp][i]]--;
    		if (inds1[v[tmp][i]] == 0)
    		stack1.push(v[tmp][i]);
    	}
    }
    assert(count1 == n);
    
    count1 = 0;
    for (int i = 0; i < n; ++ i)
    {
    	if (ind[i] == 0) stack2.push(i);
    }
    while(!stack2.empty())
    {
    	int tmp = stack2.top(); stack2.pop();
    	flabel2[tmp] = count1++;
    	for(int i = 0; i < v[tmp].size(); ++ i)
    	{
    		inds2[v[tmp][i]]--;
    		if (inds2[v[tmp][i]] == 0) stack2.push(v[tmp][i]);
    	}
    }
    assert(count1 == n);
    cout << "feline finished" << endl;
}

void handle()
{
	timer.start();
	//topological sort
	
	//find rank_order 
	//random
	/*
	rank_order.resize(n);
	for (int i = 0; i < n; ++ i)
	{
		rank_order[i] = i;
	}
	for (int i = n-1; i > 0; -- i)
	{
		int j = rand()%(i+1);
		swap(rank_order[i], rank_order[j]);
	}
	*/
	
	Ldown.resize(n);
	Lup.resize(n);
	Lin.resize(n);
	Lout.resize(n);
	queue<int> q;
	queue<int> q1;
	int count1 = 0;
	int maxDown = 0;
	int maxUp = 0;
	for (int i = 0; i < n; ++ i)
	{
		if (ind[i] == 0) 
		{
			Ldown[i] = 0;	
			q.push(i);
		}
		if (outd[i] == 0)
		{
			Lup[i] = 0;
			q1.push(i);
		}
		//Lin[i].push_back(rank_order[i]);
		//Lout[i].push_back(rank_order[i]);
	}
	
	
	//find chain
	
	for (int i = 0; i < n; ++ i) toChain[i]=originalId[i];
	cout <<"chain Num : "<< chainNum << endl;
	
	int countt = 0;
	for (int i = 0; i < chainNum; ++ i)
	{
		countt += toV[i].size();
	}
	assert(countt == n);
	
	//-------------------------------------------------------------
	//assign rank_order
	rank_order.resize(chainNum);
	for (int i = 0; i < chainNum; ++ i)
	{
		rank_order[i] = i;
	}
	for (int i = chainNum-1; i > 0; -- i)
	{
		int j = rand()%(i+1);
		swap(rank_order[i], rank_order[j]);
	}
	//rank by degree
	sort(deg.begin(), deg.end(), cmp);
	for (int i = 0; i < chainNum; ++ i)
	{
		rank_order[deg[i].index] = i;
	}
	//------------------
	
	set<int> s;
	while(!q.empty())
	{
		int tmp = q.front();
		q.pop();
		count1++;
		for (int i = 0; i < v[tmp].size(); ++ i)
		{
			ind[v[tmp][i]]--;
			if (ind[v[tmp][i]] == 0) 
			{
				Ldown[v[tmp][i]] = Ldown[tmp]+1;
				q.push(v[tmp][i]);
				maxDown = Ldown[v[tmp][i]];
			}
		}
	
		//IP construct
		
		/*
		s.clear();	
		for (int i = 0; i < vr[tmp].size(); ++ i)
		{
			int nin = vr[tmp][i];
			for (int j = 0; j < Lin[nin].size(); ++ j) s.insert(Lin[nin][j]);
		}
		s.insert(rank_order[tmp]);
		int countk = 0;
		//cout << s.size() << endl;
		for (set<int>::iterator it = s.begin(); it != s.end(); it ++)
		{
			Lin[tmp].push_back(*it);
			countk++;
			if (countk == k) break;
		}
		*/
		
		// find top k  using multi merge
		priority_queue<Node1> pq;
		//queue<Node1>pq;
		pq.push(Node1(rank_order[toChain[tmp]], toPos[tmp], -1));
		int pArray[vr[tmp].size()];
		memset(pArray,0,sizeof(pArray));
		for (int i = 0; i < vr[tmp].size(); ++ i)
		{
			int nin = vr[tmp][i];
			pq.push(Node1(Lin[nin][0].first, Lin[nin][0].second, i));
		}
		//cout <<"!"<< endl;
		//cout <<pq.size() << endl;
		for (int i = 0; i < k; ++ i)
		{
			if (pq.empty()) break;
			while(!pq.empty())
			{
				//cout << pq.size() << endl;
				Node1 topNode = pq.top();pq.pop();
				//cout << topNode.value << " " << topNode.arrayNum << endl;
				if (topNode.arrayNum == -1)
				{	
					//cout << "HI" << endl;
					Lin[tmp].push_back(make_pair(topNode.value, topNode.pos));
					break;
				}
				pArray[topNode.arrayNum] ++;
				if (pArray[topNode.arrayNum] < Lin[vr[tmp][topNode.arrayNum]].size()) 
				{pq.push(Node1(Lin[vr[tmp][topNode.arrayNum]][pArray[topNode.arrayNum]], topNode.arrayNum) ); }
				
				if (Lin[tmp].size() == 0) 
				{Lin[tmp].push_back(make_pair(topNode.value, topNode.pos));
				break;}
				else if (Lin[tmp].back().first != topNode.value) 
				{
					Lin[tmp].push_back(make_pair(topNode.value, topNode.pos));
					break;
				}
			}
		}
		
	}
	while(!q1.empty())
	{
		int tmp = q1.front();
		q1.pop();
		for (int i = 0; i < vr[tmp].size(); ++ i)
		{
			outd[vr[tmp][i]]--;
			if (outd[vr[tmp][i]] == 0) 
			{
				Lup[vr[tmp][i]] = Lup[tmp]+1;
				q1.push(vr[tmp][i]);
				maxUp = Lup[vr[tmp][i]];
			}
		}
		
		//IP construct
		/*
		vector<int> test;
		s.clear();	
		for (int i = 0; i < v[tmp].size(); ++ i)
		{
			int nout = v[tmp][i];
			for (int j = 0; j < Lout[nout].size(); ++ j) s.insert(Lout[nout][j]);
		}
		s.insert(rank_order[tmp]);
		int countk = 0;
//		cout << s.size() << endl;
		for (set<int>::iterator it = s.begin(); it != s.end(); it ++)
		{
			test.push_back(*it);
			countk++;
			if (countk == k) break;
		}
		*/
		
		// find top k  using multi merge
		priority_queue<Node> pq;
		//queue<Node>pq;
		pq.push(Node(rank_order[toChain[tmp]], toPos[tmp], -1));
		int pArray[v[tmp].size()];
		memset(pArray,0,sizeof(pArray));
		for (int i = 0; i < v[tmp].size(); ++ i)
		{
			int nin = v[tmp][i];
			pq.push(Node(Lout[nin][0], i));
		}
		//cout <<"!"<< endl;
		//cout <<pq.size() << endl;
		for (int i = 0; i < k; ++ i)
		{
			if (pq.empty()) break;
			while(!pq.empty())
			{
				//cout << pq.size() << endl;
				Node topNode = pq.top();pq.pop();
				//cout << topNode.value << " " << topNode.arrayNum << endl;
				if (topNode.arrayNum == -1)
				{	
					//cout << "HI" << endl;
					Lout[tmp].push_back(make_pair(topNode.value, topNode.pos));
					break;
				}
				pArray[topNode.arrayNum] ++;
				if (pArray[topNode.arrayNum] < Lout[v[tmp][topNode.arrayNum]].size()) 
				{pq.push(Node(Lout[v[tmp][topNode.arrayNum]][pArray[topNode.arrayNum]], topNode.arrayNum) ); }
				
				if (Lout[tmp].size() == 0)
				{ Lout[tmp].push_back(make_pair(topNode.value, topNode.pos));
					break;
				}
				else if (Lout[tmp].back().first != topNode.value) 
				{
					Lout[tmp].push_back(make_pair(topNode.value, topNode.pos));
					break;
				}
			}
		}
		/*
		//compare test and Lout[tmp]
		int a;
		if (test.size() != Lout[tmp].size())
		{
			cout << tmp << endl;
			cout << test.size() << " " << Lout[tmp].size() << endl;
			cout <<"!!" << endl;
			cin >>a;
		}
		for (int i = 0; i < test.size(); ++ i)
		{
			if (test[i] != Lout[tmp][i])
			{
				cout << "!" << endl;
				cin >> a;
			}
		}
		*/
		
		
	}
	cout << "label done. " << endl;
	assert(count1 == n);
	
	cout << "maxUp : " << maxUp << endl;
	cout << "maxDown : " << maxDown << endl;



	vector<int>().swap(ind);
	vector<int>().swap(outd);

	//find Sin Sout
	

	

	timer.stop();
	cout << "topological sort and assign rank_order " << timer.GetRuntime() << endl;
	cout << "sort done" << endl;
}
vector<ReachIndex> reachindex;
void copyIndex()
{
	reachindex.resize(n);
	for (int i = 0; i < n; ++ i)
	{
		reachindex[i].OutLimit= Lout[i].size();
		reachindex[i].InLimit= Lin[i].size()+reachindex[i].OutLimit;
		//reachindex[i].HLimit=hv.size()+reachindex[i].InLimit;
		reachindex[i].Label = new pair<int, int>[reachindex[i].InLimit];
		
		for (int j = 0; j < Lout[i].size(); ++ j) reachindex[i].Label[j] = Lout[i][j];
		for (int j = 0; j < Lin[i].size(); ++ j) reachindex[i].Label[reachindex[i].OutLimit+j] = Lin[i][j];
	} 
	
}
//--------------------------label------------------------


bool intersect(const int u1, const int u2)
{
/*
	cout << "debug --------------" << endl;
	cout << u1 << " " << u2 << endl;
	for (int i = 0; i < Lout[u1].size();++ i) cout << Lout[u1][i].first << " ";
	cout << endl;
	for (int i = 0; i < Lin[u2].size();++ i) cout << Lin[u2][i].first << " ";
	cout << endl;
	*/
	
	int p1 = 0;
	int p2 = reachindex[u2].OutLimit;
	while(p1 < reachindex[u1].OutLimit && p2 < reachindex[u2].InLimit)
	{
		if (reachindex[u1].Label[p1].first == reachindex[u2].Label[p2].first && reachindex[u1].Label[p1].second <= reachindex[u2].Label[p2].second) return 1;
		else if (reachindex[u1].Label[p1].first == reachindex[u2].Label[p2].first) {p1++;p2++;}
		else if (reachindex[u1].Label[p1].first < reachindex[u2].Label[p2].first) p1 ++;
		else p2++;
	}
	return 0;
}

//----------------------query----------------------------
int mark = 0;
int *flag;

bool IPtest(const int u, const int v)
{
	/*
	int p1 = 0; int p2 = 0;
	
	if (Lout[from][Lout[from].size()-1].first > Lout[to][0].first) {
		while(p1 < Lout[from].size() && p2 < Lout[to].size())
		{
			if (Lout[from][p1].first == Lout[to][p2].first) 
			{
				if (Lout[from][p1].second > Lout[to][p2].second) return 1;
				p1++;p2++;
			}
			else if (Lout[from][p1].first < Lout[to][p2].first) {p1++;}
			else return 1;
		}
	}
	
	p1 = 0; p2 = 0;
	if (Lin[from][0].first < Lin[to][Lin[to].size()-1].first)
	{
		while(p1 < Lin[from].size() && p2 < Lin[to].size())
		{
			if (Lin[from][p1].first == Lin[to][p2].first) 
			{
				if(Lin[from][p1].second > Lin[to][p2].second) return 1;
				p1++;p2++;
			}
			else if (Lin[from][p1].first > Lin[to][p2].first) p2++;
			else return 1;
		}
	}
	return 0;
	*/
	
	
	//new version
	
	int it1=0, it2=0;
	
	if(reachindex[u].Label[ reachindex[u].OutLimit-1 ].first > reachindex[v].Label[0].first ){
		while(it1!=reachindex[u].OutLimit && it2!=reachindex[v].OutLimit){
			if(reachindex[u].Label[it1].first == reachindex[v].Label[it2].first){
				if (reachindex[u].Label[it1].second > reachindex[v].Label[it2].second) return true;
				it1++;
				it2++;
			}else if(reachindex[u].Label[it1].first < reachindex[v].Label[it2].first){
				it1++;
			}else
				return true;
		}
	}
	
	
	if(reachindex[v].Label[ reachindex[v].InLimit-1 ].first <= reachindex[u].Label[ reachindex[u].OutLimit ].first)
		return false;

	it1=reachindex[v].OutLimit;
	it2=reachindex[u].OutLimit;

	while(it1!= reachindex[v].InLimit && it2!=reachindex[u].InLimit){
		if(reachindex[v].Label[it1].first == reachindex[u].Label[it2].first){
			if (reachindex[v].Label[it1].second < reachindex[u].Label[it2].second) return true;
			it1++;
			it2++;
		}else if(reachindex[v].Label[it1].first < reachindex[u].Label[it2].first){
			it1++;
		}else
			return true;
	}

	return false;
	
}

int insidetest(int from, int to)
{
	//linear search
	/*
	for (int i = 0; i < Lout[from].size(); ++ i)
	{
		if (Lout[from][i] == rank_order[to]) return 1;
	}
	return 0;
	*/
	/*
	int l = 0; int r = Lout[from].size()-1;
	int m;
	while(l <= r)
	{
		m = (l+r)/2;
		if (Lout[from][m].first == rank_order[toChain[to]]) 
		{
			if(Lout[from][m].second <= toPos[to]){
				return 1;
			}
			return 2;
		}
		else if (Lout[from][m].first < rank_order[toChain[to]]) l = m+1;
		else r = m-1;
	}
	return 0;
	*/
	//new version
	int l = 0; int r = reachindex[from].OutLimit-1;
	int m;
	while(l <= r)
	{
		m = (l+r)/2;
		if (reachindex[from].Label[m].first == rank_order[toChain[to]]) 
		{
			if(reachindex[from].Label[m].second <= toPos[to]){
				return 1;
			}
			return 2;
		}
		else if (reachindex[from].Label[m].first < rank_order[toChain[to]]) l = m+1;
		else r = m-1;
	}
	return 0;
}

int countQuery = 0;
bool query(int from, int to)
{
	countQuery ++;
	flag[from] = mark;
	//if (from == to) return 1;
	
	//if (Ldown[from] >= Ldown[to] || Lup[from] <= Lup[to]) return 0;
	
	//if (toChain[from] == toChain[to] ) return 1;
	
	/*
	int inside = insidetest(from, to);
	if (inside == 1) return 1;
	else if (inside == 2) return 0;
	*/
	
	//some error occured query(Tout(a), Tin(a))
	/*
	if (toChain[from] == toChain[to]) 
	{
		if (toPos[from] <= toChain[to]) return 1;
		else return 0;
	}
	*/
	if (flabel1[from]>flabel1[to] || flabel2[from]>flabel2[to]) return 0;
	if (IPtest(from, to)) return 0;
	
	//flabel test 
	
	//intersect or no
	//if (intersect(from, to)) return 1;
	
	//fast jumping 
	//caution from and to may be in the same chain
	
	
	if (inOut[from] == 1 && toChain[from]!=toChain[to])
	{
		if (pNext[from] == -1) return 0;
		else
		{
			return query(pNext[from], to);
		}
	}
	
	
	
	
	
	for (int i = 0; i < v[from].size(); ++ i)
	{
		int w = v[from][i];
		if (w == to) return 1;
		//if (insidetest(w,to)) return 1;
		if (Ldown[w]<Ldown[to] && Lup[w]>Lup[to] && flag[w]!= mark)
		{

			if (query(w,to)) return 1;
		}
	}
	return 0;
}
bool naiveQuery(int from, int to)
{
	flag[from] = mark;
	if (from == to) return 1;
	for (int i = 0; i < v[from].size(); ++ i)
	{
		int w = v[from][i];
		if (flag[w]!= mark)
		{
			if (naiveQuery(w,to)) return 1;
		}
		
	}
	return 0;
}
void query(string s)
{
	flag = new int[n];
	memset(flag,0,sizeof(int)*n);
	
	//read query
	vector<int> from;
	vector<int> to;
	fstream in;
	in.open(s.c_str(), ios::in);
	int t1, t2;
	while(in >> t1 >> t2)
	{
		from.push_back(t1);
		to.push_back(t2);
	}
	in.close();
	
	cout << "query number: " << from.size() << endl;
	
	timer.start();
	
	//begin query
	int queryNum = from.size();
	int reachNum = 0;
	for (int i = 0; i < queryNum; ++ i)
	{
		bool arrive;
		if (from[i] == to[i]) arrive = 1;
		else if (Ldown[from[i]]>=Ldown[to[i]] || Lup[from[i]]<=Lup[to[i]]) arrive = 0;
		else if (flabel1[from[i]]>flabel1[to[i]] || flabel2[from[i]]>flabel2[to[i]]) arrive = 0;
		//else if (toChain[from[i]] == toChain[to[i]] ) arrive = 1;
		else if (intersect(from[i], to[i])) arrive = 1;
		else
		{
			mark = i+1;
			arrive = query(from[i],to[i]);
		}
		reachNum += arrive;
	}
	
	timer.stop();
	cout << "query time : " << timer.GetRuntime()*1000 << endl;
	cout << "reach number: " << reachNum<< endl;
	delete [] flag;
}
//----------------------query----------------------------


int main(int argc, char* argv[])
{
	//srand(time(0));
	string s;
	k = atoi(argv[1]);
	h = atoi(argv[2]);
	//s = "arxiv_scc.txt";
	s = argv[3];
	string s2;
	//s2 = "arxiv_query1000.txt";
	s2 = argv[4];
	string s3 = argv[5];
	
	readGraph(s);
	readChainInfo(s3);
	
	feline();//feline label
	handle();
	
	copyIndex();
	query(s2);
	
	cout << countQuery << endl;

}
