// Task : Yosupo Vertex Add Path Sum
// AC : https://judge.yosupo.jp/submission/266743

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e5+3;
const ll INF = 1e9+3;
const int R = (1<<19);

int n, q;
vector<int> adj[MAXN];
vector<int> arr;
vector<int> sz;
vector<int> hv;
vector<int> top;
vector<int> pre;
vector<int> anc;
vector<ll> st(2*R);
int timer=0;

int dfs(int v, int p)
{
	sz[v]=1;
	top[v]=v;
	anc[v]=p;
	for(int u : adj[v])
	{
		if(u==p)
			continue;
		sz[v]+=dfs(u, v);
		if(sz[u]>sz[hv[v]])
			hv[v]=u;
	}
	return sz[v];
}

void hld(int v)
{
	pre[v]=++timer;
	if(hv[v])
	{
		top[hv[v]]=top[v];
		dfs(hv[v], v);
	}
	for(int u : adj[v])
		if(!pre[u])
			hld(u);
}

ll sum(int a, int b)
{
	a+=R-1;
	b+=R-1;
	if(a==b)
		return st[a];
	ll res = st[a]+st[b];
	while(a/2!=b/2)
	{
		if(a%2==0)
			res+=st[a+1];
		if(b%2==1)
			res+=st[b-1];
		a/=2;
		b/=2;
	}
	return res;
}

ll query(int a, int b)
{
	ll res=0;
	while(top[a]!=top[b])
	{
		if(pre[a]>pre[b])
			swap(a, b);
		res+=sum(pre[top[b]], pre[b]);
		b=anc[top[b]];		
	}	
	if(pre[a]>pre[b])
		swap(a, b);
	return res+sum(pre[a], pre[b]);
}

void update(int v, int val)
{
	v+=R-1;
	st[v]+=val;
	while(v/2)
	{
		v/=2;
		st[v]+=val;
	}
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>q;
	arr.resize(n+1);
	sz.resize(n+1);
	top.resize(n+1);
	hv.resize(n+1);
	anc.resize(n+1);
	pre.resize(n+1);
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	for(int i=0,a,b;i<n-1;i++)
	{
		cin>>a>>b;
		a++, b++;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(1, 0);
	hld(1);
	for(int i=1;i<=n;i++)
	{
		st[pre[i]+R-1]=arr[i];
	}
	for(int i=R-1;i;i--)
		st[i]=st[2*i]+st[2*i+1];
	for(int i=0,t,a,b;i<q;i++)
	{
		cin>>t>>a>>b;
		if(t==0)
			update(pre[a+1], b);
		else
			cout<<query(a+1, b+1)<<"\n";
	}
	
	return 0;		
}
