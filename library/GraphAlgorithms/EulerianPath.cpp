// Task : CSES Teleporters Path
// AC : https://cses.fi/problemset/result/11840489/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;

int n, m;
vector<int> adj[MAXN];
vector<int> deg(MAXN);
vector<int> path;

void quit()
{
	cout<<"IMPOSSIBLE\n";
	exit(0);
}

void dfs(int v)
{
	for(int i=adj[v].size()-1;i>=0;i--)
	{
		if(i>=adj[v].size())
		{
			i=adj[v].size();
			continue;
		}
		int u = adj[v][i];
		swap(adj[v][i], adj[v].back());
		adj[v].pop_back();
		dfs(u);	
	}
	if(adj[v].empty())
		path.pb(v);
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=0,a,b;i<m;i++)
	{
		cin>>a>>b;
		adj[a].pb(b);
		deg[a]++;
		deg[b]--;
	}
	if(deg[1]!=1 || deg[n]!=-1)
		quit();
	for(int i=2;i<n;i++)
		if(deg[i])
			quit();
	dfs(1);
	if(path.size()!=m+1)
		quit();
	reverse(path.begin(), path.end());
	for(auto v : path)
		cout<<v<<" ";
	
			
	
	return 0;
}
