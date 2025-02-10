// Task : CSES Giant Pizza
// AC : https://cses.fi/problemset/result/11899258/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const int M = 1e9+7;

int n, m;
// 2*x for true / 2*x+1 for false
vector<int> adj[MAXN];
// transposed graph
vector<int> adjt[MAXN];
vector<int> vis(MAXN);
vector<int> post;
vector<int> scc(MAXN);
int timer=0;

void add(char x, int a, char y, int b)
{
	// if not satisified for a then b
	adj[2*a+(x=='+')].pb(2*b+(y=='-'));
	adj[2*b+(y=='+')].pb(2*a+(x=='-'));
	adjt[2*b+(y=='-')].pb(2*a+(x=='+'));
	adjt[2*a+(x=='-')].pb(2*b+(y=='+'));
}


void dfs(int v)
{
	vis[v]=1;
	for(int u : adj[v])
		if(!vis[u])
			dfs(u);
	post.pb(v);
}

void dfs2(int v)
{
	scc[v]=timer;
	for(int u : adjt[v])
		if(!scc[u])
			dfs2(u);
}

void get()
{
	for(int i=0;i<2*n;i++)
		if(!vis[i])
			dfs(i);
	for(int i=post.size()-1;i>=0;i--)
		if(!scc[post[i]])
		{
			timer++;
			dfs2(post[i]);
		}
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>m>>n;
	for(int i=0;i<m;i++)
	{
		char x, y; int a, b;
		cin>>x>>a>>y>>b;
		add(x, a-1, y, b-1);
	}
	get();
	vector<char> ans;
	for(int i=0;i<n;i++)
	{
		if(scc[2*i]==scc[2*i+1])
		{
			cout<<"IMPOSSIBLE\n";
			exit(0);
		}
		ans.pb(scc[2*i] < scc[2*i+1] ? '-' : '+');
	}
	for(auto i : ans)
		cout<<i<<" ";
			
	
	return 0;
}
