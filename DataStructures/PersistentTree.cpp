// Task : CSES Range Queries anc Copies
// AC : https://cses.fi/problemset/result/11852576/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 4*1e6+3;
const int R = (1<<18);

int n, q;
vector<int> arr;
vector<int> lc(MAXN), rc(MAXN);
vector<ll> val(MAXN);
vector<int> root;
int p, k, x;
int cnt=1;

void build(int v, int a, int b)
{
	if(a>=n)
		return;
	if(a==b)
		val[v]=arr[a];
	else
	{
		int mid = (a+b)/2;
		lc[v]=++cnt;
		build(cnt, a, mid);
		rc[v]=++cnt;
		build(cnt, mid+1, b);
		val[v]=val[lc[v]]+val[rc[v]];
	}
}

void update(int v, int a, int b)
{
	if(a==b)
		val[v]=x;
	else
	{
		int mid = (a+b)/2;
		if(p<=mid)
		{
			cnt++;
			lc[cnt]=lc[lc[v]];
			rc[cnt]=rc[lc[v]];
			lc[v]=cnt;
			update(cnt, a, mid);
		}
		else
		{
			cnt++;
			lc[cnt]=lc[rc[v]];
			rc[cnt]=rc[rc[v]];
			rc[v]=cnt;
			update(cnt, mid+1, b);
		}
		val[v]=val[lc[v]]+val[rc[v]];
	}
}

ll query(int v, int a, int b)
{
	if(p>b || a>k)
		return 0;
	if(p<=a && b<=k)
		return val[v];
	int mid = (a+b)/2;	
	return query(lc[v], a, mid)+query(rc[v], mid+1, b);
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>q;
	arr.resize(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	build(1, 0, R-1);
	root.pb(1);
	for(int i=0,t,a,b,r;i<q;i++)
	{
		cin>>t;
		if(t==1)
		{
			cin>>r>>a>>x;
			r--, p=k=a-1;
			update(root[r], 0, R-1);
		}
		else if(t==2)
		{
			cin>>r>>a>>b;
			r--, p=a-1, k=b-1;
			cout<<query(root[r], 0, R-1)<<"\n"; 
		}
		else
		{
			cin>>r;
			r--, cnt++;
			val[cnt]=val[root[r]];
			lc[cnt]=lc[root[r]];
			rc[cnt]=rc[root[r]];
			root.pb(cnt);
		}
	}
	return 0;
}
