// TASK : Task Assignment
// AC : https://cses.fi/problemset/result/11642303/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e2+3;
const ll INF = 1e9+3;

struct edge{
	int a, b, c;
	int flow, cap;
};

int n;
vector<int> adj[MAXN];
vector<edge> edges;
int t;

//spfa
vector<int> dist(MAXN);
vector<int> on(MAXN);
vector<int> p(MAXN);

//choses the shortest route from source to sink
bool spfa()
{
	for(int i=1;i<=t;i++)
		dist[i]=INF;
	queue<int> q;
	q.push(0);
	while(q.size())
	{
		int v=q.front();
		q.pop();
		on[v]=0;
		for(int i : adj[v])
		{
			int u = edges[i].b;
			if(edges[i].flow==edges[i].cap || dist[u]<=dist[v]+edges[i].c)
				continue;
			p[u]=i;
			dist[u]=dist[v]+edges[i].c;
			if(!on[u])
			{
				on[u]=1;
				q.push(u);
			}
		}
	}
	return dist[t]!=INF;
}

void add(int a, int b, int val)
{
	adj[a].pb(edges.size());
	edges.pb({a, b, val, 0, 1});
	adj[b].pb(edges.size());
	edges.pb({b, a, -val, 0, 0});
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1,x;j<=n;j++)
		{
			cin>>x;
			add(i, j+n, x);
		}
	}
	t=2*n+1;
	for(int i=1;i<=n;i++)
	{
		add(0, i, 0);
		add(i+n, t, 0);
	}
	int ans=0;
	while(spfa())
	{
		int v = t;
		//adds flow to edges
		while(v)
		{
			int i = p[v];
			ans+=edges[i].c;
			edges[i].flow++;
			edges[i^1].flow--;
			v=edges[i].a;
		}
	}
	cout<<ans<<"\n";
	for(int v=1;v<=n;v++)
	{
		for(int i : adj[v])
			if(edges[i].flow==1)
			{
				cout<<v<<" "<<edges[i].b-n<<"\n";
				break;
			}
		
	}
	return 0;
}
