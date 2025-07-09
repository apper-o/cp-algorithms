// Task : CSES Range Update ans Sums
// AC : https://cses.fi/problemset/result/11851861/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const int R = (1<<18);

struct pii{
	ll sum, lz, lz2;
};

int n, q;
vector<pii> st(2*R);
vector<int> arr;
ll p, k, val=0, val2=0;

void push(int v, int l, int r, ll sz)
{
	if(st[v].lz2)
	{
		st[v].lz2+=st[v].lz;
		st[l].sum=sz*st[v].lz2;
		st[l].lz2=st[v].lz2;
		st[r].sum=sz*st[v].lz2;
		st[r].lz2=st[v].lz2;
		st[l].lz=st[r].lz=0;
	}
	else if(st[v].lz)
	{
		st[l].sum+=sz*st[v].lz;
		st[l].lz+=st[v].lz;
			
		st[r].sum+=sz*st[v].lz;
		st[r].lz+=st[v].lz;
	}
	st[v].lz=st[v].lz2=0;
}

void update(int v, int a, int b)
{
	if(p>b || a>k)
		return;
	int sz = b-a+1;
	if(p<=a && b<=k)
	{
		if(val2)
		{
			st[v].sum=sz*val2;
			st[v].lz2=val2;
			st[v].lz=0;
		}
		else if(val)
		{
			st[v].sum+=sz*val;
			st[v].lz+=val;
		}
	}
	else
	{
		int l=2*v, r=2*v+1, mid=(a+b)/2;
		push(v, l, r, sz/2);
		update(l, a, mid);
		update(r, mid+1, b);
		st[v].sum=st[l].sum+st[r].sum;
	}
}

ll query(int v, int a, int b)
{
	if(p>b || a>k)
		return 0;
	if(p<=a && b<=k)
		return st[v].sum;
	int l=2*v, r=2*v+1, mid=(a+b)/2, sz=b-a+1;
	push(v, l, r, sz/2);
	return query(l, a, mid)+query(r, mid+1, b);
}


int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>q;
	arr.resize(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	for(int i=0;i<n;i++)
		st[i+R].sum=arr[i];
	for(int i=R-1;i;i--)
		st[i].sum=st[2*i].sum+st[2*i+1].sum;
	// 1 adds x to each value in [a, b]
	// 2 sets each value in [a, b] to x
	// 3 query for the sum of values in [a, b]
	for(int i=0,t;i<q;i++)
	{
		cin>>t;
		if(t==1)
		{
			val2=0;
			cin>>p>>k>>val;
			p--, k--;
			update(1, 0, R-1);
		}
		else if(t==2)
		{
			val=0;
			cin>>p>>k>>val2;
			p--, k--;
			update(1, 0, R-1);					
		}
		else
		{
			cin>>p>>k;
			p--, k--;
			cout<<query(1, 0, R-1)<<"\n";
		}
	}
	return 0;
}
