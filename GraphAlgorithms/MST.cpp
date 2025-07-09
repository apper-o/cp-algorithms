// Task : Yosupo MST
// AC : https://judge.yosupo.jp/submission/266720

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e5+3;
const ll INF = 1e9+3;

struct pii{
	int a, b, id;
	ll c;
};

int n, m;
vector<int> p(MAXN);
vector<pii> edges;
vector<int> sz(MAXN, 1);
ll res=0;
vector<int> ids;

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
	cin>>n>>m;
	for(int i=0;i<n;i++)
		p[i]=i;
	edges.resize(m);
	for(int i=0;i<m;i++)
	{
		cin>>edges[i].a>>edges[i].b>>edges[i].c;
		edges[i].id=i;
	}
	sort(edges.begin(), edges.end(), [] (pii a, pii b) {
		return a.c<b.c;
	});
	
	
	for(int i=0;ids.size()<n-1;i++)
	{
		int a=get(edges[i].a), b=get(edges[i].b);
		if(a==b)
			continue;
		unite(a, b);
		res+=edges[i].c;
		ids.pb(edges[i].id);
	}
	cout<<res<<"\n";
	for(int i : ids)
		cout<<i<<" ";
	return 0;		
}
