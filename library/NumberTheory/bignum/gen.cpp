#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
    
/*------------------------------------code------------------------------------*/
const ll MAXN=3*1e4+3;
const ll M=10;
const ll INF=1e4;
const int X = 100;
const int V = 20;
const int Y = 20;

struct pii{
	ll x, y;
};


int seed;
int n, m, q;

string s="";

int main()
{
	cin>>seed;
	mt19937 rng(seed);
	n=rng()%M+3;

	for(int i=0;i<n;i++)
	{
		char a = 'a'+rng()%4;
		s+=a;
	}
	cout<<n<<"\n";
	cout<<s;
	


	return 0;	
}

