// Task : CSES Static Range Minimum Queries
// AC : https://cses.fi/problemset/result/11897981/
#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const int R = (1<<18);
const int X = 20;

int n, q;
// sparse table
int st[X][MAXN];
// precomputed logarithm
vector<int> lg(MAXN);

int get(int a, int b)
{
	int x = lg[b-a+1];
	return min(st[x][a], st[x][b-(1<<x)+1]);
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=2;i<=n;i++)
		lg[i]=lg[i/2]+1;
	for(int i=0;i<n;i++)
		cin>>st[0][i];
	for(int x=1;x<=lg[n];x++)
		for(int i=0;i+(1<<x)<=n;i++)
			st[x][i]=min(st[x-1][i], st[x-1][i+(1<<(x-1))]);
	for(int i=0,a,b;i<q;i++)
	{
		cin>>a>>b;
		cout<<get(a-1, b-1)<<"\n";
	}
	
	
	return 0;
}
