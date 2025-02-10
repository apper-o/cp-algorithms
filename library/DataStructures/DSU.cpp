// Task : YOSUPO Unionfind
// AC : https://judge.yosupo.jp/submission/266613

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const ll INF = 1e18;

int n, q;
vector<int> p(MAXN);
vector<int> sz(MAXN, 1);

// path compression
int get(int v){
	return (v==p[v] ? v : p[v]=get(p[v]));
}

void unite(int a, int b)
{
	if(sz[a]<sz[b])
		swap(a, b);
	p[b]=a;
	sz[a]+=sz[b];
}


int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=0;i<n;i++)
		p[i]=i;
	for(int i=0,t,a,b;i<q;i++)
	{
		cin>>t>>a>>b;
		if(t==0)
			unite(get(a), get(b));
		else
			cout<<(get(a)==get(b))<<"\n";
	}
	return 0;		
}
