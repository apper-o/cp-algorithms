// Task : Yosupo K-th smallest
// AC : https://judge.yosupo.jp/submission/266648

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 4*1e6+3;
const ll INF = 1e9+3;

int n, q;
vector<int> tree[MAXN];
vector<int> lc(MAXN), rc(MAXN);
vector<int> idl[MAXN], idr[MAXN];
vector<int> cntl[MAXN];
int nodec=1;

void build(int v, int a, int b)
{
	if(a==b)
		return;
	idl[v].resize(tree[v].size());
	idr[v].resize(tree[v].size());
	int mid=(a+b)/2, l=0, r=0;
	for(int i=0;i<tree[v].size();i++)
	{
		idl[v][i]=tree[l].size();
		idr[v][i]=tree[r].size();
		if(tree[v][i]<=mid)
		{
			if(l==0)
				l=++nodec;
			tree[l].pb(tree[v][i]);
			cntl[v].pb(1);
		}
		else
		{
			if(r==0)
				r=++nodec;
			tree[r].pb(tree[v][i]);
			cntl[v].pb(0);
		}
	}
	for(int i=1;i<tree[v].size();i++)
		cntl[v][i]+=cntl[v][i-1];
	if(l)
	{
		build(l, a, mid);
		lc[v]=l;
	}
	if(r)
	{
		build(r, mid+1, b);
		rc[v]=r;
	}
}

int query(int v, int a, int b, int k)
{
	if(!lc[v] && !rc[v])
		return tree[v][0];
	int x = cntl[v][b]-(a==0 ? 0 : cntl[v][a-1]);
	if(x>=k)
		return query(lc[v], idl[v][a], idl[v][b]-(b>0 && cntl[v][b]==cntl[v][b-1]), k);
	return query(rc[v], idr[v][a], idr[v][b]-(b>0 && cntl[v][b]!=cntl[v][b-1]), k-x);
}


int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>q;
	tree[1].resize(n);
	int mx=0, mn=INF;
	for(int i=0;i<n;i++)
	{
		cin>>tree[1][i];
		mx=max(mx, tree[1][i]);
		mn=min(mn, tree[1][i]);
	}
	build(1, mn, mx);
	for(int i=0,a,b,k;i<q;i++)
	{
		cin>>a>>b>>k;
		cout<<query(1, a, b-1, k+1)<<"\n";
	}

	return 0;		
}
