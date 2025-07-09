// Task : CSES Mail Delivery
// AC : https://cses.fi/problemset/result/11835683/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;

int n, m;
vector<pair<int, int>> adj[MAXN];
vector<int> path;
vector<int> vis(MAXN);

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
		auto [u, w] = adj[v][i];
		
		// does not use visited edges
		swap(adj[v][i], adj[v].back());
		adj[v].pop_back();
		
		if(!vis[w])	
		{
			vis[w]=1;
			dfs(u);
		}
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
		adj[a].pb({b, i});
		adj[b].pb({a, i});
	}
	// checks whether every node degree is even (imperative for Eulerian Cycle)
	for(int i=1;i<=n;i++)	
		if(adj[i].size()%2)
			quit();
	dfs(1);
	// checks whether the graph is connected
	if((int)path.size()<m+1)
		quit();
	// prints a Eulerian Cycle
	reverse(path.begin(), path.end());
	for(auto v : path)
		cout<<v<<" ";
	return 0;
}
