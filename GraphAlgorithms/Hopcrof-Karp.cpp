// Task : CSES School Dance
// AC : https://cses.fi/problemset/result/11635561/


#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 1e3+3;
const ll INF = 1e9+3;

int n, m, k;
vector<int> adj[MAXN];
vector<int> match(MAXN);
vector<int> lvl(MAXN);
int ans=0;

bool bfs()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		// nodes that are unmatched are the 'startpoints'
		if(!match[i])
		{
			lvl[i]=0;
			q.push(i);
		}
		else
			lvl[i]=INF;
	}	
	// return true if new matching was found
	lvl[0]=INF;
	while(q.size())
	{
		int v=q.front();
		q.pop();
		for(int u : adj[v])
		{
			if(lvl[match[u]]!=INF) 
				continue;
			lvl[match[u]]=lvl[v]+1;
			if(match[u]==0)
				return true;
			q.push(match[u]);
		}
	}
	return false;	
}

bool dfs(int v)
{
	// if new matching exists return true
	if(v==0)
		return true;
	for(int u : adj[v])
	{
		if(lvl[match[u]]==lvl[v]+1 && dfs(match[u]))
		{
			// recursively swap matchings
			match[v]=u;
			match[u]=v;
			return true;
		}		
	}
	// if there is no new matching mark vertex as visited (lvl[v]=INF)
	lvl[v]=INF;
	return false;
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int i=0,a,b;i<k;i++)
	{
		cin>>a>>b;
		adj[a].pb(b+n);
		adj[b+n].pb(a);
	}
	// do until there exists a matching
	while(bfs())
		for(int i=1;i<=n;i++)
			if(!match[i] && dfs(i))
				ans++;
	cout<<ans<<"\n";
	for(int i=1;i<=n;i++)
		if(match[i])
			cout<<i<<" "<<match[i]-n<<"\n";
	return 0;
}
