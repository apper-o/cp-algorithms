// Task : CSES Download Speed 
// AC : https://cses.fi/problemset/result/11617739/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e2+3;
const ll INF = 1e9+3;

// id%2==0 -> normal edge
// id%2==1 -> residual edge
struct edge{
	int to;
	ll flow, cap;
};


int n, m;
vector<int> adj[MAXN]; // stores id of an edge
vector<edge> edges;
int lvl[MAXN];
int bg[MAXN];
ll ans=0;

bool bfs()
{
	memset(lvl,0,sizeof(lvl));
	memset(bg,0,sizeof(bg));
	queue<int> q;
	q.push(1);
	lvl[1]=1;
	while(q.size())
	{
		int v = q.front();
		q.pop();
		for(int i : adj[v])
		{
			int u = edges[i].to;
			if(lvl[u] || edges[i].cap-edges[i].flow<=0)
				continue;
			lvl[u]=lvl[v]+1;
			q.push(u);
		}
	}
	return lvl[n]; // true if sink was reached
}

int dfs(int v, ll flow)
{
	if(v==n)
		return flow;
	for(int j=bg[v];j<adj[v].size();bg[v]=++j) // optimization: skips dead ends
	{
		int i=adj[v][j], u = edges[i].to;
		if(edges[i].cap-edges[i].flow<=0 || lvl[u]!=lvl[v]+1)
			continue;
		int tmp = dfs(u, min(flow, edges[i].cap-edges[i].flow));
		if(tmp)
		{
			edges[i].flow+=tmp;
			edges[i^1].flow-=tmp;
			return tmp;
		}
	}
	return 0;
}

void dinics()
{
	while(bfs())
	{
		int tmp=0;
		while(tmp = dfs(1, INF))
			ans+=tmp;
	}
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=0,a,b,c;i<m;i++)
	{
		cin>>a>>b>>c;
		adj[a].pb(edges.size());
		edges.pb({b, 0, c});
		adj[b].pb(edges.size());
		edges.pb({a, 0, 0});
	}
	dinics();
	cout<<ans<<"\n";
	return 0;
}
